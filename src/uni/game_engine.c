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

unsigned int _strikerX, _strikerOldX;
int _strikerSize;
TVector_8_8 _ballPos, _ballOldPos;
TVector_0_7 _ballVel;

void game_init() {
	hw_init();
	hw_time_init();
	LED_init();
	LED_set_string("Welcome");
	_strikerSize = 48;
}

void game_update(unsigned char blockData[4][15][2], char *lives, int *points) {
	char key, i;
	char * redraw = 0;
	int * blockHit;

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

		if (key & 4) lvl_create_menu();

		// Calculate new ball position
		for (i = 0; i < 6; ++i) {
			phy_simulate(blockData, &_ballPos, &_ballVel, _strikerX, redraw, blockHit);
			if (*redraw) {
				*redraw = 0;
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