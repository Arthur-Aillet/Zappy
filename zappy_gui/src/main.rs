mod map;
mod server;
mod tantorian;
mod ui;
mod network;
mod zappy;
mod interpreter;
mod arguments;

use std::f32::consts::PI;
use std::time::Duration;

use crate::zappy::Zappy;

use rend_ox::app::{app, App};
use rend_ox::glam::Vec3Swizzles;
use rend_ox::Vec3;
use crate::arguments::parse_arguments;
use crate::tantorian::Tantorian;

fn zappy_key_pressed(app: &rend_ox::nannou::App, model: &mut App<Zappy>, key: rend_ox::nannou::event::Key) {
    if let rend_ox::nannou::event::Key::R = key { // Testing purpose
        model.user.players[0].last_tile = model.user.players[0].pos.xy() - 0.5;
        model.user.players[0].current_tile += 1.;
        model.user.players[0].start_movement = Some(app.duration.since_start);
    }
    if let rend_ox::nannou::event::Key::Space = key {
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

fn zappy_app(nannou_app: &rend_ox::nannou::App) -> App<Zappy> {
    let mut app: App<Zappy> = app(nannou_app, Zappy::new())
        .update(zappy::zappy_update)
        .key_pressed(zappy_key_pressed);
    let (port, hostname) = parse_arguments();

    app.user.hostname = hostname;
    app.user.port = port;
    Zappy::load(&mut app);
    app.user.try_to_connect(Duration::from_millis(0));
    app.camera.position = Vec3::new(app.user.map.size[0] as f32 / 200., app.user.map.size[1] as f32 / 200., 0.04);
    app.camera.pitch = -PI/2.;
    app.user.team_names.push("Team5".to_string());
    let new = Tantorian::new_from_command(
        1, 0, 0,
        crate::tantorian::Orientation::S, 1, "Team5".to_string(),
        &app.user.team_names, &app.user.map.size, &mut app.user.players).unwrap();
    app.user.players.push(new);
    app
}

fn main() {
    rend_ox::app::launch_rendox_app(zappy_app);
}
