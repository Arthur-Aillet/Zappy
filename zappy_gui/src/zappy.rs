use rend_ox::app::App;
use rend_ox::Vec3;
use rend_ox::mesh::MeshDescriptor;
use crate::interpreter::{create_hash_function, ServerFunction};
use std::collections::HashMap;
use std::f32::consts::PI;
use std::thread::JoinHandle;
use std::time::Duration;
use rend_ox::nannou_egui::egui::CtxRef;

use crate::map::Map;
pub use crate::server::ServerConn;
use crate::tantorian::Tantorian;
use crate::ui;
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
    pub(crate) thread_handle: Option<JoinHandle<()>>,
    pub(crate) port: String,
    pub(crate) hostname: String,
    pub(crate) auto_update: bool,
    pub(crate) refresh_factor: f32,
    pub(crate) winner_team: Option<String>,
    pub(crate) last_map_update: Duration,
    pub(crate) following: Option<(i64, String)>,
}

fn _hsv_to_rgb(source: Vec3) -> Vec3
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

fn _hsv2rgb(source: Vec3) -> Vec3/* h,s,v) */ {
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
            server: None,
            ui: ZappyUi::new(),
            tantorian_mesh: None,
            functions: create_hash_function(),
            time_unit: 100.,
            thread_handle: None,
            port: "".to_string(),
            hostname: "".to_string(),
            auto_update: false,
            refresh_factor: 1.0,
            winner_team: None,
            last_map_update: Duration::from_secs_f32(20. / 100.),
            following: None,
        }
    }

    pub fn load(app: &mut App<Zappy>) {
        app.user.map.resize(8, 8);
        if let Ok(mut graphics) = app.graphics.try_borrow_mut() {
            if let Ok(mut md) = graphics.load_mesh("./obj/plane.obj") {
                if let Ok(shader) = graphics.load_shader("./src/shaders/map.wgsl") {
                    graphics.bind_shader_to_mesh(&mut md, &shader);
                } else {
                    println!("Zappy: couldn't load map shader ");
                }
                app.user.map.mesh = Some(md);
            } else {
                println!("Zappy: couldn't load plane.obj");
            }
            if let Ok(md) = graphics.load_mesh("./obj/rock.obj") {
                app.user.map.rock_mesh = Some(md);
            } else {
                println!("Zappy: couldn't load rock.obj");
            }
            if let Ok(md) = graphics.load_mesh("./obj/batgnome.obj") {
                app.user.tantorian_mesh = Some(md);
            } else {
                println!("Zappy: couldn't load bat.obj");
            }
        }
    }

    pub fn render(app: &mut App<Zappy>) {
        let player_mesh : &MeshDescriptor;
        if let Some(mesh) = &app.user.tantorian_mesh {
            player_mesh = mesh
        } else {
            return;
        }
        {
            for player in &mut app.user.players {
                player.pos = Vec3 {
                    x: player.current_tile.x as f32 + 0.5,
                    y: player.current_tile.y as f32 + 0.5,
                    z: 0.666,
                };
            }
        }
        for player in &app.user.players {
            let rot = Vec3::new(PI/2., player.orientation.as_radian(), 0.);
            app.draw_at(player_mesh, player.color.clone(), player.pos.clone(), rot, Vec3::new(0.333, 0.333, 0.333));
        }
        Map::render(app);
    }

}
pub fn display_ui(zappy : &mut App<Zappy>, at: Duration, ctx: &CtxRef) {
    zappy.user.ui
        .settings(ctx, &mut zappy.camera, zappy.camera_is_active);
    let (action, player_number, team_name) = zappy.user.ui
        .players(ctx, &mut zappy.user.players, &zappy.user.team_names, zappy.camera_is_active);
    if action == crate::ui::PlayerAction::Follow {
        for player in &zappy.user.players {
            if player.team_name == team_name && player.number == player_number {
                zappy.user.following = Some((player_number, team_name));
                break;
            }
        }
    } else if action == crate::ui::PlayerAction::GoTo {
        zappy.user.following = None;
        look_at_player(zappy, &player_number, &team_name);
    }
    let refresh_map = zappy.user.ui.tiles(ctx, &mut zappy.user.auto_update, &mut zappy.user.refresh_factor, &zappy.user.map, zappy.camera_is_active);
    if let Some(server) = &mut zappy.user.server {
        if refresh_map {
            if server.send_to_server("mct", -1, -1) == false {
                zappy.user.close_connection(at);
                zappy.user.reset_server_data();
            }
        }
        zappy.user.ui.communications(ctx, zappy.camera_is_active);
    }
    let state = zappy.user.ui.network_status(ctx, zappy.camera_is_active, &mut zappy.user.port, &mut zappy.user.hostname, zappy.user.server.is_some());
    if state == ui::State::Connect {
        zappy.user.try_to_connect(at);
    }
    if state == ui::State::Disconnect {
        zappy.user.close_connection(at);
        zappy.user.reset_server_data();
    }
    if let Some(team) = &zappy.user.winner_team {
        zappy.user.ui.win(ctx, team, zappy.camera_is_active);
    }
}

fn ask_for_update(zappy: &mut Zappy, at: Duration) {
    if let Some(server) = &mut zappy.server {
        if zappy.auto_update == true {
            if zappy.last_map_update.as_secs_f32() + 20. / zappy.time_unit * zappy.refresh_factor < at.as_secs_f32() {
                zappy.last_map_update = at;
                if server.send_to_server("mct", -1, -1) == false {
                    zappy.close_connection(at);
                    zappy.reset_server_data();
                }
            }
        }
    }
}

fn look_at_player(model: &mut App<Zappy>, number: &i64, team_name: &String) {
    for player in &model.user.players {
        if &player.team_name == team_name && &player.number == number {
            model.camera.position = Vec3 {
                x: player.pos.x / 100.,
                y: player.pos.y / 100.,
                z: 0.04,
            };
        }
    }
}

fn following(app: &rend_ox::nannou::App, model: &mut App<Zappy>) {
    if model.user.following.is_none() {
        return;
    }
    if model.camera_is_active {
        if app.keys.down.contains(&rend_ox::nannou::event::Key::Z) {
            model.user.following = None;
        }
        if app.keys.down.contains(&rend_ox::nannou::event::Key::S) {
            model.user.following = None;
        }
        if app.keys.down.contains(&rend_ox::nannou::event::Key::Q) {
            model.user.following = None;
        }
        if app.keys.down.contains(&rend_ox::nannou::event::Key::D) {
            model.user.following = None;
        }
        if app.keys.down.contains(&rend_ox::nannou::event::Key::A) {
            model.user.following = None;
        }
        if app.keys.down.contains(&rend_ox::nannou::event::Key::E) {
            model.user.following = None;
        }
    }
    if let Some((number, team_name)) = &model.user.following {
        let player_number = number.clone();
        let player_team_name = team_name.clone();

        look_at_player(model, &player_number, &player_team_name);
    }
}

pub(crate) fn zappy_update(
    nannou_app: &rend_ox::nannou::App,
    zappy: &mut App<Zappy>,
    update: rend_ox::nannou::event::Update,
    ctx: &CtxRef
) {
    rend_ox::camera_controller::default_camera(nannou_app, zappy, &update);
    following(nannou_app, zappy);
    Zappy::render(zappy);
    zappy.user.interpret_commands(update.since_start);
    ask_for_update(&mut zappy.user, update.since_start);
    display_ui(zappy, update.since_start, ctx);
}
