use rend_ox::mesh::MeshDescriptor;
use rend_ox::{Mat4, Vec3};
use rend_ox::app::App;
use rend_ox::glam::Quat;
use rend_ox::nannou::rand::random_range;
use crate::zappy::Zappy;

#[derive(Clone, Debug)]
pub struct Tile {
    pub x: usize,
    pub y: usize,
    pub q0: Vec<Mat4>,
    pub q1: Vec<Mat4>,
    pub q2: Vec<Mat4>,
    pub q3: Vec<Mat4>,
    pub q4: Vec<Mat4>,
    pub q5: Vec<Mat4>,
    pub q6: Vec<Mat4>,
}

impl Tile {
    pub fn access_to_nth_resource(&mut self, q: usize) -> &mut Vec<Mat4> {
        match q {
            0 => { &mut self.q0}
            1 => { &mut self.q1}
            2 => { &mut self.q2}
            3 => { &mut self.q3}
            4 => { &mut self.q4}
            5 => { &mut self.q5}
            6 => { &mut self.q6}
            _ => { panic!("Accessed to non existing resource") }
        }
    }

    pub fn new() -> Self {
        Self {
            x: 0,
            y: 0,
            q0: vec![],
            q1: vec![],
            q2: vec![],
            q3: vec![],
            q4: vec![],
            q5: vec![],
            q6: vec![],
        }
    }

    fn spawn_resource_mat(&self) -> Mat4 {
        let s = random_range(0.8, 1.5) as f32;
        Mat4::from_scale_rotation_translation(
            Vec3::new(s, s, s),
            Quat::from_rotation_z(random_range(0., std::f32::consts::PI * 2.)),
            Vec3::new(random_range(0.1, 0.9) + self.x as f32, random_range(0.1, 0.9) + self.y as f32, 0.))
    }

    pub fn spawn_resource(&mut self, q: usize) -> bool {
        return match q {
            0 => { self.q0.push(self.spawn_resource_mat()); true}
            1 => { self.q1.push(self.spawn_resource_mat()); true}
            2 => { self.q2.push(self.spawn_resource_mat()); true}
            3 => { self.q3.push(self.spawn_resource_mat()); true}
            4 => { self.q4.push(self.spawn_resource_mat()); true}
            5 => { self.q5.push(self.spawn_resource_mat()); true}
            6 => { self.q6.push(self.spawn_resource_mat()); true}
            _ => false
        }
    }
}

pub struct Map {
    pub size: [usize; 2],
    pub mesh: Option<MeshDescriptor>,
    pub rock_mesh: Option<MeshDescriptor>,
    pub color: Vec3,
    pub tiles: Vec<Vec<Tile>>,
}

static COLORS: [Vec3; 7] = [
    Vec3::new(188. / 255., 70. / 255., 41. / 255.),
    Vec3::new(135. / 255., 211. / 255., 191. / 255.),
    Vec3::new(145. / 255., 52. / 255., 117. / 255.),
    Vec3::new(224. / 255., 214. / 255., 136. / 255.),
    Vec3::new(22. / 255., 160. / 255., 34. / 255.),
    Vec3::new(45. / 255., 123. / 255., 191. / 255.),
    Vec3::new(184. / 255., 224. / 255., 143. / 255.),
];

impl Map {
    pub fn new(x: usize, y: usize) -> Map {
        Map {
            size: [x, y],
            mesh: None,
            rock_mesh: None,
            color: Vec3::new(0.2, 0.95, 0.25),
            tiles: vec![vec![Tile::new();y]; x],
        }
    }

    pub fn resize(&mut self, x: usize, y: usize) {
        self.size[0] = x;
        self.size[1] = y;

        self.tiles = vec![vec![Tile::new();y]; x];
        for i in 0..x {
            for j in 0..y {
                self.tiles.get_mut(i).and_then(|ts| ts.get_mut(j)).and_then(|t|{t.x = i; t.y = j; Some(t)});
            }
        }
    }
    /*
    pub fn spawn_resource(&mut self, x: usize, y: usize, q: usize) -> bool {
        self.tiles.get_mut(x).and_then(|ts| ts.get_mut(y)).and_then(|t|
            if t.spawn_resource(q) { Some(t) } else { None }
        ).is_some()
    }
    */

    pub fn update_resources(&mut self, x: usize, y: usize, q: usize, n:usize) {
        let tile = &mut self.tiles[x][y];
        let resource = tile.access_to_nth_resource(q);
        let diff = n as i32 - resource.len() as i32;
        if diff > 0 {
            for _ in 0..diff {
                tile.spawn_resource(q);
            }
        } else {
            resource.truncate(n);
        }
    }


    pub fn render(app: &mut App<Zappy>) {
        let map = &app.user.map;
        if let Some(mesh) = &app.user.map.mesh {
            let mat = Mat4::from_scale(Vec3::new(app.user.map.size[0] as f32, app.user.map.size[1] as f32, 1.0));
            app.draw_instances(mesh, vec![mat], vec![app.user.map.color]);
        }
        if let Some(md) = &map.rock_mesh {
            let mut q0_mats : Vec<Mat4> = vec![];
            let mut q1_mats : Vec<Mat4> = vec![];
            let mut q2_mats : Vec<Mat4> = vec![];
            let mut q3_mats : Vec<Mat4> = vec![];
            let mut q4_mats : Vec<Mat4> = vec![];
            let mut q5_mats : Vec<Mat4> = vec![];
            let mut q6_mats : Vec<Mat4> = vec![];

            for i in 0..map.size[0] {
                for j in 0..map.size[1] {
                    map.tiles.get(i).and_then(|ts| ts.get(j)).and_then(|t| {
                        q0_mats.append(&mut t.q0.clone());
                        q1_mats.append(&mut t.q1.clone());
                        q2_mats.append(&mut t.q2.clone());
                        q3_mats.append(&mut t.q3.clone());
                        q4_mats.append(&mut t.q4.clone());
                        q5_mats.append(&mut t.q5.clone());
                        q6_mats.append(&mut t.q6.clone());
                        Some(t)
                    });
                }
            }

            app.draw_instances(&md, q0_mats, vec![COLORS[0]]);
            app.draw_instances(&md, q1_mats, vec![COLORS[1]]);
            app.draw_instances(&md, q2_mats, vec![COLORS[2]]);
            app.draw_instances(&md, q3_mats, vec![COLORS[3]]);
            app.draw_instances(&md, q4_mats, vec![COLORS[4]]);
            app.draw_instances(&md, q5_mats, vec![COLORS[5]]);
            app.draw_instances(&md, q6_mats, vec![COLORS[6]]);
        }
    }
}
