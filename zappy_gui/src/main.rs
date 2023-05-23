//
// EPITECH PROJECT, 2023
// Zappy GUI
// File description:
// main
//

mod model;

use crate::model::{Model, model};

use nannou::prelude::*;

fn main() {
    nannou::app(model)
        .event(event)
        .view(view)
        .update(update)
        .run();
}

fn event(_app: &App, _model: &mut Model, _event: Event) {
}

fn update(_app: &App, _model: &mut Model, _update: Update) {
}

fn view(app: &App, _model: &Model, frame: Frame) {
    frame.clear(BLACK);

    let draw = app.draw();

    draw.rect()
        .color(STEELBLUE)
        .w(300.0)
        .h(200.0);

    match draw.to_frame(app, &frame) {
        Err(e) => println!("Error drawing to frame: {e:?}"),
        _ => (),
    }
}
