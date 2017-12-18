mod sortedcontainer;

use std::io::{self, Write};
use sortedcontainer::{SortedContainer, Data};

#[derive(Debug)]
enum Command {
    Insert{age: i32, name: String},
    Erase{age: i32, name: String},
    Contains{age: i32, name: String},
    Print,
    Exit,
    Error(String)
}

fn parse_command(input: String) -> Command {
    let command_items: Vec<&str> = input.split_whitespace().collect();
    match (command_items[0], command_items.len()) {
        ("p", 1) => Command::Print,
        ("x", 1) => Command::Exit,
        ("i", 3) => {
            if let Ok(age) = command_items[1].parse::<i32>() {
                Command::Insert{age: age, name: command_items[2].to_string()}
            } else {
                Command::Error("unable to parse int (age).".to_string())
            }
        },
        ("e", 3) => {
            if let Ok(age) = command_items[1].parse::<i32>() {
                Command::Erase{age: age, name: command_items[2].to_string()}
            } else {
                Command::Error("unable to parse int (age).".to_string())
            }
        },
        ("c", 3) => {
            if let Ok(age) = command_items[1].parse::<i32>() {
                Command::Contains{age: age, name: command_items[2].to_string()}
            } else {
                Command::Error("unable to parse int (age).".to_string())
            }
        },

        (_, _) => Command::Error("invalid command.".to_string())
    }
}

fn main() {

    let mut sc : SortedContainer = SortedContainer::new();
    // sc.insert(Data::new(1, "jacco".to_lowercase()));
    // sc.insert(Data::new(3, "jacco".to_lowercase()));
    // println!("{}", sc.contains(&Data::new(1, "jacco".to_lowercase())));
    // println!("{}", sc.contains(&Data::new(2, "jacco".to_lowercase())));
    // println!("{}", sc.contains(&Data::new(3, "jacco".to_lowercase())));

    // println!("{}", sc.contains(&Data::new(1, "jacco2".to_lowercase())));
    // sortedcontainer::set_root(sc);

    loop {
        let mut input = String::new();

        // sortedcontainer::print_node(sc.root);

        print!("> ");
        io::stdout().flush().unwrap();
        match io::stdin().read_line(&mut input) {
            Ok(_) => {
                match parse_command(input) {
                    Command::Insert{age, name} => {
                        sc.insert(Data::new(age, name));
                    },
                    Command::Erase{age, name} => {
                        unimplemented!();
                    },
                    Command::Contains{age, name} => {
                        if sc.contains(&Data::new(age, name)) {
                            println!("Found!");
                        } else {
                            println!("You should look somewhere else!");
                        }
                    }
                    Command::Print => {
                        unimplemented!();
                    },
                    Command::Exit => {
                        println!("Exiting...");
                        break;
                    },
                    Command::Error(error) => {
                        println!("Error: {}", error);
                    }
                }
            }
            Err(error) => println!("Error: {}", error),
        }
    }
}
