use std::env;
use getopts::Options;
use regex::Regex;

fn print_usage() {
    println!("USAGE:\t./zappy_ai -p port -h machine");
    println!("\tport\tis the port number");
    println!("\tmachine\tis the name of the machine; localhost by default");
}

fn is_ip_address(s: &str) -> bool {
    let regex_ip = Regex::new(r"^(\d{1,3}\.){3}\d{1,3}$").expect("Invalid regex expression");
    regex_ip.is_match(s)
}

pub fn parse_arguments() -> (String, String) {
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

    let port = matches
        .opt_str("p")
        .unwrap_or(String::from(""));

    let machine = matches
        .opt_str("h")
        .unwrap_or(String::from("127.0.0.1"));

    if !is_ip_address(&machine) {
        print_usage();
        std::process::exit(84);
    }
    (port, machine)
}