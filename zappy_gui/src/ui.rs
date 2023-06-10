use rend_ox::nannou_egui::egui::{self, CtxRef, Ui};

pub(crate) struct ZappyUi {
    pub selected_tile: Option<[usize; 2]>,
    pub ctx: Option<CtxRef>,
}

impl ZappyUi {
    pub(crate) fn new() -> ZappyUi {
        ZappyUi {
            ctx: None,
            selected_tile: None,
        }
    }

    pub(crate) fn settings(&mut self, camera: &mut rend_ox::camera::Camera, is_active: bool) {      
        egui::Window::new("Settings")
            .enabled(!is_active)
            .show(&self.ctx.clone().expect("Ctx not set"), |ui| {
                ui.label("Camera:");
                ui.add(egui::Slider::new(&mut camera.speed, 0.1..=10.0).text("Speed:"));
                ui.add(egui::Slider::new(&mut camera.fov, 60.0..=150.0).text("FOV:"));
                ui.add(egui::Slider::new(&mut camera.sensitivity, 0.1..=10.0).text("Sensivity:"));
            });
    }

    pub(crate) fn communications(&mut self, is_active: bool) {
        egui::Window::new("Communications")
            .enabled(!is_active)
            .show(&self.ctx.clone().expect("Ctx not set"), |ui| {
                egui::ScrollArea::vertical()
                    .auto_shrink([false; 2])
                    .max_height(100.)
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

    fn tile_buttons(&mut self, ui: &mut Ui, map: &crate::map::Map) -> Option<[usize; 2]> {
        let mut tile_clicked: Option<[usize; 2]> = self.selected_tile;
        let mut has_been_clicked = false;

        for x in 0..map.size[0] {
            for y in 0..map.size[1] {
                let mut clicked_last_frame = false;

                match self.selected_tile {
                    Some(tile) => clicked_last_frame = has_been_clicked == false && tile[0] == x && tile[1] == y,
                    None => (),
                }
                let button : egui::Button;
                if clicked_last_frame {
                    button = egui::Button::new("   ").fill(egui::Color32::from_rgb(200, 200, 200));
                } else {
                    button = egui::Button::new("   ");
                }

                if ui.add(button).clicked() {
                    if clicked_last_frame {
                        tile_clicked = None;
                    } else {
                        has_been_clicked = true;
                        tile_clicked = Some([x, y]);
                    }
                }
            }
            ui.end_row();
        }
        tile_clicked
    }

    pub(crate) fn tiles(&mut self, map: &crate::map::Map, is_active: bool) {
        egui::Window::new("Map")
            .enabled(!is_active)
            .show(&self.ctx.clone().expect("Ctx not set"), |ui| {
                ui.label("Tiles:");
                egui::Grid::new("my_grid")
                    .num_columns(map.size[0] as usize)
                    .spacing([-21., 2.])
                    .striped(true)
                    .show(ui, |ui_grid| {
                        self.selected_tile = self.tile_buttons(ui_grid, map);
                    });
            });
    }
}
