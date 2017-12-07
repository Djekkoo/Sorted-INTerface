extern crate rand;

use std::io;
use rand::Rng;
use std::cmp::Ordering;

fn main() {
    println!("Guess the number!");
    
    let guess_me = rand::thread_rng().gen_range(1, 101);
    // println!("Secret number: {}", guess_me);

    loop {
        println!("Please input your guess.");

        let mut guess = String::new();
        io::stdin().read_line(&mut guess)
            .expect("Failed to read line");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Invalid input");
                continue;
            },
        };

        println!("You guessed: {}", guess);

        match guess.cmp(&guess_me) {
            Ordering::Equal => { 
                println!("You win");
                break;
            },
            Ordering::Less  => println!("Too small"),
            Ordering::Greater => println!("Too big"),
        }
    }
}