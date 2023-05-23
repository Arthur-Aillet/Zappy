//
// EPITECH PROJECT, 2023
// Zappy GUI
// File description:
// main
//

use nannou::prelude::*;

fn main() {
    nannou::app(model)
        .update(update)
        .simple_window(view)
        .run();
}

struct Model {}

fn model(_app: &App) -> Model {
    Model {}
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
        Err(e) => println!("error drawing to frame: {e:?}"),
        _ => (),
    }
}
