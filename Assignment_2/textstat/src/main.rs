use std::error::Error;
use std::fs::File;
use std::io::prelude::*;
// use std::path::Path;
use std::path::PathBuf;
use std::env;
use std::collections::BTreeMap;
use std::collections::BTreeSet;

fn help() {
    println!(
        "usage:
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
    let split_string = text.split(" ");
    let mut total_count: usize = 0;
    for word in split_string {
        *text_map.entry(word.to_lowercase()).or_insert(0) += 1;
        let word_length: usize = word.len();
        total_count += word_length;
        let mut current_word = size_map.entry(word_length).or_insert(BTreeSet::new());
        current_word.insert(word.to_lowercase());
        // println!("Word: {}", current_word.value());
    }
    let map_length: usize = text_map.len();
    println!("Total words: {}", map_length);
    println!("Average length: {}", total_count / map_length);
    for (length, words) in &size_map {
        let mut words_string = String::from("");
        for word in words {
            if words_string.len() > 0 {
                words_string.push_str(", ");
            }
            words_string.push_str(word);
        }
        println!("{}: {}", length, words_string);
    }
    for (word, count) in &text_map {
        println!("{}: {}", word, count);
    }
}


fn main() {
    let args: Vec<String> = env::args().collect();

    match args.len() {
        // no arguments passed
        1 => {
            println!("My name is 'textstat'. Try passing some arguments!");
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

//BTreeMap
