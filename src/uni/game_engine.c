// game_engine.c

#include "game_engine.h"
#include "hw_time.h"
#include "hw_input.h"
#include "hw_LED.h"
#include "levels.h"
#include "graphics.h"
#include "util.h"
#include "physics.h"
// #include "sounds.h"
// #include <sio.h>
// #include "ansi.h"

unsigned int _strikerX, _strikerOldX;
int _strikerSize;
TVector_8_8 _ballPos, _ballOldPos;
TVector_0_7 _ballVel;

void game_init(unsigned char blockData[4][15][2], PlayerData *playerData) {
	int i;
	hw_init();
	hw_time_init();
	LED_init();
	LED_set_string("Welcome");

	for (i = 0; i < NUMBER_OF_ITEMS; ++i) {
		playerData->items[i] = 0;
	}

	playerData->energy = 255;
	playerData->coins = 0;


	_strikerSize = 48;
}

void game_update(unsigned char blockData[4][15][2], PlayerData *playerData) {
	char key, i;
	int redraw = 0;
	int blockHit = 0;

	// if (hw_read_key() && hw_time_get_next_frame()) {
	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		_strikerOldX = _strikerX;
		_ballOldPos = _ballPos;

		key = hw_read_key();

		// move striker left
		if (key & 2 && _strikerX >= _strikerSize << 7) _strikerX -= 256;

		// move striker left
		if (key & 2 && _strikerX >= _strikerSize << 7) _strikerX -= 256;

		// move striker right
		if (key & 1 && _strikerX >> 8 <= 255 - ((_strikerSize >> 1) + 1)) _strikerX += 256;

		// move striker right
		if (key & 1 && _strikerX >> 8 <= 255 - ((_strikerSize >> 1) + 1)) _strikerX += 256;

		// if (key & 4) lvl_create_menu();

		// Calculate new ball position
		for (i = 0; i < 4; ++i) {
			phy_simulate(blockData, &_ballPos, &_ballVel, _strikerX, &redraw, &blockHit);
			if (blockHit) {
				(blockHit >> 8) ? gfx_draw_block(blockHit & 0x000F, blockHit >> 4 & 0x000F, (blockHit >> 8) - 1) : gfx_erase_block(blockHit & 0x000F, blockHit >> 4 & 0x000F);
				blockHit = 0;

				// update score
				playerData->coins += 5;
				gfx_draw_number(240, 98, playerData->coins);
			}
			if (redraw) {
				redraw = 0;
				break;
			}
		}

		gfx_draw_striker(_strikerOldX, _strikerX);
		gfx_draw_ball(_ballOldPos, _ballPos);
	}
	LED_update();
}

void game_init_player() {
	_strikerX = 128 << 8;

	_ballPos.x = 128 << 8;
	_ballPos.y = 90 << 8;

	_ballVel.x = -32;
	_ballVel.y = -32;

	phy_set_ball_speed(2);
	phy_set_striker_size(_strikerSize);
	gfx_set_striker_size(_strikerSize);

	gfx_draw_striker(_strikerOldX, _strikerX);
	gfx_draw_ball(_ballPos, _ballPos);
}

void game_wait_for_input() {
	hw_wait_for_key();
}