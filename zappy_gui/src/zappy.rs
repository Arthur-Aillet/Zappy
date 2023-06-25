use std::collections::HashMap;
use std::f32::consts::PI;
use std::mem::take;
use std::thread::JoinHandle;
use std::time::Duration;
use fork::{daemon, Fork, fork};
use std::process::{Command, exit};

use rend_ox::app::App;
use rend_ox::{Mat4, Vec3};
use rend_ox::mesh::MeshDescriptor;
use rend_ox::glam::{EulerRot, Quat, Vec2};
use rend_ox::nannou::event::Update;
use rend_ox::nannou_egui::egui::CtxRef;
use rend_ox::material::MaterialDescriptor;

use crate::message::{Arrows, Message};
use crate::interpreter::{create_hash_function, ServerFunction};
use crate::map::Map;
pub use crate::server::ServerConn;
use crate::tantorian::PlayerState::{Alive, Egg};
use crate::tantorian::Tantorian;
use crate::incantation::{Incantation, IncantationState};
use crate::ui;
use crate::ui::State::Nothing;
use crate::ui::ZappyUi;

pub struct Zappy {
    pub(crate) map: Map,
    pub(crate) players: HashMap<i64, Tantorian>,
    pub(crate) teams: Vec<(String, Vec3)>,
    pub(crate) incantations: Vec<Incantation>,
    pub(crate) server: Option<ServerConn>,
    pub(crate) ui: ZappyUi,
    pub(crate) messages: Vec<Message>,
    pub(crate) arrows: Vec<Arrows>,
    pub(crate) message_mesh: Option<MeshDescriptor>,
    pub(crate) tantorian_mesh: Option<MeshDescriptor>,
    pub(crate) egg_mesh: Option<MeshDescriptor>,
    pub(crate) arrow_mesh: Option<MeshDescriptor>,
    pub(crate) magic_mesh: Option<MeshDescriptor>,
    pub(crate) functions: HashMap<String, ServerFunction>,
    pub(crate) time_unit: f32,
    pub(crate) thread_handle: Option<JoinHandle<()>>,
    pub(crate) port: String,
    pub(crate) hostname: String,
    pub(crate) auto_update: bool,
    pub(crate) refresh_factor: f32,
    pub(crate) last_map_update: Duration,
    pub(crate) player_auto_update: bool,
    pub(crate) player_refresh_factor: f32,
    pub(crate) last_player_update: Duration,
    pub(crate) winner_team: Option<String>,
    pub(crate) following: Option<(i64, String)>,
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

fn lerp(fst: f32, snd: f32, perc: f32) -> f32{
    fst + (snd - fst) * perc
}

impl Zappy {
    pub fn new() -> Zappy {
        Zappy {
            map: Map::new(0, 0),
            players: HashMap::new(),
            teams: vec![],
            incantations: vec![],
            server: None,
            ui: ZappyUi::new(),
            messages: vec![],
            arrows: vec![],
            message_mesh: None,
            tantorian_mesh: None,
            egg_mesh: None,
            arrow_mesh: None,
            magic_mesh: None,
            functions: create_hash_function(),
            time_unit: 100.,
            thread_handle: None,
            port: "".to_string(),
            hostname: "".to_string(),
            auto_update: false,
            refresh_factor: 1.0,
            winner_team: None,
            last_map_update: Duration::from_secs_f32(20. / 100.),
            player_auto_update: false,
            player_refresh_factor: 1.0,
            last_player_update: Duration::from_secs_f32(7. / 100.),
            following: None,
        }
    }

    pub fn load(app: &mut App<Zappy>) {
        app.user.map.resize(10, 10);
        if let Ok(mut md) = app.load_mesh("./obj/plane.obj") {
            let mut mat = MaterialDescriptor::new();
            mat.shader = Some("./src/shaders/map.wgsl".into());
            mat.maps.push("./textures/green-grass.png".into());
            if let Ok(material) = app.load_material(mat) {
                // if let Ok(shader) = app.load_shader("./src/shaders/map.wgsl") {
                app.bind_material_to_mesh(&mut md, &material);
            } else {
                println!("Zappy: couldn't load map shader ");
            }
            app.user.map.mesh = Some(md);
        } else {
            println!("Zappy: couldn't load plane.obj");
        }
        if let Ok(md) = app.load_mesh("./obj/rock.obj") {
            app.user.map.rock_mesh = Some(md);
        } else {
            println!("Zappy: couldn't load rock.obj");
        }
        if let Ok(md) = app.load_mesh("./obj/batgnome.obj") {
            app.user.tantorian_mesh = Some(md);
        } else {
            println!("Zappy: couldn't load batgnome.obj");
        }
        if let Ok(md) = app.load_mesh("./obj/egg.obj") {
            app.user.egg_mesh = Some(md);
        } else {
            println!("Zappy: couldn't load egg.obj");
        }
        if let Ok(md) = app.load_mesh("./obj/message.obj") {
            app.user.message_mesh = Some(md);
        } else {
            println!("Zappy: couldn't load message.obj");
        }
        if let Ok(md) = app.load_mesh("./obj/arrow.obj") {
            app.user.arrow_mesh = Some(md);
        } else {
            println!("Zappy: couldn't load arrow.obj");
        }
        if let Ok(md) = app.load_mesh("./obj/sparkles.obj") {
            app.user.magic_mesh = Some(md);
        } else {
            println!("Zappy: couldn't load sparkles.obj");
        }
    }

    pub fn update_incantations(app: &mut App<Zappy>, update: &Update) {
        let incantations = take(&mut app.user.incantations);
        app.user.incantations = incantations.into_iter().filter(|i|i.is_remain(app.user.time_unit, update)).collect();
    }

    pub fn update_players(app: &mut App<Zappy>, update: &Update) {
        for (idx, player) in &mut app.user.players {
            if let Some(movement_start) = &player.start_movement {
                if let Some(loops) = player.laying {
                    let mut progress = update.since_start.as_secs_f32() - movement_start.as_secs_f32();
                    let modifier = 1. / (42. / app.user.time_unit);

                    if progress >= 1. / modifier {
                        progress = 1. / modifier;
                        player.start_movement = None;
                    }
                    let mut new_rot: f32 = player.orientation.as_radian();
                    new_rot = lerp(new_rot, player.orientation.as_radian() + loops * PI * 2., (progress * modifier).powi(3));
                    player.rotation = Vec3 {
                        x: 0.,
                        y: 0.,
                        z: new_rot,
                    };
                } else {
                    let mut progress = update.since_start.as_secs_f32() - movement_start.as_secs_f32();
                    let modifier = 1. / (7. / app.user.time_unit);

                    if progress >= 1. / modifier {
                        progress = 1. / modifier;
                        player.start_movement = None;
                    }

                    let mut new_pos: Vec2 = player.last_tile as Vec2;
                    let mut new_rot: f32 = player.last_orientation.as_radian();

                    new_pos = new_pos.lerp(player.current_tile as Vec2, progress * modifier);
                    new_rot = lerp(new_rot, player.orientation.as_radian(), progress * modifier);
                    player.pos = Vec3 {
                        x: new_pos.x as f32 + 0.5,
                        y: new_pos.y as f32 + 0.5,
                        z: 0.0,
                    };
                    player.rotation = Vec3 {
                        x: 0.,
                        y: 0.,
                        z: new_rot,
                    };
                }
            }
        }
    }

    pub fn render(app: &mut App<Zappy>) {
        Map::render(app);
        let player_instances : Vec<Mat4> = app.user.players
            .iter()
            .filter(|(_, p)|p.state == Alive)
            .map(|(_, p)|
                Mat4::from_scale_rotation_translation(
                    Vec3::new(1., 1., 1.),
                    Quat::from_euler(EulerRot::XYZ, p.rotation.x, p.rotation.y, p.rotation.z),
                    p.pos))
            .collect();
        let egg_instances : Vec<Mat4> = app.user.players
            .iter()
            .filter(|(_, p)|p.state == Egg)
            .map(|(_, p)|
                Mat4::from_scale_rotation_translation(
                    Vec3::new(1., 1., 1.),
                    Quat::from_euler(EulerRot::XYZ, p.rotation.x, p.rotation.y, p.rotation.z),
                    p.pos))
            .collect();
        let player_colors : Vec<Vec3> = app.user.players.iter().filter(|(_, p)|p.state == Alive).map(|(_, p)| p.color).collect();
        let egg_colors : Vec<Vec3> = app.user.players.iter().filter(|(_, p)|p.state == Egg).map(|(_, p)| p.color).collect();

        if let Some(player_mesh) = &app.user.tantorian_mesh {
            app.draw_instances(player_mesh, player_instances.clone(), player_colors.clone());
        }
        if let Some(egg_mesh) = &app.user.egg_mesh {
            app.draw_instances(egg_mesh, egg_instances.clone(), egg_colors.clone());
        }
        if let Some(mesh) = &app.user.message_mesh {
            for message in &app.user.messages {
                app.draw_at(mesh, message.color, message.pos, Vec3::new(0., 0., 0.), message.scale);
            }
        }
        if let Some(mesh) = &app.user.arrow_mesh {
            for arrow in &app.user.arrows {
                app.draw_at(mesh, arrow.color, arrow.pos, arrow.rot, arrow.scale);
            }
        }
        if let Some(mesh) = &app.user.magic_mesh {
            for incantation in &app.user.incantations {
                for i in &incantation.players {
                    if let Some(player) = app.user.players.get(i) {
                        app.draw_at(mesh, player.color * 2., player.pos, Vec3::ZERO, Vec3::ONE);
                    }
                }
            }
        }
    }
}

pub fn display_ui(zappy : &mut App<Zappy>, at: Duration, ctx: &CtxRef) {
    if let Some(new_time_unit) = zappy.user.ui.settings(ctx, &mut zappy.camera, zappy.camera_is_active) {
        if let Some(server) = &mut zappy.user.server {
            server.send_to_server(format!("sst {}", new_time_unit));
        }
    }
    let (action, player_number, team_name) = zappy.user.ui
        .players(ctx, &mut zappy.user.players, &mut zappy.user.teams, &mut zappy.user.player_auto_update, &mut zappy.user.player_refresh_factor, zappy.camera_is_active);
    let refresh_player = action == crate::ui::PlayerAction::Refresh;
    if action == crate::ui::PlayerAction::Follow {
        for (idx, player) in &zappy.user.players {
            if player.team_name == team_name && player.number == player_number {
                zappy.user.following = Some((player_number, team_name));
                break;
            }
        }
    } else if action == crate::ui::PlayerAction::GoTo {
        zappy.user.following = None;
        look_at_player(zappy, &player_number, &team_name);
    }
    let refresh_map = zappy.user.ui.tiles(ctx, &mut zappy.user.auto_update, &mut zappy.user.refresh_factor, &zappy.user.map, zappy.camera_is_active, &zappy.user.players);
    if zappy.user.server.is_some() {
        zappy.user.ui.communications(ctx, zappy.camera_is_active);
    }
    let state = zappy.user.ui.network_status(ctx, zappy.camera_is_active, &mut zappy.user.port, &mut zappy.user.hostname, zappy.user.server.is_some());
    match state {
        ui::State::Nothing => {},
        ui::State::Connect => zappy.user.try_to_connect(at),
        ui::State::Disconnect => {
            zappy.user.close_connection(at);
            zappy.user.reset_server_data();
        },
        ui::State::Launching => {
            match fork() {
                Ok(Fork::Child) => {
                        println!("executing process: -p {}", zappy.user.port);
                    let p = Command::new("../zappy_server/zappy_server")
                        .arg("-p")
                        .arg(zappy.user.port.clone()).status();
                        println!("execution over;");
                        exit(0);
                }
                Ok(Fork::Parent(_)) => println!("forked"),
                Err(_) => println!("failed to fork"),
            }
            zappy.user.hostname = "127.0.0.1".into();
            std::thread::sleep(Duration::from_secs_f32(2.0));
            zappy.user.try_to_connect(at);
        },
        ui::State::SpawnAI => {}
    }
    if let Some(team) = &zappy.user.winner_team {
        zappy.user.ui.win(ctx, team, zappy.camera_is_active);
    }
    if let Some(server) = &mut zappy.user.server {
        if refresh_map {
            server.send_to_server(format!("mct"));
        }
        if refresh_player {
            for (idx, player) in &zappy.user.players {
                server.send_to_server(format!("ppo #{}", player.number));
            }
        }
    }
}

fn ask_for_update(zappy: &mut Zappy, at: Duration) {
    if let Some(server) = &mut zappy.server {
        if zappy.auto_update == true {
            if zappy.last_map_update.as_secs_f32() + 20. / zappy.time_unit * zappy.refresh_factor < at.as_secs_f32() {
                zappy.last_map_update = at;
                server.send_to_server(format!("mct"));
            }
        }
        if zappy.player_auto_update == true {
            if zappy.last_player_update.as_secs_f32() + 7. / zappy.time_unit * zappy.player_refresh_factor < at.as_secs_f32() {
                zappy.last_player_update = at;
                for (idx, player) in &zappy.players {
                    server.send_to_server(format!("ppo #{}", player.number));
                }
            }
        }
    }
}

fn look_at_player(model: &mut App<Zappy>, number: &i64, team_name: &String) {
    for (idx, player) in &model.user.players {
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
    if let Some(handle) = &zappy.user.thread_handle {
        if handle.is_finished() {
            zappy.user.ui.network_messages.push((update.since_start, format!("Host {}:{} broke connection", zappy.user.hostname, zappy.user.port)));
            zappy.user.close_connection(update.since_start);
            zappy.user.reset_server_data();
        }
    }
    rend_ox::camera_controller::default_camera(nannou_app, zappy, &update);
    following(nannou_app, zappy);
    Zappy::update_players(zappy, &update);
    Zappy::update_incantations(zappy, &update);
    Zappy::update_messages(zappy, &update);
    Zappy::update_arrows(zappy, &update);
    zappy.user.interpret_commands(update.since_start);
    ask_for_update(&mut zappy.user, update.since_start);
    Zappy::render(zappy);
    display_ui(zappy, update.since_start, ctx);
}
