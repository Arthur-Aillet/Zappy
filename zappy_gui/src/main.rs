mod interpreter;
mod map;
mod network;
mod server;
mod tantorian;
mod ui;
mod zappy;

use std::thread;

use crate::zappy::Zappy;

use crate::network::loop_server;
use rend_ox::app::{app, App};

fn zappy_key_pressed(app: &rend_ox::nannou::App, model: &mut App<Zappy>, key: rend_ox::nannou::event::Key) {
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
    let mut app = app(nannou_app, Zappy::new())
        .update(zappy::zappy_update)
        .key_pressed(zappy_key_pressed);


    Zappy::load(&mut app);
    if let Some(server) = &mut app.user.server {
        let server_clone = server.access();
        thread::spawn(move || {
            loop_server(server_clone);
        });
    }
    app
}

fn main() {
    rend_ox::app::launch_rendox_app(zappy_app);
}
