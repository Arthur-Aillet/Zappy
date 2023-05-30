//
// EPITECH PROJECT, 2023
// Zappy_gui
// File description:
// mesh parser
//

use std::fs::OpenOptions;
use std::io::{BufRead, BufReader};
use std::num::ParseIntError;
use nannou::geom::Tri;
use nannou::winit::platform::unix::x11::ffi::False;
use crate::{Vertex, Normal};
use serde::{Deserialize, Serialize};
use erased_serde::serialize_trait_object;

struct Triangle {
    points: (Vertex, Vertex, Vertex),
    normals: (Vertex, Vertex, Vertex),
    textures: (Vertex, Vertex, Vertex),
}

impl Triangle {
    fn new() -> Triangle {
        Triangle {
            points: (Vertex {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }, Vertex {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }, Vertex {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }),
            normals: (Vertex {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }, Vertex {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }, Vertex {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }),
            textures: (Vertex {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }, Vertex {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }, Vertex {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }),
        }
    }
}

struct Mesh {
    triangles : Vec<Triangle>,
    normals : Vec<Normal>,
    vertices : Vec<Vertex>,
    indices : Vec<u16>,
}

impl Mesh {
    fn parse_face_point(&mut self, point : String) -> Option<(Vertex, Option<Vertex>, Option<Vertex>)> {
        let mut iter = &mut point.split('/');
        let mut position = Vertex{x: 0., y: 0.,z: 0.};
        let mut normal = Some(Option{x: 0., y: 0.,z: 0.});
        let mut texture = None;

        if iter.count() != 3 {
            return none;
        }
        for (i, item) in iter.enumerate() {
            match i {
                i if i == 0 => {
                    match item.parse::<u16>() {
                        Ok(x) => {
                            if self.verticies.size() < x {
                                position = self.vertices[x]
                            } else {
                                return None
                            }
                        }
                        Err(_) => { return none }
                    }
                },
                i if i == 1 => { continue; },
                i if i == 2 => {
                    if item.is_empty() {
                        normal = None;
                        continue
                    }
                    match item.parse::<u16>() {
                        Ok(x) => {
                            if self.normals.size() < x {
                                normal = self.normals[x]
                            } else {
                                return None
                            }
                        }
                        Err(_) => { return none }
                    }
                },
                _ => { return none}
            }
        }
        return Some((position, None, normal));
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
        let fst_triangle = Triangle::new();
        for i in 0..3 {
            match parse_face_point(points[i]) {
                Some(point) => {
                    fst_triangle.points[i] = point.0;
                    fst_triangle.points[i] = point.1;
                    fst_triangle.points[i] = point.2;
                },
                None => { return false }
            }
        }
        self.triangles.push(fst_triangle);
        if len == 4 {
            return true
        }
        return true
    }

    pub fn parse_vertex(&mut self, line: String) -> Option<Vertex> {
        let mut new_vertex: Vertex = Vertex { x: 0.0, y: 0.0, z: 0.0, };
        let mut iter = line.split_ascii_whitespace().filter(|&x| !x.is_empty());

        iter.next();
        for coord in [&mut new_vertex.x, &mut new_vertex.y, &mut new_vertex.z].iter_mut() {
            if let Some(point) = iter.next() {
                if let Ok(point) = (point).parse::<f64>() {
                    **coord = point as f32;
                } else {
                    return None;
                };
            } else {
                return None;
            }
        }
        Some(new_vertex)
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
                        s if s.starts_with("vn ") => { continue; }
                        s if s.starts_with("vt ") => { continue; }
                        s if s.starts_with("s ") => { continue; }
                        s if s.starts_with("v ") => {
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
                        s if s.starts_with("mtllib ") => { continue; }
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