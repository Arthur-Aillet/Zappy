use crate::{Vertex, Normal};
use crate::obj_parser::Triangle;

#[derive(Clone)]
struct vert_binding {
    pub idx : usize,
    pub vp : usize,
    pub nm : usize,
    pub uv : usize,
}

fn binding_find(binding : & mut Vec<Vec<vert_binding>>, idx : usize, vp : usize, uv : usize, nm : usize) -> (bool, usize) {
    for corner in &binding[vp] {
        if corner.uv == uv && corner.nm == nm {
            return (true, corner.idx);
        }
    }

    binding[vp].push(vert_binding{
        idx,
        vp,
        nm,
        uv,
    });

    (false, idx)
}

 pub(crate) fn solve_indices(pos : &Vec<Vertex>, uvs : &Vec<Vertex>, normals : &Vec<Normal>, faces : &Vec<Triangle>) -> (Vec<Vertex>, Vec<Vertex>, Vec<Normal>, Vec<usize>) {
    let mut out_vp : Vec<Vertex> = Vec::new();
    let mut out_nm : Vec<Normal> = Vec::new();
    let mut out_uv : Vec<Vertex> = Vec::new();
    let mut binding : Vec<Vec<vert_binding>> = vec![Vec::new(); pos.len()];

    let mut out_faces : Vec<usize> = Vec::new();

    let mut counter = 0;

    for face in faces {
        for i in 0..3 {
            let (found, idx) = binding_find(&mut binding, counter,face.points[i], face.textures.unwrap_or([0; 3])[i], face.normals.unwrap_or([0; 3])[i]);
            if !found {
                counter += 1;
                out_vp.push(pos[face.points[i]]);
                out_uv.push(uvs[face.textures.unwrap_or([0; 3])[i]]);
                out_nm.push(normals[face.normals.unwrap_or([0; 3])[i]]);
            }
            out_faces.push(idx);
        }
    }

    (out_vp, out_uv, out_nm, out_faces)
}