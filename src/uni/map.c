#include "map.h"
#include "game_engine.h"
#include "hw_time.h"
#include "hw_input.h"
#include "graphics.h"

char mapButtons[5][9] = { "shop", "dokuu", "alderaan", "tatoiine", "menu" };

void map_show(PlayerData *playerData) {
	gfx_window(0, 0, 258, 104);

	gfx_draw_text(6, 2, "the andromeda galaxy");

	gfx_draw_btn(6, 6, mapButtons[0], 1);



	gfx_draw_thumb(32, 16, 0);
	gfx_draw_btn(32, 32, mapButtons[1], 0);

	gfx_draw_thumb(32, 40, 1);
	gfx_draw_btn(32, 56, mapButtons[2], 0);

	gfx_draw_thumb(32, 64, 2);
	gfx_draw_btn(32, 80, mapButtons[3], 0);

	gfx_draw_btn(212, 90, mapButtons[4], 0);
}

void map_update(int *mode, char *lastKey, int *focus, GameData *gameData, PlayerData *playerData) {
	char key;

	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		key = hw_read_key();

		if (key != *lastKey) {
			*lastKey = key;

			if (*lastKey & 4) {
				if (*focus > 0 && *focus < 4) {
					gameData->level = *focus - 1;
					*mode = 2;
				} else if (*focus == 0) {
					*mode = 3;
				} else {
					*mode = 0;
				}
				*focus = 0;
			}

			if (*focus == 0) {
				gfx_draw_btn_focus(6, 6, mapButtons[0], 0);
			} else if (*focus == 1) {
				gfx_draw_btn_focus(32, 32, mapButtons[1], 0);
			} else if (*focus == 2) {
				gfx_draw_btn_focus(32, 56, mapButtons[2], 0);
			} else if (*focus == 3) {
				gfx_draw_btn_focus(32, 80, mapButtons[3], 0);
			} else if (*focus == 4) {
				gfx_draw_btn_focus(212, 90, mapButtons[4], 0);
			}

			if (*lastKey & 0x02) --(*focus);
			if (*lastKey & 0x01) ++(*focus);

			*focus %= 5;
			if (*focus < 0) * focus += 5;

			if (*focus == 0) {
				gfx_draw_btn_focus(6, 6, mapButtons[0], 1);
			} else if (*focus == 1) {
				gfx_draw_btn_focus(32, 32, mapButtons[1], 1);
			} else if (*focus == 2) {
				gfx_draw_btn_focus(32, 56, mapButtons[2], 1);
			} else if (*focus == 3) {
				gfx_draw_btn_focus(32, 80, mapButtons[3], 1);
			} else if (*focus == 4) {
				gfx_draw_btn_focus(212, 90, mapButtons[4], 1);
			}
		}
	}
}
