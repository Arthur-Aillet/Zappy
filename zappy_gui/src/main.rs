mod map;
mod server;
mod tantorian;
mod zappy;

use crate::zappy::Zappy;
use rend_ox::app::{app, App};
use rend_ox::nannou_egui::egui;

fn zappy_app(nannou_app: &rend_ox::nannou::App) -> App<Zappy> {
    return app(nannou_app, Zappy::new(), zappy_update);
}

fn zappy_update(
    _nannou_app: &rend_ox::nannou::App,
    zappy: &mut App<Zappy>,
    update: rend_ox::nannou::event::Update,
) {
    let egui = &mut zappy.egui_instance;

    egui.set_elapsed_time(update.since_start);
    let ctx = egui.begin_frame();

    egui::Window::new("Settings").show(&ctx, |ui| {
        ui.add(egui::Slider::new(&mut zappy.camera.speed, 0.1..=10.0).text("Speed:"));
    });
}

fn main() {
    rend_ox::app::launch_rendox_app(zappy_app);
}
