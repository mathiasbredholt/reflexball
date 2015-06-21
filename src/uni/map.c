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
					map_info_show(focus);
					*mode = 5;
					// *mode = 2;
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


void map_info_show(int *map) {
	int y;

	//--map;
	gfx_window(0, 0, 258, 104);

	y = 60;

	if (*map == 1) {

		gfx_draw_text(119, 35, "dokuu");
		gfx_draw_thumb(122, 40, 0);
		gfx_draw_text(57, y, "oh no boss");
		gfx_draw_text(57, y + 3, "theres an asteroid field");
		gfx_draw_text(57, y + 6, "its blocking our way past dokuu");
		gfx_draw_text(57, y + 9, "prepare the balls for max bounciness");

	} else if (*map == 2) {

		gfx_draw_text(113, 35, "alderaan");
		gfx_draw_thumb(122, 40, 1);
		gfx_draw_text(71, y, "phew that was a close one");
		gfx_draw_text(71, y + 3, "we almost lost all our balls");
		gfx_draw_text(71, y + 6, "what is this");
		gfx_draw_text(71, y + 9, "oh no boss");
		gfx_draw_text(71, y + 12, "an evil alderaan has appeared");
		gfx_draw_text(71, y + 15, "what are your orders");

	} else if (*map == 3) {


		gfx_draw_text(113, 35, "tatoiine");
		gfx_draw_thumb(122, 40, 2);
		gfx_draw_text(77, y, "finally");
		gfx_draw_text(77, y + 3, "lets hope were safe");
		gfx_draw_text(77, y + 6, "oh no boss");
		gfx_draw_text(77, y + 9, "a huge monster just jumped");
		gfx_draw_text(77, y + 12, "in to weapons range");
		gfx_draw_text(77, y + 15, "and its opening fire");
		gfx_draw_text(77, y + 18, "boss");

	} else if (*map == 4) {

		gfx_draw_text(107, 35, "darth vader");
		gfx_draw_thumb(122, 40, 3);
		gfx_draw_text(75, y, "the horrors of space travel");
		gfx_draw_text(75, y + 3, "surely we must be safe now");
		gfx_draw_text(75, y + 6, "oh no boss");
		gfx_draw_text(75, y + 9, "its the feared pirate queen");
		gfx_draw_text(75, y + 12, "darth vader");

	} else if (*map == 5) {

		gfx_draw_text(95, 35, "somewhere unknown");
		gfx_draw_thumb(122, 40, 4);
		gfx_draw_text(43, y, "argh boss");
		gfx_draw_text(43, y + 3, "destroying vaders ship has");
		gfx_draw_text(43, y + 6, "warped the space time continuum");
		gfx_draw_text(43, y + 9, "were being sucked in to a new dimension");
		gfx_draw_text(43, y + 12, "and its filled with generic arkanoid levels");
		gfx_draw_text(43, y + 15, "good thing we brought our best balls");

	} else if (*map == 6) {

		gfx_draw_text(70, 35, "pub at the end of the universe");
		gfx_draw_thumb(122, 40, 5);
		gfx_draw_text(33, y, "wow boss we made it");
		gfx_draw_text(33, y + 3, "we safely returned to normal 2 dimensional space");
		gfx_draw_text(33, y + 6, "but where are we");
		gfx_draw_text(33, y + 9, "i sure could go for some food");
		gfx_draw_text(33, y + 12, "oh look its the pub at the end of the universe");
		gfx_draw_text(33, y + 15, "boss");
		gfx_draw_text(33, y + 18, "they refuse to serve us");

	}

	gfx_draw_text(5, 90, "press left to warp to starmap");
	gfx_draw_text(170, 90, "press right to engage");

}

void map_info_update(int *mode, char *lastKey) {
	char key;
	key = hw_read_key();
	if (key != *lastKey) {
		*lastKey = key;
		if (*lastKey & 0x01) *mode = 2;
		if (*lastKey & 0x02) *mode = 1;

	}
}

