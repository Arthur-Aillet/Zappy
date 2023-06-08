use super::zappy::ServerConn;
use super::zappy::Zappy;
use rend_ox::Vec3;

pub struct Tantorian {
    pub pos: Vec3,
    pub level: u32,
    pub orientation: u8,
    pub mesh_descriptor: u32,
}

impl Tantorian {
    pub fn new() -> Tantorian {
        Tantorian {
            pos: Vec3::new(0., 0., 0.),
            level: 0,
            orientation: 0,
            mesh_descriptor: 0,
        }
    }

    // pub fn update(&mut self, server: &mut ServerConn) {}

    // pub fn draw(&self, &mut app: &mut App) {
    //     app.draw(self.mesh_descriptor, rend_ox::glam::Mat4::from_translation(self.pos.into()));
    // }
}