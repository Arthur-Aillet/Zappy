use rend_ox::app::App;
use rend_ox::{Vec3, Mat4};
use rend_ox::mesh::MeshDescriptor;
use rend_ox::wgpu::Color;
use crate::interpreter::{create_hash_function, ServerFunction};
use std::collections::HashMap;
use rend_ox::nannou_egui::egui::CtxRef;
use std::cmp::{max, min};
use rend_ox::material::MaterialDescriptor;

use crate::map::Map;
pub use crate::server::ServerConn;
use crate::tantorian::Tantorian;
use crate::ui::ZappyUi;

pub struct Zappy {
    pub(crate) map: Map,
    pub(crate) players: Vec<Tantorian>,
    pub(crate) team_names: Vec<String>,
    pub(crate) server: Option<ServerConn>,
    pub(crate) ui: ZappyUi,
    pub(crate) tantorian_mesh: Option<MeshDescriptor>,
    pub(crate) functions: HashMap<String, ServerFunction>,
    pub(crate) time_unit: f32,
}

fn hsv_to_rgb(source: Vec3) -> Vec3
{
    let mut r = ((source.x) * 1. * std::f32::consts::PI).cos();
    let mut g = ((source.x - (1. / 3.)) * 1. * std::f32::consts::PI).cos();
    let mut b = ((source.x - (2. / 3.)) * 1. * std::f32::consts::PI).cos();

    // r = source.y * r + source.y - 1.;
    // g = source.y * g + source.y - 1.;
    // b = source.y * b + source.y - 1.;

    r = source.z * r;
    g = source.z * g;
    b = source.z * b;

    // ((source.x) * 2. * std::f32::consts::PI).cos();
    // ((source.x - (1. / 3.)) * 2. * std::f32::consts::PI).cos();
    // ((source.x - (2. / 3.)) * 2. * std::f32::consts::PI).cos();


    Vec3::new(r, g, b)
}

fn hsv2rgb(source: Vec3) -> Vec3/* h,s,v) */ {
    let mut r = ((((source.x + (3. / 3.)) % 1.) * 2. - 1.).abs() * 3. - 1.).clamp(0., 1.);
    let mut g = ((((source.x + (5. / 3.)) % 1.) * 2. - 1.).abs() * 3. - 1.).clamp(0., 1.);
    let mut b = ((((source.x + (4. / 3.)) % 1.) * 2. - 1.).abs() * 3. - 1.).clamp(0., 1.);

    r = source.y * r + 1. - source.y;
    g = source.y * g + 1. - source.y;
    b = source.y * b + 1. - source.y;

    r = source.z * r;
    g = source.z * g;
    b = source.z * b;

    Vec3::new(r, g, b)
}

impl Zappy {
    pub fn new() -> Zappy {
        Zappy {
            map: Map::new(0, 0),
            players: vec![],
            team_names: vec![],
            server: None, //ServerConn::new(),
            ui: ZappyUi::new(),
            tantorian_mesh: None,
            functions: create_hash_function(),
            time_unit: 100.,
        }
    }
    pub fn load(app: &mut App<Zappy>) {
        app.user.map.resize(8, 8);
        if let Ok(mut md) = app.load_mesh("./obj/plane.obj") {
            let mut mat = MaterialDescriptor::new();
            mat.shader = Some("./src/shaders/map.wgsl".into());
            mat.maps.push("./textures/happy-tree.png".into());
            if let Ok(material) = app.load_material(mat) {
            // if let Ok(shader) = app.load_shader("./src/shaders/map.wgsl") {
                app.bind_material_to_mesh(&mut md, &material);
            }
            app.user.map.mesh = Some(md);
        }
        if let Ok(mut md) = app.load_mesh("./obj/rock.obj") {
            app.user.map.rock_mesh = Some(md);
        }
        if let Ok(md) = app.load_mesh("./obj/batgnome.obj") {
            println!("Zappy: loaded bat.obj");
            app.user.tantorian_mesh = Some(md);
        } else {
            println!("Zappy: couldn't load bat.obj");
        }

        // TODO : Allow skipping this in order to test things offline
        app.user.server = Some(ServerConn::new());

        // TODO : Remove this default population
        let player_count = 16;
        for i in 0..player_count {
            let mut t = Tantorian::new();
            t.pos = Vec3::new(0., i as f32, 0.);
            t.color = hsv2rgb(Vec3::new(i as f32 / (player_count as f32), 0.9, 0.7));
            app.user.players.push(t);
            app.user.map.spawn_resource(i * 8654 % 8, i * 865 % 8, i);
        }
    }

    pub fn render(app: &mut App<Zappy>) {
        if let Some(mesh) = &app.user.tantorian_mesh {
            let mat = Mat4::from_rotation_x(std::f32::consts::PI * 0.5);
            let instances : Vec<Mat4> = app.user.players.iter().map(|p| Mat4::from_translation(p.pos + Vec3::new(0., 0., 2.)) * mat).collect();
            let colors : Vec<Vec3> = app.user.players.iter().map(|p| p.color).collect();
            app.draw_instances(mesh, instances.clone(), colors.clone());
        }
        Map::render(app);
    }
}

pub(crate) fn zappy_update(
    nannou_app: &rend_ox::nannou::App,
    zappy: &mut App<Zappy>,
    update: rend_ox::nannou::event::Update,
    ctx: CtxRef
) {
    rend_ox::camera_controller::default_camera(nannou_app, zappy, &update);

    Zappy::render(zappy);
    zappy.user.interpret_commands();
    zappy.user.ui.ctx = Some(ctx);
    zappy
        .user
        .ui
        .settings(&mut zappy.camera, zappy.camera_is_active);
    zappy
        .user
        .ui
        .players(&zappy.user.players, &zappy.user.team_names, zappy.camera_is_active);
    if let Some(server) = &zappy.user.server {
        zappy
            .user
            .ui
            .communications(zappy.camera_is_active, &server.commands.lock().expect("Lock poisoned"));
        zappy.user.ui.tiles(&zappy.user.map, zappy.camera_is_active);
    }
}
