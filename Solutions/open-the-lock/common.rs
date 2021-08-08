struct Solution;

fn main() {
    macro_rules! deadends {
        ( $( $x:expr ),* ) => {
            {
                let mut temp_vec = Vec::new();
                $(
                    temp_vec.push($x.to_string());
                )*
                temp_vec
            }
        };
    }

    let run = |deadends, answer: &'static str| {
        print!("deadends = {:?}, answer = {}, ", deadends, answer);
        let step = Solution::open_lock(deadends, answer.to_string());
        println!("step = {}", step);
    };

    run(
        deadends!["0201","0101","0102","1212","2002"],
        "0202"
    );
    run(
        deadends!["2022","0230","1330","2033","2113","2113","2102","3013","0120","3021"],
        "3102"
    );
}
