use std::time::Duration;
use rend_ox::mesh::MeshDescriptor;
use rend_ox::Vec3;

pub(crate) struct Message {
    pub(crate) pos: Vec3,
    pub(crate) scale: Vec3,
    pub(crate) color: Vec3,
    pub(crate) start: Duration,
}
