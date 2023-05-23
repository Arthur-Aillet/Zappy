//
// EPITECH PROJECT, 2023
// Zappy GUI
// File description:
// main
//

mod model;

use crate::model::{Model, model};
use nannou_egui::{self, egui};

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

fn update(_app: &App, model: &mut Model, update: Update) {
    let egui = &mut model.egui;

    egui.set_elapsed_time(update.since_start);
    let ctx = egui.begin_frame();
    let mut value = 0.0;
    let mut value2 = 0.0;

    egui::Window::new("Title").show(&ctx, |ui| {
        // Resolution slider
        ui.heading("Big title");
        ui.label("Label");
        ui.add(egui::Slider::new(&mut value, 0.0..=100.0).text("My value"));
    });
    egui::Window::new("Title2").show(&ctx, |ui| {
        // Resolution slider
        ui.heading("Big title2");
        ui.label("Label2");
        ui.add(egui::Slider::new(&mut value2, 0.0..=100.0).text("My value2"));
    });
}

fn view(app: &App, model: &Model, frame: Frame) {
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

    match model.egui.draw_to_frame(&frame) {
        Err(e) => println!("Error drawing to egui frame: {e:?}"),
        _ => (),
    }
}
