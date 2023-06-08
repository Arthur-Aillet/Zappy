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

fn update(app: &App<Zappy>, model: &mut Zappy) {
    // let mut player = Tantorian::new();
    // player.mesh_descriptor = app.loadAsset("player.obj");
    // model.players.push(player);
}