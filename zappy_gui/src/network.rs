use std::sync::{Arc, Mutex};
use std::collections::HashMap;

use crate::server::ServerConn;

pub type NetworkFunction = fn(_: &Arc<Mutex<ServerConn>>);

pub(crate) fn set_map_size (_: &Arc<Mutex<ServerConn>>) {

}
pub(crate) fn create_hash_function() -> HashMap<String, NetworkFunction> {
    let mut functions : HashMap<String, NetworkFunction> = HashMap::new();

    functions.insert("msz".to_string(), set_map_size);
    functions
}

pub(crate) fn loop_server(server_access : Arc<Mutex<ServerConn>>) {
    let mut server_lock = server_access.lock().expect("Mutex Poisoned");

    server_lock.recv_from_server().expect("Error received for welcome"); // Welcome
    server_lock.send_to_server("GRAPHIC", -1, -1);
    println!("{:?}", server_lock.recv_from_server().expect("Error received for welcome").lines()); // Welcome
}