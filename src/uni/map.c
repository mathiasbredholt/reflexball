#include "map.h"
#include "game_engine.h"
#include "hw_time.h"
#include "hw_input.h"
#include "graphics.h"

#define NUMBER_OF_BTNS 3
#define NUMBER_OF_LEVELS 2


void map_show(PlayerData *playerData) {
	gfx_window(0, 0, 258, 104);

	gfx_draw_text(6, 2, "the andromeda galaxy");

	gfx_draw_planet(32, 16, 0);
	gfx_draw_btn(32, 8, "alderaan", 1);
	gfx_draw_btn(32, 32, "namek", 0);
	gfx_draw_btn(32, 56, "back", 0);
}

void map_update(int *mode, char *lastKey, int *focus, GameData *gameData, PlayerData *playerData) {
	char key;
	char btns[NUMBER_OF_BTNS][9] = { "alderaan", "namek", "back" };

	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		key = hw_read_key();
		if (key != *lastKey) {
			*lastKey = key;

			if (*lastKey & 4) {
				if (*focus < NUMBER_OF_LEVELS) {
					gameData->level = *focus + 1;
					*mode = 3;
				} else {
					*mode = 0;
				}
				*focus = 0;
			}

			gfx_draw_btn_focus(32, 8 + 24 * *focus, btns[*focus], 0);

			if (*lastKey & 0x02) --(*focus);
			if (*lastKey & 0x01) ++(*focus);
			*focus %= NUMBER_OF_BTNS;
			if (*focus < 0) *focus += NUMBER_OF_BTNS;

			gfx_draw_btn_focus(32, 8 + 24 * *focus, btns[*focus], 1);
		}
	}
}
