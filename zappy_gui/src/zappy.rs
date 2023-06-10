use rend_ox::app::App;

use crate::map::Map;
pub use crate::server::ServerConn;
use crate::tantorian::Tantorian;
use crate::ui::ZappyUi;

pub struct Zappy {
    pub(crate) map: Map,
    pub(crate) players: Vec<Tantorian>,
    pub(crate) server: ServerConn,
    pub(crate) ui: ZappyUi,
}

impl Zappy {
    pub fn new() -> Zappy {
        Zappy {
            map: Map::new(),
            players: vec![],
            server: ServerConn::new(),
            ui: ZappyUi::new(),
        }
    }
}

pub(crate) fn zappy_update(
    _nannou_app: &rend_ox::nannou::App,
    zappy: &mut App<Zappy>,
    update: rend_ox::nannou::event::Update,
) {
    zappy.egui_instance.set_elapsed_time(update.since_start);
    zappy.user.ui.ctx = Some(zappy.egui_instance.begin_frame().context());
    zappy
        .user
        .ui
        .settings(&mut zappy.camera, zappy.camera_is_active);
    zappy.user.ui.communications(zappy.camera_is_active);
    zappy.user.ui.tiles(&zappy.user.map, zappy.camera_is_active);
}
