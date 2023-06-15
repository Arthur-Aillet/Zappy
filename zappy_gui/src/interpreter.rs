use std::collections::HashMap;
use std::sync::{Arc, Mutex};
use crate::zappy::Zappy;

pub type ServerFunction = fn(&mut Zappy, String);

pub(crate) fn create_hash_function() -> HashMap<String, ServerFunction> {
    let mut functions : HashMap<String, ServerFunction> = HashMap::new();

    functions.insert("msz".to_string(), Zappy::set_map_size);
    functions
}


impl Zappy {
    fn set_map_size(&mut self, command: String) {
        let args: Vec<&str> = command.split(" ").collect();

        if args.len() == 3 {
            let x: usize;
            let x_result: Result<usize, _> = args[1].parse();
            match x_result {
                Ok(val) => {x = val}
                Err(_) => {println!("width needs to be a unsigned integer"); return;}
            }

            let y: usize;
            let y_result: Result<usize, _> = args[1].parse();
            match y_result {
                Ok(val) => {y = val}
                Err(_) => {println!("height needs to be a unsigned integer"); return;}
            }
            self.map.size = [x, y];
        } else {
            println!("Invalid arguments to the size command received");
        }
    }

    fn interpret_command(&mut self, raw_command : String) {
        let command_split = raw_command.split("\n");

        for command in command_split {
            let command_name = command.split(" ").next().expect("invalid cmd");
            let maybe_func = self.functions.get(command_name);

            match maybe_func {
                None => { println!("Command received unknown: {command_name}") }
                Some(function) => { function(self, command.to_string()) }
            }
        }
    }

    pub(crate) fn interpret_commands(&mut self) {
        let commands_access: Arc<Mutex<Vec<String>>>;

        match &mut self.server {
            None => {return}
            Some(server) => {commands_access = Arc::clone(&server.commands);}
        };
        let mut commands = commands_access.lock().expect("Mutex poisoned");
        for _ in 0..commands.len() {
            if let Some(command) = commands.pop() {
                self.interpret_command(command);
            }
        }
    }
}