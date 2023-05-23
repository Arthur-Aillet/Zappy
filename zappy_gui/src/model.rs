//
// EPITECH PROJECT, 2023
// Zappy GUI
// File description:
// model
//

use nannou::prelude::*;
use nannou_egui::{self, Egui};

pub struct Model {
    pub egui: Egui,
}

fn window_event(_app: &App, _model: &mut Model, _event: WindowEvent) {
}

fn raw_window_event(_app: &App, model: &mut Model, event: &nannou::winit::event::WindowEvent) {
    model.egui.handle_raw_event(event);
}

pub fn model(app: &App) -> Model {
    let window_id = app.new_window()
        .size(720, 720)
        .event(window_event)
        .raw_event(raw_window_event)
        .build()
        .expect("Error getting window");

    let window = app.window(window_id).expect("Error getting window");

    Model {
        egui: Egui::from_window(&window)
    }
}