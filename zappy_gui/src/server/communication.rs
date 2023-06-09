use getopts::Options;
use regex::Regex;
use std::env;
use std::io::{self, Read, Write};
use std::net::{Shutdown, TcpStream};
use std::thread;
use std::time::Duration;

fn is_ip_address(s: &str) -> bool {
    let regex_ip = Regex::new(r"^(\d{1,3}\.){3}\d{1,3}$").unwrap();
    regex_ip.is_match(s)
}

fn parse_arguments() -> (String, String) {
    let args: Vec<String> = env::args().collect();
    let mut opts = Options::new();

    opts.optopt("p", "", "port number", "PORT");
    opts.optopt("h", "", "machine name", "MACHINE");

    let matches = match opts.parse(&args[1..]) {
        Ok(m) => m,
        Err(_) => {
            print_usage();
            std::process::exit(84);
        }
    };

    let port = matches.opt_str("p").unwrap_or_else(|| {
        print_usage();
        std::process::exit(84);
    });

    let machine = matches
        .opt_str("h")
        .unwrap_or_else(String::from("127.0.0.1"));
    if !is_ip_address(&machine) {
        print_usage();
        std::process::exit(84);
    }

    (port, machine)
}

fn print_usage() {
    println!("USAGE:\t./zappy_ai -p port -h machine");
    println!("\tport\tis the port number");
    println!("\tmachine\tis the name of the machine; localhost by default");
}

//NOTE - Create the connection with the server and return the tcp connection
pub fn set_tcp_stream() -> TcpStream {
    let (port, machine) = parse_arguments();
    let connect = format!("{}:{}", machine, port);

    TcpStream::connect(connect)
        .expect("Couldn't connect to the server...");
        .set_nonblocking(true)
        .expect("Couldn't set nonblocking mode")
}

//NOTE - Read the connexion flux and return a string or an error.
// If the string is empty, it's because the read is non blocking and he just read nothing.
// The string return is NOT parsed.
pub fn recv_from_server(mut stream: &TcpStream) -> Result<String, io::Error> {
    let mut buffer = vec![0; 1024];
    let mut result = String::new();

    loop {
        match stream.read(&mut buffer) {
            Ok(size) if size > 0 => {
                let tmp = String::from_utf8_lossy(&buffer[..size]);
                result.push_str(&tmp);
                if size < buffer.len() {
                    break;
                }
            }
            Ok(_) => break,
            Err(ref err) if err.kind() == io::ErrorKind::WouldBlock => {
                break;
            }
            Err(err) => return Err(err),
        }
    }
    Ok(result)
}

//NOTE - This function takes as parameters a TcpStream to send the message to the server,
//       the command to be sent, and two optional integers.
//       These are required for certain commands.
//       If you don't need them, set the value to negative
pub fn send_to_server(mut stream: &TcpStream, s: &str, x: i32, y: i32) {
    let concatenated_string: String;

    if x < 0 && y < 0 {
        concatenated_string = format!("{}", s);
    } else if x >= 0 && y >= 0 {
        concatenated_string = format!("{} {} {}", s, x, y);
    } else if x >= 0 && y < 0 {
        concatenated_string = format!("{} {}", s, x);
    } else {
        concatenated_string = format!("{} {}", s, y);
    }
    write!(stream, "{}\n", concatenated_string).expect("Could't send message to server");
}

//NOTE - Close the socket flux
pub fn shutdown_stream(mut stream: &TcpStream) {
    stream
        .shutdown(Shutdown::Both)
        .expect("Couldn't shut down connection");
}
