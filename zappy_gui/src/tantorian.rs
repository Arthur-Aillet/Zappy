use std::collections::hash_map::DefaultHasher;
use std::f32::consts::PI;
use rend_ox::glam::Vec2;
use rend_ox::Vec3;
use std::hash::{Hash, Hasher};
use std::time::Duration;

#[derive(Clone, Copy)]
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
            Orientation::N => 180. * PI/180.,
            Orientation::E => 270. * PI/180.,
            Orientation::S => 0.,
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
    pub alive: bool,
    pub food: u32,
    pub linemate: u32,
    pub deraumere: u32,
    pub sibur: u32,
    pub mendiane: u32,
    pub phiras: u32,
    pub thystame: u32,
}

impl Tantorian {
    /*pub fn new() -> Tantorian {
        Tantorian {
            team_name: "".to_string(),
            number: 0,
            pos: Vec3::new(0., 0., 0.),
            color: Vec3::new(1., 1., 1.),
            level: 0,
            orientation: Orientation::N,
            mesh_descriptor: 0,
            current_tile: UVec2::new(0, 0),
            alive: true,
            food: 0,
            linemate: 0,
            deraumere: 0,
            sibur: 0,
            mendiane: 0,
            phiras: 0,
            thystame: 0,
        }
    }*/

    pub fn new_from_command(number: i64, x: usize, y: usize, orientation: Orientation, level : u32, team_name: String, teams: &Vec<(String, Vec3)>, map_size: &[usize; 2], players: &mut Vec<Tantorian>) -> Option<Tantorian> {
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
            z: 0.666,
        };
        let rot = Vec3::new(PI/2., orientation.as_radian(), 0.);
        for player in players {
            if player.team_name == team_name && player.number == number && player.alive == true {
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
                player.alive = true;
                player.food = 0;
                player.linemate = 0;
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
            alive: true,
            food: 0,
            linemate: 0,
            deraumere: 0,
            sibur: 0,
            mendiane: 0,
            phiras: 0,
            thystame: 0,
        })
    }
}
