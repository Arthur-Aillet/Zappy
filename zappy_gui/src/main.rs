mod map;
mod server;
mod tantorian;
mod zappy;

use crate::zappy::Zappy;
use rend_ox::app::{app, App};

fn zappy_app(nannou_app: &rend_ox::nannou::App) -> App<Zappy> {
    return app(nannou_app, Zappy::new(), zappy::zappy_update);
}

fn main() {
    rend_ox::app::launch_rendox_app(zappy_app);
}
