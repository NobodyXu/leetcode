struct Solution;

fn main() {
    let run = |num1: &'static str, num2: &'static str| {
        print!("num1 = {}, num2 = {}, ", num1, num2);
        let result = Solution::add_strings(num1.to_string(), num2.to_string());
        println!("result = {}", result);
    };

    run("11", "123");
}
