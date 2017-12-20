extern crate regex;

use std::error::Error;
use std::fs::File;
use std::io::prelude::*;
// use std::path::Path;
use std::path::PathBuf;
use std::env;
use std::collections::BTreeMap;
use regex::Regex;

fn help() {
    println!(
        "Usage:
textstat <file.txt>
    Analyse file.txt"
    );
}

fn file_to_string(path: &PathBuf) -> String {
    let display = path.display();

    // Open the path in read-only mode, returns `io::Result<File>`
    let mut file = match File::open(path) {
        // The `description` method of `io::Error` returns a string that
        // describes the error
        Err(why) => panic!("couldn't open {}: {}", display, why.description()),
        Ok(file) => file,
    };

    // Read the file contents into a string, returns `io::Result<usize>`
    let mut s = String::new();

    match file.read_to_string(&mut s) {
        Err(why) => panic!("couldn't read {}: {}", display, why.description()),
        Ok(_) => s = s,
    }

    return s;
    // `file` goes out of scope, and the "hello.txt" file gets closed
}

fn analyze(text: String) {
    let mut text_map = BTreeMap::new();
    let mut size_map = BTreeMap::new();

    // Replace punctuation
    let re = Regex::new(r"[^\w\s'’]").unwrap();
    let nopunc_text = re.replace_all(&text, "");

    // Split whitespace (and newlines)
    let split_string = nopunc_text.split_whitespace();

    // Keep track of total number of words and total length of these words
    let mut total_count: usize = 0;
    let mut word_count: usize = 0;

    // Iterate the split string to create a map for:
    // - number of words per length 
    // - occurences of a single word
    for word in split_string {
        *text_map.entry(word.to_lowercase()).or_insert(0) += 1;
        let word_length: usize = word.len();
        total_count += word_length;
        word_count += 1;
        *size_map.entry(word_length).or_insert(0) += 1;
    }
    println!("Total words: {}", word_count);

    // Check if the total_count can safely divided
    match total_count.checked_div(word_count) {
        Some(_x) => {
            println!("Average length: {}", (total_count as f32)/(word_count as f32));

            println!("\nWordlength with occurence: ");
            for (length, count) in size_map.iter() {
                println!("{}: {}", length, count);
            }

            println!("\nTop 10 most used words: ");
            let mut count_vec: Vec<(&String, &usize)> = text_map.iter().collect();
            count_vec.sort_by(|a, b| b.1.cmp(a.1));
            for &(word, count) in count_vec.iter().take(10) {
                println!("{}: {}", word, count);
            }
        }
        None => { panic!("No words found! So no average, occurences and top 10 list."); }
    }
    
}

fn main() {
    let args: Vec<String> = env::args().collect();

    match args.len() {
        // no arguments passed
        1 => {
            println!("My name is 'textstat'. Provide a textfile as argument!");
        }
        // one argument passed
        2 => {
            // Create a path to the current directory and push the path to the file
            let mut absolute_path = match std::env::current_dir() {
                Err(why) => panic!("Couldn't open current directory: {}", why.description()),
                Ok(absolute_path) => absolute_path,
            };
            let relative_path = PathBuf::from(&args[1]);
            absolute_path.push(relative_path);
            let text: String = file_to_string(&absolute_path);
            analyze(text);
        }
        // all the other cases
        _ => {
            // show a help message
            help();
        }
    }
}