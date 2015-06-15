#include "levels.h"
#include "game_engine.h"
#include "graphics.h"

void lvl_create_menu() {
	gfx_window(64, 16, 192, 80, "REFLEXBALL", 1);
	game_wait_for_input();
	gfx_window(64, 16, 192, 80, "REFLEXBALL", 0);
	// lvl_create_lvl1();
}

void lvl_create_lvl1(char block_data[2][15][4]) {
	block_data[0][0][0] = 0xFF;
	block_data[1][0][0] = 0xFF;

	gfx_draw_bounds();
	gfx_draw_all_blocks(block_data);
}