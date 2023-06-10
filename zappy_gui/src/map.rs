pub struct Map {
    pub size: [usize; 2],
}

impl Map {
    pub fn new() -> Map {
        Map { size: [8, 8] }
    }
}
