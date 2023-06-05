// use nannou::prelude::*;
use nannou::winit;
use nannou::wgpu;

use nannou::Frame;
use nannou::time::DurationF64;
use nannou::event::Update;
use nannou::event::Key;
use nannou::event::Event;
use nannou::math::Mat4LookTo;

use glam::Mat4;
use glam::Vec3;
use glam::UVec2;
use glam::Vec3A;

use wgpu::util::DeviceExt;

use std::cell::RefCell;
use std::convert::Infallible;
use std::ops::{Index, Sub};

use rend_ox::obj::{Mesh, Vertices, Indices, Normals};

struct Model {
    camera_is_active: bool,
    graphics: RefCell<Graphics>,
    camera: rend_ox::camera::Camera,
    mesh: Mesh,
    buffers: (Indices, Vertices, Vertices, Normals),
}

struct Graphics {
    vertex_buffer: wgpu::Buffer,
    uv_buffer: wgpu::Buffer,
    normal_buffer: wgpu::Buffer,
    index_buffer: wgpu::Buffer,
    uniform_buffer: wgpu::Buffer,
    depth_texture: wgpu::Texture,
    depth_texture_view: wgpu::TextureView,
    bind_group: wgpu::BindGroup,
    render_pipeline: wgpu::RenderPipeline,
}

#[repr(C)]
#[derive(Copy, Clone, Debug)]
pub struct Uniforms {
    world: glam::Mat4,
    view: glam::Mat4,
    proj: glam::Mat4,
}

fn main() {
    nannou::app(model).event(event).update(update).run();
}

fn model(app: &nannou::App) -> Model {
    match create_model(app) {
        Ok(model) => model,
        Err(err) => {
            eprintln!("Failed to create Model: {err}");
            std::process::exit(84)
        }
    }
}

fn create_model(app: &nannou::App) -> Result<Model, Box<dyn std::error::Error>> {
    let w_id = match app
        .new_window()
        .size(1024, 576)
        .key_pressed(key_pressed)
        .view(view)
        .build() {
            Ok(val) => val,
            Err(err) => { return Err(Box::new(rend_ox::error::RendError::new("Window Builder failed"))) }
    };

    let window = match app.window(w_id) {
        None => return Err(Box::new(rend_ox::error::RendError::new("Invalid window id found"))),
        Some(val) => val,
    };
    let camera_is_active = true;
    match window.set_cursor_grab(true) {
        Err(error) => return Err(Box::new(rend_ox::error::RendError::new("Cursor can't be grabbed"))),
        _ => {}
    }
    window.set_cursor_visible(false);
    let device = window.device();
    let format = Frame::TEXTURE_FORMAT;
    let msaa_samples = window.msaa_samples();
    let window_size : glam::UVec2 = window.inner_size_pixels().into();

    let vs_desc = wgpu::include_wgsl!("shaders/vs.wgsl");
    let fs_desc = wgpu::include_wgsl!("shaders/fs.wgsl");
    let vs_mod = device.create_shader_module(&vs_desc);
    let fs_mod = device.create_shader_module(&fs_desc);

    let mut mesh: Mesh = Mesh::new();
    let status = mesh.parse_obj("./.objs/bat.obj");

    let buffers = mesh.as_buffers();

    let indices_bytes = indices_as_bytes_copy(&buffers.0);
    let vertices_bytes = vertices_as_bytes_copy(&buffers.1);
    let uvs_bytes = vertices_as_bytes_copy(&buffers.2);
    let normals_bytes = vertices_as_bytes_copy(&buffers.3);


    let vertex_usage = wgpu::BufferUsages::VERTEX;
    let index_usage = wgpu::BufferUsages::INDEX;
    let vertex_buffer = device.create_buffer_init(&wgpu::BufferInitDescriptor {
        label: None,
        contents: &*vertices_bytes,
        usage: vertex_usage,
    });
    let uv_buffer = device.create_buffer_init(&wgpu::BufferInitDescriptor {
        label: None,
        contents: &*uvs_bytes,
        usage: vertex_usage,
    });
    let normal_buffer = device.create_buffer_init(&wgpu::BufferInitDescriptor {
        label: None,
        contents: &*normals_bytes,
        usage: vertex_usage,
    });
    let index_buffer = device.create_buffer_init(&wgpu::BufferInitDescriptor {
        label: None,
        contents: &*indices_bytes,
        usage: index_usage,
    });

    let camera = rend_ox::camera::Camera::new();

    let depth_texture = wgpu::TextureBuilder::new()
        .size([window_size.x , window_size.y])
        .format(wgpu::TextureFormat::Depth32Float)
        .usage(wgpu::TextureUsages::RENDER_ATTACHMENT)
        .sample_count(msaa_samples)
        .build(device);

    let depth_texture_view = depth_texture.view().build();

    let uniforms = create_uniforms(window_size, camera.calc_view_matrix());
    let uniforms_bytes = uniforms_as_bytes(&uniforms);
    let usage = wgpu::BufferUsages::UNIFORM | wgpu::BufferUsages::COPY_DST;
    let uniform_buffer = device.create_buffer_init(&wgpu::BufferInitDescriptor {
        label: None,
        contents: uniforms_bytes,
        usage,
    });

    let bind_group_layout = create_bind_group_layout(device);
    let bind_group = create_bind_group(device, &bind_group_layout, &uniform_buffer);
    let pipeline_layout = create_pipeline_layout(device, &bind_group_layout);
    let render_pipeline = create_render_pipeline(
        device,
        &pipeline_layout,
        &vs_mod,
        &fs_mod,
        format,
        wgpu::TextureFormat::Depth32Float,
        msaa_samples,
    );

    let graphics = RefCell::new(Graphics{
        vertex_buffer,
        uv_buffer,
        normal_buffer,
        index_buffer,
        uniform_buffer,
        depth_texture,
        depth_texture_view,
        bind_group,
        render_pipeline,
    });

    println!("Use the `W`, `A`, `S`, `D`, `Q` and `E` keys to move the camera.");
    println!("Use the mouse to orient the pitch and yaw of the camera.");
    println!("Press the `Space` key to toggle camera mode.");

    Ok(Model {
        camera_is_active,
        graphics,
        camera,
        mesh,
        buffers,
    })
}

// Move the camera based on the current key pressed and its current direction.
fn update(app: &nannou::App, model: &mut Model, update: Update) {
    const CAM_SPEED_HZ: f64 = 0.1;

    if model.camera_is_active {
        let velocity = (update.since_last.secs() * CAM_SPEED_HZ) as f32;

        if app.keys.down.contains(&Key::Z) {
            model.camera.move_forward(velocity);
        }

        if app.keys.down.contains(&Key::S) {
            model.camera.move_forward(-velocity);
        }

        if app.keys.down.contains(&Key::Q) {
            model.camera.move_right(-velocity)
        }

        if app.keys.down.contains(&Key::D) {
            model.camera.move_right(velocity)
        }

        if app.keys.down.contains(&Key::A) {
            model.camera.move_up(-velocity)
        }

        if app.keys.down.contains(&Key::E) {
            model.camera.move_up(velocity)
        }
    }
}

// Use raw device motion event for camera pitch and yaw.
// TODO: Check device ID for mouse here - not sure if possible with winit currently.
fn event(_app: &nannou::App, model: &mut Model, event: nannou::Event) {
    if model.camera_is_active {
        if let Event::DeviceEvent(_device_id, event) = event {
            if let winit::event::DeviceEvent::Motion { axis, value } = event {
                let sensitivity = 0.004;
                match axis {
                    // Yaw left and right on mouse x axis movement.
                    0 => model.camera.yaw -= (value * sensitivity) as f32,
                    // Pitch up and down on mouse y axis movement.
                    _ => {
                        let max_pitch = std::f32::consts::PI * 0.5 - 0.0001;
                        let min_pitch = -max_pitch;
                        model.camera.pitch = (model.camera.pitch + (-value * sensitivity) as f32)
                            .min(max_pitch)
                            .max(min_pitch)
                    }
                }
            } else if let winit::event::DeviceEvent::MouseMotion { delta } = event {
                let sensitivity = 0.004;
                model.camera.yaw -= (delta.0 * sensitivity) as f32;
                let max_pitch = std::f32::consts::PI * 0.5 - 0.0001;
                let min_pitch = -max_pitch;
                model.camera.pitch = (model.camera.pitch + (-delta.1 * sensitivity) as f32)
                    .min(max_pitch)
                    .max(min_pitch);
            }
        }
    }
}

// Toggle cursor grabbing and hiding on Space key.
fn key_pressed(app: &nannou::App, model: &mut Model, key: Key) {
    if let Key::Space = key {
        let window = app.main_window();
        if !model.camera_is_active {
            if window.set_cursor_grab(true).is_ok() {
                model.camera_is_active = true;
            }
        } else {
            if window.set_cursor_grab(false).is_ok() {
                model.camera_is_active = false;
            }
        }
        window.set_cursor_visible(!model.camera_is_active);
    }
}

fn view(_app: &nannou::App, model: &Model, frame: Frame) {
    let mut g = model.graphics.borrow_mut();

    // If the window has changed size, recreate our depth texture to match.
    let depth_size = g.depth_texture.size();
    let device = frame.device_queue_pair().device();
    let frame_size = frame.texture_size();
    if frame_size != depth_size {
        let sample_count = frame.texture_msaa_samples();
        g.depth_texture = wgpu::TextureBuilder::new()
            .size(frame_size)
            .format(g.depth_texture.format())
            .usage(wgpu::TextureUsages::RENDER_ATTACHMENT)
            .sample_count(sample_count)
            .build(device);
        g.depth_texture_view = g.depth_texture.view().build();
    }

    // Update the uniforms (rotate around the teapot).
    let uniforms = create_uniforms(frame_size.into(), model.camera.calc_view_matrix().into());
    let uniforms_size = std::mem::size_of::<Uniforms>() as wgpu::BufferAddress;
    let uniforms_bytes = uniforms_as_bytes(&uniforms);
    let usage = wgpu::BufferUsages::COPY_SRC;
    let new_uniform_buffer = device.create_buffer_init(&wgpu::BufferInitDescriptor {
        label: None,
        contents: uniforms_bytes,
        usage,
    });

    let mut encoder = frame.command_encoder();
    encoder.copy_buffer_to_buffer(&new_uniform_buffer, 0, &g.uniform_buffer, 0, uniforms_size);
    let mut render_pass = wgpu::RenderPassBuilder::new()
        .color_attachment(frame.texture_view(), |color| color)
        // We'll use a depth texture to assist with the order of rendering fragments based on depth.
        .depth_stencil_attachment(&g.depth_texture_view, |depth| depth)
        .begin(&mut encoder);
    render_pass.set_bind_group(0, &g.bind_group, &[]);
    render_pass.set_pipeline(&g.render_pipeline);
    render_pass.set_index_buffer(g.index_buffer.slice(..), wgpu::IndexFormat::Uint16);
    render_pass.set_vertex_buffer(0, g.vertex_buffer.slice(..));
    render_pass.set_vertex_buffer(1, g.uv_buffer.slice(..));
    render_pass.set_vertex_buffer(2, g.normal_buffer.slice(..));
    render_pass.draw_indexed( 0..model.buffers.0.len() as u32, 0, 0..1);
}

fn create_uniforms(size: UVec2, view: glam::Mat4) -> Uniforms {
    let rotation = glam::Mat4::from_rotation_y(0f32);
    let aspect_ratio = size.x as f32 / size.y as f32;
    let fov_y = std::f32::consts::FRAC_PI_2;
    let near = 0.0001;
    let far = 100.0;
    let proj = glam::Mat4::perspective_rh_gl(fov_y, aspect_ratio, near, far);
    let scale = glam::Mat4::from_scale(Vec3::splat(0.01));
    Uniforms {
        world: rotation,
        view: (view * scale).into(),
        proj: proj.into(),
    }
}

fn create_bind_group_layout(device: &wgpu::Device) -> wgpu::BindGroupLayout {
    wgpu::BindGroupLayoutBuilder::new()
        .uniform_buffer(wgpu::ShaderStages::VERTEX, false)
        .build(device)
}

fn create_bind_group(
    device: &wgpu::Device,
    layout: &wgpu::BindGroupLayout,
    uniform_buffer: &wgpu::Buffer,
) -> wgpu::BindGroup {
    wgpu::BindGroupBuilder::new()
        .buffer::<Uniforms>(uniform_buffer, 0..1)
        .build(device, layout)
}

fn create_pipeline_layout(
    device: &wgpu::Device,
    bind_group_layout: &wgpu::BindGroupLayout,
) -> wgpu::PipelineLayout {
    let desc = wgpu::PipelineLayoutDescriptor {
        label: None,
        bind_group_layouts: &[&bind_group_layout],
        push_constant_ranges: &[],
    };
    device.create_pipeline_layout(&desc)
}

fn create_render_pipeline(
    device: &wgpu::Device,
    layout: &wgpu::PipelineLayout,
    vs_mod: &wgpu::ShaderModule,
    fs_mod: &wgpu::ShaderModule,
    dst_format: wgpu::TextureFormat,
    depth_format: wgpu::TextureFormat,
    sample_count: u32,
) -> wgpu::RenderPipeline {
    wgpu::RenderPipelineBuilder::from_layout(layout, vs_mod)
        .fragment_shader(&fs_mod)
        .color_format(dst_format)
        .color_blend(wgpu::BlendComponent::REPLACE)
        .alpha_blend(wgpu::BlendComponent::REPLACE)
        .add_vertex_buffer::<glam::Vec3>(&wgpu::vertex_attr_array![0 => Float32x3])
        .add_vertex_buffer::<glam::Vec3>(&wgpu::vertex_attr_array![1 => Float32x3])
        .add_vertex_buffer::<glam::Vec3>(&wgpu::vertex_attr_array![2 => Float32x3])
        .depth_format(depth_format)
        .sample_count(sample_count)
        .build(device)
}

fn vertices_as_bytes_copy(data: &Vec<glam::Vec3A>) -> Vec<u8> {
    let mut final_bytes: Vec<u8> = vec![];
    for elem in data {
        for i in 0..3 {
            final_bytes.extend(elem.index(i).to_le_bytes());
        }
    }
    final_bytes
}

fn indices_as_bytes_copy(data: &Vec<u16>) -> Vec<u8>  {
    let mut final_bytes: Vec<u8> = vec![];
    for elem in data {
        final_bytes.push(*elem as u8);
        final_bytes.push((*elem >> 8) as u8);
    }
    final_bytes
}

fn uniforms_as_bytes(uniforms: &Uniforms) -> &[u8] {
    unsafe { wgpu::bytes::from(uniforms) }
}