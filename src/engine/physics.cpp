#include "physics.hpp"

void Gravity(sf::Sprite *player_sprite, float accel) {
    /* Gravity of player */
    player_sprite->move(0, accel);
}

void JumpPhysics(sf::Sprite *player_sprite, MotionState *motion_state,
                 MotionSpeed motion_speed) {
    /* Jump physics */
    if (motion_state->jump) {
        player_sprite->move(0.F, -motion_speed.accel * 3);
        motion_state->jump_frames += 1;
    }

    if (motion_state->jump_frames == 8) {
        motion_state->jump = false;
        motion_state->jump_frames = 0;
    }
}
