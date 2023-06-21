use std::fmt::Display;
use std::time::Duration;
use rend_ox::nannou_egui::egui::{self, CtxRef, Ui};
use rend_ox::nannou_egui::egui::CollapsingHeader;

use crate::tantorian::Tantorian;
use crate::ui::State::{Connect, Disconnect, Nothing};

pub(crate) struct ZappyUi {
    pub selected_tile: Option<[usize; 2]>,
    pub network_messages: Vec<(Duration, String)>,
    pub broadcast_messages: Vec<(Duration, String, i64, String)>,
}

#[derive(PartialEq)]
pub(crate) enum State {
    Nothing,
    Connect,
    Disconnect,
}

impl ZappyUi {
    pub(crate) fn new() -> ZappyUi {
        ZappyUi {
            selected_tile: None,
            network_messages: vec![],
            broadcast_messages: vec![],
        }
    }

    pub(crate) fn win(&mut self, ctx: &CtxRef, team_name: &String, is_active: bool) {
        egui::Window::new("Winner team found!").enabled(!is_active).show(
            &ctx,
            |ui| {
                ui.heading(format!("Team {team_name} won!"));
            },
        );
    }

    pub(crate) fn settings(&mut self, ctx: &CtxRef, camera: &mut rend_ox::camera::Camera, is_active: bool) {
        egui::Window::new("Settings").enabled(!is_active).show(
            &ctx,
            |ui| {
                ui.label("Camera:");
                ui.add(egui::Slider::new(&mut camera.speed, 0.1..=10.0).text("Speed:"));
                ui.add(egui::Slider::new(&mut camera.fov, 60.0..=150.0).text("FOV:"));
                ui.add(egui::Slider::new(&mut camera.sensitivity, 0.1..=10.0).text("Sensitivity:"));
            },
        );
    }

    pub(crate) fn network_status(&mut self, ctx: &CtxRef, is_active: bool, port: &mut String, hostname: &mut String, status: bool) -> State {
        let mut state = Nothing;

        egui::Window::new("Network Status")
            .enabled(!is_active)
            .resizable(false)
            .show(ctx, |ui| {
                ui.add(egui::TextEdit::singleline(port).hint_text("port"));
                ui.add(egui::TextEdit::singleline(hostname).hint_text("hostname"));
                if status {
                    ui.add(egui::Label::new(format!("Current status: Connected")));
                    if ui.add(egui::Button::new("Disconnect")).clicked() {
                        state = Disconnect;
                    }
                } else {
                    ui.add(egui::Label::new(format!("Current status: Disconnected")));
                    if ui.add(egui::Button::new("Connect")).clicked() {
                        state = Connect;
                    }
                }
                ui.add(egui::Label::new("________________________________________________").strong());
                ui.add_space(10.);
                egui::ScrollArea::vertical()
                    .max_height(100.)
                    .stick_to_bottom()
                    .show(ui, |ui| {
                        egui::Grid::new("Network Messages")
                            .num_columns(2)
                            .striped(true)
                            .show(ui, |grid| {
                                for message in &self.network_messages {
                                    ZappyUi::display_stat(grid, &*format!("<{:.4}s>", message.0.as_secs_f32()), &message.1);
                                }
                            });
                    });
            });
        state
    }

    pub(crate) fn communications(&mut self, ctx: &CtxRef, is_active: bool) {
        egui::Window::new("Communications")
            .enabled(!is_active)
            .show(ctx, |ui| {
                egui::ScrollArea::vertical()
                    .auto_shrink([false, true])
                    .max_height(100.)
                    .stick_to_bottom()
                    .show(ui, |ui| {
                        egui::Grid::new("Broadcast Messages")
                            .num_columns(2)
                            .striped(true)
                            .show(ui, |grid| {
                                for (time, team_name, number, message) in self.broadcast_messages.iter() {
                                    ZappyUi::display_stat(grid, &*format!("<{team_name}:{number} {:.1}s>", time.as_secs_f32()), &message);
                                }
                            });
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
                    Some(tile) => {
                        clicked_last_frame =
                            has_been_clicked == false && tile[0] == x && tile[1] == y
                    }
                    None => (),
                }
                let button: egui::Button;
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

    fn display_stat(ui :&mut Ui, label: &str, value: impl Display) {
        ui.add(egui::Label::new(format!("{label}:")).underline());
        ui.add(egui::Label::new(format!("{}", value)));
        ui.end_row();
    }

    fn tile_content(grid :&mut Ui, map: &crate::map::Map, selected: &[usize; 2]) {
        ZappyUi::display_stat(grid,"Food", map.tiles[selected[0]][selected[1]].q0.len());
        ZappyUi::display_stat(grid,"Linemate", map.tiles[selected[0]][selected[1]].q1.len());
        ZappyUi::display_stat(grid,"Deraumere", map.tiles[selected[0]][selected[1]].q2.len());
        ZappyUi::display_stat(grid,"Sibur", map.tiles[selected[0]][selected[1]].q3.len());
        ZappyUi::display_stat(grid,"Mendiane", map.tiles[selected[0]][selected[1]].q4.len());
        ZappyUi::display_stat(grid,"Phiras", map.tiles[selected[0]][selected[1]].q5.len());
        ZappyUi::display_stat(grid,"Thystame", map.tiles[selected[0]][selected[1]].q6.len());
    }

    pub(crate) fn tiles(&mut self, ctx: &CtxRef, map: &crate::map::Map, is_active: bool) {
        egui::Window::new("Map").vscroll(true).enabled(!is_active).show(
            ctx, |ui| {
                ui.add(egui::Label::new("Tiles:").heading());
                egui::Grid::new("Tiles")
                    .num_columns(map.size[0] as usize)
                    .spacing([-21., 2.])
                    .striped(true)
                    .show(ui, |ui_grid| {
                        self.selected_tile = self.tile_buttons(ui_grid, map);
                    });
                if let Some(selected) = self.selected_tile {
                    ui.add(egui::Label::new("_______________________________").strong());
                    ui.add_space(10.);

                    let title = format!("Tile {} {}: ", selected[0], selected[1]);
                    ui.add(egui::Label::new(title).heading());
                    egui::Grid::new("Tile")
                        .num_columns(2)
                        .spacing([40.0, 4.0])
                        .striped(true)
                        .show(ui, |grid| {
                            ZappyUi::tile_content(grid, map, &selected);
                        });
                }
            },
        );
    }

    pub(crate) fn team(ui :&mut Ui, players: &Vec<Tantorian>, team_name: &String) {
        for player in players.iter().filter(|x| {x.team_name == *team_name}) {
            CollapsingHeader::new(player.number)
                .default_open(false)
                .show(ui, |col| {
                    ZappyUi::display_stat(col, "Number", player.number);

                    let state: &str;
                    if player.alive {
                        state = "alive";
                    } else  {
                        state = "dead";
                    }
                    ZappyUi::display_stat(col, "Status", state);
                });
        }
    }

    pub(crate) fn players(&mut self, ctx: &CtxRef, players: &Vec<Tantorian>, teams: &Vec<String>, is_active: bool) {
        egui::Window::new("Players")
            .enabled(!is_active)
            .resizable(true)
            .show(ctx, |ui| {
                for team in teams {
                    CollapsingHeader::new(team)
                        .default_open(false)
                        .show(ui, |col| {
                            ZappyUi::team(col, players, team);
                        });
                }
            });

    }
}
