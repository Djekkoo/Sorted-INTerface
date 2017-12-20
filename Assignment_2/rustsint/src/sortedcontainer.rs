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
        return Data {
            age: age,
            name: name,
        };
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
        return Node {
            data: data,
            left: None,
            right: None,
        };
    }
    pub fn insert(&mut self, data: Data) {
        match self.data.compare(&data) {
            Ordering::Equal => {
                return;
            }
            Ordering::Greater => match self.left {
                None => {
                    self.left = Some(Box::new(Node::new(data)));
                }
                Some(ref mut node) => {
                    node.insert(data);
                }
            },
            Ordering::Less => match self.right {
                None => {
                    self.right = Some(Box::new(Node::new(data)));
                }
                Some(ref mut node) => {
                    node.insert(data);
                }
            },
        }
    }
    pub fn contains(&self, ref data: &Data) -> bool {
        match self.data.compare(&data) {
            Ordering::Equal => {
                return true;
            }
            Ordering::Greater => match self.left {
                None => {
                    return false;
                }
                Some(ref node) => {
                    return node.contains(&data);
                }
            },
            Ordering::Less => match self.right {
                None => {
                    return false;
                }
                Some(ref node) => {
                    return node.contains(&data);
                }
            },
        }
    }

    pub fn erase(&mut self, ref data: &Data) {
        match self.data.compare(&data) {
            Ordering::Equal => {
                println!("Can't be happening.");
            }
            Ordering::Greater => match self.left.take() {
                None => {
                    return;
                }
                Some(mut node) => {
                    match node.data.compare(&data) {
                        // Node found, erase this one
                        Ordering::Equal => match (node.left.take(), node.right.take()) {
                            (None, None) => {}
                            (Some(l), None) => self.left = Some(l),
                            (None, Some(r)) => self.left = Some(r),
                            (Some(l), Some(mut r)) => match r.left.take() {
                                None => {
                                    r.left = Some(l);
                                    self.left = Some(r);
                                }
                                Some(mut lmc) => while true {
                                    match lmc.left.take() {
                                        None => break,
                                        Some(mut lmcleft) => match lmcleft.left.take() {
                                            None => {
                                                match lmcleft.right.take() {
                                                    None => {}
                                                    Some(lmcleftright) => {
                                                        lmc.left = Some(lmcleftright);
                                                    }
                                                }
                                                lmcleft.left = Some(l);
                                                lmcleft.right = Some(r);
                                                self.left = Some(lmcleft);
                                                break;
                                            }
                                            Some(superleft) => {
                                                lmcleft.left = Some(superleft);
                                                lmc.left = Some(lmcleft);
                                            }
                                        },
                                    }
                                },
                            },
                        },
                        // Node not found, go recursively
                        Ordering::Greater => {
                            node.erase(&data);
                            self.left = Some(node);
                        }
                        Ordering::Less => {
                            node.erase(&data);
                            self.left = Some(node);
                        }
                    }
                }
            },
            Ordering::Less => match self.right.take() {
                None => {
                    return;
                }
                Some(mut node) => {
                    match node.data.compare(&data) {
                        // Node found, erase this one
                        Ordering::Equal => match (node.left.take(), node.right.take()) {
                            (None, None) => {}
                            (Some(l), None) => self.right = Some(l),
                            (None, Some(r)) => self.right = Some(r),
                            (Some(l), Some(mut r)) => match r.left.take() {
                                None => {
                                    r.left = Some(l);
                                    self.right = Some(r);
                                }
                                Some(mut lmc) => while true {
                                    match lmc.left.take() {
                                        None => break,
                                        Some(mut lmcleft) => match lmcleft.left.take() {
                                            None => {
                                                match lmcleft.right.take() {
                                                    None => {}
                                                    Some(lmcleftright) => {
                                                        lmc.left = Some(lmcleftright);
                                                    }
                                                }
                                                lmcleft.left = Some(l);
                                                lmcleft.right = Some(r);
                                                self.right = Some(lmcleft);
                                                break;
                                            }
                                            Some(superleft) => {
                                                lmcleft.left = Some(superleft);
                                                lmc.left = Some(lmcleft);
                                            }
                                        },
                                    }
                                },
                            },
                        },
                        // Node not found, go recursively
                        Ordering::Greater => {
                            node.erase(&data);
                            self.right = Some(node);
                        }
                        Ordering::Less => {
                            node.erase(&data);
                            self.right = Some(node);
                        }
                    }
                }
            },
        }
    }
	
	pub fn print_children(&self, indent: String) {
		match self.left {
			Some(ref node) => {
				println!("{}{}", indent, node.data);
				node.print_children(format!("{} ", indent));
			}
			None => {
                println!("{}()", indent);
            }
		}
		match self.right {
			Some(ref node) => {
				println!("{}{}", indent, node.data);
				node.print_children(format!("{} ", indent));
			}
			None => {
                println!("{}()", indent);
            }
		}
    }
}

impl SortedContainer {
    pub fn new() -> Self {
        return SortedContainer { root: None };
    }

    pub fn insert(&mut self, data: Data) {
        match self.root {
            None => {
                self.root = Some(Box::new(Node::new(data)));
            }
            Some(ref mut node) => {
                node.insert(data);
            }
        }
    }

    pub fn contains(&self, ref data: &Data) -> bool {
        match self.root {
            None => {
                return false;
            }
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

    pub fn erase(&mut self, ref data: &Data) {
        let root_node = self.root.take();
        match root_node {
            None => {
                println!("Empty SortedContainer");
                return;
            }
            Some(mut root) => {
                // create auxillary root
                let mut aux: Node = Node::new(Data::new(0, "auxillary root".to_string()));
                match aux.data.compare(&root.data) {
                    Ordering::Equal => {
                        panic!("Auxillary root already exists. Please name your root differently.");
                    }
                    Ordering::Greater => {
                        aux.left = Some(root);
                    }
                    Ordering::Less => {
                        aux.right = Some(root);
                    }
                }
                self.root = Some(Box::new(aux));

                // delete data
                match self.root.take() {
                    None => {
                        println!("Empty root.");
                    }
                    Some(mut root) => {
                        root.erase(&data);
                        self.root = Some(root);
                    }
                }

                // remove auxillary root
                match self.root.take() {
                    None => {
                        println!("Empty root.");
                    }
                    Some(mut root) => match (root.left.take(), root.right.take()) {
                        (None, None) => {
                            self.root = None;
                        }
                        (Some(l), None) => {
                            self.root = Some(l);
                        }
                        (None, Some(r)) => {
                            self.root = Some(r);
                        }
                        (Some(l), Some(r)) => {
                            println!("Something went wrong: auxillary root has 2 children");
                        }
                    },
                }
            }
        }
    }
}
