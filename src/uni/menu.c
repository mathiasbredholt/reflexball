#include "graphics.h"
#include "hw_time.h"
#include "hw_input.h"
#include <stdio.h>

void menu_show() {
	gfx_window(64, 16, 192, 80, 1);
	gfx_draw_text(68, 18, "reflexball");

	gfx_draw_btn(68, 24, "play", 1);
	gfx_draw_btn(68, 32, "shop", 0);
	gfx_draw_btn(68, 40, "load", 0);
	gfx_draw_btn(68, 48, "exit", 0);
}

void menu_update(int *mode, char *lastKey, int *focus) {
	char key;
	char btns[4][5] = { "play", "shop", "load", "exit" };

	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		key = hw_read_key();
		if (key != *lastKey) {
			*lastKey = key;

			if (*lastKey & 4) {
				*mode = *focus + 1;
				*focus = 0;
			}

			gfx_draw_btn_focus(68, 24 + 8 * *focus, btns[*focus], 0);

			if (*lastKey & 0x02) --(*focus);
			if (*lastKey & 0x01) ++(*focus);
			*focus &= 0x03;

			gfx_draw_btn_focus(68, 24 + 8 * *focus, btns[*focus], 1);
		}
	}
}
