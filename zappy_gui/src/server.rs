use std::io::{self, Read, Write};
use std::net::{Shutdown, TcpStream};
use std::sync::{Arc, Mutex};

pub struct ServerConn {
    pub commands: Arc<Mutex<Vec<String>>>,
    pub listening: Arc<Mutex<bool>>,
    pub stream: TcpStream,
}

impl ServerConn {
    pub(crate) fn access(&self) -> ServerConn {
        ServerConn {
            commands: Arc::clone(&self.commands),
            listening: Arc::clone(&self.listening),
            stream: self.stream.try_clone().expect("stream wrongfully setup"),
        }
    }

    pub fn new(port: &String, machine: &String) -> Option<ServerConn> {
        let try_stream = ServerConn::set_tcp_stream(port, machine);

        match try_stream {
            None => {None}
            Some(stream) => {
                Some(ServerConn {
                commands: Arc::new(Mutex::new(Vec::new())),
                listening: Arc::new(Mutex::new(true)),
                stream,
                })
            }
        }
    }

    //NOTE - Create the connection with the server and return the tcp connection
    pub fn set_tcp_stream(port: &String, machine: &String) -> Option<TcpStream> {
        let connect = format!("{}:{}", machine, port);

        let stream = match TcpStream::connect(connect) {
            Ok(stream) => {stream}
            Err(_) => {
                return None;
            }
        };
        stream.set_nonblocking(true).expect("Non blocking refused");
        Some(stream)
    }

    // NOTE - Read the connexion flux and return a string or an error.
    //  If the string is empty, it's because the read is non blocking and he just read nothing.
    //  The string return is NOT parsed.
    pub fn recv_from_server(&mut self) -> Result<String, io::Error> {
        let mut buffer = vec![0; 1024];
        let mut result = String::new();

        loop {
            match self.stream.read(&mut buffer) {
                Ok(size) if size > 0 => {
                    let tmp = String::from_utf8_lossy(&buffer[..size]);
                    result.push_str(&tmp);
                    if size < buffer.len() {
                        break;
                    }
                }
                Ok(_) => {return Err(io::Error::new(io::ErrorKind::ConnectionAborted, "Connection aborted"))},
                Err(ref err) if err.kind() == io::ErrorKind::WouldBlock => {
                    break;
                }
                Err(err) => return Err(err),
            }
        }
        Ok(result)
    }

    //NOTE - This function takes the message to send to the server,
    //       the command to be sent, and two optional integers.
    //       These are required for certain commands.
    //       If you don't need them, set the value to negative
    //       Returns false in case of error, true if none.
    pub fn send_to_server(&mut self, s: String) -> bool {
        match write!(self.stream, "{}\n", s) {
            Ok(_) => true,
            Err(e) => {println!("error in message sent: {e}"); false}
        }
    }

    //NOTE - Close the socket flux
    pub fn shutdown_stream(&mut self) {
        self.stream
            .shutdown(Shutdown::Both)
            .expect("Couldn't shut down connection");
    }
}
