#pragma bank 255

#include "data/states_defines.h"
#include "states/topdown.h"

#include "actor.h"
#include "camera.h"
#include "collision.h"
#include "data_manager.h"
#include "game_time.h"
#include "input.h"
#include "trigger.h"
#include "math.h"
#include "vm.h"

#ifndef INPUT_TOPDOWN_INTERACT
#define INPUT_TOPDOWN_INTERACT INPUT_A
#endif

UBYTE topdown_grid;
UBYTE topdown_followers;
point16_t pos1;
point16_t pos2;
point16_t pos3;
point16_t pos4;

void topdown_init(void) BANKED {
    camera_offset_x = 0;
    camera_offset_y = 0;
    camera_deadzone_x = 0;
    camera_deadzone_y = 0;

	pos4 = PLAYER.pos;
	pos3 = PLAYER.pos;
	pos2 = PLAYER.pos;
	pos1 = PLAYER.pos;
	
	topdown_grid = 16;
	
	if (topdown_followers >= 1) {
		actors[1].pos = PLAYER.pos;
	}
	if (topdown_followers >= 2) {
		actors[2].pos = PLAYER.pos;
	}
	if (topdown_followers >= 3) {
		actors[3].pos = PLAYER.pos;
	}
	
    if (topdown_grid == 16) {
        // Snap to 16px grid
        PLAYER.pos.x = ((PLAYER.pos.x >> 8) << 8);
        PLAYER.pos.y = ((PLAYER.pos.y >> 8) << 8) + 128;
    } else {
        PLAYER.pos.x = ((PLAYER.pos.x >> 7) << 7);
        PLAYER.pos.y = ((PLAYER.pos.y >> 7) << 7);
    }
}

void topdown_update(void) BANKED {
    actor_t *hit_actor;
    UBYTE tile_start, tile_end;
    direction_e new_dir = DIR_NONE;
	
	// move actors towards relevant pos
		if (topdown_followers >= 1) {
			if (actors[1].pos.x < pos2.x) {
				actors[1].pos.x += PLAYER.move_speed;
				actor_set_dir(&actors[1], DIR_RIGHT, TRUE);
			} else if (actors[1].pos.x > pos2.x) {
				actors[1].pos.x -= PLAYER.move_speed;
				actor_set_dir(&actors[1], DIR_LEFT, TRUE);
			} else if (actors[1].pos.y < pos2.y) {
				actors[1].pos.y += PLAYER.move_speed;
				actor_set_dir(&actors[1], DIR_DOWN, TRUE);
			} else if (actors[1].pos.y > pos2.y) {
				actors[1].pos.y -= PLAYER.move_speed;
				actor_set_dir(&actors[1], DIR_UP, TRUE);
			}
		}
		if (topdown_followers >= 2) {
			if (actors[2].pos.x < pos3.x) {
				actors[2].pos.x += PLAYER.move_speed;
				actor_set_dir(&actors[2], DIR_RIGHT, TRUE);
			} else if (actors[2].pos.x > pos3.x) {
				actors[2].pos.x -= PLAYER.move_speed;
				actor_set_dir(&actors[2], DIR_LEFT, TRUE);
			} else if (actors[2].pos.y < pos3.y) {
				actors[2].pos.y += PLAYER.move_speed;
				actor_set_dir(&actors[2], DIR_DOWN, TRUE);
			} else if (actors[2].pos.y > pos3.y) {
				actors[2].pos.y -= PLAYER.move_speed;
				actor_set_dir(&actors[2], DIR_UP, TRUE);
			}
		}
		if (topdown_followers >= 3) {
			if (actors[3].pos.x < pos4.x) {
				actors[3].pos.x += PLAYER.move_speed;
				actor_set_dir(&actors[3], DIR_RIGHT, TRUE);
			} else if (actors[3].pos.x > pos4.x) {
				actors[3].pos.x -= PLAYER.move_speed;
				actor_set_dir(&actors[3], DIR_LEFT, TRUE);
			} else if (actors[3].pos.y < pos4.y) {
				actors[3].pos.y += PLAYER.move_speed;
				actor_set_dir(&actors[3], DIR_DOWN, TRUE);
			} else if (actors[3].pos.y > pos4.y) {
				actors[3].pos.y -= PLAYER.move_speed;
				actor_set_dir(&actors[3], DIR_UP, TRUE);
			}
		}

    // Is player on an 8x8px tile?
    if ((topdown_grid == 16 && ON_16PX_GRID(PLAYER.pos)) ||
        (topdown_grid == 8 && ON_8PX_GRID(PLAYER.pos))) {
        // Player landed on an tile
        // so stop movement for now
        player_moving = FALSE;
		
		// player finished moving, update pos1
		pos1 = PLAYER.pos;
		
        // Check for trigger collisions
        if (trigger_activate_at_intersection(&PLAYER.bounds, &PLAYER.pos, FALSE)) {
            // Landed on a trigger
            return;
        }

        // Check input to set player movement
        if (INPUT_RECENT_LEFT) {
            player_moving = TRUE;
            new_dir = DIR_LEFT;

            // Check for collisions to left of player
            tile_start = (((PLAYER.pos.y >> 4) + PLAYER.bounds.top)    >> 3);
            tile_end   = (((PLAYER.pos.y >> 4) + PLAYER.bounds.bottom) >> 3) + 1;
            UBYTE tile_x = ((PLAYER.pos.x >> 4) + PLAYER.bounds.left) >> 3;
            while (tile_start != tile_end) {
                if (tile_at(tile_x - 1, tile_start) & COLLISION_RIGHT) {
                    player_moving = FALSE;
                    break;
                }
                tile_start++;
            }
			
			// Turn player and check for actor in front of player
			actor_set_dir(&PLAYER, new_dir, player_moving);
			hit_actor = actor_in_front_of_player(topdown_grid, FALSE);
			
			// If player is moving and no actor in front, update all pos
			if (player_moving && hit_actor == NULL) {
				pos4 = pos3;
				pos3 = pos2;
				pos2 = pos1;
			}
			
        } else if (INPUT_RECENT_RIGHT) {
            player_moving = TRUE;
            new_dir = DIR_RIGHT;

            // Check for collisions to right of player
            tile_start = (((PLAYER.pos.y >> 4) + PLAYER.bounds.top)    >> 3);
            tile_end   = (((PLAYER.pos.y >> 4) + PLAYER.bounds.bottom) >> 3) + 1;
            UBYTE tile_x = ((PLAYER.pos.x >> 4) + PLAYER.bounds.right) >> 3;
            while (tile_start != tile_end) {
                if (tile_at(tile_x + 1, tile_start) & COLLISION_LEFT) {
                    player_moving = FALSE;
                    break;
                }
                tile_start++;
            }
			
			// Turn player and check for actor in front of player
			actor_set_dir(&PLAYER, new_dir, player_moving);
			hit_actor = actor_in_front_of_player(topdown_grid, FALSE);
			
			// If player is moving and no actor in front, update all pos
			if (player_moving && hit_actor == NULL) {
				pos4 = pos3;
				pos3 = pos2;
				pos2 = pos1;
			}
			
        } else if (INPUT_RECENT_UP) {
            player_moving = TRUE;
            new_dir = DIR_UP;

            // Check for collisions below player
            tile_start = (((PLAYER.pos.x >> 4) + PLAYER.bounds.left)  >> 3);
            tile_end   = (((PLAYER.pos.x >> 4) + PLAYER.bounds.right) >> 3) + 1;
            UBYTE tile_y = ((PLAYER.pos.y >> 4) + PLAYER.bounds.top) >> 3;
            while (tile_start != tile_end) {
                if (tile_at(tile_start, tile_y - 1) & COLLISION_BOTTOM) {
                    player_moving = FALSE;
                    break;
                }
                tile_start++;
            }
			
			// Turn player and check for actor in front of player
			actor_set_dir(&PLAYER, new_dir, player_moving);
			hit_actor = actor_in_front_of_player(topdown_grid, FALSE);
			
			// If player is moving and no actor in front, update all pos
			if (player_moving && hit_actor == NULL) {
				pos4 = pos3;
				pos3 = pos2;
				pos2 = pos1;
			}
			
        } else if (INPUT_RECENT_DOWN) {
            player_moving = TRUE;
            new_dir = DIR_DOWN;

            // Check for collisions below player
            tile_start = (((PLAYER.pos.x >> 4) + PLAYER.bounds.left)  >> 3);
            tile_end   = (((PLAYER.pos.x >> 4) + PLAYER.bounds.right) >> 3) + 1;
            UBYTE tile_y = ((PLAYER.pos.y >> 4) + PLAYER.bounds.bottom) >> 3;
            while (tile_start != tile_end) {
                if (tile_at(tile_start, tile_y + 1) & COLLISION_TOP) {
                    player_moving = FALSE;
                    break;
                }
                tile_start++;
            }
			
			// Turn player and check for actor in front of player
			actor_set_dir(&PLAYER, new_dir, player_moving);
			hit_actor = actor_in_front_of_player(topdown_grid, FALSE);
			
			// If player is moving and no actor in front, update all pos
			if (player_moving && hit_actor == NULL) {
				pos4 = pos3;
				pos3 = pos2;
				pos2 = pos1;
			}
        }

        if (IS_FRAME_ODD) {
            // Check for actor overlap
            hit_actor = actor_overlapping_player(FALSE);
            if (hit_actor != NULL && hit_actor->collision_group) {
                player_register_collision_with(hit_actor);
            }
        }

        // Check if walked in to actor
        if (player_moving) {
            hit_actor = actor_in_front_of_player(topdown_grid, FALSE);
            if (hit_actor != NULL) {
                player_register_collision_with(hit_actor);
                actor_stop_anim(&PLAYER);
                player_moving = FALSE;
            }
        }
		
		// Update idle animations
        if (new_dir == DIR_NONE) {
            actor_set_anim_idle(&PLAYER);
		}
		if (!player_moving) {
			if (topdown_followers >= 1) {
				actor_set_anim_idle(&actors[1]);
			}
			if (topdown_followers >= 2) {
				actor_set_anim_idle(&actors[2]);
			}
			if (topdown_followers >= 3) {
				actor_set_anim_idle(&actors[3]);
			}
        }

        if (INPUT_PRESSED(INPUT_TOPDOWN_INTERACT)) {
            hit_actor = actor_in_front_of_player(topdown_grid, TRUE);
            if (hit_actor != NULL && !hit_actor->collision_group) {
                actor_set_dir(hit_actor, FLIPPED_DIR(PLAYER.dir), FALSE);
                player_moving = FALSE;
                if (hit_actor->script.bank) {
                    script_execute(hit_actor->script.bank, hit_actor->script.ptr, 0, 1, 0);
                }
            }
        }
    }

    if (player_moving) point_translate_dir(&PLAYER.pos, PLAYER.dir, PLAYER.move_speed);
}
