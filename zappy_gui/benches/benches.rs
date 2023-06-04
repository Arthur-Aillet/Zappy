use std::thread::sleep;
use zappy_gui::obj_parser::Mesh;

use criterion::{
    black_box,
    criterion_main,
    criterion_group,
    Criterion
};

fn indices_as_bytes(data: &[u16]) -> &[u8] {
    bytemuck::cast_slice(data)
}

fn indices_as_bytes_copy(data: &Vec<u16>) -> Vec<u8>  {
    let mut final_bytes: Vec<u8> = vec![];
    for elem in data {
        final_bytes.push(*elem as u8);
        final_bytes.push((*elem >> 8) as u8);
    }
    final_bytes
}

fn bench_buffer_copy(c: &mut Criterion) {
    let mut mesh: Mesh = Mesh::new();
    let status = mesh.parse_obj("./.objs/bat.obj");

    let buffers = mesh.as_buffers();


    let mut group = c.benchmark_group("buffer copy");
    group.bench_function("cast", |b| b.iter(|| indices_as_bytes(&buffers.0)));
    group.bench_function("copy", |b| b.iter(|| indices_as_bytes_copy(&buffers.0)));
    group.finish();
}

criterion_group!(benches, bench_buffer_copy);
criterion_main!(benches);
