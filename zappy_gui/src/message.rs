use std::f32::consts::PI;
use std::time::Duration;
use rend_ox::app::App;
use rend_ox::glam::{EulerRot, Quat, Vec3Swizzles};
use rend_ox::mesh::MeshDescriptor;
use rend_ox::nannou::event::Update;
use rend_ox::Vec3;
use crate::zappy::Zappy;

pub(crate) struct Message {
    pub(crate) pos: Vec3,
    pub(crate) scale: Vec3,
    pub(crate) color: Vec3,
    pub(crate) start: Duration,
}

pub(crate) struct Arrows {
    pub(crate) pos: Vec3,
    pub(crate) start_pos: Vec3,
    pub(crate) scale: Vec3,
    pub(crate) rot: Vec3,
    pub(crate) color: Vec3,
    pub(crate) start: Duration,
}

impl Arrows {
    pub fn new_from_direction(direction : Vec3, x: f32, y: f32, color: Vec3, at: Duration) -> Arrows {
        Arrows{
            pos: Vec3::new(x, y, 2.5),
            start_pos: Vec3::new(x, y, 2.5),
            scale: Vec3::new(0.2, 0.2, 0.2),
            rot: direction,
            color,
            start: at,
        }
    }
}

impl Zappy {
    pub fn update_arrows(app: &mut App<Zappy>, update: &Update) {
        let mut ended: Vec<usize> = vec![];

        for (elem, arrow) in app.user.arrows.iter_mut().enumerate() {
            let mut progress = update.since_start.as_secs_f32() - arrow.start.as_secs_f32();
            let modifier = 1. / (7. / app.user.time_unit);

            if progress >= 1. / modifier {
                progress = 1. / modifier;
                ended.push(elem);
            }
            let direction = Vec3::new(0., 1., 0.);
            arrow.pos = arrow.start_pos.lerp(arrow.start_pos + Quat::from_euler(EulerRot::XYZ, arrow.rot.x, arrow.rot.y, arrow.rot.z).mul_vec3(direction) / 3., (progress * modifier * PI * 1.5).sin());
        }
        for to_end in ended.iter().rev() {
            app.user.arrows.remove(*to_end);
        }
    }

    pub fn update_messages(app: &mut App<Zappy>, update: &Update) {
        let mut ended: Vec<usize> = vec![];

        for (elem, message) in app.user.messages.iter_mut().enumerate() {
            let mut progress= update.since_start.as_secs_f32() - message.start.as_secs_f32();
            let modifier = 1. / (7. / app.user.time_unit);

            if progress >= 1. / modifier {
                progress = 1. / modifier;
                ended.push(elem);
            }

            message.scale = Vec3::new(1., 1., 1.).lerp( Vec3::new(16., 16., 0.), (progress * modifier).powi(2));
        }
        for to_end in ended.iter().rev()  {
            app.user.messages.remove(*to_end);
        }
    }
}