mod map;
mod server;
mod tantorian;
mod ui;
mod network;
mod zappy;
mod interpreter;

use std::thread;

use crate::zappy::Zappy;

use rend_ox::app::{app, App};
use crate::network::loop_server;

fn zappy_app(nannou_app: &rend_ox::nannou::App) -> App<Zappy> {
    let mut app = app(nannou_app, Zappy::new(), zappy::zappy_update);
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
