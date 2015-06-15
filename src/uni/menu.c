#include "graphics.h"
#include "hw_time.h"
#include "hw_input.h"

void menu_show() {
	gfx_window(64, 16, 192, 80, 1);
	gfx_draw_text(68, 18, "reflexball");

	gfx_draw_btn(68, 24, "play", 1);
	gfx_draw_btn(68, 32, "shop", 0);
}

void menu_update(int *mode, char *lastKey) {
	char key;

	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		key = hw_read_key();
		if (key != *lastKey) {
			*lastKey = key;

			if (*lastKey & 4) {
				*mode = 2;
			}
		}
	}
};