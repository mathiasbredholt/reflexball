#include "graphics.h"
#include "hw_time.h"
#include "hw_input.h"

char menuButtons[4][12] = { "play", "load game", "exit" };

void menu_show() {
	gfx_window(64, 16, 192, 80);
	gfx_draw_text(68, 18, "reflexball");

	gfx_draw_btn(108, 24, menuButtons[0], 1);
	gfx_draw_btn(108, 32, menuButtons[1], 0);
	gfx_draw_btn(108, 40, menuButtons[2], 0);
}

void menu_update(int *mode, char *lastKey, int *focus, int *animFrame1, int *animFrame2) {
	char key;

	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		key = hw_read_key();
		if (key != *lastKey) {
			*lastKey = key;

			if (*lastKey & 4) {
				*mode = *focus + 1;
				*focus = 0;
			}

			gfx_draw_btn_focus(108, 24 + 8 * *focus, menuButtons[*focus], 0);

			if (*lastKey & 0x02) --(*focus);
			if (*lastKey & 0x01) ++(*focus);

			*focus %= sizeof(menuButtons) / sizeof(menuButtons[0]) - 1;
			if (*focus < 0) *focus += sizeof(menuButtons) / sizeof(menuButtons[0]) - 1;

			gfx_draw_btn_focus(108, 24 + 8 * *focus, menuButtons[*focus], 1);
		}

		gfx_draw_stars(*animFrame1);
		gfx_draw_stars(*animFrame2);
		++*animFrame1;
		++*animFrame2;
		*animFrame1 %= 208;
		*animFrame2 %= 208;
	}
}
