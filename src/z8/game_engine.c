#include <sio.h>
#include "game_engine.h"
#include "hw_time.h"
#include "hw_input.h"
#include "hw_LED.h"
#include "levels.h"
#include "graphics.h"
// #include "sounds.h"
// #include "physics.h"

int _strikerOldX, _strikerX;
int _ballOldX, _ballOldY, _ballX, _ballY;
char last_key_input = 0;
char last_keys = 0;

void game_init() {
	HW_init();
	hw_time_init();
	LED_init();
	LED_setString("Welcome");
}

void game_update() {
	if (hw_time_get_nextframe()) {
		hw_time_set_nextframe(0);

		// phy_simulate();
		--_ballY;
		gfx_draw_striker(_strikerOldX, _strikerX);
		gfx_draw_ball(_ballOldX, _ballOldY, _ballX, _ballY);
	}
	LED_update();
}

void game_init_player() {
	_strikerX = 128;
	gfx_draw_striker(_strikerOldX, _strikerX);

	_ballX = 128;
	_ballY = 84;
	gfx_draw_ball(_ballOldX, _ballOldY, _ballX, _ballY);
}