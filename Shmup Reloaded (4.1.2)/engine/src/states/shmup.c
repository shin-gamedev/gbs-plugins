// Shmup Reloaded plugin by Shin
	// PLAYER.pos.x and y are in subpixels
	// shooter_pos and shooter_dest are in subpixels
    // camera_offset_x and y are in pixels

#pragma bank 255

#include "data/states_defines.h"
#include "states/shmup.h"

#include "actor.h"
#include "camera.h"
#include "collision.h"
#include "data_manager.h"
#include "game_time.h"
#include "input.h"
#include "trigger.h"
#include "vm.h"

#ifndef SHOOTER_HURT_IFRAMES
#define SHOOTER_HURT_IFRAMES 10
#endif

#define TILE 8

UINT8 shooter_scroll_speed = 16;
UBYTE shooter_reached_end;
UWORD shooter_dest;
UWORD shooter_pos;
direction_e shooter_direction;

void shmup_init(void) BANKED {

    camera_offset_x = 0;
    camera_offset_y = 0;
    camera_deadzone_x = 0;
    camera_deadzone_y = 0;

    shooter_direction = PLAYER.dir;


    if (shooter_direction == DIR_LEFT) {
        // Right to left scrolling
        shooter_dest = (SCREEN_WIDTH_HALF - TILE) << 4;
        shooter_pos = (image_width - SCREEN_WIDTH_HALF - TILE) << 4;
    } else if (shooter_direction == DIR_RIGHT) {
        // Left to right scrolling
        shooter_dest = (image_width - SCREEN_WIDTH_HALF - TILE) << 4;
        shooter_pos = (SCREEN_WIDTH_HALF - TILE) << 4;
    } else if (shooter_direction == DIR_UP) {
        // Bottom to top scrolling
        shooter_dest = (SCREEN_HEIGHT_HALF - TILE) << 4;
        shooter_pos = (image_height - SCREEN_HEIGHT_HALF) << 4;
    } else {
        // Top to bottom scrolling
        shooter_dest = (image_height - SCREEN_HEIGHT_HALF - TILE) << 4;
        shooter_pos = (SCREEN_HEIGHT_HALF - TILE) << 4;
    }

    shooter_reached_end = FALSE;
}

void shmup_update(void) BANKED {
	actor_t *hit_actor;
    UBYTE tile_start, tile_end;
    UBYTE angle = 0;

    player_moving = FALSE;
	
    // Check if scroll complete
	if (shooter_direction == DIR_RIGHT || shooter_direction == DIR_DOWN) {
		if (shooter_pos >= shooter_dest) {
			shooter_reached_end = TRUE;
		}
	} else {
		if (shooter_pos <= shooter_dest) {
			shooter_reached_end = TRUE;
		}
	}
	
    // Scroll
	if (!shooter_reached_end) {
		if (shooter_direction == DIR_RIGHT) {
			shooter_pos += shooter_scroll_speed;
			PLAYER.pos.x += shooter_scroll_speed;
		} else if (shooter_direction == DIR_UP) {
			shooter_pos -= shooter_scroll_speed;
			PLAYER.pos.y -= shooter_scroll_speed;
		} else if (shooter_direction == DIR_LEFT) {
			shooter_pos -= shooter_scroll_speed;
			PLAYER.pos.x -= shooter_scroll_speed;
		} else {
			shooter_pos += shooter_scroll_speed;
			PLAYER.pos.y += shooter_scroll_speed;
		}
	}

    // Player movement
    if (INPUT_LEFT) {
        player_moving = TRUE;
        if (INPUT_UP) {
            angle = ANGLE_315DEG;
        } else if (INPUT_DOWN) {
            angle = ANGLE_225DEG;
        } else {
            angle = ANGLE_270DEG;
        }
    } else if (INPUT_RIGHT) {
        player_moving = TRUE;
        if (INPUT_UP) {
            angle = ANGLE_45DEG;
        } else if (INPUT_DOWN) {
            angle = ANGLE_135DEG;
        } else {
            angle = ANGLE_90DEG;
        }
    } else if (INPUT_UP) {
        player_moving = TRUE;
        angle = ANGLE_0DEG;
    } else if (INPUT_DOWN) {
        player_moving = TRUE;
        angle = ANGLE_180DEG;
    }

    if (player_moving) {
        point16_t new_pos;
        new_pos.x = PLAYER.pos.x;
        new_pos.y = PLAYER.pos.y;
        point_translate_angle(&new_pos, angle, PLAYER.move_speed);

        // Step X
        tile_start = (((PLAYER.pos.y >> 4) + -8)    >> 3);
        tile_end   = (((PLAYER.pos.y >> 4) + 7) >> 3) + 1;
        if (angle < ANGLE_180DEG) {
            UBYTE tile_x = ((new_pos.x >> 4) + 15) >> 3;
            while (tile_start != tile_end) {

                if (tile_at(tile_x, tile_start) & COLLISION_LEFT) {
                    new_pos.x = (((tile_x << 3) - 15) << 4) - 1;
                    break;
                }
                tile_start++;
            }
            PLAYER.pos.x = MIN((image_width - 15 - 1) << 4, new_pos.x);
        } else {
            UBYTE tile_x = ((new_pos.x >> 4) + 0) >> 3;
            while (tile_start != tile_end) {
                if (tile_at(tile_x, tile_start) & COLLISION_RIGHT) {
                    new_pos.x = ((((tile_x + 1) << 3) - 0) << 4) + 1;
                    break;
                }
                tile_start++;
            }
            // Check if overshot left edge of screen
            if (new_pos.x <= PLAYER.pos.x) {
                PLAYER.pos.x = MAX(0, (WORD)new_pos.x);
            } else {
                PLAYER.pos.x = 0;
            }
        }

        // Step Y
        tile_start = (((PLAYER.pos.x >> 4) + 0)  >> 3);
        tile_end   = (((PLAYER.pos.x >> 4) + 15) >> 3) + 1;
        if (angle > ANGLE_90DEG && angle < ANGLE_270DEG) {
            UBYTE tile_y = ((new_pos.y >> 4) + 7) >> 3;
            while (tile_start != tile_end) {
                if (tile_at(tile_start, tile_y) & COLLISION_TOP) {
                    new_pos.y = ((((tile_y) << 3) - 7) << 4) - 1;
                    break;
                }
                tile_start++;
            }
            PLAYER.pos.y = new_pos.y;
        } else {
            UBYTE tile_y = (((new_pos.y >> 4) + -8) >> 3);
            while (tile_start != tile_end) {
                if (tile_at(tile_start, tile_y) & COLLISION_BOTTOM) {
                    new_pos.y = ((((UBYTE)(tile_y + 1) << 3) - -8) << 4) + 1;
                    break;
                }
                tile_start++;
            }
            if (shooter_direction == DIR_RIGHT || shooter_direction == DIR_LEFT) {
                PLAYER.pos.y = MAX(TILE << 4, (WORD)new_pos.y);
            } else {
                PLAYER.pos.y = new_pos.y;
            }
        }
    }
	
	// Check collision with edges of screen
	if (shooter_direction == DIR_RIGHT || shooter_direction == DIR_LEFT) {
		if (PLAYER.pos.x < shooter_pos - (SCREEN_WIDTH_HALF << 4) + (TILE << 4)) {
			PLAYER.pos.x = shooter_pos - (SCREEN_WIDTH_HALF << 4) + (TILE << 4);
		} else if (PLAYER.pos.x > shooter_pos + (SCREEN_WIDTH_HALF << 4) - (TILE << 4)) {
			PLAYER.pos.x = shooter_pos + (SCREEN_WIDTH_HALF << 4) - (TILE << 4);
		}
	} else {
		if (PLAYER.pos.y < shooter_pos - (SCREEN_HEIGHT_HALF - 16) * 16) {
			PLAYER.pos.y = shooter_pos - (SCREEN_HEIGHT_HALF - 16) * 16;
		} else if (PLAYER.pos.y > shooter_pos + (SCREEN_HEIGHT_HALF) * 16) {
			PLAYER.pos.y = shooter_pos + (SCREEN_HEIGHT_HALF) * 16;
		}
	}

    // Set player animation
    if (INPUT_RECENT_UP) {
        actor_set_dir(&PLAYER, DIR_UP, player_moving);
    } else if (INPUT_RECENT_DOWN) {
        actor_set_dir(&PLAYER, DIR_DOWN, player_moving);
    } else if (INPUT_RECENT_LEFT) {
        actor_set_dir(&PLAYER, DIR_LEFT, player_moving);
    } else if (INPUT_RECENT_RIGHT) {
        actor_set_dir(&PLAYER, DIR_RIGHT, player_moving);
    } else {
        actor_set_anim_idle(&PLAYER);
    }
	
	// Set camera offset
	if (shooter_direction == DIR_RIGHT || shooter_direction == DIR_LEFT) {
		camera_offset_x = (PLAYER.pos.x - shooter_pos) >> 4;
	} else {
		camera_offset_y = (PLAYER.pos.y - shooter_pos) >> 4;
	}

    // Check collisions
    hit_actor = NULL;
    if (IS_FRAME_ODD) {
        // Check for trigger at edge of screen
        if (shooter_direction == DIR_RIGHT) {
		    trigger_activate_at((((shooter_pos >> 4) + SCREEN_WIDTH_HALF - TILE) >> 3), 0, FALSE);
	    } else if (shooter_direction == DIR_LEFT) {
            trigger_activate_at((((shooter_pos >> 4) - SCREEN_WIDTH_HALF + TILE * 2) >> 3), 0, FALSE);
        } else if (shooter_direction == DIR_DOWN) {
            trigger_activate_at(0, (((shooter_pos >> 4) + SCREEN_HEIGHT_HALF) >> 3), FALSE);
        } else {
		    trigger_activate_at(0, (((shooter_pos >> 4) - SCREEN_HEIGHT_HALF + TILE * 2) >> 3), FALSE);
	    }

        // Check for actor collisions
        hit_actor = actor_overlapping_player(FALSE);
        if (hit_actor != NULL && hit_actor->collision_group) {
            player_register_collision_with(hit_actor);
        }
    }
}
