use std::time::Duration;
use rend_ox::glam::Vec2;

#[derive(PartialEq)]
pub enum IncantationState {
    Running,
    Success,
    Failed,
}

impl IncantationState {
    pub fn as_string(&self) -> &'static str {
        match self {
            IncantationState::Running => {"running"},
            IncantationState::Success => {"success"},
            IncantationState::Failed => {"failed"},
        }
    }
}

pub struct Incantation {
    pub(crate) pos: Vec2,
    pub(crate) level: u32,
    pub(crate) players: Vec<i64>,
    pub(crate) state: IncantationState,
    pub(crate) since: Duration,
}

impl Incantation {
    pub fn new(
        pos: Vec2,
        level: u32,
        players: Vec<i64>,
        since: Duration,
    ) -> Incantation {
        Incantation {
            pos,
            level,
            players,
            state: IncantationState::Running,
            since,
        }
    }
}