use crate::tantorian::{generate_color_from_string, Orientation, Tantorian};
use crate::zappy::Zappy;
use regex::Regex;
use std::collections::HashMap;
use std::f32::consts::PI;
use std::sync::{Arc, Mutex};
use std::time::Duration;
use rend_ox::glam::{Vec2, Vec3Swizzles};
use rend_ox::Vec3;
use crate::incantation::{Incantation, IncantationState};
use crate::message::{Arrows, Message};
use crate::tantorian::PlayerState::{Alive, Dead, Egg};

pub type ServerFunction = fn(&mut Zappy, String, Duration);

pub(crate) fn create_hash_function() -> HashMap<String, ServerFunction> {
    let mut functions: HashMap<String, ServerFunction> = HashMap::new();

    functions.insert("msz".to_string(), Zappy::set_map_size);
    functions.insert("bct".to_string(), Zappy::tile_content);
    functions.insert("tna".to_string(), Zappy::add_team_name);
    functions.insert("pnw".to_string(), Zappy::connect_new_player);
    functions.insert("ppo".to_string(), Zappy::player_position);
    functions.insert("plv".to_string(), Zappy::player_level);
    functions.insert("pin".to_string(), Zappy::player_inventory);
    functions.insert("pex".to_string(), Zappy::player_expulsion);
    functions.insert("pbc".to_string(), Zappy::broadcast);
    functions.insert("pic".to_string(), Zappy::add_incantation);
    functions.insert("pie".to_string(), Zappy::end_incantation);
    functions.insert("pfk".to_string(), Zappy::player_fork);
    functions.insert("pdr".to_string(), Zappy::drop_resource);
    functions.insert("pgt".to_string(), Zappy::collect_resource);
    functions.insert("pdi".to_string(), Zappy::death_of_player);
    functions.insert("enw".to_string(), Zappy::new_egg);
    functions.insert("ebo".to_string(), Zappy::connection_to_egg);
    functions.insert("edi".to_string(), Zappy::death_of_an_egg);
    functions.insert("sgt".to_string(), Zappy::set_time_unit);
    functions.insert("sst".to_string(), Zappy::set_time_unit);
    functions.insert("seg".to_string(), Zappy::end_of_game);
    functions.insert("smg".to_string(), Zappy::message_from_server);
    functions.insert("suc".to_string(), Zappy::invalid_command_sent);
    functions.insert("sbp".to_string(), Zappy::invalid_arg_sent);
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
    fn player_fork(&mut self, command: String, at: Duration) {
        let re = Regex::new(r"^pfk #?(-?\d+)$")
            .expect("Invalid regex");

        if let Some(capture) = re.captures(&*command) {
            parse_capture!(i64, 1, number, capture, "pfk: invalid player number");

            let mut found = false;
            for (idx, player) in &mut self.players {
                if player.number == number {
                    player.laying = Some(5.0);
                    player.start_movement = Some(at);
                    found = true;
                }
            }
            if !found {
                println!("pfk: invalid command given");
            }
        } else {
            println!("pfk: invalid command given");
        }
    }

    fn player_expulsion(&mut self, command: String, at: Duration) {
        let re = Regex::new(r"^pex #?(-?\d+)$")
            .expect("Invalid regex");

        if let Some(capture) = re.captures(&*command) {
            parse_capture!(i64, 1, number, capture, "pex: invalid player number");

            let mut found = false;
            let mut pos = [0;2];
            let mut orientation = Orientation::N;
            for (idx, player) in &mut self.players {
                if player.number == number && player.state == Alive {
                    found = true;
                    orientation = player.orientation;
                    pos = [player.current_tile.x as usize, player.current_tile.y as usize];
                    self.arrows.push(Arrows::new_from_direction(Vec3::new(0., 0., -player.orientation.as_radian()), player.pos.x, player.pos.y, player.color.clone(), at.clone()));
                }
            }
            if !found {
                println!("pex: player not found");
            }


            for (idx, player) in &mut self.players {
                if [player.current_tile.x as usize, player.current_tile.y as usize] == pos && player.number != number {
                    if player.state == Egg {
                        player.state = Dead
                    }
                    if player.state == Alive {
                        let mut x = player.current_tile.x + (orientation == Orientation::E) as u8 as f32 - (orientation == Orientation::W) as u8 as f32;
                        let mut y = player.current_tile.y + (orientation == Orientation::N) as u8 as f32 - (orientation == Orientation::S) as u8 as f32;
                        if x < 0. {
                            x = self.map.size[0] as f32 - 1.;
                        }
                        if y < 0. {
                            y = self.map.size[1] as f32 - 1.;
                        }
                        player.last_tile = player.pos.xy() - 0.5;
                        player.current_tile = Vec2::new(x as f32, y as f32);
                        player.start_movement = Some(at);
                    }
                }
            }
        } else {
            println!("pex: invalid command given");
        }
    }

    fn drop_resource(&mut self, command: String, at: Duration) {
        let re = Regex::new(r"^pdr #?(-?\d+) ([0-6])$")
            .expect("Invalid regex");

        if let Some(capture) = re.captures(&*command) {
            parse_capture!(i64, 1, number, capture, "pdr: invalid player number");
            parse_capture!(usize, 2, ressource, capture, "pdr: invalid resource number");

            for (idx, player) in &mut self.players {
                if player.number == number && player.state == Alive {
                    let x = player.current_tile.as_uvec2().x as usize;
                    let y = player.current_tile.as_uvec2().y as usize;
                    let before_quantity = self.map.tiles[x][y].access_to_nth_resource(ressource).len();
                    self.map.update_resources(x, y, ressource, before_quantity + player.access_nth_resource(ressource).clone() as usize);
                    *player.access_nth_resource(ressource) = 0;
                    self.arrows.push(Arrows::new_from_direction(Vec3::new(-PI/2., 0., 0.), player.pos.x, player.pos.y, player.color.clone(), at.clone()));
                    return;
                } else if player.number == number {
                    println!("pdr: player not alive");
                    return;
                }
            }
            println!("pdr: player not found");
        } else {
            println!("pdr: invalid command given");
        }
    }

    fn collect_resource(&mut self, command: String, at: Duration) {
        let re = Regex::new(r"^pgt #?(-?\d+) ([0-6])$")
            .expect("Invalid regex");

        if let Some(capture) = re.captures(&*command) {
            parse_capture!(i64, 1, number, capture, "pgt: invalid player number");
            parse_capture!(usize, 2, ressource, capture, "pgt: invalid resource number");

            for (idx, player) in &mut self.players {
                if player.number == number && player.state == Alive {
                    let x = player.current_tile.as_uvec2().x as usize;
                    let y = player.current_tile.as_uvec2().y as usize;
                    *player.access_nth_resource(ressource) += self.map.tiles[x][y].access_to_nth_resource(ressource).len() as u32;
                    self.map.update_resources(x, y, ressource, 0);
                    self.arrows.push(Arrows::new_from_direction(Vec3::new(PI/2., 0., 0.), player.pos.x, player.pos.y, player.color.clone(), at.clone()));
                    return;
                } else if player.number == number {
                    println!("pgt: player not alive");
                    return;
                }
            }
            println!("pgt: player not found");
        } else {
            println!("pgt: invalid command given");
        }
    }

    fn death_of_an_egg(&mut self, command: String, _at: Duration) {
        let re = Regex::new(r"^edi #?(-?\d+)$")
            .expect("Invalid regex");
        if let Some(capture) = re.captures(&*command) {
            parse_capture!(i64, 1, egg_number, capture, "edi: invalid egg number");

            for (idx, player) in &mut self.players {
                if player.number == egg_number && player.state == Egg {
                    player.state = Dead;
                    return;
                } else if player.number == egg_number {
                    println!("edi: player not an egg");
                    return;
                }
            }
            println!("edi: player not found");
        } else {
            println!("edi: invalid command given");
        }
    }

    fn connection_to_egg(&mut self, command: String, _at: Duration) {
        let re = Regex::new(r"^ebo #?(-?\d+)$")
            .expect("Invalid regex");
        if let Some(capture) = re.captures(&*command) {
            parse_capture!(i64, 1, egg_number, capture, "ebo: invalid egg number");

            for (idx, player) in &mut self.players {
                if player.number == egg_number && player.state == Egg {
                    player.state = Alive;
                    return;
                } else if player.number == egg_number {
                    println!("ebo: player not an egg");
                    return;
                }
            }
            println!("ebo: player not found");
        } else {
            println!("ebo: invalid command given");
        }
    }

    fn new_egg(&mut self, command: String, _at: Duration) {
        let re = Regex::new(r"^enw #?(-?\d+) #?(-?\d+) (\d+) (\d+)$")
            .expect("Invalid regex");

        if let Some(capture) = re.captures(&*command) {
            parse_capture!(i64, 1, egg_number, capture, "enw: invalid egg number");
            parse_capture!(i64, 2, number, capture, "enw: invalid player number");
            parse_capture!(usize, 3, x, capture, "enw: invalid player x coordinate");
            parse_capture!(usize, 4, y, capture, "enw: invalid player y coordinate");

            if x > self.map.size[0] {
                println!("enw: x coordinate out of bounds");
                return;
            }
            if y > self.map.size[1] {
                println!("enw: y coordinate out of bounds");
                return;
            }
            let mut found = false;
            for (idx, player) in &self.players {
                if player.number == number {
                    found = true;
                }
            }
            if !found {
                println!("enw: player not found");
                return;
            }
            if let Some(egg) = Tantorian::new_egg(egg_number, x, y, &self.map.size, number, &self.teams, &self.players) {
                self.players.insert(egg_number, egg);
            }
        } else {
            println!("enw: invalid command given");
        }
    }

    fn invalid_arg_sent(&mut self, _command: String, at: Duration) {
        self.ui.network_messages.push((at, String::from("Server received invalid argument")));
        println!("Server received invalid argument");
    }

    fn invalid_command_sent(&mut self, _command: String, at: Duration) {
        self.ui.network_messages.push((at, String::from("Server received invalid command")));
        println!("Server received invalid command");
    }

    fn message_from_server(&mut self, command: String, at: Duration) {
        let args: Vec<&str> = command.split(" ").collect();

        self.ui.network_messages.push((at, String::from(args[1])));
        println!("Server sent: {}", args[1]);
    }

    fn player_inventory(&mut self, command: String, at: Duration) {
        let re = Regex::new(r"^pin #?(-?\d+) (\d+) (\d+) (\d+) (\d+) (\d+) (\d+) (\d+) (\d+) (\d+)$")
            .expect("Invalid regex");

        if let Some(capture) = re.captures(&*command) {
            parse_capture!(i64, 1, number, capture, "pin: invalid player number");
            parse_capture!(usize, 2, x, capture, "pin: invalid player x coordinate");
            parse_capture!(usize, 3, y, capture, "pin: invalid player y coordinate");

            parse_capture!(usize, 4, q0, capture, "pin: invalid player q0 resource");
            parse_capture!(usize, 5, q1, capture, "pin: invalid player q1 resource");
            parse_capture!(usize, 6, q2, capture, "pin: invalid player q2 resource");
            parse_capture!(usize, 7, q3, capture, "pin: invalid player q3 resource");
            parse_capture!(usize, 8, q4, capture, "pin: invalid player q4 resource");
            parse_capture!(usize, 9, q5, capture, "pin: invalid player q5 resource");
            parse_capture!(usize, 10, q6, capture, "pin: invalid player q6 resource");

            if x > self.map.size[0] {
                println!("pin: x coordinate out of bounds");
                return;
            }
            if y > self.map.size[1] {
                println!("pin: y coordinate out of bounds");
                return;
            }
            let mut found = false;
            for (idx, player) in &mut self.players {
                if player.number == number {
                    found = true;
                    player.last_tile = player.pos.xy() - 0.5;
                    player.current_tile = Vec2::new(x as f32, y as f32);
                    player.start_movement = Some(at);
                    player.food = q0 as u32;
                    player.linemate = q1 as u32;
                    player.deraumere = q2 as u32;
                    player.sibur = q3 as u32;
                    player.mendiane = q4 as u32;
                    player.phiras = q5 as u32;
                    player.thystame = q6 as u32;
                }
            }
            if !found {
                println!("pin: player not found");
            }
        } else {
            println!("pin: invalid command given");
        }
    }

    fn player_level(&mut self, command: String, _at: Duration) {
        let re = Regex::new(r"^plv #?(-?\d+) ([1-8])$")
            .expect("Invalid regex");

        if let Some(capture) = re.captures(&*command) {
            parse_capture!(i64, 1, number, capture, "plv: invalid player number");
            parse_capture!(usize, 2, level, capture, "plv: invalid player level coordinate");

            let mut found = false;
            for (idx, player) in &mut self.players {
                if player.number == number {
                    found = true;
                    player.level = level as u32;
                }
            }
            if !found {
                println!("plv: player not found");
            }
        } else {
            println!("plv: invalid command given");
        }
    }

    fn player_position(&mut self, command: String, at: Duration) {
        let re = Regex::new(r"^ppo #?(-?\d+) (\d+) (\d+) ([1-4])$")
            .expect("Invalid regex");

        if let Some(capture) = re.captures(&*command) {
            parse_capture!(i64, 1, number, capture, "ppo: invalid player number");
            parse_capture!(usize, 2, x, capture, "ppo: invalid player x coordinate");
            parse_capture!(usize, 3, y, capture, "ppo: invalid player y coordinate");
            parse_capture!(usize, 4, orientation, capture, "ppo: invalid player orientation");

            if orientation < 1 || orientation > 4 {
                println!("ppo: invalid player orientation");
                return;
            }
            if x > self.map.size[0] {
                println!("ppo: x coordinate out of bounds");
                return;
            }
            if y > self.map.size[1] {
                println!("ppo: y coordinate out of bounds");
                return;
            }
            let mut found = false;
            for (idx, player) in &mut self.players {
                if player.number == number {
                    found = true;
                    player.last_tile = player.pos.xy() - 0.5;
                    player.last_orientation = player.orientation;
                    player.orientation = Orientation::from_usize(orientation);
                    player.current_tile = Vec2::new(x as f32, y as f32);
                    player.start_movement = Some(at);
                }
            }
            if !found {
                println!("ppo: player not found");
            }
        } else {
            println!("ppo: invalid command given");
        }
    }

    fn broadcast(&mut self, command: String, at: Duration) {
        let args: Vec<&str> = command.split(" ").collect();

        if args.len() != 3 {
            println!("pbc: wrong number of arguments");
        } else {
            let maybe_number : Result<i64, _> = args[1].to_string().parse();

            match maybe_number {
                Ok(number) => {
                    for (idx, player) in &mut self.players {
                        if player.number == number && player.state == Alive {
                            self.messages.push(Message{
                                pos: Vec3::new(player.pos.x, player.pos.y, 0.),
                                scale: Vec3::new(1., 1., 1.),
                                color: player.color.clone(),
                                start: at.clone()
                            });
                            self.ui.broadcast_messages.push((at, player.team_name.clone(), number, String::from(args[2])));
                            return;
                        }
                    }
                    println!("pbc: player not found");
                }
                Err(_) => {println!("pbc: invalid player number");}
            }
        }
    }

    fn add_incantation(&mut self, command: String, at: Duration) {
        let args: Vec<&str> = command.split(" ").collect();

        if args.len() < 4 {
            println!("pic: wrong number of arguments");
        } else {
            let x : Result<u32, _> = args[1].to_string().parse();
            let y : Result<u32, _> = args[2].to_string().parse();
            let level : Result<u32, _> = args[3].to_string().parse();
            let mut players : Vec<i64> = vec![];
            for arg in &args[4..] {
                println!("pic: player: {}:  {:?}", arg, arg.to_string().parse() as Result<i64, _>);
                match arg.to_string().parse() {
                    Ok(p) => { players.push(p)}
                    _ => { println!("pic: invalid player number"); return; }
                }
            }

            if let (Ok(x), Ok(y), (Ok(level))) = (x, y, level) {
                self.incantations.push(Incantation::new(
                    Vec2::new(x as f32, y as f32),
                    level,
                    players,
                    at
                ));
            } else {
                println!("pic: invalid arguments");
            }
        }
    }

    fn end_incantation(&mut self, command: String, at: Duration) {
        let args: Vec<&str> = command.split(" ").collect();

        if args.len() != 4 {
            println!("pic: wrong number of arguments");
        } else {
            let x : Result<u32, _> = args[1].to_string().parse();
            let y : Result<u32, _> = args[2].to_string().parse();
            let state = match args[3] {
                "Ok" => IncantationState::Success,
                "KO" => IncantationState::Failed,
                _ => IncantationState::Failed,
            };

            if let (Ok(x), Ok(y)) = (x, y) {
                for incantation in &mut self.incantations {
                    if incantation.pos.x as u32 == x && incantation.pos.y as u32 == y && incantation.state == IncantationState::Running {
                        incantation.state = state;
                        incantation.since = at;
                        return;
                    }
                }
            } else {
                println!("pic: invalid arguments");
            }
        }
    }

    fn end_of_game(&mut self, command: String, at: Duration) {
        let args: Vec<&str> = command.split(" ").collect();

        if args.len() != 2 {
            println!("seg: wrong number of arguments");
        } else {
            if !self.teams.iter().any(|(name, _color)| *name == args[1].to_string()) {
                println!("seg: invalid team name");
            } else {
                self.close_connection(at);
                self.winner_team = Some(args[1].to_string());
            }
        }
    }

    fn death_of_player(&mut self, command: String, _at: Duration) {
        let args: Vec<&str> = command.split(" ").collect();

        if args.len() != 2 {
            println!("pdi: wrong number of arguments");
        } else {
            let maybe_number : Result<i64, _> = args[1].to_string().parse();

            match maybe_number {
                Ok(number) => {
                    for (idx, player) in &mut self.players {
                        if player.number == number {
                            player.state = Dead;
                        }
                    }
                }
                Err(_) => {println!("pdi: invalid player number");}
            }
        }
    }

    fn connect_new_player(&mut self, command: String, _at: Duration) {
        let re = Regex::new(r"^pnw #?(-?\d+) (\d+) (\d+) ([1-4]) ([0-8]) (\w+)$")
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
            if x > self.map.size[0] {
                println!("pnw: x coordinate out of bounds");
                return;
            }
            if y > self.map.size[1] {
                println!("pnw: y coordinate out of bounds");
                return;
            }
            if let Some(new_player) = Tantorian::new_from_command(
                number,
                x,
                y,
                Orientation::from_usize(orientation),
                level,
                team_name,
                &self.teams,
                &self.map.size,
                &mut self.players,
            ) {
                self.players.insert(number, new_player);
            }
        } else {
            println!("pnw: invalid command given")
        }
    }

    fn add_team_name(&mut self, command: String, _at: Duration) {
        let args: Vec<&str> = command.split(" ").collect();

        if args.len() != 2 {
            println!("tna: wrong number of arguments");
        } else {
            let team_name = args[1].to_string();
            if !self.teams.iter().any(|(name, _color)| name == &team_name) {
                let color = generate_color_from_string(&team_name);

                self.teams.push((team_name, color))
            } else {
                println!("tna: Team name already given");
            }
        }
    }

    fn set_time_unit(&mut self, command: String, _at: Duration) {
        let args: Vec<&str> = command.split(" ").collect();

        if args.len() != 2 {
            println!("sgt/sst: wrong number of arguments");
        } else {
            let result: Result<f32, _> = args[1].parse();
            match result {
                Ok(val) => self.time_unit = val,
                Err(_) => {
                    println!("sgt/sst: argument must be an int")
                }
            }
        }
    }

    fn tile_content(&mut self, command: String, _at: Duration) {
        let mut invalid = false;
        let args: Vec<usize> = command
            .split(" ")
            .skip(1)
            .filter(|&x| !x.is_empty())
            .map(|x| -> usize {
                return match x.parse() {
                    Ok(val) => {val},
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
            println!("bct: wrong number of arguments");
            return;
        }
        if args[0] > self.map.size[0] || args[1] > self.map.size[1] {
            println!("bct: tile outside of the map");
            return;
        }
        for i in 0..7 {
            self.map.update_resources(args[0], args[1], i, args[2 + i]);
        }
    }

    fn set_map_size(&mut self, command: String, _at: Duration) {
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
        let command_split =
            raw_command.split("\n")
                .filter(|&x| !x.is_empty())
                .filter(|&x| !(x.len() == 1 && x.as_bytes()[0] == 0));

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
            let command = commands.remove(0);
            self.interpret_command(command, at);
        }
    }
}
