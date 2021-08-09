//! rustc --edition 2018 \
//!     -C lto=yes \
//!     -C codegen-units=1 \
//!     -C opt-level=3 \
//!     -C overflow-checks=no \
//!     -C panic=abort \
//!     -C target-cpu=native \
//!     solution1.rs
include!("common.rs");

mod basics {
    use std::convert::{From, TryInto};
    use std::cmp::{Ord, PartialOrd, Eq, PartialEq, Ordering, min};
    use std::fmt::{Debug, Formatter, Error};

    #[derive(Copy, Clone, Debug)]
    struct Wheel(u8);
    const WHEELS: [Wheel; 4] = [
        Wheel(0),
        Wheel(1),
        Wheel(2),
        Wheel(3),
    ];

    #[derive(Copy, Clone, Default, Eq, PartialEq, Hash)]
    pub struct State (u16);
    const BITS: u8 = 4; // number of bits for one wheel
    const MASK: u16 = (1 << BITS) - 1;
    impl State {
        #[inline(always)]
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

        #[inline(always)]
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

        #[inline(always)]
        fn to_array(self) -> [u8; 4] {
            let mut arr = [0_u8; 4];

            for (bits, entry) in (0..16).step_by(BITS as usize).zip(&mut arr) {
                *entry = ((self.0 >> bits) & MASK) as u8
            }

            arr
        }

        #[inline(always)]
        fn to_decimal(self) -> u16 {
            self.to_array()
                .iter()
                .zip(&[1_u16, 10_u16, 100_u16, 1000_u16])
                .map(|(entry, ratio)| (*entry as u16) * (*ratio as u16))
                .sum()
        }
    }
    impl Debug for State {
        fn fmt(&self, f: &mut Formatter<'_>) -> Result<(), Error> {
            f.write_fmt(format_args!("{:?}", self.to_array()))
        }
    }
    impl From<String> for State {
        #[inline(always)]
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
    #[inline(always)]
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

    const MAX_SIZE: usize = 10 * 10 * 10 * 10;
    const BITSET_SIZE: usize = MAX_SIZE / 8 + (MAX_SIZE % 8) as usize;

    /// * `SIZE` - number of bytes required for your array
    struct Bitset {
        array: [u8; BITSET_SIZE],
    }
    impl Default for Bitset {
        fn default() -> Self {
            Self {
                array: [0; BITSET_SIZE],
            }
        }
    }
    impl Bitset {
        #[inline(always)]
        fn set(&mut self, index: usize) {
            let byte = &mut self.array[index / 8];
            *byte |= 1 << (index % 8);
        }

        #[inline(always)]
        fn get(&self, index: usize) -> bool {
            let bit = self.array[index / 8] >> (index % 8);
            (bit & 1) != 0
        }
    }

    #[derive(Default)]
    pub struct Expander {
        /// the deadends and the expanded
        excluded: Bitset,
    }
    impl Expander {
        pub fn new(v: Vec<String>) -> Self {
            let mut expander: Self = Default::default();
            let deadends = &mut expander.excluded;

            for s in v {
                let state: State = s.into();
                deadends.set(state.to_decimal() as usize);
            }

            expander
        }

        /// Return (# num of states returned, states, as a fixed-size array)
        #[inline(always)]
        fn do_expand(&self, state: State) -> (usize, [State; 8]) {
            let mut cnt: usize = 0;
            let mut states = [<State as Default>::default(); 8];

            // rotate upwards and downwards separately in different loops to help
            // vectorization and loop unroll
            let it1 = WHEELS.iter().map(|wheel| state.rotate_up(*wheel));
            let it2 = WHEELS.iter().map(|wheel| state.rotate_down(*wheel));

            it1.chain(it2).for_each(|new_state| {
                if !self.excluded.get(new_state.to_decimal() as usize) {
                    states[cnt] = new_state;
                    cnt += 1;
                }
            });

            (cnt, states)
        }

        /// Return (# num of states returned, states, as a fixed-size array)
        #[inline(always)]
        pub fn expand(&mut self, state: State) -> (usize, [State; 8]) {
            let index = state.to_decimal() as usize;
            if self.excluded.get(index) {
                return Default::default();
            }

            let ret = self.do_expand(state);
            self.excluded.set(index);
            ret
        }

        /// This function should be called on the states returned by expand
        #[inline(always)]
        pub fn heuristic(&self, state: State, target: State) -> u8 {
            distance(state, target)
        }
    }
    
    /// First field represents step_cnt, second represents heuristic
    /// Since there are at most 10 * 10 * 10 * 10 possible states, the maximum
    /// step_cnt must also be 10000.
    /// u16 is more than enough for 10000.
    #[derive(Copy, Clone, Debug)]
    pub struct HeapEntry(pub u16, pub u8, pub State);
    impl HeapEntry {
        #[inline(always)]
        fn get_cost(self) -> u16 {
            self.0 + self.1 as u16
        }
    }
    impl PartialEq for HeapEntry {
        #[inline(always)]
        fn eq(&self, other: &Self) -> bool {
            self.get_cost() == other.get_cost()
        }
    }
    impl Eq for HeapEntry {}
    impl PartialOrd for HeapEntry {
        #[inline(always)]
        fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
            Some(self.cmp(other))
        }
    }
    impl Ord for HeapEntry {
        #[inline(always)]
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
        // Since BinaryHeap by default returns the biggest, Reverse is required
        use std::cmp::Reverse;

        let target: State = target.into();

        let mut state: State = Default::default();
        let mut expander = Expander::new(deadends);
        let mut heap = BinaryHeap::with_capacity(100);

        let mut step_cnt: u16 = 0;
        loop {
            if state == target {
                break step_cnt as i32;
            }
            
            step_cnt += 1;
            
            let (sz, arr) = expander.expand(state);
            let it = (&arr[0..sz]).iter()
                .map(|child_state| {
                    let child_state = *child_state;
                    let h = expander.heuristic(child_state, target);
                    Reverse(HeapEntry(step_cnt, h, child_state))
                });
            heap.extend(it);

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
