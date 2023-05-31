//
// EPITECH PROJECT, 2023
// Zappy_gui
// File description:
// mesh parser
//

use std::fs::OpenOptions;
use std::io::{BufRead, BufReader};
use crate::{Vertex, Normal};

#[derive(Clone, Debug)]
struct Triangle {
    points: [usize; 3],
    normals: Option<[usize; 3]>,
    calculated_normal: Option<usize>,
    textures: Option<[usize; 3]>,
}

impl Triangle {
    fn normal_from_points(point_a: Vertex, point_b: Vertex, point_c: Vertex) -> Normal {
        (point_a - point_b).cross_product(point_a - point_c).normalize().into()
    }

    fn new() -> Triangle {
        Triangle {
            points: [0; 3],
            normals: None,
            calculated_normal: None,
            textures: None,
        }
    }
}

struct Mesh {
    triangles : Vec<Triangle>,
    normals : Vec<Normal>,
    calculated : Vec<Normal>,
    vertices : Vec<Vertex>,
    indices : Vec<u16>,
}

impl Mesh {
    fn parse_face_point(&self, point : &str) -> Option<(usize, Option<usize>, Option<usize>)> {
        let iter = &mut point.split('/');
        let mut position = 0;
        let mut normal: Option<usize> = None;
        let mut texture: Option<usize> = None;

        if let Some(str) = iter.next() {
            match str.parse::<usize>() {
                Ok(x) => {
                    if self.vertices.len() < x {
                        position = x
                    } else {
                        return None
                    }
                }
                Err(_) => { return None }
            };
        } else {
            return None
        }
        if let Some(str) = iter.next() {
        //texture
        } else {
            return None
        }
        if let Some(str) = iter.next() {
            if str.is_empty() {
                return Some((position, None, None));
            } else {
                match str.parse::<usize>() {
                    Ok(x) => {
                        if self.normals.len() < x {
                            normal = Some(x)
                        } else {
                            return None
                        }
                    }
                    Err(_) => { return None }
                }
            }
        } else {
            return None
        }
        return Some((position, texture, normal));
    }

    fn normal_from_indexes(&self, triangle: &Triangle) -> Normal {
        Triangle::normal_from_points(self.vertices[triangle.points[0]], self.vertices[triangle.points[1]], self.vertices[triangle.points[2]])
    }

    fn get_second_face(&mut self, fst_triangle: &Triangle, last_point: &str) -> Option<Triangle> {
        let mut points: [usize; 3] = [fst_triangle.points[1], fst_triangle.points[2], 0];
        let mut textures = match fst_triangle.textures {
            Some(tex ) => Some([tex[1], tex[2], 0]),
            None => None
        };
        let mut normals = match fst_triangle.textures {
            Some(nor ) => Some([nor[1], nor[2], 0]),
            None => None
        };

        if let Some(indexes) = self.parse_face_point(last_point) {
            points[2] = indexes.0;

            match indexes.1 {
                Some(index) => {
                    if let Some(ref mut point_texture) = textures {
                        point_texture[2] = index;
                    }
                }
                None => { textures = None }
            }
            match indexes.2 {
                Some(index) => {
                    if let Some(ref mut point_normal) = normals {
                        point_normal[2] = index;
                    }
                }
                None => { normals = None }
            }
        } else {
            return None
        }

        let mut snd_triangle = Triangle {
            points,
            normals,
            calculated_normal: None,
            textures,
        };
        if normals.is_none() {
            let index = self.calculated.len();
            self.calculated.push(self.normal_from_indexes(&snd_triangle));
            snd_triangle.calculated_normal = Some(index);
        }
        return Some(snd_triangle);
    }

    pub fn parse_face(&mut self, line : String, vertices : &Vec<Vertex>) -> bool {
        let points: Vec<&str> = line.split_ascii_whitespace()
            .filter(|&x| !x.is_empty())
            .skip(1)
            .collect();
        let vertices_available = vertices.len();
        let len = points.len();
        if len < 3 || len > 4 {
            return false
        }
        let mut fst_triangle = Triangle::new();
        for i in 0..3 {
            if let Some(point) =  self.parse_face_point(points[i]) {
                fst_triangle.points[i] = point.0;

                if let Some(mut texture) = fst_triangle.textures {
                    match point.1 {
                        Some(valid_point) => { texture[i] = valid_point }
                        None => {fst_triangle.textures = None}
                    }
                }
                if let Some(mut normal) = fst_triangle.normals {
                    match point.2 {
                        Some(valid_point) => { normal[i] = valid_point }
                        None => {fst_triangle.textures = None}
                    }
                }
            } else {
                return false
            }
        }
        if fst_triangle.normals.is_none() {
            let index = self.calculated.len();
            self.calculated.push(self.normal_from_indexes(&fst_triangle));
            fst_triangle.calculated_normal = Some(index);
        }
        if len == 4 {
            if let Some(snd_face) = self.get_second_face(&fst_triangle, points[4]) {
                self.triangles.push(snd_face);
            } else { return false }
        }
        self.triangles.push(fst_triangle);
        return true
    }

    pub fn parse_vertex(&mut self, line: String) -> Option<Vertex> {
        let mut new_vertex: Vertex = Vertex { x: 0.0, y: 0.0, z: 0.0, };
        let mut iter = line.split_ascii_whitespace().filter(|&x| !x.is_empty());

        iter.next();
        for coord in [new_vertex.x, new_vertex.y, new_vertex.z].iter_mut() {
            if let Some(point) = iter.next() {
                if let Ok(point) = point.parse::<f32>() {
                    *coord = point as f32;
                } else {
                    return None;
                };
            } else {
                return None;
            }
        }
        Some(new_vertex)
    }

    pub fn parse_normal(&mut self, line: String) -> Option<Normal> {
        let mut new_normal_asv = self.parse_vertex(line);
        if let Some(normal_vertex) = new_normal_asv {
            Some(normal_vertex.from().normalize())
        } else {
            None
        }
    }

    pub fn parse_obj(&mut self, file_name: &str) {
        let file = OpenOptions::new().read(true).open(file_name);

        if let Ok(obj) = file {
            let mut vertexes: Vec<Vertex> = Vec::new();

            for option_line in BufReader::new(obj).lines() {
                match option_line {
                    Err(why) => panic!("{:?}", why),
                    Ok(line) => match line {
                        s if s.chars().all(|x| x.is_ascii_whitespace()) => { continue; }
                        s if s.starts_with('#') => { continue; }
                        s if s.starts_with("o ") => { continue; }
                        s if s.starts_with("vt ") => { continue; }
                        s if s.starts_with("s ") => { continue; }
                        s if s.starts_with("mtllib ") => { continue; }
                        s if s.starts_with("v ") => {
                            if let Some(vertex) = self.parse_vertex(s) {
                                vertexes.push(vertex);
                            } else {
                                println!("Invalid vertexes in \"{}\" !", file_name);
                                return;
                            }
                        }
                        s if s.starts_with("vn ") => {
                            if let Some(vertex) = self.parse_vertex(s) {
                                vertexes.push(vertex);
                            } else {
                                println!("Invalid vertexes in \"{}\" !", file_name);
                                return;
                            }
                        }
                        s if s.starts_with("f ") => {
                            if !self.parse_face(s, &vertexes) {
                                println!("Invalid face in \"{}\" !", file_name);
                                return;
                            }
                        }
                        _ => {
                            println!("Invalid \"{}\" mesh file!", file_name);
                            return;
                        }
                    }
                }
            }
        } else {
            println!("Cant open \"{}\" mesh file!", file_name);
        }
    }
}