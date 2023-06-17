use rend_ox::glam::UVec2;
use rend_ox::Vec3;

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
}


pub struct Tantorian {
    pub team_name: String,
    pub number: i64,
    pub pos: Vec3,
    pub color: Vec3,
    pub current_tile: UVec2,
    pub level: u32,
    pub orientation: Orientation,
    pub mesh_descriptor: u32,
}

impl Tantorian {
    pub fn new() -> Tantorian {
        Tantorian {
            team_name: "".to_string(),
            number: 0,
            pos: Vec3::new(0., 0., 0.),
            color: Vec3::new(1., 1., 1.),
            level: 0,
            orientation: Orientation::N,
            mesh_descriptor: 0,
            current_tile: UVec2::new(0, 0),
        }
    }

    pub fn new_from_command(number: i64, x: usize, y: usize, orientation: Orientation, level : u32, team_name: String, teams: &Vec<String>, map_size: &[usize; 2], players: &Vec<Tantorian>) -> Option<Tantorian> {
        if !teams.contains(&team_name) {
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
        for player in players {
            if player.team_name == team_name && player.number == number {
                println!("New player number already attributed!");
                return None;
            }
        }
        Some(Tantorian {
            team_name,
            number,
            pos: Vec3::new(x as f32, y as f32, 0.),
            color: Vec3::new(1., 1., 1.),
            level,
            orientation,
            mesh_descriptor: 0,
            current_tile: UVec2::new(x as u32, y as u32),
        })
    }

    // pub fn update(&mut self, server: &mut ServerConn) {}

    // pub fn draw(&self, &mut app: &mut App) {
    //     app.draw(self.mesh_descriptor, rend_ox::glam::Mat4::from_translation(self.pos.into()));
    // }
}
