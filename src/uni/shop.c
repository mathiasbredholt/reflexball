#if defined(__APPLE__)||defined(__WIN32__)
#include <stdio.h>
#endif

#if defined(_Z8F6403)
#include <sio.h>
#endif

#include "game_engine.h"
#include "graphics.h"
#include "hw_input.h"
#include "hw_time.h"

void shop_show(PlayerData *playerData) {
	int i, j;
	char str[15];

	gfx_window(-1, -1, 258, 104);

	gfx_draw_text(8, 2, "welcome to my shop");
	gfx_draw_text(8, 6, "what does your heart desire");

	for (i = 0; i < 2; ++i) {
		for (j = 0; j < 4; j++) {
			gfx_draw_meter(32 + 48 * j, 16 + 32 * i, playerData->items[i + j * 4]);
			gfx_draw_item(44 + 48 * j, 18 + 32 * i, i + j * 4);
			gfx_draw_btn(32 + 48 * j, 32  + 32 * i, "buy", i + j * 4 == 0);
		}
	}

	gfx_draw_btn(212, 90, "exit", 0);

	sprintf(str, "coins %8d", playerData->coins);
	gfx_draw_text(196, 2, str);
}

void shop_update(int *mode, char *lastKey, int *focus, PlayerData *playerData) {
	int i, j;
	char key;

	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		key = hw_read_key();
		if (key != *lastKey) {
			*lastKey = key;

			// if (*focus == 8) {
			// 	gfx_draw_btn(16, 16, "exit", 0);
			// } else {
			// 	gfx_draw_btn_focus(32 + *focus * 24, 64, "buy", 0);
			// }

			if (*lastKey & 0x01) ++(*focus);
			if (*lastKey & 0x02) --(*focus);

			*focus %= 9;
			if (*focus < 0) *focus += 9;

			// if (*focus == 8) {
			// 	gfx_draw_btn(16, 16, "exit", 1);
			// } else {
			// 	gfx_draw_btn_focus(32 + *focus * 24, 64, "buy", 1);
			// }

			if (*lastKey & 4 && *focus != 8) {
				char str[15];
				--playerData->coins;
				++playerData->items[*focus];

				sprintf(str, "coins %8d", playerData->coins);
				gfx_draw_text(196, 2, str);
			}
			if (*lastKey & 4 && *focus == 8) {
				*focus = 0;
				*mode = 1;
			}

			// for (i = 0; i < 8; ++i) {
			// 	gfx_draw_meter(32 + 24 * i, 40, playerData->items[i]);
			// }
		}


	}
}