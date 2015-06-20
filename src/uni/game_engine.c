#if defined(__APPLE__) || defined(__WIN32__)
#include <stdio.h>
#endif

#if defined(_Z8F6403)
#include <stdio.h>
#endif

// game_engine.c

#include "game_engine.h"
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


void game_init(GameData *gameData, PlayerData *playerData) {
	int i, j;
	char str[9];

	playerData->energy = 0x0FFF;

	gfx_window(-1, -1, 258, 98);

	gfx_draw_text(200, 98, "coins");
	gfx_draw_energy_meter();

	for (i = 0; i < 15; ++i) {
		for (j = 0; j < 8; ++j) {
			gameData->blockData[i][j] = levelData[gameData->level][i][j];
		}
	}

	gfx_draw_all_blocks(gameData);
	sprintf(str, "%8d", playerData->coins);
	gfx_draw_text(224, 98, str);

	gameData->strikerPos = 127 << 8;

	gameData->ballPos.x = 127 << 8;
	gameData->ballPos.y = 90 << 8;
	gameData->ballOldPos.x = gameData->ballPos.x;
	gameData->ballOldPos.y = gameData->ballPos.y;

	gameData->ballVel.x = 0;
	gameData->ballVel.y = -(int)32;

	gameData->ballSpeed = 3;

	gameData->strikerSize = 24;

	gfx_init_striker(gameData);
	gfx_init_ball(gameData);

	// Flags used by physics engine to avoid hitting same block twice in consecutive calls to phy_simulate
	gameData->blockHit[2] = 0;	// Wether or not the ball was touching a block last iteration
	gameData->bouncedTop = 0;	// Touching top game border
	gameData->bouncedSide = 0;	// Touching side game border
	gameData->bouncedStriker = 0;	// Touching the striker
}

void game_update(int *mode, GameData *gameData, PlayerData *playerData) {
	char key, i;
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

		key = hw_read_key();



		//if (playerData->energy <= 0) game_end(mode, 0);

		// sprintf(debug, "%d", (int) hw_read_analog());
		// gfx_draw_text(200, 80, debug);

		// if (key & 4) *mode = 0;

		if (key & 4) {
			gfx_draw_bullet(gameData->strikerPos, gameData->strikerPos, 0, 0);
		}

		// Calculate new ball position
		for (i = 0; i < 8; ++i) {
			phy_simulate(gameData);
			if (gameData->blockHit[0]) {
				(gameData->blockHit[0] >> 8) ? gfx_draw_block(gameData->blockHit[0] & 0x000F, gameData->blockHit[0] >> 4 & 0x000F, gameData->blockHit[0] >> 8) : gfx_erase_block(gameData->blockHit[0] & 0x000F, gameData->blockHit[0] >> 4 & 0x000F);
				gameData->blockHit[0] = 0;
				if (gameData->blockHit[1]) {
					(gameData->blockHit[1] >> 8) ? gfx_draw_block(gameData->blockHit[1] & 0x000F, gameData->blockHit[1] >> 4 & 0x000F, gameData->blockHit[1] >> 8) : gfx_erase_block(gameData->blockHit[1] & 0x000F, gameData->blockHit[1] >> 4 & 0x000F);
					gameData->blockHit[1] = 0;
					playerData->coins += 5;
				}

				// update score
				playerData->coins += 5;
				gfx_draw_score(playerData);
				hw_sound_play(260, 25, 250);
			}
			if (gameData->redraw) {
				gameData->redraw = 0;
				break;
			}
		}

		gameData->ballVel.y++;

		gfx_draw_striker(gameData);
		gfx_draw_ball(gameData);
	}
	LED_update();
	hw_sound_update();
}
void game_end(int *mode, int win) {
	if (win == 0) {
		gfx_window(87, 45, 163, 60);
		gfx_draw_game_over();
	} else {
		gfx_window(76, 45, 181, 60);
		gfx_draw_victory();
	}
	gfx_draw_text(91, 54, "press to continue");
	while (1) {
		if (hw_read_key() == 4) {
			* mode = 0;
			break;
		}
	}
}

