#include "game_engine.h"
#include "hw_time.h"
// #include "hw_input.h"
// #include "hw_LED.h"
// #include "sounds.h"
// #include "levels.h"
#include "graphics.h"
// #include "physics.h"

char _strikerX, _strikerY, _ballX, _ballY;

void game_init() {
	hw_time_init();
}

void game_update() {
	if (hw_time_get_nextframe()) {
		hw_time_set_nextframe(0);

		// phy_simulate();
		++_ballY;
	}
}

void game_init_player() {
	_strikerX = 128;
	_strikerY = 92;
	gfx_draw_striker(_strikerX, _strikerY);

	_ballX = 128;
	_ballY = 84;
	gfx_draw_ball(_ballX, _ballY);
}