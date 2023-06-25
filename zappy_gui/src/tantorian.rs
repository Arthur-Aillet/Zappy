use std::collections::hash_map::DefaultHasher;
use std::collections::HashMap;
use std::f32::consts::PI;
use rend_ox::glam::Vec2;
use rend_ox::Vec3;
use std::hash::{Hash, Hasher};
use std::time::Duration;
use crate::tantorian::PlayerState::{Alive, Dead, Egg};

#[derive(Clone, Copy, PartialEq)]
pub enum Orientation {
    N = 1,
    E = 2,
    S = 3,
    W = 4,
}

impl Orientation {
    pub fn from_usize(value: usize) -> Orientation {
        match value {
            1 => Orientation::N,
            2 => Orientation::E,
            3 => Orientation::S,
            4 => Orientation::W,
            _ => panic!("Orientation: Unknown value: {}", value),
        }
    }

    pub fn to_char(&self) -> char {
        match self {
            Orientation::N => 'N',
            Orientation::E => 'E',
            Orientation::S => 'S',
            Orientation::W => 'W',
        }
    }

    pub fn as_radian(&self) -> f32 {
        match self {
            Orientation::S => 0. * PI/180.,
            Orientation::E => 270. * PI/180.,
            Orientation::N => 180. * PI/180.,
            Orientation::W => 90. * PI/180.,
        }
    }
}

pub fn generate_color_from_string(string: &String) -> Vec3 {
    let mut hasher = DefaultHasher::new();
    string.hash(&mut hasher);
    let hash = hasher.finish();
    let mut r = (hash & 0xFF0000) >> 16;
    let mut g = (hash & 0x00FF00) >> 8;
    let mut b = hash & 0x0000FF;
    if r + g + b < 30 {
        r += 10;
        g += 10;
        b += 10;
    }
    return Vec3::new(r as f32/255. , g as f32/255., b as f32/255.)
}

#[derive(Clone, Copy, PartialEq)]
pub enum PlayerState {
    Dead,
    Alive,
    Egg
}

impl PlayerState {
    pub fn as_string(&self) -> &'static str {
        match self {
            Dead => {"dead"}
            Alive => {"alive"}
            PlayerState::Egg => {"egg"}
        }
    }
}

pub struct Tantorian {
    pub team_name: String,
    pub number: i64,
    pub pos: Vec3,
    pub color: Vec3,
    pub current_tile: Vec2,
    pub last_tile: Vec2,
    pub last_orientation: Orientation,
    pub rotation: Vec3,
    pub start_movement: Option<Duration>,
    pub level: u32,
    pub orientation: Orientation,
    pub mesh_descriptor: u32,
    pub state: PlayerState,
    pub parent: Option<i64>,
    pub laying: Option<f32>,
    pub food: u32,
    pub linemate: u32,
    pub deraumere: u32,
    pub sibur: u32,
    pub mendiane: u32,
    pub phiras: u32,
    pub thystame: u32,
}

impl Tantorian {
    pub fn access_nth_resource(&mut self, q: usize) -> &mut u32 {
        match q {
            0 => { &mut self.food}
            1 => { &mut self.linemate}
            2 => { &mut self.deraumere}
            3 => { &mut self.sibur}
            4 => { &mut self.mendiane}
            5 => { &mut self.phiras}
            6 => { &mut self.thystame}
            _ => { panic!("Accessed to non existing resource") }
        }
    }

    pub fn new_egg(number: i64, x: usize, y: usize, map_size: &[usize; 2], parent_number: i64, teams: &Vec<(String, Vec3)>, players: &HashMap<i64, Tantorian>) -> Option<Tantorian> {
        let mut parent_player: Option<&Tantorian> = None;
        for (idx, player) in players {
            if player.number == number && player.state != Dead {
                println!("Player number already attributed");
                return None;
            }
            if player.number == parent_number {
                parent_player = Some(player);
            }
        }
        if let Some(parent) = parent_player {
            if x >= map_size[0] || y >= map_size[1] {
                println!("New player outside of map!");
                return None;
            }

            let pos = Vec3 {
                x: x as f32 + 0.5,
                y: y as f32 + 0.5,
                z: 0.,
            };
            let rot = Vec3::new(0., 0., parent.orientation.as_radian());

            let number_color = generate_color_from_string(&format!("{number}"));
            let mut team_color = Vec3::default();
            for (current_name, current_color) in teams {
                if current_name == &parent.team_name {
                    team_color = current_color.clone();
                }
            }
            return Some(Tantorian {
                team_name: parent.team_name.clone(),
                number,
                pos,
                color: team_color.lerp(number_color, 0.2),
                level: parent.level,
                orientation: parent.orientation,
                last_orientation: parent.orientation,
                rotation: rot,
                mesh_descriptor: 0,
                current_tile: Vec2::new(x as f32, y as f32),
                last_tile: Vec2::new(x as f32, y as f32),
                start_movement: None,
                state: Egg,
                food: 0,
                parent: Some(parent_number),
                linemate: 0,
                deraumere: 0,
                sibur: 0,
                mendiane: 0,
                phiras: 0,
                thystame: 0,
                laying: None,
            })
        }
        println!("Parent player not found");
        None
    }

    pub fn new_from_command(number: i64, x: usize, y: usize, orientation: Orientation, level : u32, team_name: String, teams: &Vec<(String, Vec3)>, map_size: &[usize; 2], players: &mut HashMap<i64, Tantorian>) -> Option<Tantorian> {
        if !teams.iter().any(|(name, _color)| *name == team_name) {
            println!("New player team name does not exist!");
            return None;
        }
        if x >= map_size[0] || y >= map_size[1] {
            println!("New player outside of map!");
            return None;
        }
        if level > 8 {
            println!("New player too high level!");
            return None;
        }
        let pos = Vec3 {
            x: x as f32 + 0.5,
            y: y as f32 + 0.5,
            z: 0.0,
        };
        let rot = Vec3::new(0., 0., orientation.as_radian());
        for (idx, player) in players {
            if player.team_name == team_name && player.number == number && player.state == Alive {
                println!("New player number already attributed!");
                return None;
            } else if player.team_name == team_name && player.number == number {
                player.team_name = team_name;
                player.number = number;
                player.pos = pos;
                player.rotation = rot;
                player.color = player.color;
                player.level = level;
                player.orientation = orientation;
                player.last_orientation = orientation;
                player.mesh_descriptor = 0;
                player.current_tile = Vec2::new(x as f32, y as f32);
                player.last_tile = Vec2::new(x as f32, y as f32);
                player.start_movement = None;
                player.laying = None;
                player.state = Alive;
                player.food = 0;
                player.linemate = 0;
                player.parent = None;
                player.deraumere = 0;
                player.sibur = 0;
                player.mendiane = 0;
                player.phiras = 0;
                player.thystame = 0;
                return None;
            }
        }

        let number_color = generate_color_from_string(&format!("{number}"));
        let mut team_color = Vec3::default();
        for (current_name, current_color) in teams {
            if current_name == &team_name {
                team_color = current_color.clone();
            }
        }
        Some(Tantorian {
            team_name,
            number,
            pos,
            color: team_color.lerp(number_color, 0.2),
            level,
            orientation,
            last_orientation: orientation,
            rotation: rot,
            mesh_descriptor: 0,
            current_tile: Vec2::new(x as f32, y as f32),
            last_tile: Vec2::new(x as f32, y as f32),
            start_movement: None,
            state: Alive,
            food: 0,
            parent: None,
            linemate: 0,
            deraumere: 0,
            sibur: 0,
            mendiane: 0,
            phiras: 0,
            thystame: 0,
            laying: None,
        })
    }
}
