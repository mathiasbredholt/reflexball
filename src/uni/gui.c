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
#include "hw_flash.h"
#include "lore.h"

char menuButtons[4][12] = { "play", "load game", "exit" };
char mapButtons[9][9] = { "dokuu", "alderaan", "tatoiine", "darth", "unknown", "the pub", "save", "shop", "menu" };

void menu_show() {
	// Call drawing functions for GUI creation
	hw_sound_set_music(0);
	gfx_window(64, 16, 192, 80);
	gfx_draw_text(9, 68, 18, "reflexball");

	gfx_draw_btn(66, 73, menuButtons[0], 1);
	gfx_draw_btn(108, 73, menuButtons[1], 0);
	gfx_draw_btn(150, 73, menuButtons[2], 0);
}

void menu_update(int *mode, char *lastKey, int *focus, int *animFrame1, int *animFrame2, PlayerData *playerData) {
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
				hw_sound_play(1);
				*mode = 1;
				if (*focus == 1) {
					hw_flash_load(playerData);
				} else if (*focus == 2) {
					*mode = 6;
				}
				*focus = 0;

			} else if (*lastKey & 0x03) {
				// Blur button currently in focus
				gfx_draw_btn_focus(66 + 42 * *focus, 73, menuButtons[*focus], 0);

				// If left or right key is pressed increment or decrement focus index
				if (*lastKey & 0x02) --(*focus);
				if (*lastKey & 0x01) ++(*focus);

				// Apply modulus to focus index to make sure it stays in range
				*focus %= 3;
				if (*focus < 0) *focus += 3;

				// Focus button at the new focus index
				gfx_draw_btn_focus(66 + 42 * *focus, 73, menuButtons[*focus], 1);
			}
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
	hw_sound_play(1);	// Because a button was pressed to get here

	gfx_window(-1, -1, 257, 104);

	gfx_draw_text(9, 8, 2, "welcome to my shop");
	gfx_draw_text(9, 8, 6, "what does your heart desire");

	for (i = 0; i < 2; ++i) {
		for (j = 0; j < 4; j++) {
			gfx_draw_meter(32 + 48 * j, 16 + 32 * i, playerData->items[j + i * 4]);
			gfx_draw_item(44 + 48 * j, 18 + 32 * i, j + i * 4);
			gfx_draw_btn(32 + 48 * j, 32  + 32 * i, "buy", j + i * 4 == 0);
		}
	}

	gfx_draw_btn(212, 90, "exit", 0);

	sprintf(str, "coins %8d", playerData->coins);
	gfx_draw_text(9, 196, 2, str);
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
				hw_sound_play(1);
				if (*focus != 8) {
					int i, j;

					char str[15];
					--playerData->coins;
					++playerData->items[*focus];

					sprintf(str, "coins %8d", playerData->coins);
					gfx_draw_text(9, 196, 2, str);

					for (i = 0; i < 2; ++i) {
						for (j = 0; j < 4; j++) {
							gfx_draw_meter(32 + 48 * j, 16 + 32 * i, playerData->items[j + i * 4]);
						}
					}
				} else {
					*focus = 0;
					*mode = 1;
				}

			} else if (*lastKey & 0x03) {
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
}

void map_show(PlayerData *playerData, int *focus) {
	hw_sound_set_music(1);

	gfx_window(-1, -1, 257, 104);

	gfx_draw_text(9, 6, 2, "the andromeda galaxy");


	// level 1
	gfx_draw_thumb(16, 8, 0, 9);
	gfx_draw_btn(4, 25, mapButtons[0], *focus == 0);

	// level 2
	gfx_draw_thumb(32, 40, 1, playerData->progress >= 1 ? 10 : 7);
	gfx_draw_btn(20, 57, mapButtons[1], *focus == 1);

	// level 3
	gfx_draw_thumb(68, 76, 2, playerData->progress >= 2 ? 11 : 7);
	gfx_draw_btn(56, 93, mapButtons[2], *focus == 2);

	// level 4
	gfx_draw_thumb(116, 36, 3, playerData->progress >= 3 ? 12 : 7);
	gfx_draw_btn(104, 53, mapButtons[3], *focus == 3);

	// level 5
	gfx_draw_thumb(224, 48, 4, playerData->progress >= 4 ? 13 : 7);
	gfx_draw_btn(212, 65, mapButtons[4], *focus == 4);

	// level 6
	gfx_draw_thumb(204, 6, 5, playerData->progress >= 5 ? 14 : 7);
	gfx_draw_btn(192, 23, mapButtons[5], *focus == 5);

	// save
	gfx_draw_btn(131, 96, mapButtons[6], 0);

	// shop
	gfx_draw_btn(173, 96, mapButtons[7], 0);

	// menu
	gfx_draw_btn(215, 96, mapButtons[8], 0);
}

void map_update(int *mode, char *lastKey, int *focus, GameData *gameData, PlayerData *playerData) {
	char key;

	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		key = hw_read_key();

		if (key != *lastKey) {
			*lastKey = key;

			if (*lastKey & 4) {
				hw_sound_play(1);
				if (*focus < 6) {
					gameData->level = *focus;
					*mode = 2;
				} else if (*focus == 6) {
					hw_flash_save(playerData);
				} else if (*focus == 7) {
					*mode = 4;
					*focus = 0;
				} else {
					*mode = 0;
					*focus = 0;
				}
			} else if (*lastKey & 0x03) {
				if (*focus == 0) {
					gfx_draw_btn_focus(4, 25, mapButtons[0], 0);
				} else if (*focus == 1) {
					gfx_draw_btn_focus(20, 57, mapButtons[1], 0);
				} else if (*focus == 2) {
					gfx_draw_btn_focus(56, 93, mapButtons[2], 0);
				} else if (*focus == 3) {
					gfx_draw_btn_focus(104, 53, mapButtons[3], 0);
				} else if (*focus == 4) {
					gfx_draw_btn_focus(212, 65, mapButtons[4], 0);
				} else if (*focus == 5) {
					gfx_draw_btn_focus(192, 23, mapButtons[5], 0);
				} else if (*focus == 6) {
					gfx_draw_btn_focus(131, 96, mapButtons[6], 0);
				} else if (*focus == 7) {
					gfx_draw_btn_focus(173, 96, mapButtons[7], 0);
				} else if (*focus == 8) {
					gfx_draw_btn_focus(215, 96, mapButtons[8], 0);
				}

				if (*lastKey & 0x02) {
					if (*focus == 6) {
						*focus -= 6 - playerData->progress;
					} else {
						--*focus;
					}
				}
				if (*lastKey & 0x01) {
					if (*focus == playerData->progress) {
						*focus += 6 - playerData->progress;
					} else {
						++*focus;
					}
				}

				*focus %= 9;
				if (*focus < 0) * focus += 9;

				if (*focus == 0) {
					gfx_draw_btn_focus(4, 25, mapButtons[0], 1);
				} else if (*focus == 1) {
					gfx_draw_btn_focus(20, 57, mapButtons[1], 1);
				} else if (*focus == 2) {
					gfx_draw_btn_focus(56, 93, mapButtons[2], 1);
				} else if (*focus == 3) {
					gfx_draw_btn_focus(104, 53, mapButtons[3], 1);
				} else if (*focus == 4) {
					gfx_draw_btn_focus(212, 65, mapButtons[4], 1);
				} else if (*focus == 5) {
					gfx_draw_btn_focus(192, 23, mapButtons[5], 1);
				} else if (*focus == 6) {
					gfx_draw_btn_focus(131, 96, mapButtons[6], 1);
				} else if (*focus == 7) {
					gfx_draw_btn_focus(173, 96, mapButtons[7], 1);
				} else if (*focus == 8) {
					gfx_draw_btn_focus(215, 96, mapButtons[8], 1);
				}

			}
		}
	}
}


void map_info_show(GameData *gameData) {
	int y, i, j;
	gfx_window(-1, -1, 257, 104);

	y = 60;


	if (gameData->level == 0) {
		//dokuu
		gfx_draw_text(9, 119, 35, lore[0]);
		gfx_draw_thumb(122, 40, 0, 9);

		for (i = 1; i < 5; ++i) {
			gfx_draw_text(9, 57, y + i * 3, lore[i]);

		}
	} else if (gameData->level == 1) {
		// ALderan
		gfx_draw_text(9, 113, 35, lore[5]);
		gfx_draw_thumb(122, 40, 1, 10);

		for (i = 1; i < 7; ++i) {
			gfx_draw_text(9, 71, y + i * 3, lore[i + 5]);
		}

	} else if (gameData->level == 2) {
		// tatoiine

		gfx_draw_text(9, 113, 35, lore[12]);
		gfx_draw_thumb(122, 40, 2, 11);

		for (i = 1; i < 8; ++i) {
			gfx_draw_text(9, 77, y + i * 3, lore[i + 12]);
		}

	} else if (gameData->level == 3) {
		// darth

		gfx_draw_text(9, 107, 35, lore[20]);
		gfx_draw_thumb(122, 40, 3, 12);

		for (i = 1; i < 6; ++i)	{
			gfx_draw_text(9, 75, y + i * 3, lore[i + 20]);
		}

	} else if (gameData->level == 4) {
		//	unknown

		gfx_draw_text(9, 95, 35, lore[26]);
		gfx_draw_thumb(122, 40, 4, 13);

		for (i = 1; i < 7; ++i) {
			gfx_draw_text(9, 53, y + i * 3, lore[i + 26]);
		}

	} else if (gameData->level == 5) {
		// the pub

		gfx_draw_text(9, 70, 35, lore[33]);
		gfx_draw_thumb(122, 40, 5, 14);

		for (i = 1; i < 8; ++i) {
			gfx_draw_text(9, 33, y + i * 3, lore[i + 33]);
		}
	}
	gfx_draw_text(9, 5, 90, "press left to warp to starmap");
	gfx_draw_text(9, 170, 90, "press right to engage");
}

void map_info_update(int *mode, char *lastKey) {
	char key;
	key = hw_read_key();
	if (key != *lastKey) {
		*lastKey = key;
		if (*lastKey & 0x01) *mode = 3;
		if (*lastKey & 0x02) *mode = 1;

	}
}