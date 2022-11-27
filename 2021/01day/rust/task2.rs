use std::fs::File;
use std::io;
use std::io::{BufRead, BufReader};
use std::vec::Vec;

fn read_file(filename: &str, v: &mut Vec<u32>) -> std::io::Result<()> {
    let f = File::open(filename)?;
    let reader = BufReader::new(&f);
    for line in reader.lines() {
        let val: u32 = line?.trim().parse().unwrap();
        v.push(val);
    }
    Ok(())
}

fn read_to_vec(filename: &str) -> Vec<u32> {
    let mut v: Vec<u32> = Vec::with_capacity(200);
    match read_file(&filename, &mut v) {
        Err(err) => println!("Failed to read file: {} with error {}", filename, err),
        Ok(()) => println!("Success"),
    }
    v
}

fn main() {
    let fname = "input.in";
    let vec = read_to_vec(fname);
    for first in &vec {
        for second in &vec {
            for third in &vec  {
                if (first + second + third == 2020) {
                    println!("First: {}, second {}: mul {}", first, second, first * second * third);
                    return;
                }
            }
        }
    }
}
