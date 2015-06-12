#include "graphics.h"

void lvl_create_lvl1() {
	int numberOfBars = 8;
	int i;

	gfx_draw_bounds();

	for (i = 0; i < numberOfBars; ++i) {
		gfx_draw_bar(8 + i * 6, 4);
	}
}