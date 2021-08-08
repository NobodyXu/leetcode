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
    let step = Solution::open_lock(
        deadends!["0201","0101","0102","1212","2002"],
        "0202".to_string()
    );

    println!("step = {}", step);
}
