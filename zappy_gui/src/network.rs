use std::thread;
use std::thread::JoinHandle;
use std::time::Duration;
use crate::server::ServerConn;
use crate::zappy::Zappy;

impl Zappy {
    pub(crate) fn reset_server_data(&mut self) {
        self.team_names = vec![];
        self.players = vec![];
        self.time_unit = 100.0;
        self.map.resize(8, 8);
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
    server.send_to_server("GRAPHIC", -1, -1);
    loop {
        let string = server.recv_from_server().expect("Error received from new message");
        if !string.is_empty() {
            {
                let mut commands = (&mut server.commands).lock().expect("Mutex poisoned");
                commands.push(string);
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