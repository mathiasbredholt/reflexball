#include "levels.h"
#include "game_engine.h"
#include "graphics.h"

void lvl_create_menu() {
	gfx_window(64, 16, 192, 80, 1);
	game_wait_for_input();
	gfx_window(64, 16, 192, 80, 0);
	// lvl_create_lvl1();
}

void lvl_create_lvl1(char blockData[4][15][2]) {
	blockData[0][0][0] = 0xFF;
	blockData[0][0][1] = 0xFF;

	gfx_draw_bounds();
	gfx_draw_all_blocks(blockData);
}