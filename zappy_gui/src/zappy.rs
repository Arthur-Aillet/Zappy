use std::sync::{Arc, Mutex};
use rend_ox::app::App;
use rend_ox::{Vec3, Mat4};
use rend_ox::mesh::MeshDescriptor;
use crate::interpreter::{create_hash_function, ServerFunction};
use std::collections::HashMap;

use crate::map::Map;
pub use crate::server::ServerConn;
use crate::tantorian::Tantorian;
use crate::ui::ZappyUi;

pub struct Zappy {
    pub(crate) map: Map,
    pub(crate) players: Vec<Tantorian>,
    pub(crate) server: Option<ServerConn>,
    pub(crate) ui: ZappyUi,
    pub(crate) tantorian_mesh: Option<MeshDescriptor>,
    pub(crate) functions: HashMap<String, ServerFunction>,
}

impl Zappy {
    pub fn new() -> Zappy {
        Zappy {
            map: Map::new(),
            players: vec![],
            server: None, //ServerConn::new(),
            ui: ZappyUi::new(),
            tantorian_mesh: None,
            functions: create_hash_function(),
        }
    }
    pub fn load(app: &mut App<Zappy>) {
        if let Ok(mut graphics) = app.graphics.try_borrow_mut() {
            if let Ok(md) = graphics.load_mesh("./.objs/plane.obj") {
                app.user.map.mesh = Some(md);
            }
            if let Ok(md) = graphics.load_mesh("./.objs/bat.obj") {
                println!("Zappy: loaded bat.obj");
                app.user.tantorian_mesh = Some(md);
            } else {
                println!("Zappy: couldn't load bat.obj");
            }
        }

        // TODO : Allow skipping this in order to test things offline
        app.user.server = Some(ServerConn::new());

        // TODO : Remove this default population
        for i in 0..4 {
            let mut t = Tantorian::new();
            t.pos = Vec3::new(0., i as f32, 0.);
            app.user.players.push(t);
        }
    }
    pub fn render(app: &mut App<Zappy>) {
        if let Some(mesh) = &app.user.map.mesh {
            app.draw_instances(mesh, vec![Mat4::from_scale(Vec3::new(app.user.map.size[0] as f32, app.user.map.size[1] as f32, 1.0))]);
        }
        if let Some(mesh) = &app.user.tantorian_mesh {
            let mat = Mat4::from_scale(Vec3::new(1., 1., 0.75)) * Mat4::from_rotation_x(std::f32::consts::PI * 0.5);
            let instances : Vec<Mat4> = app.user.players.iter().map(|p| Mat4::from_translation(p.pos + Vec3::new(0., 0., 2.)) * mat).collect();
            app.draw_instances(mesh, instances);
        }
    }
}

pub(crate) fn zappy_update(
    _nannou_app: &rend_ox::nannou::App,
    zappy: &mut App<Zappy>,
    update: rend_ox::nannou::event::Update,
) {
    Zappy::render(zappy);
    zappy.user.interpret_commands();
    zappy.egui_instance.set_elapsed_time(update.since_start);
    zappy.user.ui.ctx = Some(zappy.egui_instance.begin_frame().context());
    zappy
        .user
        .ui
        .settings(&mut zappy.camera, zappy.camera_is_active);
    zappy
        .user
        .ui
        .players(&zappy.user.players, zappy.camera_is_active);
    if let Some(server) = &zappy.user.server {
        zappy
            .user
            .ui
            .communications(zappy.camera_is_active, &server.commands.lock().expect("Lock poisoned"));
        zappy.user.ui.tiles(&zappy.user.map, zappy.camera_is_active);
    }
}
