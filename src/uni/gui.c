#if defined(__APPLE__)||defined(__WIN32__)
#include <stdio.h>
#endif

#if defined(_Z8F6403)
#include <sio.h>
#endif

#include "gui.h"
#include "game_data.h"
#include "graphics.h"
#include "hw_input.h"
#include "hw_time.h"
#include "hw_sound.h"


char menuButtons[4][12] = { "play", "load game", "exit" };
char mapButtons[5][9] = { "dokuu", "alderaan", "tatoiine", "darth", "unknown", "the pub", "shop", "menu" };

void menu_show() {
	// Call drawing functions for GUI creation
	hw_sound_set_music(0);
	gfx_window(64, 16, 192, 80);
	gfx_draw_text(68, 18, "reflexball");

	gfx_draw_btn(108, 24, menuButtons[0], 1);
	gfx_draw_btn(108, 32, menuButtons[1], 0);
	gfx_draw_btn(108, 40, menuButtons[2], 0);
}

void menu_update(int *mode, char *lastKey, int *focus, int *animFrame1, int *animFrame2) {
	char key;

	// Wait for frame interrupt flag
	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		// Get current key reading
		key = hw_read_key();

		// If key is rising edge
		if (key != *lastKey) {
			*lastKey = key;

			// Select key is pressed
			if (*lastKey & 4) {
				*mode = *focus + 1;
				*focus = 0;
			}

			// Blur button currently in focus
			gfx_draw_btn_focus(108, 24 + 8 * *focus, menuButtons[*focus], 0);

			// If left or right key is pressed increment or decrement focus index
			if (*lastKey & 0x02) --(*focus);
			if (*lastKey & 0x01) ++(*focus);

			// Apply modulus to focus index to make sure it stays in range
			*focus %= 3;
			if (*focus < 0) *focus += 3;

			// Focus button at the new focus index
			gfx_draw_btn_focus(108, 24 + 8 * *focus, menuButtons[*focus], 1);
		}

		// Update background animation
		gfx_draw_stars(*animFrame1);
		gfx_draw_stars(*animFrame2);
		++*animFrame1;
		++*animFrame2;
		*animFrame1 %= 208;
		*animFrame2 %= 208;
	}
}

void shop_show(PlayerData *playerData) {
	int i, j;
	char str[15];

	hw_sound_set_music(0);

	gfx_window(-1, -1, 257, 104);

	gfx_draw_text(8, 2, "welcome to my shop");
	gfx_draw_text(8, 6, "what does your heart desire");

	for (i = 0; i < 2; ++i) {
		for (j = 0; j < 4; j++) {
			gfx_draw_meter(32 + 48 * j, 16 + 32 * i, playerData->items[j + i * 4]);
			gfx_draw_item(44 + 48 * j, 18 + 32 * i, j + i * 4);
			gfx_draw_btn(32 + 48 * j, 32  + 32 * i, "buy", j + i * 4 == 0);
		}
	}

	gfx_draw_btn(212, 90, "exit", 0);

	sprintf(str, "coins %8d", playerData->coins);
	gfx_draw_text(196, 2, str);
}

void shop_update(int *mode, char *lastKey, int *focus, PlayerData *playerData) {
	char key;

	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		key = hw_read_key();
		if (key != *lastKey) {
			*lastKey = key;

			// select event
			if (*lastKey & 4) {
				if (*focus != 8) {
					int i, j;

					char str[15];
					--playerData->coins;
					++playerData->items[*focus];

					sprintf(str, "coins %8d", playerData->coins);
					gfx_draw_text(196, 2, str);

					for (i = 0; i < 2; ++i) {
						for (j = 0; j < 4; j++) {
							gfx_draw_meter(32 + 48 * j, 16 + 32 * i, playerData->items[j + i * 4]);
						}
					}
				} else {
					*focus = 0;
					*mode = 1;
				}

			}

			// focus handling
			if (*focus == 8) {
				gfx_draw_btn_focus(212, 90, "exit", 0);
			} else {
				gfx_draw_btn(
				    32 + 48 * (*focus & 0x03),
				    32  + 32 * ((*focus & 0x04) >> 2),
				    "buy",
				    0
				);
			}

			if (*lastKey & 0x01) ++(*focus);
			if (*lastKey & 0x02) --(*focus);

			*focus %= 9;
			if (*focus < 0) *focus += 9;

			if (*focus == 8) {
				gfx_draw_btn_focus(212, 90, "exit", 1);
			} else {
				gfx_draw_btn(
				    32 + 48 * (*focus & 0x03),
				    32  + 32 * ((*focus & 0x04) >> 2),
				    "buy",
				    1
				);
			}
		}
	}
}

void map_show(PlayerData *playerData) {
	hw_sound_set_music(1);

	gfx_window(-1, -1, 257, 104);

	gfx_draw_text(6, 2, "the andromeda galaxy");

	gfx_draw_btn(6, 6, mapButtons[0], 1);





	gfx_draw_thumb(4, 4, 0);
	gfx_draw_btn(32, 56, mapButtons[0], 1);

	gfx_draw_thumb(4, 20, 1);
	gfx_draw_btn(32, 80, mapButtons[1], 0);

	gfx_draw_thumb(32, 16, 2);
	gfx_draw_btn(32, 32, mapButtons[2], 0);

	gfx_draw_thumb(64, 40, 3);
	gfx_draw_btn(32, 56, mapButtons[3], 0);

	gfx_draw_thumb(128, 32, 4);
	gfx_draw_btn(128, 80, mapButtons[4], 0);

	gfx_draw_thumb(128, 64, 5);
	gfx_draw_btn(128, 80, mapButtons[5], 0);

	gfx_draw_btn(164, 90, mapButtons[7], 0);
	gfx_draw_btn(212, 90, mapButtons[8], 0);
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
					*mode = 5;
				} else if (*focus == 0) {
					*mode = 3;
					*focus = 0;
				} else {
					*mode = 0;
					*focus = 0;
				}
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
	gfx_window(-1, -1, 257, 104);

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