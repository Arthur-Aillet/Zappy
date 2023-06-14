use std::cell::RefCell;
use std::sync::{Arc, Mutex};
use std::collections::HashMap;
use std::net::TcpStream;

use crate::server::ServerConn;

pub type NetworkFunction = fn(_: &Arc<Mutex<ServerConn>>);

pub(crate) fn set_map_size (_: &Arc<Mutex<ServerConn>>) {
}

pub(crate) fn create_hash_function() -> HashMap<String, NetworkFunction> {
    let mut functions : HashMap<String, NetworkFunction> = HashMap::new();

    functions.insert("msz".to_string(), set_map_size);
    functions
}

pub(crate) fn loop_server(mut server: ServerConn) {
    println!("{:?}", server.recv_from_server().expect("Error received for welcome"));
    server.send_to_server("GRAPHIC", -1, -1);
    println!("{:?}", server.recv_from_server().expect("Error received for welcome").lines()); // Welcome*/
    /*loop {
        {
            server_lock.recv_from_server().expect("Error received for welcome"); // Welcome
        }
    }*/
}