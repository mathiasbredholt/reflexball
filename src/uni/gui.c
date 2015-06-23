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
char shopDescriptions[6][2][50] = { {"battery                              ", "more power for your ship                     "}, {"high power superconductor force field", "gives the ball an extra push                 "}, {"upgraded thrusters                   ", "give your ship ninja reflexes                "} , {"photonic laser blaster               ", "low power laser cannon                       "}, {"intergalactic laser annihilator      ", "annihilates any obstacle                     "}, {"hyper-density black hole launcher    ", "a black hole strapped to a rocket   nuff said"} };

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
							gameData->strikerSpeed += 2;
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
	int y;
	gfx_window(1, -1, -1, 257, 104);

	y = 60;


	if (gameData->level == 0) {

		//dokuu
		// gfx_draw_text(9, 119, 35, "dokuu");
		gfx_draw_thumb(122, 40, 0, 9);
		// gfx_draw_text(9, 57, y, "oh no boss");
		// gfx_draw_text(9, 57, y + 3, "theres an asteroid field");
		// gfx_draw_text(9, 57, y + 6, "its blocking our way past dokuu");
		// gfx_draw_text(9, 57, y + 9, "prepare the balls for max bounciness");

	} else if (gameData->level == 1) {

		// ALderan
		// gfx_draw_text(9, 113, 35, "alderaan");
		gfx_draw_thumb(122, 40, 1, 10);
		// gfx_draw_text(9, 71, y, "phew that was a close one");
		// gfx_draw_text(9, 71, y + 3, "we almost lost all our balls");
		// gfx_draw_text(9, 71, y + 6, "what is this");
		// gfx_draw_text(9, 71, y + 9, "oh no boss");
		// gfx_draw_text(9, 71, y + 12, "an evil alderaan has appeared");
		// gfx_draw_text(9, 71, y + 15, "what are your orders");

	} else if (gameData->level == 2) {

		// tatoiine

		// gfx_draw_text(9, 113, 35, "tatoiine");
		gfx_draw_thumb(122, 40, 2, 11);
		// gfx_draw_text(9, 77, y, "finally");
		// gfx_draw_text(9, 77, y + 3, "lets hope were safe");
		// gfx_draw_text(9, 77, y + 6, "oh no boss");
		// gfx_draw_text(9, 77, y + 9, "a huge monster just jumped");
		// gfx_draw_text(9, 77, y + 12, "in to weapons range");
		// gfx_draw_text(9, 77, y + 15, "and its opening fire");
		// gfx_draw_text(9, 77, y + 18, "boss");
	} else if (gameData->level == 3) {

		// darth

		// gfx_draw_text(9, 107, 35, "darth vader");
		gfx_draw_thumb(122, 40, 3, 12);
		// gfx_draw_text(9, 75, y, "the horrors of space travel");
		// gfx_draw_text(9, 75, y + 3, "surely we must be safe now");
		// gfx_draw_text(9, 75, y + 6, "oh no boss");
		// gfx_draw_text(9, 75, y + 9, "its the feared pirate queen");
		// gfx_draw_text(9, 75, y + 12, "darth vader");

	} else if (gameData->level == 4) {
		//	unknown

		// gfx_draw_text(9, 95, 35, "somewhere unknown");
		gfx_draw_thumb(122, 40, 4, 13);
		// gfx_draw_text(9, 43, y, "argh boss");
		// gfx_draw_text(9, 43, y + 3, "destroying vaders ship has");
		// gfx_draw_text(9, 43, y + 6, "warped the space time continuum");
		// gfx_draw_text(9, 43, y + 9, "were being sucked in to a new dimension");
		// gfx_draw_text(9, 43, y + 12, "and its filled with generic arkanoid levels");
		// gfx_draw_text(9, 43, y + 15, "good thing we brought our best balls");

	} else if (gameData->level == 5) {
		// the pub

		// gfx_draw_text(9, 70, 35, "pub at the end of the universe");
		gfx_draw_thumb(122, 40, 5, 14);
		// gfx_draw_text(9, 33, y, "wow boss we made it");
		// gfx_draw_text(9, 33, y + 3, "we safely returned to normal 2 dimensional space");
		// gfx_draw_text(9, 33, y + 6, "but where are we");
		// gfx_draw_text(9, 33, y + 9, "i sure could go for some food");
		// gfx_draw_text(9, 33, y + 12, "oh look its the pub at the end of the universe");
		// gfx_draw_text(9, 33, y + 15, "boss");
		// gfx_draw_text(9, 33, y + 18, "they refuse to serve us");

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
	int y;
	gfx_window(1, 5, 16 + 22, 119 , 101 - 12);
	gfx_window(0, 139, 16 + 22, 252 , 101 - 12);
	gfx_draw_title(47, 3 + 22);
// story info, window to the left

	y = 39;
	gfx_draw_text(9, 8 , y, "welcome to the glorious");
	gfx_draw_text(9, 8, y + 3, "tale of commander boss");
	gfx_draw_text(9, 8, y + 6, "a grand adventurer");
	gfx_draw_text(9, 8, y + 9, "pilot of the striker");
	gfx_draw_text(9, 8, y + 12, "a ship capable of bouncing");
	gfx_draw_text(9, 8, y + 15, "balls made of pure energy");
	gfx_draw_text(9, 8, y + 18, "a ship that supports the ");
	gfx_draw_text(9, 8, y + 21, "most advanced weaponry");
	gfx_draw_text(9, 8, y + 24, "in the universe");
	gfx_draw_text(9, 8, y + 27, "if you can pay");
	gfx_draw_text(9, 8, y + 33, "unfortunately");
	gfx_draw_text(9, 9, y + 36, "you are dirt poor");
	gfx_draw_text(9, 9, y + 39, "better go mining and hope");
	gfx_draw_text(9, 9, y + 42, "for some treasure");

	gfx_draw_text(9, 9, y + 45, "theres gold in them blocks");

// Meta info,
#if defined(_Z8F6403)
	gfx_draw_text(9, 143, y, "use the command stick");
#else
	gfx_draw_text(9, 143, y, "use a and d");
#endif

	gfx_draw_text(9, 143, y + 3, "to control the striker");
	gfx_draw_text(9, 143, y + 6, "to navigate the menus");
#if defined(_Z8F6403)
	gfx_draw_text(9, 143, y + 9, "use the buttons");
#else
	gfx_draw_text(9, 143, y + 9, "use a and d");
#endif
	gfx_draw_text(9, 143, y + 12, "buy upgrades for the");
	gfx_draw_text(9, 143, y + 15, "weapons and the striker");
	gfx_draw_text(9, 143, y + 18, "in the shop");
	gfx_draw_text(9, 143, y + 24, "be careful you dont");
	gfx_draw_text(9, 143, y + 27, "run out of energy");
	gfx_draw_text(9, 143, y + 33, "good luck");
	gfx_draw_text(9, 143, y + 39, "press any key to continue");
}

void intro_update(int *mode, char *lastKey) {
	char key;
	key = hw_read_key();
	if (key != *lastKey) {
		if (key != 0) *mode = 0;
	}
}