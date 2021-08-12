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
    pub fn min_flips_mono_incr(s: String) -> i32 {
        let bytes = s.as_bytes();

        let leading_zero_cnt = bytes
            .iter()
            .take_while(|byte| **byte == b'0')
            .count();

        let trailing_zero_cnt = bytes
            .iter()
            .rev()
            .take_while(|byte| **byte == b'1')
            .count();

        let bytes = &bytes[leading_zero_cnt..(bytes.len() - trailing_zero_cnt)];
        if bytes.is_empty() {
            return 0;
        }

        let len = bytes.len();

        // bytes now look like this:
        //
        //     1...0
        if len == 2 {
            return 1;
        }

        let zeros = bytes[1..(len - 1)]
            .iter()
            .filter(|byte| **byte  == b'0')
            .count() + 1;
        let ones = len - zeros;

        if zeros == 1 || ones == 1 {
            return 1;
        }

        let mut left_ones: i32 = 0;
        let mut right_zeros: i32 = zeros as i32;

        // Here, the situation where all bits are flipped to 1/0 is ignored.
        bytes[0..(len - 1)]
            .iter()
            .map(|byte| {
                if *byte == b'1' {
                    left_ones += 1;
                } else {
                    right_zeros -= 1;
                }

                left_ones + right_zeros
            })
            // Here the all-flip cases are considered.
            .chain([ones as i32, zeros as i32].iter().map(|val| *val))
            .min()
            .unwrap()
    }
}
