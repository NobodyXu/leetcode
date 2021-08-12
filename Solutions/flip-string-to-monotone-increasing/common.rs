struct Solution;

fn main() {
    let run = |s: &'static str| {
        print!("s = {}, ", s);
        let result = Solution::min_flips_mono_incr(s.to_string());
        println!("result = {}", result);
    };

    run("11");
    run("00110");
    run("010110");
    run("00011000");
    run("00011000");
    run("1111001110");
}
