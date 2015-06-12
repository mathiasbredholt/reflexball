#include "graphics.h"

void lvl_create_lvl1() {
	int numberOfBars = 8;
	int i, j;

	gfx_draw_bounds();

	for (i = 0; i < numberOfBars; ++i) {
		for (j = 0; j < numberOfBars; ++j) {
			gfx_draw_bar(8 + i * 12, 4 + j * 2);
		}
	}
}