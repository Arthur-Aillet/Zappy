use rend_ox::mesh::MeshDescriptor;

pub struct Map {
    pub size: [usize; 2],
    pub mesh: Option<MeshDescriptor>
}

impl Map {
    pub fn new() -> Map {
        Map {
            size: [8, 8],
            mesh: None
        }
    }
}
