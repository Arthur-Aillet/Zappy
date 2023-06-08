// use nannou::prelude::*;

mod zappy;
mod map;
mod server;
mod tantorian;

use rend_ox::app::{app, App};
use rend_ox::nannou::app::ModelFn;
use rend_ox::process::{event, update};
use crate::zappy::Zappy;

// fn zappy_app()

fn main() {
    let cl = {|nannou_app : &rend_ox::nannou::App| {return app(nannou_app, Zappy::new());}};
    rend_ox::nannou::app(cl).event(event).update(update).run();
}