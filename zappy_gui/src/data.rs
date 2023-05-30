use crate::{Normal, Vertex};

pub const NORMALS: [Normal; 3] = [
    Normal {
        x: 0.0,
        y: 0.0,
        z: 0.0
    }, // dummy vector because in the original model indices
    // start at 1
    Normal {
        x: 0.0,
        y: 0.0,
        z: 1.0
    },
    Normal {
        x: 0.0,
        y: 0.0,
        z: 1.0
    },
];


pub const VERTICES: [Vertex; 5] = [
    Vertex {
        x: 0.,
        y: 0.,
        z: 0.
    }, // dummy vector because in the original model indices
    // start at 1
    Vertex {
        x: -1.,
        y: -1.,
        z: 0.
    },
    Vertex {
        x: -1.,
        y: 1.,
        z: 0.,
    },
    Vertex {
        x: 1.,
        y: -1.,
        z: 0.
    },
    Vertex {
        x: 1.,
        y: 1.,
        z: 0.
    }
];

pub const INDICES: [u16; 6] = [
    1, 2, 3, 2, 3, 4u16
];