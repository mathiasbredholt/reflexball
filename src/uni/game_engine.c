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
	char str[9];

	playerData->energy = 0xFFFF;

	gfx_window(-1, -1, 258, 98);

	gfx_draw_text(200, 98, "coins");
	gfx_draw_energy_meter(255);

	gfx_draw_all_blocks(gameData);
	sprintf(str, "%8d", playerData->coins);
	gfx_draw_text(224, 98, str);

	gameData->strikerPos = 128 << 8;

	gameData->ballPos.x = 128 << 8;
	gameData->ballPos.y = 90 << 8;
	gameData->ballOldPos.x = gameData->ballPos.x;
	gameData->ballOldPos.y = gameData->ballPos.y;

	gameData->ballVel.x = -(int)32;
	gameData->ballVel.y = 0;

	gameData->ballSpeed = 3;

	gfx_draw_striker(gameData);
	gfx_init_ball(gameData);
}

void game_update(int *mode, GameData *gameData, PlayerData *playerData) {
	char key, i;
	char debug[20];
	gameData->redraw = 0;
	gameData->blockHit[0] = 0;
	gameData->blockHit[1] = 0;

	// if (hw_read_key() && hw_time_get_next_frame()) {
	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		gameData->strikerOldPos = gameData->strikerPos;
		gameData->ballOldPos = gameData->ballPos;

		key = hw_read_key();

		// move striker left
		if (key & 2 && (gameData->strikerPos >> 7) >= gameData->strikerSize) {
			gameData->strikerPos -= 256;
			--playerData->energy;
			gfx_update_energy_meter(playerData->energy);
		}

		// move striker left
		if (key & 2 && (gameData->strikerPos >> 7) >= gameData->strikerSize) {
			gameData->strikerPos -= 256;
			--playerData->energy;
			gfx_update_energy_meter(playerData->energy);
		}

		// move striker right
		if (key & 1 && gameData->strikerPos >> 8 <= 255 - ((gameData->strikerSize >> 1) + 1)) {
			gameData->strikerPos += 256;
			--playerData->energy;
			gfx_update_energy_meter(playerData->energy);
		}

		// move striker right
		if (key & 1 && gameData->strikerPos >> 8 <= 255 - ((gameData->strikerSize >> 1) + 1)) {
			gameData->strikerPos += 256;
			--playerData->energy;
			gfx_update_energy_meter(playerData->energy);
		}

		//if (playerData->energy <= 0) *mode = 0;

		hw_read_analog();
		// sprintf(debug, "%d", (int) hw_read_analog());
		// gfx_draw_text(200, 80, debug);

		// if (key & 4) *mode = 0;

		if (key & 4) {
			gfx_draw_bullet(gameData->strikerPos, gameData->strikerPos, 0, 0);
		}

		// Calculate new ball position
		for (i = 0; i < 1; ++i) {
			phy_simulate(gameData);
			if (gameData->blockHit[0]) {
				char str[9];
				(gameData->blockHit[0] >> 8) ? gfx_draw_block(gameData->blockHit[0] & 0x000F, gameData->blockHit[0] >> 4 & 0x000F, (gameData->blockHit[0] >> 8) - 1) : gfx_erase_block(gameData->blockHit[0] & 0x000F, gameData->blockHit[0] >> 4 & 0x000F);
				gameData->blockHit[0] = 0;
				if (gameData->blockHit[1]) {
					(gameData->blockHit[1] >> 8) ? gfx_draw_block(gameData->blockHit[1] & 0x000F, gameData->blockHit[1] >> 4 & 0x000F, (gameData->blockHit[1] >> 8) - 1) : gfx_erase_block(gameData->blockHit[1] & 0x000F, gameData->blockHit[1] >> 4 & 0x000F);
					gameData->blockHit[1] = 0;
					playerData->coins += 5;
				}

				// update score
				playerData->coins += 5;
				sprintf(str, "%8d", playerData->coins);
				gfx_draw_text(224, 98, str);
			}
			if (gameData->redraw) {
				gameData->redraw = 0;
				break;
			}
		}

		gfx_draw_striker(gameData);
		gfx_draw_ball(gameData);
	}
	LED_update();
	hw_sound_update();
}