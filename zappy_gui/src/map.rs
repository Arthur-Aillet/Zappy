use rend_ox::mesh::MeshDescriptor;
use rend_ox::Vec3;


pub struct Map {
    pub size: [usize; 2],
    pub mesh: Option<MeshDescriptor>,
    pub color: Vec3,
}

impl Map {
    pub fn new() -> Map {
        Map {
            size: [8, 8],
            mesh: None,
            color: Vec3::new(0.2, 0.9, 0.4),
        }
    }
}
