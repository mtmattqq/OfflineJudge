use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let input: Vec<u32> = input.trim().split(" ")
        .map(|x| x.parse().expect("Not an integer!"))
        .collect();
    println!("{}", input[0] + input[1]);
}