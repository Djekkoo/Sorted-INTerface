use std::error::Error;
use std::fs::File;
use std::io::prelude::*;
use std::path::Path;
use std::env;


fn help() {
    println!("usage:
textstat <file.txt>
    Analyse file.txt");
}

fn analyze(path: &Path) -> bool {
    let display = path.display();

    // Open the path in read-only mode, returns `io::Result<File>`
    let mut file = match File::open(path) {
        // The `description` method of `io::Error` returns a string that
        // describes the error
        Err(why) => panic!("couldn't open {}: {}", display,
                                                   why.description()),
        Ok(file) => file,
    };

    // Read the file contents into a string, returns `io::Result<usize>`
    let mut s = String::new();
    match file.read_to_string(&mut s) {
        Err(why) => panic!("couldn't read {}: {}", display,
                                                   why.description()),
        Ok(_) => print!("{} contains:\n{}", display, s),
    }

    return false;
    // `file` goes out of scope, and the "hello.txt" file gets closed
}


fn main() {
    let args: Vec<String> = env::args().collect();

    match args.len() {
        // no arguments passed
        1 => {
            println!("My name is 'textstat'. Try passing some arguments!");
        },
        // one argument passed
        2 => {
            // Create a path to the desired file   
            // println!("My path is {}", args[1]);
            let path = Path::new(&args[1]);
            analyze(path);
            // let pathString:String = args[1].parse();
            // let path = Path::new(&pathString);
            // analyze(path);
        },
        // all the other cases
        _ => {
            // show a help message
            help();
        }
    }  
}

//BTreeMap