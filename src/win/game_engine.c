#include <stdio.h>
#include "game_engine.h"
// #include "hw_time.h"
#include "hw_input.h"
// #include "hw_LED.h"
#include "levels.h"
#include "graphics.h"
#include "util.h"
// #include "sounds.h"
#include "physics.h"

int _strikerX, _strikerOldX;
TVector_8_8 _ballPos, _ballOldPos;
TVector_0_7 _ballVel;

void game_init() {
	hw_init();
	// hw_time_init();
	// LED_init();
	// LED_set_string("Welcome");
}

void game_update() {
	char key;

	// if (hw_time_get_next_frame()) {
	// 	hw_time_set_next_frame(0);

	_strikerOldX = _strikerX;
	_ballOldPos = _ballPos;

	key = hw_read_key();
	// key = 0;
	// printf("%d\n", (int) key);

	// move striker left
	if (key & 2) {
		_strikerX -= 256;
	}

	// move striker right
	if (key & 1) {
		_strikerX += 256;
	}

	// Calculate new ball position
	phy_simulate(&_ballPos, &_ballVel);

	gfx_draw_striker(_strikerOldX, _strikerX);
	gfx_draw_ball(_ballOldPos, _ballPos);
	// }
	// LED_update();
}

void game_init_player() {
	_strikerX = 128 << 8;
	gfx_draw_striker(_strikerOldX, _strikerX);

	_ballPos.x = 128 << 8;
	_ballPos.y = 84 << 8;

	_ballVel.x = 0;
	_ballVel.y = 128;

	phy_set_ball_speed(1);

	gfx_draw_ball(_ballPos, _ballPos);
}