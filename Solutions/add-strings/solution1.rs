//! rustc --edition 2018 \
//!     -C lto=yes \
//!     -C codegen-units=1 \
//!     -C opt-level=3 \
//!     -C overflow-checks=no \
//!     -C panic=abort \
//!     -C target-cpu=native \
//!     solution1.rs
include!("common.rs");

impl Solution {
    pub fn add_strings(mut num1: String, num2: String) -> String {
        if num1.len() < num2.len() {
            return Self::add_strings(num2, num1);
        }

        let inc = {
            let num1_bytes = unsafe { num1.as_bytes_mut() };
            let num2_bytes = num2.as_bytes();

            num1_bytes
                .iter_mut()
                .rev()
                .zip(num2_bytes.iter().rev())
                .for_each(|(x, y)| {
                   *x += *y - b'0';
                });

            let mut it = num1_bytes
                .iter_mut()
                .rev()
                .peekable();

            'outer: loop {
                let mut val = match it.next() {
                    Some(val) => val,
                    None => break false,
                };

                loop {
                    if *val <= b'9' {
                        break;
                    }

                    *val -= 10;
                    match it.next() {
                        Some(next) => {
                            val = next;
                            *val += 1;
                        },
                        None => break 'outer true,
                    }
                }
            }
        };

        if inc {
            num1.insert(0, '1');
        }

        num1
    }
}
