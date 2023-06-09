use rend_ox::nannou_egui::egui::{self, CtxRef};

pub(crate) fn settings(ctx: &CtxRef, camera: &mut rend_ox::camera::Camera, is_active: bool) {
    egui::Window::new("Settings")
        .enabled(!is_active)
        .show(ctx, |ui| {
            ui.label("Camera:");
            ui.add(egui::Slider::new(&mut camera.speed, 0.1..=10.0).text("Speed:"));
            ui.add(egui::Slider::new(&mut camera.fov, 60.0..=150.0).text("FOV:"));
            ui.add(egui::Slider::new(&mut camera.sensitivity, 0.1..=10.0).text("Sensivity:"));
        });
}

pub(crate) fn communications(ctx: &CtxRef, is_active: bool) {
    egui::Window::new("Communications")
        .enabled(!is_active)
        .fixed_size([100., 100.])
        .show(ctx, |ui| {
            egui::ScrollArea::vertical()
                .auto_shrink([false; 2])
                .max_height(100.)
                .always_show_scroll(true)
                .stick_to_bottom()
                .show(ui, |ui| {
                    ui.label("Test");
                    ui.label("Test");
                    ui.label("Test");
                    ui.label("Test");
                    ui.label("Test");
                    ui.label("Test");
                    ui.label("Test");
                });
        });
}
