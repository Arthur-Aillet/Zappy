use crate::server::ServerConn;

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