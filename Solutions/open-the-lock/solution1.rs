include!("common.rs");

mod basics {
    use std::convert::{From, TryInto};
    use std::cmp::{Ord, PartialOrd, Eq, PartialEq, Ordering, min};
    use std::collections::hash_map::HashMap;

    #[derive(Copy, Clone, Debug)]
    struct Wheel(u8);
    const WHEELS: [Wheel; 4] = [
        Wheel(0),
        Wheel(1),
        Wheel(2),
        Wheel(3),
    ];

    #[derive(Copy, Clone, Debug, Default, Eq, PartialEq, Hash)]
    pub struct State (u16);
    const BITS: u8 = 4; // number of bits for one wheel
    const MASK: u16 = (1 << BITS) - 1;
    impl State {
        #[inline]
        fn rotate_up(mut self, wheel: Wheel) -> Self {
            let bits = wheel.0 * BITS;
            let val = (self.0 >> bits) & MASK;

            if val == 9 {
                let mask = !(MASK << bits);
                self.0 &= mask;
            } else {
                self.0 += 1 << bits;
            }
            
            self
        }

        #[inline]
        fn rotate_down(mut self, wheel: Wheel) -> Self {
            let bits = wheel.0 * BITS;
            let val = (self.0 >> bits) & MASK;

            if val == 0 {
                self.0 |= 9 << bits;
            } else {
                self.0 -= 1 << bits;
            }
            
            self
        }
        
        fn to_array(self) -> [u8; 4] {
            let mut arr = [0_u8; 4];
            
            for (bits, entry) in (0..16).step_by(BITS as usize).zip(&mut arr) {
                *entry = ((self.0 >> bits) & MASK) as u8
            }
            
            arr
        }
    }
    impl From<String> for State {
        fn from(s: String) -> Self {
            let mut state = 0;
            let bytes = s.into_bytes();
            // Make sure the array is of length 4 AOT so that the compiler can perform
            // loop unrolling and vectorization.
            let bytes: &[u8; 4] = bytes.as_slice().try_into().unwrap();
            
            for (bits, byte) in (0..16).step_by(BITS as usize).zip(bytes) {
                let val = (byte - b'0') as u16;
                state |= val << bits;
            }
            
            Self(state)
        }
    }
    fn distance(x: State, y: State) -> u8 {
        let x = x.to_array();
        let y = y.to_array();
        
        let substracted = x.iter()
            .zip(&y)
            .map(|(x, y)| (*x as i8) - (*y as i8));
        
        let diff1 = substracted.clone()
            .map(|result| {
                if result < 0 {
                    (0 - result) as u8
                } else {
                    result as u8
                }
            });

        let diff2 = substracted.clone()
            .map(|result| (10 + result) as u8);

        let diff3 = substracted
            .map(|result| (10 - result) as u8);
        
        let min_tup = |(v1, v2)| min(v1, v2);
        
        diff1.zip(diff2)
            .map(min_tup)
            .zip(diff3)
            .map(min_tup)
            .sum()
    }

    #[derive(Debug, Default)]
    pub struct Expander {
        /// the deadends and the expanded
        excluded: HashMap<State, ()>,
    }
    impl Expander {
        pub fn new(v: Vec<String>) -> Self {
            let mut expander: Self = Default::default();
            let deadends = &mut expander.excluded;
            
            deadends.reserve(v.len() + 20);
            
            for s in v {
                deadends.insert(s.into(), ());
            }
            
            expander
        }
    }
    impl Expander {
        /// Return (# num of states returned, states, as a fixed-size array)
        fn do_expand(&self, state: State) -> (usize, [State; 8]) {
            let mut cnt: usize = 0;
            let mut states = [<State as Default>::default(); 8];

            // rotate upwards and downwards separately in different loops to help vectorization and
            // loop unroll
            let it1 = WHEELS.iter().map(|wheel| state.rotate_up(*wheel));
            let it2 = WHEELS.iter().map(|wheel| state.rotate_down(*wheel));
            
            it1.chain(it2).for_each(|new_state| {
                if let None = self.excluded.get(&new_state) {
                    states[cnt] = new_state;
                    cnt += 1;
                }
            });

            (cnt, states)
        }

        /// Return (# num of states returned, states, as a fixed-size array)
        pub fn expand(&mut self, state: State) -> (usize, [State; 8]) {                        
            if let Some(_) = self.excluded.get(&state) {
                return Default::default();
            }

            let ret = self.do_expand(state);

            // `insert` after `get` so that the lookup can be faster due to smaller table.
            //
            // Also, insertion involves some extremely complicated logic, which might get in the way of the
            // OOE.
            self.excluded.insert(state, ());
            
            ret
        }

        /// This function should be called on the states returned by expand
        ///
        /// Returns None if state != target and state has no child (hence it will never reach the target).
        /// Returns Some(0) if state == target, otherwise Some(positive number).
        pub fn heuristic(&self, state: State, target: State) -> Option<u8> {
            if state == target {
                return Some(0);
            }
            
            // Every child state generated by expand is guaranteed to be not in self.excluded
            let (sz, arr) = self.do_expand(state);
            (&arr[0..sz]).iter()
                .map(|child_state| distance(*child_state, target))
                .min()
                // Going from state into one of the `child_state`s requires one step
                .map(|val| val + 1)
        }
    }
    
    /// First field represents step_cnt, second represents heuristic
    #[derive(Copy, Clone, Debug)]
    pub struct HeapEntry(pub u32, pub u8, pub State);
    impl HeapEntry {
        fn get_cost(self) -> u64 {
            self.0 as u64 + self.1 as u64
        }
    }
    impl PartialEq for HeapEntry {
        fn eq(&self, other: &Self) -> bool {
            self.get_cost() == other.get_cost()
        }
    }
    impl Eq for HeapEntry {}
    impl PartialOrd for HeapEntry {
        fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
            Some(self.cmp(other))
        }
    }
    impl Ord for HeapEntry {
        fn cmp(&self, other: &Self) -> Ordering {
            self.get_cost().cmp(&other.get_cost())
        }
    }
} // end of mod basics

impl Solution {
    /// Implemented using A* algorithm.
    pub fn open_lock(deadends: Vec<String>, target: String) -> i32 {
        use basics::*;
        use std::collections::binary_heap::BinaryHeap;
        use std::cmp::Reverse; // Since BinaryHeap by default returns the biggest, Reverse is required

        let target: State = target.into();
        
        let mut state: State = Default::default();
        let mut expander = Expander::new(deadends);
        let mut heap = BinaryHeap::with_capacity(100);
        
        let mut step_cnt: u32 = 0;
        loop {
            if state == target {
                break step_cnt as i32;
            }
            
            step_cnt += 1;
            
            let (sz, arr) = expander.expand(state);
            (&arr[0..sz]).iter()
                .for_each(|child_state| {
                    if let Some(h) = expander.heuristic(*child_state, target) {
                        heap.push(Reverse(HeapEntry(step_cnt, h, *child_state)));
                    }
                });
            
            match heap.pop() {
                Some(entry) => {
                    let entry = entry.0;
                    step_cnt = entry.0;
                    state = entry.2;
                },
                None => break -1,
            };
        }
    }
} // end of impl Solution
