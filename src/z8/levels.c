#include "graphics.h"

void lvl_create_menu() {
	gfx_window(64, 16, 192, 80, "REFLEXBALL");
}

void lvl_create_lvl1() {
	int numberOfBars = 15;
	int i, j;

	gfx_draw_bounds();

	for (i = 0; i < numberOfBars; ++i) {
		for (j = 0; j < numberOfBars; ++j) {
			gfx_draw_bar(10 + i * 16, 4 + j * 4,  i);
		}
	}
}