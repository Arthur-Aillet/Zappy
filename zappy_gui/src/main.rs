// use nannou::prelude::*;

use rend_ox::model::{model};
use rend_ox::process::{event, update};

fn main() {
    rend_ox::nannou::app(model).event(event).update(update).run();
}