/*
  ##      #    #   #  ####          ####   #  #    ##    ###    #  #   ####
 #  #    # #   ## ##  #             #      ## #   #  #    #     ## #   #
 #      #   #  # # #  ###           ###    # ##   #       #     # ##   ###
 # ##   #####  # # #  #             #      #  #   # ##    #     #  #   #
 #  #   #   #  #   #  #             #      #  #   #  #    #     #  #   #
  ##    #   #  #   #  ####          ####   #  #    ##    ###    #  #   ####
*/

#include "game_engine.h"
#include "game_data.h"
#include "hw_time.h"
#include "hw_input.h"
#include "hw_sound.h"
#include "hw_LED.h"
#include "hw_flash.h"
#include "levels.h"
#include "graphics.h"
#include "physics.h"
#include "story.h"
#include "charset.h"


#if defined(_Z8F6403)
#include <sio.h>
#else
#include <stdio.h>
#endif

char menuButtons[4][12] = { "play", "load game", "exit" };
char mapButtons[9][9] = { "dokuu", "alderaan", "tatoiine", "darth", "unknown", "the pub", "save", "shop", "menu" };
char shopDescriptions[6][2][50] = { {"battery                              ", "more power for your ship                     "}, {"high power superconductor force field", "gives the ball an extra push                 "}, {"new ship                             ", "bigger and faster ship                       "} , {"photonic laser blaster               ", "low power laser cannon                       "}, {"intergalactic laser annihilator      ", "annihilates any obstacle                     "}, {"hyper-density black hole launcher    ", "a black hole strapped to a rocket   nuff said"} };

void init(int *mode, int *focus, int *lastKey, int *animFrame1, int *animFrame2, PlayerData *playerData, GameData *gameData) {
	int i;
	char str[49];

	/////////////////////////
	// Hardware initialize //
	/////////////////////////

	hw_init();
	hw_time_init();
	hw_ADC_init();
	hw_sound_init();
	hw_flash_init();
	LED_init();

	///////////////////
	// gui variables //
	///////////////////
	*mode = 0;
	*focus = 0;
	*lastKey = 0;

	*animFrame1 = 0;
	*animFrame2 = 104;

	///////////////////////
	// Reset player data //
	///////////////////////
	for (i = 0; i < NUMBER_OF_ITEMS; ++i) {
		playerData->items[i] = 0;
	}

	playerData->coins = 0;
	playerData->progress = 0;
	playerData->energyMax = 0x7FFF;
	playerData->strikerSpeed = 4;
	playerData->bouncinessFactor = 10;

	gameData->strikerSize = 48;

	///////////////////////
	// Show intro screen //
	///////////////////////

	gfx_window(1, 5, 36, 119 , 89);
	gfx_window(0, 139, 36, 252 , 89);
	gfx_draw_title();

	// story info, window to the left

	for (i = 0; i < 12; ++i) {
		hw_ROM_to_RAM(str, story[40 + i]);
		gfx_draw_text(9, 8, 39 + i * 3, str);
	}

	// Meta info,

	for (i = 0; i < 11; ++i) {
		hw_ROM_to_RAM(str, story[52 + i]);
		gfx_draw_text(9, 143, 39 + i * 3, str);
	}
	while (hw_read_key() == 0x00);
}

void game_save(PlayerData *playerData) {
	int i, loc = 0xFF00;

	WriteByteToFlash(loc + 0,  playerData->progress);
	WriteByteToFlash(loc + 1,  playerData->coins & 0xFF);
	WriteByteToFlash(loc + 2,  (playerData->coins >> 8) & 0xFF);

	for (i = 0; i < NUMBER_OF_ITEMS; ++i)
		WriteByteToFlash(loc + 3 + i, playerData->items[i]);

	WriteByteToFlash(loc + 9,  playerData->energyMax & 0xFF);
	WriteByteToFlash(loc + 10, (playerData->energyMax >> 8) & 0xFF);
	WriteByteToFlash(loc + 11, (playerData->energyMax >> 16) & 0xFF);
	WriteByteToFlash(loc + 12, playerData->strikerSpeed & 0xFF);
	WriteByteToFlash(loc + 13, playerData->bouncinessFactor & 0xFF);
}

void game_load(PlayerData *playerData) {
	int i, loc = 0xFF00;

	playerData->progress         = ReadByteFromFlash(loc + 0);
	playerData->coins            = (int) ReadByteFromFlash(loc + 1);
	playerData->coins            |= ((int) ReadByteFromFlash(loc + 2)) << 8;

	for (i = 0; i < NUMBER_OF_ITEMS; ++i)
		playerData->items[i]     = ReadByteFromFlash(loc + 3 + i);

	playerData->energyMax        = (long) ReadByteFromFlash(loc + 9);
	playerData->energyMax        |= ((long) ReadByteFromFlash(loc + 10)) << 8;
	playerData->energyMax        |= ((long) ReadByteFromFlash(loc + 11)) << 16;
	playerData->strikerSpeed     = ((int) ReadByteFromFlash(loc + 12)) & 0xFF;
	playerData->bouncinessFactor = ((int) ReadByteFromFlash(loc + 13)) & 0xFF;
}

/*
 #   #  ####   #  #   #  #          #   #   ##    ###    ####
 ## ##  #      ## #   #  #          ## ##  #  #   #  #   #
 # # #  ###    # ##   #  #          # # #  #  #   #  #   ###
 # # #  #      #  #   #  #          # # #  #  #   #  #   #
 #   #  #      #  #   #  #          #   #  #  #   #  #   #
 #   #  ####   #  #    ##           #   #   ##    ###    ####
*/

void menu_init() {
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
					game_load(playerData);
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

/*
 #   #    #    ###           #   #   ##    ###    ####
 ## ##   # #   #  #          ## ##  #  #   #  #   #
 # # #  #   #  #  #          # # #  #  #   #  #   ###
 # # #  #####  ###           # # #  #  #   #  #   #
 #   #  #   #  #             #   #  #  #   #  #   #
 #   #  #   #  #             #   #   ##    ###    ####
*/

void map_init(PlayerData *playerData, int *focus) {
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

			if (key & 0x10) {
				// Cheat key
				++playerData->progress;
				map_init(playerData, focus);
			}

			if (*lastKey & 4) {
				hw_sound_play(1);
				if (*focus < 6) {
					gameData->level = *focus;
					*mode = 2;
				} else if (*focus == 6) {
					game_save(playerData);
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


void map_info_init(GameData *gameData) {
	int i, y;
	char str[49];

	gfx_window(1, -1, -1, 257, 104);

	y = 60;
	if (gameData->level == 0) {

		//dokuu

		hw_ROM_to_RAM(str, story[1]);
		gfx_draw_text(9, 119, 35, str);
		gfx_draw_thumb(122, 40, 0, 9);

		for (i = 1; i < 5; ++i) {
			hw_ROM_to_RAM(str, story[i]);
			gfx_draw_text(9, 57, y + i * 3, str);
		}

	} else if (gameData->level == 1) {

		// ALderan

		hw_ROM_to_RAM(str, story[4]);
		gfx_draw_text(9, 113, 35, str);
		gfx_draw_thumb(122, 40, 1, 10);



		for (i = 1; i < 7; ++i) {
			hw_ROM_to_RAM(str, story[i + 4]);
			gfx_draw_text(9, 71, y + i * 3, str);
		}

	} else if (gameData->level == 2) {

		// tatoiine

		hw_ROM_to_RAM(str, story[11]);
		gfx_draw_text(9, 113, 35, str);
		gfx_draw_thumb(122, 40, 2, 11);


		for (i = 1; i < 8; ++i) {
			hw_ROM_to_RAM(str, story[i + 11]);
			gfx_draw_text(9, 77, y + i * 3, str);
		}

	} else if (gameData->level == 3) {

		// darth

		hw_ROM_to_RAM(str, story[19]);
		gfx_draw_text(9, 107, 35, str);
		gfx_draw_thumb(122, 40, 3, 12);


		for (i = 1; i < 6; ++i)	{
			hw_ROM_to_RAM(str, story[i + 19]);
			gfx_draw_text(9, 75, y + i * 3, str);
		}

	} else if (gameData->level == 4) {
		//	unknown

		hw_ROM_to_RAM(str, story[25]);
		gfx_draw_text(9, 95, 35, str);
		gfx_draw_thumb(122, 40, 4, 13);


		for (i = 1; i < 7; ++i) {
			hw_ROM_to_RAM(str, story[i + 25]);
			gfx_draw_text(9, 43, y + i * 3, str);
		}

	} else if (gameData->level == 5) {
		// the pub

		hw_ROM_to_RAM(str, story[32]);
		gfx_draw_text(9, 70, 35, str);
		gfx_draw_thumb(122, 40, 5, 14);


		for (i = 1; i < 8; ++i) {
			hw_ROM_to_RAM(str, story[i + 32]);
			gfx_draw_text(9, 33, y + i * 3, str);
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

/*
  ##      #    #   #  ####          #   #   ##    ###    ####
 #  #    # #   ## ##  #             ## ##  #  #   #  #   #
 #      #   #  # # #  ###           # # #  #  #   #  #   ###
 # ##   #####  # # #  #             # # #  #  #   #  #   #
 #  #   #   #  #   #  #             #   #  #  #   #  #   #
  ##    #   #  #   #  ####          #   #   ##    ###    ####
*/

void game_init(GameData *gameData, PlayerData *playerData, AnimationData *animationData) {
	int i, j;
	playerData->energy = playerData->energyMax;

	gfx_window(1, -1, -1, 257, 98);

	gfx_draw_text(11, 200, 98, "coins");
	gfx_draw_score(playerData);
	gfx_draw_energy_meter(playerData);

	// Load level data
	for (i = 0; i < 15; ++i) {
		for (j = 0; j < 8; ++j) {
			gameData->blockData[i][j] = levelData[gameData->level][i][j];
		}
	}

	gfx_draw_all_blocks(gameData);

	gameData->strikerPos = 127 << 8;

	gameData->ballPos.x = 127 << 8;
	gameData->ballPos.y = 90 << 8;
	gameData->ballOldPos.x = gameData->ballPos.x;
	gameData->ballOldPos.y = gameData->ballPos.y;

	gameData->ballVel.x = 0;
	gameData->ballVel.y = -(int)32;

	gameData->ballSpeed = 3;

	gameData->multiplier = 0;

	gameData->strikerSize = 24;

	gfx_init_striker(gameData);
	gfx_init_ball(gameData);

	for (i = 0; i < 5; ++i) {
		animationData->projectileType[i] = -1;
		animationData->eraseProjectile[i] = 0;
	}

	// Flags used by physics engine to avoid hitting same block twice in consecutive calls to phy_simulate
	gameData->blockHit[2] = 0;	// Wether or not the ball was touching a block last iteration
	gameData->bouncedTop = 0;	// Touching top game border
	gameData->bouncedSide = 0;	// Touching side game border
	gameData->bouncedStriker = 0;	// Touching the striker

	if (gameData->level < 0) {
		hw_sound_set_music(1);
	} else if (gameData->level == 1) {
		hw_sound_set_music(2);
	} else if (gameData->level == 2) {
		hw_sound_set_music(3);
	} else if (gameData->level == 3) {
		hw_sound_set_music(2);
	} else if (gameData->level == 4) {
		hw_sound_set_music(3);
	} else if (gameData->level == 5) {
		hw_sound_set_music(0);
	}
}

void create_bullet(GameData *gameData, AnimationData *animationData, int type, int side) {	// side: 0 = left, 1 = right
	int num;

	// Find available slot in animationData->projectilePos
	for (num = 0; num < 5; ++num) {
		if (animationData->projectileType[num] == -1) break;
	}
	if (num < 5) {	// If num == 5, it means that there was no available slot - bullet will not be created
		hw_sound_play(9 + type);
		animationData->projectilePos[num][0] = (gameData->strikerPos >> 8) + (type == 2 ? 0 : (side ? (gameData->strikerSize >> 1) : (-(gameData->strikerSize >> 1) + 1)));
		animationData->projectilePos[num][1] = striker_height - (type < 2 ? 1 : 3);
		animationData->projectileType[num] = (char) type;
	}
}

void game_update(int *mode, char *lastKey, GameData *gameData, PlayerData *playerData, AnimationData *animationData) {
	char key, i, won = 0, lostBall = 0;
	gameData->redraw = 0;
	gameData->blockHit[0] = 0;	// Data of last block hit, used to update graphics
	gameData->blockHit[1] = 0;	// Same as 0, used if two blocks are hit simultaneously

	// if (hw_read_key() && hw_time_get_next_frame()) {
	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		gameData->strikerOldPos = gameData->strikerPos;
		gameData->ballOldPos = gameData->ballPos;

		phy_move_striker(gameData, playerData, hw_read_analog());

		gfx_update_energy_meter(playerData);

		if (playerData->energy <= 0) game_end(mode, 0, playerData, gameData);

		// sprintf(debug, "%d", (int) hw_read_analog());
		// gfx_draw_text(9, 200, 80, debug);

		// if (key & 4) *mode = 0;

		phy_update_bullets(gameData, animationData);

		// Calculate new ball position
		for (i = 0; i < 8; ++i) {
			phy_simulate(gameData, playerData, &lostBall);
			if (gameData->blockHit[0]) {
				(gameData->blockHit[0] >> 8) ? gfx_draw_block(gameData->blockHit[0] & 0x000F, gameData->blockHit[0] >> 4 & 0x000F, gameData->blockHit[0] >> 8) : gfx_erase_block(gameData->blockHit[0] & 0x000F, gameData->blockHit[0] >> 4 & 0x000F);
				gameData->blockHit[0] = 0;
				if (gameData->blockHit[1]) {
					(gameData->blockHit[1] >> 8) ? gfx_draw_block(gameData->blockHit[1] & 0x000F, gameData->blockHit[1] >> 4 & 0x000F, gameData->blockHit[1] >> 8) : gfx_erase_block(gameData->blockHit[1] & 0x000F, gameData->blockHit[1] >> 4 & 0x000F);
					gameData->blockHit[1] = 0;
					playerData->coins += 5 * gameData->multiplier;
				}

				// update score
				playerData->coins += 5 * gameData->multiplier;
				gfx_draw_score(playerData);
			}
			if (gameData->redraw) {
				gameData->redraw = 0;
				gfx_draw_ball(gameData);
				gameData->ballOldPos = gameData->ballPos;
			}
			if (lostBall) {
				gfx_update_energy_meter(playerData);
				playerData->oldEnergy = playerData->energy;
				playerData->energy -= 0x1000;
				gfx_update_energy_meter(playerData);
				lostBall = 0;

			}
		}

		gameData->ballVel.y++;	// Gravity

		key = hw_read_key();
		// If key is rising edge
		if (key != *lastKey) {
			*lastKey = key;
			if (key & 1) {
				if (playerData->items[4] == 1) {
					create_bullet(gameData, animationData, 0, 1);
					playerData->oldEnergy = playerData->energy;
					playerData->energy -= 0x800;
				} else if (playerData->items[4] == 2) {
					create_bullet(gameData, animationData, 1, 1);
					playerData->oldEnergy = playerData->energy;
					playerData->energy -= 0x400;
				}
				gfx_update_energy_meter(playerData);
			}
			if (key & 2) {
				if (playerData->items[3] == 1) {
					create_bullet(gameData, animationData, 0, 0);
					playerData->oldEnergy = playerData->energy;
					playerData->energy -= 0x800;
				} else if (playerData->items[3] == 2) {
					create_bullet(gameData, animationData, 1, 0);
					playerData->oldEnergy = playerData->energy;
					playerData->energy -= 0x400;
				}
				gfx_update_energy_meter(playerData);
			}
			if ((key & 8) && playerData->items[5]) {
				create_bullet(gameData, animationData, 2, 0);
				playerData->oldEnergy = playerData->energy;
				playerData->energy -= 0x3000;
				gfx_update_energy_meter(playerData);
			}
		}

		gfx_draw_striker(gameData);
		gfx_draw_ball(gameData);
		gfx_update_animation(animationData);
	} else {
		// check for victory
		won = 1;
		for (i = 0; i < 15; ++i) {
			if (gameData->blockData[i][0] || gameData->blockData[i][1]) {
				won = 0;
			}
		}
		if (won) game_end(mode, 1, playerData, gameData);
	}
	//LED_update();
}

void game_end(int *mode, int win, PlayerData *playerData, GameData *gameData) {
	hw_sound_mute();
	if (win == 0) {
		hw_sound_play(13);
		gfx_window(1, 87, 45, 163, 60);
		gfx_draw_game_over();
		LED_set_string("YOU DEAD");
	} else {
		if (playerData->progress < 6 && gameData->level == playerData->progress) ++playerData->progress;
		hw_sound_play(12);
		gfx_window(1, 76, 45, 181, 60);
		gfx_draw_victory();
		LED_set_string("You win!");
	}
	gfx_draw_text(9, 91, 54, "press to continue");
	while (1) {
		LED_update();
		if (hw_read_key() == 4) {
			*mode = 1;
			break;
		}
	}
}

/*
  ##    #  #    ##    ###           #   #   ##    ###    ####
 #  #   #  #   #  #   #  #          ## ##  #  #   #  #   #
  #     ####   #  #   #  #          # # #  #  #   #  #   ###
   #    #  #   #  #   ###           # # #  #  #   #  #   #
 #  #   #  #   #  #   #             #   #  #  #   #  #   #
  ##    #  #    ##    #             #   #   ##    ###    ####

*/

void shop_init(PlayerData *playerData) {
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


			if (key & 0x10) {
				// Cheat key
				playerData->coins += 1000;
				sprintf(str, "coins %8d", playerData->coins);
				gfx_draw_text(9, 196, 2, str);
			}

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
							playerData->strikerSpeed += 1;
							gameData->strikerSize += 4;
						} else if (*focus == 2) {
							playerData->bouncinessFactor += 2;
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