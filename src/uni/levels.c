#include "levels.h"
#include "game_engine.h"
#include "graphics.h"

void lvl_create_menu() {
	gfx_window(64, 16, 192, 80, "REFLEXBALL", 1);
	game_wait_for_input();
	gfx_window(64, 16, 192, 80, "REFLEXBALL", 0);
	lvl_create_lvl1();
}

void lvl_create_lvl1() {
	gfx_draw_bounds();
	gfx_draw_bars();
}