use std::collections::HashMap;
use std::sync::{Arc, Mutex};
use crate::server::ServerConn;
use crate::zappy::Zappy;

pub type ServerFunction = fn(&mut Zappy, String);

pub(crate) fn create_hash_function() -> HashMap<String, ServerFunction> {
    let mut functions : HashMap<String, ServerFunction> = HashMap::new();

    functions.insert("msz".to_string(), Zappy::set_map_size);
    functions
}


impl Zappy {
    fn set_map_size(&mut self, command: String) {
        println!("Set :D");
    }

    pub(crate) fn interpret_commands(&mut self) {
        let mut commands_access: Arc<Mutex<Vec<String>>>;
        if let Some(server) = &mut self.server {
            commands_access = Arc::clone(&server.commands);
        } else {
            return;
        }
        let mut commands = commands_access.lock().expect("Mutex poisoned");
        for _ in 0..commands.len() {
            if let Some(command) = commands.pop() {
                let command_splited = command.split("\n");

                for command in command_splited {
                    let command_name = command.split(" ").next().expect("invalid cmd");
                    let maybe_func = self.functions.get(command_name);

                    match maybe_func {
                        None => { println!("Command received unknown: {command_name}") }
                        Some(function) => { function(self, command.to_string()) }
                    }
                }
            }
        }
    }
}