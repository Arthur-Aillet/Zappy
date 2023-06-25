use std::{io, thread, time};
use std::collections::HashMap;
use std::thread::JoinHandle;
use std::time::Duration;
use crate::server::ServerConn;
use crate::zappy::Zappy;

impl Zappy {
    pub(crate) fn reset_server_data(&mut self) {
        self.teams = vec![];
        self.players = HashMap::new();
        self.time_unit = 100.0;
        self.map.resize(10, 10);
        self.winner_team = None;
        self.ui.selected_tile = None;
    }

    pub(crate) fn close_connection(&mut self, at: Duration) {
        self.ui.network_messages.push((at, format!("Closing connection to {}:{}", self.hostname, self.port)));
        if let Some(server) = &mut self.server {
            {
                *server.listening.lock().expect("Mutex poisoned") = false;
            }
        }
        self.thread_handle.take().map(JoinHandle::join);
        self.thread_handle = None;
        self.server = None;
    }

    pub(crate) fn try_to_connect(&mut self, at: Duration) {
        if self.server.is_some() {
            self.close_connection(at);
            self.reset_server_data();
        }
        self.ui.network_messages.push((at, format!("New connection tried to {}:{}", self.hostname, self.port)));
        self.server = ServerConn::new(&self.port, &self.hostname);
        if let Some(server) = &mut self.server {
            let server_clone = server.access();
            self.thread_handle = Some(thread::spawn(move || {
                loop_server(server_clone);
            }));
            self.ui.network_messages.push((at, format!("Connection to {}:{} working", self.hostname, self.port)));
        } else {
            self.ui.network_messages.push((at, format!("Connection to {}:{} failed", self.hostname, self.port)));
        }
    }
}

pub(crate) fn loop_server(mut server: ServerConn) {
    server.recv_from_server().expect("Error received for welcome");
    server.send_to_server(format!("GRAPHIC"));
    thread::sleep(time::Duration::from_millis(100));
    server.send_to_server(format!("tna"));
    thread::sleep(time::Duration::from_millis(100));
    server.send_to_server(format!("msz"));
    thread::sleep(time::Duration::from_millis(100));
    server.send_to_server(format!("mct"));
    thread::sleep(time::Duration::from_millis(100));
    server.send_to_server(format!("sgt"));
    thread::sleep(time::Duration::from_millis(100));
    loop {
        match server.recv_from_server() {
            Ok(string) => {
                if !string.is_empty() {
                    {
                        let mut commands = (&mut server.commands).lock().expect("Mutex poisoned");
                        commands.push(string);
                    }
                }
            }
            Err(error) => {
                if error.kind() == io::ErrorKind::ConnectionAborted {break;} else {
                    panic!("Error receiving message form server")
                }
            }
        }
        {
            if !*server.listening.lock().expect("Mutex poisoned") {
                server.shutdown_stream();
                return;
            }
        }
    }
}