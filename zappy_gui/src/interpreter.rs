use std::collections::HashMap;
use std::sync::{Arc, Mutex};
use crate::map::Tile;
use crate::zappy::Zappy;

pub type ServerFunction = fn(&mut Zappy, String);

pub(crate) fn create_hash_function() -> HashMap<String, ServerFunction> {
    let mut functions : HashMap<String, ServerFunction> = HashMap::new();

    functions.insert("msz".to_string(), Zappy::set_map_size);
    functions.insert("bct".to_string(), Zappy::tile_content);
    functions
}


impl Zappy {
    fn tile_content(&mut self, command: String) {
        let mut invalid = false;
        let args: Vec<usize> = command.split(" ").skip(1).map(|x| -> usize {
            return match x.parse() {
                Ok(val) => { val }
                Err(_) => {
                    println!("bct: value needs to be a unsigned integers");
                    invalid = true;
                    0
                }
            }
        }).collect();
        if invalid == true {
            return;
        }
        if args.len() != 9 {
            println!("btc: wrong number of arguments");
            return;
        }
        if args[1] > self.map.size[0] || args[0] > self.map.size[1] {
            println!("btc: tile outside of the map");
            return;
        }
        let selected_tile = &mut self.map.tiles[args[1] + self.map.size[1] * args[0]];
        selected_tile.food = args[2];
        selected_tile.linemate = args[3];
        selected_tile.deraumere = args[4];
        selected_tile.sibur = args[5];
        selected_tile.mendiane = args[6];
        selected_tile.phiras = args[7];
        selected_tile.thystame = args[8];
    }

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
            self.map.tiles.resize(x*y, Tile::new());
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