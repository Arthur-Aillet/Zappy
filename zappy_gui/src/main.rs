mod map;
mod server;
mod tantorian;
mod ui;
mod network;
mod zappy;
mod interpreter;
mod arguments;
mod message;
mod incantation;

use std::f32::consts::PI;
use std::time::Duration;

use crate::zappy::Zappy;

use rend_ox::app::{app, App};
use rend_ox::{nannou, Vec3};
use rend_ox::nannou::{Event, winit};
use crate::arguments::parse_arguments;

fn zappy_event(_nannou_app: &nannou::App, app: &mut App<Zappy>, event: nannou::Event) {
    if app.camera_is_active {
        if let Event::DeviceEvent(_device_id, event) = event {
            if let winit::event::DeviceEvent::Motion { axis, value } = event {
                let sensitivity = app.camera.sensitivity / 1000.;
                match axis {
                    // Yaw left and right on mouse x axis movement.
                    0 => app.camera.yaw -= (value * sensitivity) as f32,
                    // Pitch up and down on mouse y axis movement.
                    _ => {
                        let max_pitch = std::f32::consts::PI * 0.5 - 0.0001;
                        let min_pitch = -max_pitch;
                        app.camera.pitch = (app.camera.pitch + (-value * sensitivity) as f32)
                            .min(max_pitch)
                            .max(min_pitch)
                    }
                }
            } else if let winit::event::DeviceEvent::MouseMotion { delta } = event {
                let sensitivity = app.camera.sensitivity / 1000.;
                app.camera.yaw -= (delta.0 * sensitivity) as f32;
                let max_pitch = std::f32::consts::PI * 0.5 - 0.0001;
                let min_pitch = -max_pitch;
                app.camera.pitch = (app.camera.pitch + (-delta.1 * sensitivity) as f32)
                    .min(max_pitch)
                    .max(min_pitch);
            }
        }
    }
}

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
    let mut app: App<Zappy> = app(nannou_app, Zappy::new())
        .update(zappy::zappy_update)
        .key_pressed(zappy_key_pressed)
        .event(zappy_event);
    let (port, hostname) = parse_arguments();

    println!("Use the `Z`, `Q`, `S`, `D`, `A` and `E` keys to move the camera.");
    println!("Use the mouse to orient the pitch and yaw of the camera.");
    println!("Press the `Space` key to toggle camera mode.");

    app.user.hostname = hostname;
    app.user.port = port;
    Zappy::load(&mut app);
    app.user.try_to_connect(Duration::from_millis(0));
    app.camera.position = Vec3::new(app.user.map.size[0] as f32 / 200., app.user.map.size[1] as f32 / 200., 0.04);
    app.camera.pitch = -PI/2.;
    app
}

fn main() {
    rend_ox::app::launch_rendox_app(zappy_app);
}
