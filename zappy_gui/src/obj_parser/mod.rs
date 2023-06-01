//
// EPITECH PROJECT, 2023
// Zappy_gui
// File description:
// mesh parser
//

use std::fs::OpenOptions;
use std::io::{BufRead, BufReader};
use nannou::mesh::vertices;
use crate::{Vertex, Normal};

#[derive(Clone, Debug)]
struct Triangle {
    points: [usize; 3],
    normals: Option<[usize; 3]>,
    calculated_normal: usize,
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
            calculated_normal: 0,
            textures: None,
        }
    }
}

pub struct Mesh {
    triangles : Vec<Triangle>,
    normals : Vec<Normal>,
    calculated : Vec<Normal>,
    vertices : Vertices,
}

pub type Vertices = Vec<Vertex>;
pub type Indices = Vec<u16>;
pub type Normals = Vec<Normal>;

impl Mesh {
    pub fn as_buffers(&mut self) -> (Vertices, Indices, Normals) {
        let mut indices: Indices = vec![];

        for triangle in &self.triangles {
            indices.extend(triangle.points.iter().map(|x| *x as u16));
        }
        (self.vertices.clone(), indices, self.calculated.clone())
    }

    fn parse_face_point(&self, point : &str) -> Option<(usize, Option<usize>, Option<usize>)> {
        let iter = &mut point.split('/');
        let mut position = 0;
        let mut normal: Option<usize> = None;
        let texture: Option<usize> = None;

        if let Some(str) = iter.next() {
            match str.parse::<usize>() {
                Ok(x) => {
                    if self.vertices.len() >= x && x > 0 {
                        position = x - 1
                    } else { return None }
                }
                Err(_) => { return None }
            };
        } else { return None }
        if let Some(str) = iter.next() {
        //texture
        } else { return None }
        if let Some(str) = iter.next() {
            if str.is_empty() {
                return Some((position, None, None));
            } else {
                match str.parse::<usize>() {
                    Ok(x) => {
                        if self.normals.len() >= x && x > 0 {
                            normal = Some(x - 1)
                        } else { return None }
                    }
                    Err(_) => { return None }
                }
            }
        } else { return None }
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
        } else { return None }
        let calculated_normal = self.calculated.len();
        let snd_triangle = Triangle {
            points,
            normals,
            calculated_normal,
            textures,
        };
        self.calculated.push(self.normal_from_indexes(&snd_triangle));
        Some(snd_triangle)
    }

    fn parse_face(&mut self, line : String) -> bool {
        let points: Vec<&str> = line.split_ascii_whitespace()
            .filter(|&x| !x.is_empty())
            .skip(1)
            .collect();
        let len = points.len();
        if len < 3 || len > 4 { return false }
        let mut fst_triangle = Triangle::new();
        for i in 0..3 {
            if let Some(point) = self.parse_face_point(points[i]) {
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
            } else { return false }
        }
        fst_triangle.calculated_normal = self.calculated.len();

        self.calculated.push(self.normal_from_indexes(&fst_triangle));
        if len == 4 {
            if let Some(snd_face) = self.get_second_face(&fst_triangle, points[4]) {
                self.triangles.push(snd_face);
            } else { return false }
        }
        self.triangles.push(fst_triangle);
        true
    }

    fn parse_vertex(&mut self, line: String) -> Option<Vertex> {
        let mut new_vertex: Vertex = Vertex { x: 0.0, y: 0.0, z: 0.0, };
        let mut iter = line.split_ascii_whitespace().filter(|&x| !x.is_empty());

        iter.next();
        for coord in [&mut new_vertex.x, &mut new_vertex.y, &mut new_vertex.z].iter_mut() {
            if let Some(point) = iter.next() {
                if let Ok(point) = point.parse::<f32>() {
                    **coord = point as f32;
                } else { return None };
            } else { return None }
        }
        Some(new_vertex)
    }

    fn parse_normal(&mut self, line: String) -> Option<Normal> {
        let mut new_normal_asv = self.parse_vertex(line);
        if let Some(normal_vertex) = new_normal_asv {
            Some(Normal::from(normal_vertex.normalize()))
        } else {
            None
        }
    }

    pub fn new() -> Mesh {
        Mesh {
            triangles: vec![],
            normals: vec![],
            calculated: vec![],
            vertices: vec![],
        }
    }

    pub fn parse_obj(&mut self, file_name: &str) -> bool {
        let file = OpenOptions::new().read(true).open(file_name);

        if let Ok(obj) = file {
            for option_line in BufReader::new(obj).lines() {
                match option_line {
                    Err(why) => panic!("{:?}", why),
                    Ok(line) => match line {
                        s if s.chars().all(|x| x.is_ascii_whitespace()) => { continue; }
                        s if s.starts_with('#') => { continue; }
                        s if s.starts_with("o ") => { continue; }
                        s if s.starts_with("vt ") => { continue; }
                        s if s.starts_with("s ") => { continue; }
                        s if s.starts_with("usemtl ") => { continue; }
                        s if s.starts_with("mtllib ") => { continue; }
                        s if s.starts_with("v ") => {
                            if let Some(vertex) = self.parse_vertex(s) {
                                self.vertices.push(vertex);
                            } else {
                                println!("Invalid vertexes in \"{}\" !", file_name);
                                return false;
                            }
                        }
                        s if s.starts_with("vn ") => {
                            if let Some(normal) = self.parse_normal(s) {
                                self.normals.push(normal);
                            } else {
                                println!("Invalid normal in \"{}\" !", file_name);
                                return false;
                            }
                        }
                        s if s.starts_with("f ") => {
                            if !self.parse_face(s) {
                                println!("Invalid face in \"{}\" !", file_name);
                                return false;
                            }
                        }
                        other => {
                            println!("Invalid \"{file_name}\" mesh file!, \"{other}\" string not supported");
                            return false;
                        }
                    }
                }
            }
        } else {
            println!("Cant open \"{}\" mesh file!", file_name);
        }
        true
    }
}