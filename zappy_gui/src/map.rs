use rend_ox::mesh::MeshDescriptor;

#[derive(Clone)]
pub struct Tile {
    pub food: usize,
    pub linemate: usize,
    pub deraumere: usize,
    pub sibur: usize,
    pub mendiane: usize,
    pub phiras: usize,
    pub thystame : usize,
}

impl Tile {
    pub fn new() -> Tile {
        Tile {
            food: 0,
            linemate: 0,
            deraumere: 0,
            sibur: 0,
            mendiane: 0,
            phiras: 0,
            thystame: 0,
        }
    }
}

pub struct Map {
    pub size: [usize; 2],
    pub tiles: Vec<Tile>,
    pub mesh: Option<MeshDescriptor>
}

impl Map {
    pub fn new() -> Map {
        Map {
            size: [8, 8],
            tiles: vec![Tile::new(); 8*8],
            mesh: None
        }
    }
}
