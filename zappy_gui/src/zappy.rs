use rend_ox::app::App;
use rend_ox::nannou_egui::egui;

pub use crate::map::Map;
pub use crate::server::ServerConn;
pub use crate::tantorian::Tantorian;

pub struct Zappy {
    pub(crate) map: Map,
    pub(crate) players: Vec<Tantorian>,
    pub(crate) server: ServerConn,
}

impl Zappy {
    pub fn new() -> Zappy {
        Zappy {
            map: Map::new(),
            players: vec![],
            server: ServerConn::new(),
        }
    }
}

pub(crate) fn zappy_update(
    _nannou_app: &rend_ox::nannou::App,
    zappy: &mut App<Zappy>,
    update: rend_ox::nannou::event::Update,
) {
    let egui = &mut zappy.egui_instance;

    egui.set_elapsed_time(update.since_start);
    let ctx = egui.begin_frame();

    egui::Window::new("Settings")
        .enabled(!zappy.camera_is_active)
        .show(&ctx, |ui| {
            ui.label("Camera:");
            ui.add(egui::Slider::new(&mut zappy.camera.speed, 0.1..=10.0).text("Speed:"));
            ui.add(egui::Slider::new(&mut zappy.camera.fov, 60.0..=150.0).text("FOV:"));
            ui.add(egui::Slider::new(&mut zappy.camera.sensitivity, 0.1..=10.0).text("Sensivity:"));
        });
    egui::Window::new("Communications")
        .enabled(!zappy.camera_is_active)
        .show(&ctx, |ui| {
            egui::ScrollArea::vertical()
                .auto_shrink([false; 2])
                .max_height(100.0)
                .stick_to_bottom()
                .show(ui, |ui| {
                    ui.label("Test");
                    ui.label("Test");
                    ui.label("Test");
                    ui.label("Test");
                    ui.label("Test");
                    ui.label("Test");
                    ui.label("Test");
                });
        });
}
