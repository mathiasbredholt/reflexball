#if defined(_Z8F6403)
#include <sio.h>
#else
#include <stdio.h>
#endif


#include "gui.h"
#include "game_data.h"
#include "graphics.h"
#include "hw_input.h"
#include "hw_time.h"
#include "hw_sound.h"
#include "hw_flash.h"

char menuButtons[4][12] = { "play", "load game", "exit" };
char mapButtons[9][9] = { "dokuu", "alderaan", "tatoiine", "darth", "unknown", "the pub", "save", "shop", "menu" };
char shopDescriptions[6][2][50] = { {"battery                              ", "more power for your ship                     "}, {"high power superconductor force field", "gives the ball an extra push                 "}, {"new ship                             ", "bigger and faster ship                       "} , {"photonic laser blaster               ", "low power laser cannon                       "}, {"intergalactic laser annihilator      ", "annihilates any obstacle                     "}, {"hyper-density black hole launcher    ", "a black hole strapped to a rocket   nuff said"} };

void menu_show() {
	// Call drawing functions for GUI creation
	hw_sound_set_music(0);
	gfx_window(1, 64, 16, 192, 80);
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

	gfx_window(1, -1, -1, 257, 104);

	gfx_draw_text(9, 8, 2, "welcome to my shop");
	gfx_draw_text(9, 8, 6, "what does your heart desire");

	for (i = 0; i < 2; ++i) {
		for (j = 0; j < 3; j++) {
			gfx_draw_meter(37 + 64 * j, 40 + 25 * i, playerData->items[j + i * 3]);
			gfx_draw_item(48 + 64 * j, 42 + 25 * i, j + i * 3);
			gfx_draw_btn(36 + 64 * j, 56  + 25 * i, playerData->items[j + i * 3] == itemMax[j + i * 3] ? "max" : "buy", j + i * 3 == 0);
		}
	}

	gfx_draw_btn(212, 90, "exit", 0);

	gfx_draw_text(9, 12, 24, shopDescriptions[0][0]);
	gfx_draw_text(9, 12, 30, shopDescriptions[0][1]);
	gfx_draw_text(9, 210, 24, "     ");
	sprintf(str, "price  %4d", itemPrice[0]);
	gfx_draw_text(9, 210, 30, str);

	sprintf(str, "coins %8d", playerData->coins);
	gfx_draw_text(9, 196, 2, str);
}

void shop_update(int *mode, char *lastKey, int *focus, PlayerData *playerData, GameData *gameData) {
	char key;
	char str[15];
	int price;

	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		key = hw_read_key();
		if (key != *lastKey) {
			*lastKey = key;


			// select event
			if (*lastKey & 4) {
				if (*focus != 6) {
					price = itemPrice[*focus] << playerData->items[*focus];
					if (playerData->items[*focus] < itemMax[*focus] && playerData->coins >= price) {
						hw_sound_play(1);
						playerData->coins -= price;
						++playerData->items[*focus];
						if (playerData->items[*focus] < itemMax[*focus]) {
							sprintf(str, "price  %4d", price << 1);
						} else {
							sprintf(str, "maxed      ");
						}
						gfx_draw_text(9, 210, 30, str);
						if ((*focus == 3 || *focus == 4) && playerData->items[*focus] == 1) {
							gfx_draw_text(9, 12, 24, shopDescriptions[4][0]);
							gfx_draw_text(9, 12, 30, shopDescriptions[4][1]);
						}
						if (*focus == 0) {
							playerData->energyMax += 0x7FFF;
						} else if (*focus == 1) {
							gameData->strikerSpeed += 1;
							gameData->strikerSize += 4;
						} else if (*focus == 2) {
							gameData->bouncinessFactor += 2;
						}
					} else {
						hw_sound_play(0);
					}

					sprintf(str, "coins %8d", playerData->coins);
					gfx_draw_text(9, 196, 2, str);

					gfx_draw_meter(37 + 64 * (*focus % 3), 40 + 25 * (*focus / 3), playerData->items[*focus]);

					if (playerData->items[*focus] == itemMax[*focus]) {
						gfx_draw_btn(36 + 64 * (*focus % 3), 56  + 25 * (*focus / 3), "max", 1);
					}

				} else {
					hw_sound_play(1);
					*focus = 0;
					*mode = 1;
				}

			} else if (*lastKey & 0x03) {
				// focus handling
				if (*focus == 6) {
					gfx_draw_btn_focus(212, 90, "exit", 0);
				} else {
					gfx_draw_btn(
					    36 + 64 * (*focus % 3),
					    56  + 25 * (*focus / 3),
					    playerData->items[*focus] == itemMax[*focus] ? "max" : "buy",
					    0
					);
				}

				if (*lastKey & 0x01) ++(*focus);
				if (*lastKey & 0x02) --(*focus);

				*focus %= 7;
				if (*focus < 0) *focus += 7;
				if (*focus == 6) {
					gfx_draw_btn_focus(212, 90, "exit", 1);
					gfx_draw_text(9, 12, 24, "                                 ");
					gfx_draw_text(9, 12, 30, "                                                             ");
				} else {
					price = itemPrice[*focus] << playerData->items[*focus];
					if (*focus == 3 || *focus == 4) {
						gfx_draw_text(9, 12, 24, shopDescriptions[playerData->items[*focus] ? 4 : 3][0]);
						gfx_draw_text(9, 12, 30, shopDescriptions[playerData->items[*focus] ? 4 : 3][1]);
						gfx_draw_text(9, 210, 24, *focus == 3 ? "left " : "right");
					} else {
						gfx_draw_text(9, 12, 24, shopDescriptions[*focus][0]);
						gfx_draw_text(9, 12, 30, shopDescriptions[*focus][1]);
						gfx_draw_text(9, 210, 24, "     ");
					}
					if (playerData->items[*focus] < itemMax[*focus]) {
						sprintf(str, "price  %4d", price);
					} else {
						sprintf(str, "maxed      ");
					}
					gfx_draw_text(9, 210, 30, str);
					gfx_draw_btn(
					    36 + 64 * (*focus % 3),
					    56  + 25 * (*focus / 3),
					    playerData->items[*focus] == itemMax[*focus] ? "max" : "buy",
					    1
					);
				}
			}
		}
	}
}

void map_show(PlayerData *playerData, int *focus) {
	hw_sound_set_music(1);

	gfx_window(1, -1, -1, 257, 104);

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

			if (key & 8) {
				// Cheat key
				++playerData->progress;
			}

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
	gfx_window(1, -1, -1, 257, 104);

	if (gameData->level == 0) {

		//dokuu
		// gfx_draw_text(9, 119, 35, "dokuu");
		gfx_draw_thumb(122, 40, 0, 9);

		gfx_draw_text(9, 57, 60, "oh no boss");
		gfx_draw_text(9, 57, 63, "theres an asteroid field");
		gfx_draw_text(9, 57, 66, "its blocking our way past dokuu");
		gfx_draw_text(9, 57, 69, "prepare the balls for max bounciness");

	} else if (gameData->level == 1) {

		// ALderan
		// gfx_draw_text(9, 113, 35, "alderaan");
		gfx_draw_thumb(122, 40, 1, 10);
		gfx_draw_text(9, 71, 60, "phew that was a close one");
		gfx_draw_text(9, 71, 63, "we almost lost all our balls");
		gfx_draw_text(9, 71, 66, "what is this");
		gfx_draw_text(9, 71, 69, "oh no boss");
		gfx_draw_text(9, 71, 12, "an evil alderaan has appeared");
		gfx_draw_text(9, 71, 75, "what are your orders");


	} else if (gameData->level == 2) {

		// tatoiine

		// gfx_draw_text(9, 113, 35, "tatoiine");
		gfx_draw_thumb(122, 40, 2, 11);
		gfx_draw_text(9, 77, 60, "finally");
		gfx_draw_text(9, 77, 63, "lets hope were safe");
		gfx_draw_text(9, 77, 66, "oh no boss");
		gfx_draw_text(9, 77, 69, "a huge monster just jumped");
		gfx_draw_text(9, 77, 72, "in to weapons range");
		gfx_draw_text(9, 77, 65, "and its opening fire");
		gfx_draw_text(9, 77, 78, "boss");

	} else if (gameData->level == 3) {

		// darth

		// gfx_draw_text(9, 107, 35, "darth vader");
		gfx_draw_thumb(122, 40, 3, 12);

		gfx_draw_text(9, 75, 60, "the horrors of space travel");
		gfx_draw_text(9, 75, 63, "surely we must be safe now");
		gfx_draw_text(9, 75, 66, "oh no boss");
		gfx_draw_text(9, 75, 69, "its the feared pirate queen");
		gfx_draw_text(9, 75, 72, "darth vader");

	} else if (gameData->level == 4) {
		//	unknown

		// gfx_draw_text(9, 95, 35, "somewhere unknown");
		gfx_draw_thumb(122, 40, 4, 13);
		gfx_draw_text(9, 43, 60, "argh boss");
		gfx_draw_text(9, 43, 63, "destroying vaders ship has");
		gfx_draw_text(9, 43, 66, "warped the space time continuum");
		gfx_draw_text(9, 43, 69, "were being sucked in to a new dimension");
		gfx_draw_text(9, 43, 72, "and its filled with generic arkanoid levels");
		gfx_draw_text(9, 43, 75, "good thing we brought our best balls");

	} else if (gameData->level == 5) {
		// the pub

		// gfx_draw_text(9, 70, 35, "pub at the end of the universe");
		gfx_draw_thumb(122, 40, 5, 14);
		gfx_draw_text(9, 33, 60, "wow boss we made it");
		gfx_draw_text(9, 33, 63, "we safely returned to normal 2 dimensional space");
		gfx_draw_text(9, 33, 66, "but where are we");
		gfx_draw_text(9, 33, 69, "i sure could go for some food");
		gfx_draw_text(9, 33, 72, "oh look its the pub at the end of the universe");
		gfx_draw_text(9, 33, 75, "boss");
		gfx_draw_text(9, 33, 78, "they refuse to serve us");

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

void intro_play() {
	gfx_window(1, 5, 36, 119 , 89);
	gfx_window(0, 139, 36, 252 , 89);
	gfx_draw_title();
// story info, window to the left

	gfx_draw_text(9, 8, 39, "welcome to the glorious");
	gfx_draw_text(9, 8, 42, "tale of commander boss");
	gfx_draw_text(9, 8, 45, "a grand adventurer");
	gfx_draw_text(9, 8, 48, "pilot of the striker");
	gfx_draw_text(9, 8, 51, "a ship capable of bouncing");
	gfx_draw_text(9, 8, 54, "balls made of pure energy");
	gfx_draw_text(9, 8, 57, "a ship that supports the ");
	gfx_draw_text(9, 8, 60, "most advanced weaponry");
	gfx_draw_text(9, 8, 63, "in the universe");
	gfx_draw_text(9, 8, 66, "if you can pay");
	gfx_draw_text(9, 8, 72, "unfortunately");
	gfx_draw_text(9, 9, 75, "you are dirt poor");
	gfx_draw_text(9, 9, 78, "better go mining and hope");
	gfx_draw_text(9, 9, 81, "for some treasure");

	gfx_draw_text(9, 9, 76, "theres gold in them blocks");

// Meta info,
#if defined(_Z8F6403)
	gfx_draw_text(9, 143, 39, "use the command stick");
#else
	gfx_draw_text(9, 143, 39, "use a and d");
#endif

	gfx_draw_text(9, 143, 42, "to control the striker");
	gfx_draw_text(9, 143, 45, "to navigate the menus");
#if defined(_Z8F6403)
	gfx_draw_text(9, 143, 48, "use the buttons");
#else
	gfx_draw_text(9, 143, 48, "use a and d");
#endif
	gfx_draw_text(9, 143, 51, "buy upgrades for the");
	gfx_draw_text(9, 143, 54, "weapons and the striker");
	gfx_draw_text(9, 143, 57, "in the shop");
	gfx_draw_text(9, 143, 63, "be careful you dont");
	gfx_draw_text(9, 143, 66, "run out of energy");
	gfx_draw_text(9, 143, 72, "good luck");
	gfx_draw_text(9, 143, 78, "press any key to continue");
}

void intro_update(int *mode, char *lastKey) {
	char key;
	key = hw_read_key();
	if (key != *lastKey) {
		if (key != 0) *mode = 0;
	}
}