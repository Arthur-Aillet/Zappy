use std::thread::sleep;
use rend_ox::obj::Mesh;
use nannou::wgpu;

use criterion::{
    black_box,
    criterion_main,
    criterion_group,
    Criterion
};
use glam::{Vec3A};

fn indices_as_bytes_copy(data: &Vec<u16>) -> Vec<u8>  {
    let mut final_bytes: Vec<u8> = vec![];
    for elem in data {
        final_bytes.push(*elem as u8);
        final_bytes.push((*elem >> 8) as u8);
    }
    final_bytes
}

fn vertices_as_bytes_copy(data: &Vec<glam::Vec3A>) -> Vec<u8> {
    let mut final_bytes: Vec<u8> = vec![];
    for elem in data {
        for i in 0..3 {
            final_bytes.extend(elem[i].to_le_bytes());
        }
    }
    final_bytes
}

unsafe fn nannou_indices_as_bytes(data: &[u16]) -> &[u8] {
    wgpu::bytes::from_slice(data)
}

unsafe fn nannou_vertices_as_bytes(data: &[Vec3A]) -> &[u8] {
    wgpu::bytes::from_slice(data)
}

fn bench_buffer_copy(c: &mut Criterion) {
    let mut mesh: Mesh = Mesh::new();
    let status = mesh.parse_obj("./.objs/bat.obj");

    let buffers = mesh.as_buffers();


    let mut group = c.benchmark_group("buffer copy");
    group.bench_function("cast", |b| b.iter(|| {
        unsafe { let _a = nannou_indices_as_bytes(&buffers.0); }
        unsafe { let _b = nannou_vertices_as_bytes(&buffers.1); }
        unsafe { let _c = nannou_vertices_as_bytes(&buffers.2); }
        unsafe { let _d = nannou_vertices_as_bytes(&buffers.3); }

    }));
    group.bench_function("copy", |b| b.iter(|| {
        indices_as_bytes_copy(&buffers.0);
        vertices_as_bytes_copy(&buffers.1);
        vertices_as_bytes_copy(&buffers.2);
        vertices_as_bytes_copy(&buffers.3);
    }));
    group.finish();
}

criterion_group!(benches, bench_buffer_copy);
criterion_main!(benches);
