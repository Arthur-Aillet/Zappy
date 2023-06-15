use crate::server::ServerConn;

pub(crate) fn loop_server(mut server: ServerConn) {
    server.recv_from_server().expect("Error received for welcome");
    server.send_to_server("GRAPHIC", -1, -1);
    let string = server.recv_from_server().expect("Error received for init");
    {
        let mut commands = (&mut server.commands).lock().expect("Mutex poisonned");
        commands.push(string);
    }
    loop {
        let string = server.recv_from_server().expect("Error received for welcome"); // Welcome
        {
            let mut commands = (&mut server.commands).lock().expect("Mutex poisonned");
            commands.push(string);
        }
    }
}