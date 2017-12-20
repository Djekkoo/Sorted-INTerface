// extern crate libc;

// use libc::strcmp;
use std::cmp::Ordering;
use std::fmt;

// #[derive(Eq)]
pub struct Data {
    age: i32,
    name: String,
}

pub struct Node {
    data: Data,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

pub struct SortedContainer {
    pub root: Option<Box<Node>>,
}


// pub fn set_root(mut sc:SortedContainer) {
//     let data:Data = new_data(12, "jacco".to_lowercase());
//     let node:Node = new_node(data);
//     let b:Box<Node> = Box::new(node);
//     sc.root = Some(b);
// }

impl Data {

    pub fn new(age: i32, name: String) -> Self {
        return Data { age:age, name:name };
    }
    
    pub fn compare(&self, ref d2: &Data) -> Ordering {
        if self.age != d2.age { 
            return self.age.cmp(&d2.age);
        }
        return self.name.cmp(&d2.name);
    }
    
}

impl fmt::Display for Data {
    fn fmt(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
        return write!(formatter, "{} {}", self.age, self.name);
    }
}


impl Node {
    pub fn new(data: Data) -> Self {
        return Node { data:data, left:None, right: None };
    }
    pub fn insert(&mut self, data: Data) {
        match self.data.compare(&data) {
            Ordering::Equal => {
                return;
            },
            Ordering::Greater => {
                match self.left {
                    None => {
                        self.left = Some(Box::new(Node::new(data)));
                    },
                    Some(ref mut node) => {
                        node.insert(data);
                    }
                }
            },
            Ordering::Less => {
                match self.right {
                    None => {
                        self.right = Some(Box::new(Node::new(data)));
                    },
                    Some(ref mut node) => {
                        node.insert(data);
                    }
                }
            }
        }
    }
    pub fn contains(&self, ref data: &Data) -> bool {
        match self.data.compare(&data) {
            Ordering::Equal => {
                return true;
            },
            Ordering::Greater => {
                match self.left {
                    None => {
                        return false;
                    },
                    Some(ref node) => {
                        return node.contains(&data);
                    }
                }
            },
            Ordering::Less => {
                match self.right {
                    None => {
                        return false;
                    },
                    Some(ref node) => {
                        return node.contains(&data);
                    }
                }
            }
        }
    }

	pub fn print_children(&self, indent: String) {
		match self.left {
			Some(ref node) => {
				println!("{}{}", indent, node.data);
				node.print_children(format!("{} ", indent));
			}
			None => {}
		}
		match self.right {
			Some(ref node) => {
				println!("{}{}", indent, node.data);
				node.print_children(format!("{} ", indent));
			}
			None => {}
		}
    }
}

impl SortedContainer {


    pub fn new() -> Self {
        return SortedContainer{ root: None };
    }

    pub fn insert(&mut self, data: Data) {
        match self.root {
            None => {
                self.root = Some(Box::new(Node::new(data)));
            },
            Some(ref mut node) => {
                node.insert(data);
            }
        }
    }

    pub fn contains(&self, ref data: &Data) -> bool {
        match self.root {
            None => {
                return false;
            },
            Some(ref root) => {
                return root.contains(&data);
            }
        }
    }

    pub fn print(&self) {
        match self.root {
            None => {
                println!("Empty SortedContainer");
            }
            Some(ref root) => {
                println!("{}", root.data);
                root.print_children(" ".to_string());
            }
        }
    }

}
