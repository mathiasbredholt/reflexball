// game_engine.c

#include "game_engine.h"
#include "game_data.h"
#include "hw_time.h"
#include "hw_input.h"
#include "hw_LED.h"
#include "hw_sound.h"
#include "levels.h"
#include "graphics.h"
#include "util.h"
#include "physics.h"
// #include "sounds.h"
// #include <sio.h>
// #include "ansi.h"


void game_init(GameData *gameData, PlayerData *playerData, AnimationData *animationData) {
	int i, j;

	playerData->energy = playerData->energyMax;

	gfx_window(1, -1, -1, 257, 98);

	gfx_draw_text(11, 200, 98, "coins");
	gfx_draw_score(playerData);
	gfx_draw_energy_meter(playerData);

	for (i = 0; i < 15; ++i) {
		for (j = 0; j < 8; ++j) {
			gameData->blockData[i][j] = levelData[gameData->level][i][j];
		}
	}

	gfx_draw_all_blocks(gameData);

	gameData->strikerPos = 127 << 8;

	gameData->ballPos.x = 127 << 8;
	gameData->ballPos.y = 90 << 8;
	gameData->ballOldPos.x = gameData->ballPos.x;
	gameData->ballOldPos.y = gameData->ballPos.y;

	gameData->ballVel.x = 0;
	gameData->ballVel.y = -(int)32;

	gameData->ballSpeed = 3;

	gameData->multiplier = 0;

	gameData->strikerSize = 24;

	gfx_init_striker(gameData);
	gfx_init_ball(gameData);

	for (i = 0; i < 5; ++i) {
		animationData->projectileType[i] = -1;
		animationData->eraseProjectile[i] = 0;
	}

	// Flags used by physics engine to avoid hitting same block twice in consecutive calls to phy_simulate
	gameData->blockHit[2] = 0;	// Wether or not the ball was touching a block last iteration
	gameData->bouncedTop = 0;	// Touching top game border
	gameData->bouncedSide = 0;	// Touching side game border
	gameData->bouncedStriker = 0;	// Touching the striker

	if (gameData->level < 0) {
		hw_sound_set_music(1);
	} else if (gameData->level == 1) {
		hw_sound_set_music(2);
	} else if (gameData->level == 2) {
		hw_sound_set_music(3);
	} else if (gameData->level == 3) {
		hw_sound_set_music(2);
	} else if (gameData->level == 4) {
		hw_sound_set_music(3);
	} else if (gameData->level == 5) {
		hw_sound_set_music(0);
	}
}

void create_bullet(GameData *gameData, AnimationData *animationData, int type, int side) {	// side: 0 = left, 1 = right
	int num;

	// Find available slot in animationData->projectilePos
	for (num = 0; num < 5; ++num) {
		if (animationData->projectileType[num] == -1) break;
	}
	if (num < 5) {	// If num == 5, it means that there was no available slot - bullet will not be created
		hw_sound_play(9 + type);
		animationData->projectilePos[num][0] = (gameData->strikerPos >> 8) + (side ? (gameData->strikerSize >> 1) : (-(gameData->strikerSize >> 1) + 1));
		animationData->projectilePos[num][1] = striker_height - (type < 2 ? 1 : 3);
		animationData->projectileType[num] = (char) type;
	}
}

void game_update(int *mode, char *lastKey, GameData *gameData, PlayerData *playerData, AnimationData *animationData) {
	char key, i, won = 0, lostBall = 0;
	gameData->redraw = 0;
	gameData->blockHit[0] = 0;	// Data of last block hit, used to update graphics
	gameData->blockHit[1] = 0;	// Same as 0, used if two blocks are hit simultaneously

	// if (hw_read_key() && hw_time_get_next_frame()) {
	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		gameData->strikerOldPos = gameData->strikerPos;
		gameData->ballOldPos = gameData->ballPos;

		phy_move_striker(gameData, playerData, hw_read_analog());

		gfx_update_energy_meter(playerData);

		if (playerData->energy <= 0) game_end(mode, 0, playerData);

		// sprintf(debug, "%d", (int) hw_read_analog());
		// gfx_draw_text(9, 200, 80, debug);

		// if (key & 4) *mode = 0;

		phy_update_bullets(gameData, animationData);

		// Calculate new ball position
		for (i = 0; i < 8; ++i) {
			phy_simulate(gameData, &lostBall);
			if (gameData->blockHit[0]) {
				(gameData->blockHit[0] >> 8) ? gfx_draw_block(gameData->blockHit[0] & 0x000F, gameData->blockHit[0] >> 4 & 0x000F, gameData->blockHit[0] >> 8) : gfx_erase_block(gameData->blockHit[0] & 0x000F, gameData->blockHit[0] >> 4 & 0x000F);
				gameData->blockHit[0] = 0;
				if (gameData->blockHit[1]) {
					(gameData->blockHit[1] >> 8) ? gfx_draw_block(gameData->blockHit[1] & 0x000F, gameData->blockHit[1] >> 4 & 0x000F, gameData->blockHit[1] >> 8) : gfx_erase_block(gameData->blockHit[1] & 0x000F, gameData->blockHit[1] >> 4 & 0x000F);
					gameData->blockHit[1] = 0;
					playerData->coins += 5 * gameData->multiplier;
				}

				// update score
				playerData->coins += 5 * gameData->multiplier;
				gfx_draw_score(playerData);
			}
			if (gameData->redraw) {
				gameData->redraw = 0;
				gfx_draw_ball(gameData);
				gameData->ballOldPos = gameData->ballPos;
			}
			if (lostBall) {
				gfx_update_energy_meter(playerData);
				playerData->oldEnergy = playerData->energy;
				playerData->energy -= 0x1000;
				gfx_update_energy_meter(playerData);
				lostBall = 0;

			}
		}

		gameData->ballVel.y++;	// Gravity

		key = hw_read_key();
		// If key is rising edge
		if (key != *lastKey) {
			*lastKey = key;
			if (key & 1) {
				create_bullet(gameData, animationData, 0, 1);
			}
			if (key & 2) {
				create_bullet(gameData, animationData, 1, 0);
			}
			if (key & 4) {
				create_bullet(gameData, animationData, 2, 0);
			}
		}

		gfx_draw_striker(gameData);
		gfx_draw_ball(gameData);
		gfx_update_animation(animationData);
	} else {
		// check for victory
		for (i = 0; i < 15; ++i) {
			won |= (gameData->blockData[i][0] || gameData->blockData[i][1]);
		}
		if (won) game_end(mode, 1, playerData);
	}
	//LED_update();
}

void game_end(int *mode, int win, PlayerData *playerData) {
	hw_sound_mute();
	if (win == 0) {
		hw_sound_play(13);
		gfx_window(1, 87, 45, 163, 60);
		gfx_draw_game_over();
		LED_set_string("YOU DEAD");
	} else {
		if (playerData->progress < 6) ++playerData->progress;
		hw_sound_play(12);
		gfx_window(1, 76, 45, 181, 60);
		gfx_draw_victory();
		LED_set_string("You win!");
	}
	gfx_draw_text(9, 91, 54, "press to continue");
	while (1) {
		LED_update();
		if (hw_read_key() == 4) {
			*mode = 1;
			break;
		}
	}
}

