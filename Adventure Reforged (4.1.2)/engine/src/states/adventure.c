#pragma bank 255

#include "data/states_defines.h"
#include "states/adventure.h"

#include "actor.h"
#include "camera.h"
#include "collision.h"
#include "game_time.h"
#include "input.h"
#include "scroll.h"
#include "trigger.h"
#include "data_manager.h"
#include "rand.h"
#include "vm.h"
#include "math.h"

#ifndef ADVENTURE_CAMERA_DEADZONE
#define ADVENTURE_CAMERA_DEADZONE 8
#endif

point16_t new_pos;
point16_t old_pos;
UBYTE angle = 0;
UBYTE old_angle = 0;
UBYTE checked_tile = 0;
UBYTE solid_ladders = 0;
UBYTE swimming = 0;
UBYTE swim_speed = 0;
direction_e new_dir = DIR_NONE;

void adventure_init(void) BANKED {
    // Set camera to follow player
    camera_offset_x = 0;
    camera_offset_y = 0;
    camera_deadzone_x = ADVENTURE_CAMERA_DEADZONE;
    camera_deadzone_y = ADVENTURE_CAMERA_DEADZONE;
}

void adventure_update(void) BANKED {
    actor_t *hit_actor;
    UBYTE tile_start, tile_end;
    player_moving = FALSE;
	old_pos = PLAYER.pos;

	new_dir = DIR_NONE;
	
    if (INPUT_RECENT_LEFT) {
        new_dir = DIR_LEFT;
    } else if (INPUT_RECENT_RIGHT) {
        new_dir = DIR_RIGHT;
    } else if (INPUT_RECENT_UP) {
        new_dir = DIR_UP;
    } else if (INPUT_RECENT_DOWN) {
        new_dir = DIR_DOWN;
    }

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
    } else {
		angle = 0;
	}
	
    new_pos.x = PLAYER.pos.x;
    new_pos.y = PLAYER.pos.y;
	
	// If changed movement angle this frame, round subpixel position to nearest pixel position. Prevents jittering on diagonal movement
		if (angle != old_angle) {
			PLAYER.pos.x = PLAYER.pos.x & 0xFFF0;
			PLAYER.pos.y = PLAYER.pos.y & 0xFFF0;
		}
		old_angle = angle;
	
	if (swimming) {
		if (INPUT_A_PRESSED && swim_speed == 0) {
			swim_speed = 16;
		} else if (swim_speed > 0) {
			swim_speed--;
		}
		switch (angle) {
			case ANGLE_0DEG:
				new_pos.y = PLAYER.pos.y - 8 - swim_speed;
				break;
			case ANGLE_45DEG:
				new_pos.x = PLAYER.pos.x + 5 + (swim_speed * 7 / 10);
				new_pos.y = PLAYER.pos.y - 5 - (swim_speed * 7 / 10);
				break;
			case ANGLE_90DEG:
				new_pos.x = PLAYER.pos.x + 8 + swim_speed;
				break;
			case ANGLE_135DEG:
				new_pos.x = PLAYER.pos.x + 5 + (swim_speed * 7 / 10);
				new_pos.y = PLAYER.pos.y + 5 + (swim_speed * 7 / 10);
				break;
			case ANGLE_180DEG:
				new_pos.y = PLAYER.pos.y + 8 + swim_speed;
				break;
			case ANGLE_225DEG:
				new_pos.x = PLAYER.pos.x - 5 - (swim_speed * 7 / 10);
				new_pos.y = PLAYER.pos.y + 5 + (swim_speed * 7 / 10);
				break;
			case ANGLE_270DEG:
				new_pos.x = PLAYER.pos.x - 8 - swim_speed;
				break;
			case ANGLE_315DEG:
				new_pos.x = PLAYER.pos.x - 5 - (swim_speed * 7 / 10);
				new_pos.y = PLAYER.pos.y - 5 - (swim_speed * 7 / 10);
				break;
		}
	} else if (player_moving) {
		// Update new pos
        // point_translate_angle(&new_pos, angle, PLAYER.move_speed);
		switch (angle) {
			case ANGLE_0DEG:
				new_pos.y = PLAYER.pos.y - 16;
				break;
			case ANGLE_45DEG:
				new_pos.x = PLAYER.pos.x + 11;
				new_pos.y = PLAYER.pos.y - 11;
				break;
			case ANGLE_90DEG:
				new_pos.x = PLAYER.pos.x + 16;
				break;
			case ANGLE_135DEG:
				new_pos.x = PLAYER.pos.x + 11;
				new_pos.y = PLAYER.pos.y + 11;
				break;
			case ANGLE_180DEG:
				new_pos.y = PLAYER.pos.y + 16;
				break;
			case ANGLE_225DEG:
				new_pos.x = PLAYER.pos.x - 11;
				new_pos.y = PLAYER.pos.y + 11;
				break;
			case ANGLE_270DEG:
				new_pos.x = PLAYER.pos.x - 16;
				break;
			case ANGLE_315DEG:
				new_pos.x = PLAYER.pos.x - 11;
				new_pos.y = PLAYER.pos.y - 11;
				break;
		}
	}
	
	if (player_moving) {
		
        // Step X
        tile_start = (((PLAYER.pos.y >> 4) + PLAYER.bounds.top)    >> 3);
        tile_end   = (((PLAYER.pos.y >> 4) + PLAYER.bounds.bottom) >> 3) + 1;
        if (angle < ANGLE_180DEG) {
            UBYTE tile_x = ((new_pos.x >> 4) + PLAYER.bounds.right) >> 3;
            while (tile_start != tile_end) {
				checked_tile = tile_at(tile_x, tile_start);
                if (checked_tile & COLLISION_LEFT && (!(checked_tile & TILE_PROP_LADDER) || checked_tile & TILE_PROP_LADDER && solid_ladders)) {
                    new_pos.x = (((tile_x << 3) - PLAYER.bounds.right) << 4) - 1;           
                    break;
                }
                tile_start++;
            }
            PLAYER.pos.x = MIN((image_width - 16) << 4, new_pos.x);
        } else {
            UBYTE tile_x = ((new_pos.x >> 4) + PLAYER.bounds.left) >> 3;
            while (tile_start != tile_end) {
				checked_tile = tile_at(tile_x, tile_start);
                if (checked_tile & COLLISION_RIGHT && (!(checked_tile & TILE_PROP_LADDER) || checked_tile & TILE_PROP_LADDER && solid_ladders)) {
                    new_pos.x = ((((tile_x + 1) << 3) - PLAYER.bounds.left) << 4) + 1;         
                    break;
                }
                tile_start++;
            }
            PLAYER.pos.x = MAX(0, (WORD)new_pos.x);
        }

        // Step Y
        tile_start = (((PLAYER.pos.x >> 4) + PLAYER.bounds.left)  >> 3);
        tile_end   = (((PLAYER.pos.x >> 4) + PLAYER.bounds.right) >> 3) + 1;
        if (angle > ANGLE_90DEG && angle < ANGLE_270DEG) {
            UBYTE tile_y = ((new_pos.y >> 4) + PLAYER.bounds.bottom) >> 3;
            while (tile_start != tile_end) {
				checked_tile = tile_at(tile_start, tile_y);
                if (checked_tile & COLLISION_TOP && (!(checked_tile & TILE_PROP_LADDER) || checked_tile & TILE_PROP_LADDER && solid_ladders)) {
                    new_pos.y = ((((tile_y) << 3) - PLAYER.bounds.bottom) << 4) - 1;
                    break;
                }
                tile_start++;
            }
            PLAYER.pos.y = new_pos.y;
        } else {
            UBYTE tile_y = (((new_pos.y >> 4) + PLAYER.bounds.top) >> 3);
            while (tile_start != tile_end) {
				checked_tile = tile_at(tile_start, tile_y);
                if (checked_tile & COLLISION_BOTTOM && (!(checked_tile & TILE_PROP_LADDER) || checked_tile & TILE_PROP_LADDER && solid_ladders)) {
                    new_pos.y = ((((UBYTE)(tile_y + 1) << 3) - PLAYER.bounds.top) << 4) + 1;
                    break;
                }
                tile_start++;
            }
            PLAYER.pos.y = new_pos.y;
        }
    }

    if (new_dir != DIR_NONE) {
        actor_set_dir(&PLAYER, new_dir, player_moving);
    } else {
        actor_set_anim_idle(&PLAYER);
    }

    hit_actor = NULL;
    if (IS_FRAME_ODD) {
        // Check for trigger collisions
        if (trigger_activate_at_intersection(&PLAYER.bounds, &PLAYER.pos, FALSE)) {
            // Landed on a trigger
            return;
        }
	}
	
    // Check for actor collisions
	// If overlapping solid actor
    hit_actor = actor_overlapping_player(FALSE);
    if (hit_actor != NULL) {
		if (hit_actor->collision_group == 0 || hit_actor->collision_group == 8) {
			// Move player back to previous frame position
			PLAYER.pos.x = old_pos.x;
			PLAYER.pos.y = old_pos.y;
			//If actor in front of player direction
			hit_actor = actor_in_front_of_player(1, TRUE);
			if (hit_actor != NULL && hit_actor->collision_group == 0 || hit_actor != NULL && hit_actor->collision_group == 8) {
			// Slide is blocked, no movement
			} else {
			// Allow slide, movement in slide direction only
				if (new_dir == DIR_LEFT || new_dir == DIR_RIGHT) {
					PLAYER.pos.x = new_pos.x;
				} else {
					PLAYER.pos.y = new_pos.y;
				}
			}
			
			
		}
		// Else trigger on hit script
		else {
			player_register_collision_with(hit_actor);
		}
    }

    if (INPUT_A_PRESSED) {
        if (!hit_actor) {
            hit_actor = actor_in_front_of_player(8, TRUE);
        }
        if (hit_actor && !hit_actor->collision_group && hit_actor->script.bank) {
            script_execute(hit_actor->script.bank, hit_actor->script.ptr, 0, 1, 0);
        }
    }
}
