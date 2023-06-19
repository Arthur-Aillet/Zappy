use crate::map::Tile;
use crate::tantorian::{Orientation, Tantorian};
use crate::zappy::Zappy;
use regex::Regex;
use std::collections::HashMap;
use std::sync::{Arc, Mutex};
use std::thread::JoinHandle;
use std::time::Duration;

pub type ServerFunction = fn(&mut Zappy, String, Duration);

pub(crate) fn create_hash_function() -> HashMap<String, ServerFunction> {
    let mut functions: HashMap<String, ServerFunction> = HashMap::new();

    functions.insert("msz".to_string(), Zappy::set_map_size);
    functions.insert("bct".to_string(), Zappy::tile_content);
    functions.insert("sgt".to_string(), Zappy::set_time_unit);
    functions.insert("tna".to_string(), Zappy::add_team_name);
    functions.insert("pnw".to_string(), Zappy::connect_new_player);
    functions.insert("pdi".to_string(), Zappy::death_of_player);
    functions.insert("seg".to_string(), Zappy::end_of_game);
    functions
}

macro_rules! parse_capture {
    ($typ:ty, $index:expr, $name:ident, $capture:expr, $message:expr) => {
        let $name: $typ;
        if let Some(matched) = $capture.get($index) {
            if let Ok(found) = matched.as_str().to_string().parse() {
                $name = found;
            } else {
                println!($message);
                return;
            }
        } else {
            println!($message);
            return;
        }
    };
}

impl Zappy {
    fn end_of_game(&mut self, command: String, at: Duration) {
        let args: Vec<&str> = command.split(" ").collect();

        if args.len() != 2 {
            println!("seg: Too many arguments");
        } else {
            if !self.team_names.contains(&args[1].to_string()) {
                println!("seg: invalid team name");
            } else {
                self.close_connection(at);
            }
        }
    }

    fn death_of_player(&mut self, command: String, at: Duration) {
        let args: Vec<&str> = command.split(" ").collect();

        if args.len() != 2 {
            println!("pdi: Too many arguments");
        } else {
            let maybe_number : Result<i64, _> = args[1].to_string().parse();

            match maybe_number {
                Ok(number) => {
                    for player in &mut self.players {
                        if player.number == number {
                            player.alive = false;
                        }
                    }
                }
                Err(_) => {println!("pdi: invalid player number");}
            }
        }
    }

    fn connect_new_player(&mut self, command: String, at: Duration) {
        let re = Regex::new(r"^pnw (-?\d+) (\d+) (\d+) ([1-4]) ([0-8]) (\w+)$")
            .expect("Invalid regex");

        if let Some(capture) = re.captures(&*command) {
            parse_capture!(i64, 1, number, capture, "pnw: invalid player number");
            parse_capture!(usize, 2, x, capture, "pnw: invalid player x coordinate");
            parse_capture!(usize, 3, y, capture, "pnw: invalid player y coordinate");
            parse_capture!(usize, 4, orientation, capture, "pnw: invalid player orientation");
            parse_capture!(u32, 5, level, capture, "pnw: invalid player level");
            parse_capture!(String, 6, team_name, capture, "pnw: invalid player team name");

            if orientation < 1 || orientation > 4 {
                println!("pnw: invalid player orientation");
                return;
            }
            if let Some(new_player) = Tantorian::new_from_command(
                number,
                x,
                y,
                Orientation::from_usize(orientation),
                level,
                team_name,
                &self.team_names,
                &self.map.size,
                &mut self.players,
            ) {
                self.players.push(new_player)
            }
        } else {
            println!("pnw: invalid command given")
        }
    }

    fn add_team_name(&mut self, command: String, at: Duration) {
        let args: Vec<&str> = command.split(" ").collect();

        if args.len() != 2 {
            println!("tna: Too many arguments");
        } else {
            if !self.team_names.contains(&args[1].to_string()) {
                self.team_names.push(args[1].to_string())
            } else {
                println!("tna: Team name already given");
            }
        }
    }

    fn set_time_unit(&mut self, command: String, at: Duration) {
        let args: Vec<&str> = command.split(" ").collect();

        if args.len() != 2 {
            println!("sgt: Too many arguments");
        } else {
            let result: Result<f32, _> = args[1].parse();
            match result {
                Ok(val) => self.time_unit = val,
                Err(_) => {
                    println!("sgt: argument must be an int")
                }
            }
        }
    }

    fn tile_content(&mut self, command: String, at: Duration) {
        let mut invalid = false;
        let args: Vec<usize> = command
            .split(" ")
            .skip(1)
            .map(|x| -> usize {
                return match x.parse() {
                    Ok(val) => val,
                    Err(_) => {
                        println!("bct: value needs to be a unsigned integers");
                        invalid = true;
                        0
                    }
                };
            })
            .collect();
        if invalid == true {
            return;
        }
        if args.len() != 9 {
            println!("btc: wrong number of arguments");
            return;
        }
        if args[0] > self.map.size[0] || args[1] > self.map.size[1] {
            println!("btc: tile outside of the map");
            return;
        }
        for i in 0..7 {
            self.map.update_resources(args[0], args[1], i, args[2 + i]);
        }
    }

    fn set_map_size(&mut self, command: String, at: Duration) {
        let args: Vec<&str> = command.split(" ").collect();

        if args.len() == 3 {
            let x: usize;
            let x_result: Result<usize, _> = args[1].parse();
            match x_result {
                Ok(val) => x = val,
                Err(_) => {
                    println!("width needs to be a unsigned integer");
                    return;
                }
            }

            let y: usize;
            let y_result: Result<usize, _> = args[2].parse();
            match y_result {
                Ok(val) => y = val,
                Err(_) => {
                    println!("height needs to be a unsigned integer");
                    return;
                }
            }
            self.map.resize(x, y);
        } else {
            println!("Invalid arguments to the size command received");
        }
    }

    fn interpret_command(&mut self, raw_command: String, at: Duration) {
        let command_split = raw_command.split("\n").filter(|&x| !x.is_empty());

        for command in command_split {
            let command_name = command.split(" ").next().expect("invalid cmd");
            let maybe_func = self.functions.get(command_name);

            match maybe_func {
                Some(function) => function(self, command.to_string(), at),
                None => {
                    println!("Command received unknown: \"{command}\"")
                }
            }
        }
    }

    pub(crate) fn interpret_commands(&mut self, at: Duration) {
        let commands_access: Arc<Mutex<Vec<String>>>;

        match &mut self.server {
            None => return,
            Some(server) => {
                commands_access = Arc::clone(&server.commands);
            }
        };
        let mut commands = commands_access.lock().expect("Mutex poisoned");
        for _ in 0..commands.len() {
            if let Some(command) = commands.pop() {
                self.interpret_command(command, at);
            }
        }
    }
}
