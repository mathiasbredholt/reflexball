#include "graphics.h"
#include "hw_input.h"
#include "hw_time.h"

void shop_show(char *items) {
	int i;

	gfx_window(0, 0, 256, 96, 1);

	gfx_draw_text(8, 2, "welcome to my shop");
	gfx_draw_text(8, 6, "what does your heart desire");

	for (i = 0; i < 8; ++i) {
		gfx_draw_meter(32 + 24 * i, 40, items[i]);
		gfx_draw_item(34 + 24 * i, 48, 0);
		gfx_draw_btn(32 + 24 * i, 64, "buy", i == 0);
	}

	gfx_draw_btn(16, 16, "exit", 0);
}

void shop_update(int *mode, char *lastKey, int *focus, char items[8]) {
	int i;
	char key;

	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		key = hw_read_key();
		if (key != *lastKey) {
			*lastKey = key;

			if (*lastKey & 2 && *focus > 0) {
				if (*focus == 8) {
					gfx_draw_btn(16, 16, "exit", 0);
				} else {
					gfx_draw_btn_focus(32 + *focus * 24, 64, "buy", 0);
				}
				--(*focus);
				gfx_draw_btn_focus(32 + *focus * 24, 64, "buy", 1);
			}

			if (*lastKey & 1 && *focus < 8) {
				gfx_draw_btn_focus(32 + *focus * 24, 64, "buy", 0);
				++(*focus);
				if (*focus == 8) {
					gfx_draw_btn(16, 16, "exit", 1);
				} else {
					gfx_draw_btn_focus(32 + *focus * 24, 64, "buy", 1);
				}
			}

			if (*lastKey & 4 && *focus != 8) {
				++items[*focus];
			} if (*lastKey & 4 && *focus == 8) {
				*focus = 0;
				*mode = 0;
			}

			for (i = 0; i < 8; ++i) {
				gfx_draw_meter(32 + 24 * i, 40, items[i]);
			}
		}


	}
}