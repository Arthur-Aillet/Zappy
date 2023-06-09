use rend_ox::app::App;

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
    zappy.egui_instance.set_elapsed_time(update.since_start);
    let ctx = zappy.egui_instance.begin_frame();
    crate::ui::settings(&ctx, &mut zappy.camera, zappy.camera_is_active);
    crate::ui::communications(&ctx, zappy.camera_is_active);
}
