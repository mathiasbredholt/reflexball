#if defined(__APPLE__) || defined(__WIN32__)
#define GCC
#include <stdio.h>
#endif

#if defined(_Z8F6403)
#include <sio.h>
#endif

// graphics.c

#include "ansi.h"
#include "util.h"
#include "graphics.h"
#include "charset.h"
#include "game_data.h"

#define BTN_WIDTH 40

void gfx_draw_ball(GameData *gameData) {
	unsigned char newX = (unsigned char) (gameData->ballPos.x >> 8);
	unsigned char newY = (unsigned char) (gameData->ballPos.y >> 8);
	unsigned char oldX = (unsigned char) (gameData->ballOldPos.x >> 8);
	unsigned char oldY = (unsigned char) (gameData->ballOldPos.y >> 8);

	fg_color(15);

	if (oldX != newX || oldY != newY) {
		if ((char) (newY - oldY) == 0 && (char) (newX - oldX) == 1) {
			go_to_xy((int) oldX, (int) oldY);
			printf(" %c%c", 219, 219);
		} else if ((char) (newY - oldY) == 0 && (char) (newX - oldX) == -1) {
			go_to_xy((int) oldX - 1, (int) oldY);
			printf("%c%c ", 219, 219);
		} else {
			go_to_xy((int) oldX, (int) oldY);
			// Erase old ball
			printf("  ");
			// Draw new ball
			go_horiz((int) (char) (newX - oldX) - 2);
			go_vert((int) (char) (newY - oldY));
			// go_to_xy((int) newX, (int) newY);
			printf("%c%c", 219, 219);
		}
	}


#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_init_ball(GameData *gameData) {
	fg_color(15);
	go_to_xy(gameData->ballPos.x >> 8, gameData->ballPos.y >> 8);
	printf("%c%c", 219, 219);
}

void gfx_draw_striker(GameData *gameData) 	{
	unsigned char oldX = (char) (gameData->strikerOldPos >> 8);
	unsigned char newX = (char) (gameData->strikerPos >> 8);
	char dX = (char) newX - (char) oldX;
	fg_color(10);
	if (dX > 0) {
		go_to_xy(oldX - (gameData->strikerSize >> 1) + 1, striker_height);
		spacer(dX, (int) ' ');
		printf("%c", 204);
		go_right(gameData->strikerSize - dX - 2);
		//go_to_xy(oldX + (gameData->strikerSize >> 1), striker_height);
		// spacer(gameData->strikerSize - 2, 205);
		spacer(dX, 205);
		printf("%c", 185);
	} else if (dX < 0) {
		go_to_xy(newX - (gameData->strikerSize >> 1) + 1, striker_height);
		printf("%c", 204);
		// spacer(gameData->strikerSize - 2, 205);
		spacer(-dX, 205);
		go_right(gameData->strikerSize + dX - 2);
		printf("%c", 185);
		spacer(-dX, (int) ' ');
	}

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_init_striker(GameData *gameData) {
	fg_color(10);
	go_to_xy((gameData->strikerPos >> 8) - (gameData->strikerSize >> 1) + 1, striker_height);
	printf("%c", 204);
	spacer(gameData->strikerSize - 2, 205);
	printf("%c", 185);
}

void gfx_erase_striker(GameData *gameData) {
	go_to_xy((int) ((gameData->strikerPos >> 8) - (gameData->strikerSize >> 1) + 1), striker_height);
	spacer(gameData->strikerSize, (int) ' ');

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_update_animation(AnimationData *animationData) {
	int i, j;
	for (i = 0; i < 5; ++i) {
		if (animationData->eraseProjectile[i]) {
			go_to_xy(animationData->projectilePos[i][0], animationData->projectilePos[i][1] + 1);
			printf(" ");
			if (animationData->projectileType[i] == 2) {	// Rocket
				go_left(1);
				go_down(1);
				printf(" ");
				go_left(1);
				go_down(1);
				printf(" ");
			}
			animationData->projectileType[i] = -1;
			animationData->eraseProjectile[i] = 0;
		} else if (animationData->projectileType[i] >= 0) {	// Bullet exists
			if (animationData->projectileType[i] == 0) { // Laser 1
				fg_color(9);
				go_to_xy(animationData->projectilePos[i][0], animationData->projectilePos[i][1] + 1);
				printf(" ");
				go_left(1);
				go_up(1);
				printf("*");
			} else if (animationData->projectileType[i] == 1) { // Laser 2
				fg_color(9);
				go_to_xy(animationData->projectilePos[i][0], animationData->projectilePos[i][1] + 1);
				printf(" ");
				go_left(1);
				go_up(1);
				printf("%c", 233);
			} else if (animationData->projectileType[i] == 2) { // Rocket
				fg_color(7);
				go_to_xy(animationData->projectilePos[i][0], animationData->projectilePos[i][1] + 3);
				printf(" ");
				go_left(1);
				go_up(1);
				printf("^");
				go_left(1);
				go_up(1);
				printf("H");
				go_left(1);
				go_up(1);
				printf("A");
			}
		}
	}

	if (animationData->rocketHit[2]) {
		// Erase blocks in custom order for more explosiony look
		gfx_erase_block(animationData->rocketHit[0], animationData->rocketHit[1]);
		gfx_erase_block(animationData->rocketHit[0], animationData->rocketHit[1] - 1);
		gfx_erase_block(animationData->rocketHit[0] - 1, animationData->rocketHit[1] - 1);
		gfx_erase_block(animationData->rocketHit[0] + 1, animationData->rocketHit[1] - 1);
		gfx_erase_block(animationData->rocketHit[0] - 1, animationData->rocketHit[1]);
		gfx_erase_block(animationData->rocketHit[0] + 1, animationData->rocketHit[1]);
		gfx_erase_block(animationData->rocketHit[0] - 1, animationData->rocketHit[1] + 1);
		gfx_erase_block(animationData->rocketHit[0] + 1, animationData->rocketHit[1] + 1);
		animationData->rocketHit[2] = 0;
	}
}

void gfx_draw_all_blocks(GameData *gameData) {
	char type, oldType, row, column, line, nibble;

	go_to_xy(0, 0);
	ansi_save();
	oldType = 0;

	for (row = 0; row < 15; ++row) { // Rows
		for (line = 0; line < 4; ++line) { // Block lines
			for (column = 0; column < 8; ++column) { // Column (byte)
				for (nibble = 0; nibble < 2; ++nibble) { // Left/right nibble
					type = nibble ?
					       gameData->blockData[row][column] & 0x0F : // Right side
					       gameData->blockData[row][column] >> 4; // Left side
					if (type) {	// Block type is > 0
						if (type != oldType) {
							if (type == 1) {
								fg_color(1);
							} else if (type == 3) {
								fg_color(2);
							} else if (type == 6) {
								fg_color(3);
							} else if (type == 10) {
								fg_color(4);
							} else {
								fg_color(8);
							}
							oldType = type;
						}
						if (line == 0) {
							printf("%c", 201);  // top left corner
							spacer(14, 203); // top line
							printf("%c", 187);	// top right corner
						} else if (line < 3) {
							printf("%c", 204);
							spacer(14, 206);
							printf("%c", 185);
						} else {
							printf("%c", 200);  // corner
							spacer(14, 202);
							printf("%c", 188);  // corner
						}
					} else {
						go_right(16);
					}
				}
			}
			ansi_load();
			oldType = 0;
			go_down(line + (row << 2) + 1);
		}
	}

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_block(int x, int y, int type) {
	char color;
	x = x << 4;
	y = y << 2;

	if (type == 0) {
		color = 1;
	} else if (type <= 2) {
		color = 2;
	} else if (type <= 5) {
		color = 3;
	} else if (type <= 9) {
		color = 4;
	} else {
		color = 8;
	}

	fg_color(color);

	go_to_xy(x + 1, y + 1);
	ansi_save();

	// Sides
	if (type == 1 || type == 3 || type == 6 || type == 10 || type == 11) {
		spacer(14, 206);
		go_to_xy(x + 1, y + 2);
		spacer(14, 206);
	} else if (type == 2 || type == 4 || type == 7) {
		spacer(14, 45);
		go_to_xy(x + 1, y + 2);
		spacer(14, 45);
	} else if (type == 5 || type == 8) {
		spacer(14, 97);
		go_to_xy(x + 1, y + 2);
		spacer(14, 97);
	} else if (type == 9) {
		spacer(14, 99);
		go_to_xy(x + 1, y + 2);
		spacer(14, 99);
	}

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_erase_block(int x, int y) {
	if (x >= 0 && x < 16 && y >= 0 && x < 15) {
		x = x << 4;
		y = y << 2;

		fg_color(15);
		go_to_xy(x, y);
		ansi_save();

		spacer(16, (int) ' '); // top line
		// go_to_xy(x, y + 1);
		ansi_load();
		go_down(1);
		spacer(16, (int) ' '); // middle line
		// go_to_xy(x, y + 2);
		ansi_load();
		go_down(2);
		spacer(16, (int) ' '); // middle line
		// go_to_xy(x, y + 3);
		ansi_load();
		go_down(3);
		spacer(16, (int) ' '); // bottom line
	}

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_window(int x1, int y1, int x2, int y2) {
	int w = x2 - x1;
	int h = y2 - y1;
	int i;

	clr_scr();
	hide_csr();
	fg_color(10);

	reverse(0);
	go_to_xy(x1, y1);
	ansi_save();

	// print top line
	printf("%c", 201);  // corner
	spacer( w - 2, 205);
	printf("%c", 187);  // corner

	// print sides
	for (i = 1; i < h - 1; i++) {
		ansi_load();
		go_down(i);
		printf("%c", 186);
		go_right(w - 2);
		printf("%c", 186);
	}
	// print bottom line
	go_to_xy(x1, y2 - 1);
	printf("%c", 200);  // corner
	spacer(w - 2, 205);
	printf("%c", 188);  // corner

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_text(int col, int x, int y, char *str) {
	int i, j, k;
	int index;
	char length = util_strlen(str);
	char line[5];

	fg_color(col);

	go_to_xy(x, y);
	ansi_save();
	for (j = 0; j < 3; ++j) {   // line
		ansi_load();
		if (j != 0) {
			go_down(j);
		}
		for (i = 0; i < length; ++i) { // letters
			if ((int) str[i] >= 97) {
				index = 97; // ASCII index of letter a
			} else {
				index = 22; // ASCII index of 0 (48) - length of alphabet (26)
			}
			if (str[i] != ' ') {
				for (k = 0; k < 4; k++) {
					line[k] = font_mini[ (int) (str[i] - index) ][j][k];
				}
				line[k] = '\0';
				printf("%s", line);
			} else {
				spacer(4, 32);
			}
		}
	}

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_btn(int x, int y, char *str, int focus) {
	fg_color(10);

	// left corners
	go_to_xy(x, y);
	printf("%c", 201);
	go_to_xy(x, y + 5);
	printf("%c", 200);

	// right corners
	go_to_xy(x + BTN_WIDTH - 1, y);
	printf("%c", 187);
	go_to_xy(x + BTN_WIDTH - 1, y + 5);
	printf("%c", 188);


	// sides
	go_to_xy(x, y + 1);
	printf("%c", 186);
	go_to_xy(x, y + 2);
	printf("%c", 186);
	go_to_xy(x, y + 3);
	printf("%c", 186);
	go_to_xy(x, y + 4);
	printf("%c", 186);
	go_to_xy(x + BTN_WIDTH - 1, y + 1);
	printf("%c", 186);
	go_to_xy(x + BTN_WIDTH - 1, y + 2);
	printf("%c", 186);
	go_to_xy(x + BTN_WIDTH - 1, y + 3);
	printf("%c", 186);
	go_to_xy(x + BTN_WIDTH - 1, y + 4);
	printf("%c", 186);


	// top and bottom
	go_to_xy(x + 1, y);
	spacer(BTN_WIDTH - 2, 205);
	go_to_xy(x + 1, y + 5);
	spacer(BTN_WIDTH - 2, 205);

	gfx_draw_btn_focus(x, y, str, focus);

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_btn_focus(int x, int y, char * str, int focus) {
	int textW = util_strlen(str) * 4;
	int padding = BTN_WIDTH - textW;
	int i;

	focus ? bg_color(2) : bg_color(0);

	go_to_xy(x + 1, y + 1);
	ansi_save();

	for (i = 0; i < 4; ++i) {
		ansi_load();
		go_vert(i);
		spacer(BTN_WIDTH - 2, 32);
	}

	focus ? gfx_draw_text(0, x + padding / 2 + 1, y + 1, str) : gfx_draw_text(9, x + padding / 2 + 1, y + 1, str);

	bg_color(0);

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_item(int x, int y, int item) { //temp fix
	int i, j;

	fg_color(15);

	for (i = 0; i < 8; ++i) {
		go_to_xy(x, y + i);
		for (j = 0; j < 16; ++j)
		{
			printf("%c", items[item][i][j]);
		}
	}

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_meter(int x, int y, int val) {
	fg_color(2);
	go_to_xy(x, y);
	spacer(16, 32);
	go_to_xy(x, y);
	spacer(val, 221);

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_energy_meter(PlayerData *playerData) {
	int level = (playerData->energy >> 10);

	char str[15];
	int i;

	color(0, 6);
	sprintf(str, "energy");
	gfx_draw_text(0, 0, 98, str);

	go_to_xy(0, 101);
	spacer(level, 32);

	for (i = 98; i < 102; ++i) {
		go_to_xy(24, i);
		spacer(level - 24, 32);
	}

	color(10, 0);
	go_to_xy(0, 102);
	spacer(127, 205);

	for (i = 98; i < 102; ++i) {
		go_to_xy(127, i);
		spacer(1, 186);
	}

	go_to_xy(127, 102);
	spacer(1, 188);

	for (i = 98; i < 102; ++i) {
		go_to_xy(-1, i);
		spacer(1, 186);
	}

	go_to_xy(-1, 102);
	spacer(1, 200);

	go_to_xy(-1, 97);
	spacer(1, 204);

	go_to_xy(127, 97);
	spacer(1, 203);
}

void gfx_update_energy_meter(PlayerData *playerData) {
	int newLevel = (playerData->energy >> 10), level;
	int i;
	// go_to_xy(200, 10);
	// printf("%8d  %8d", level, playerData->energy);
	if (newLevel >= 0 && (playerData->oldEnergy >> 10) - newLevel > 0) {
		level = (playerData->oldEnergy >> 10) - 1;
		go_to_xy(level, 98 - 1);

		while (level >= newLevel) {
			for (i = 0; i < 4; ++i) {
				go_down(1);
				printf(" ");
				go_left(1);
			}
			go_left(1);
			go_up(4);
			--level;
		}
	}
#ifdef GCC
	fflush(stdout);
#endif
}

// void gfx_draw_bullet(int x, int newY, int oldY, int type) {
// 	int i;
// 	fg_color(1);
// 	go_to_xy(x >> 8, 90);
// 	for (i = 0; i < 80; ++i) {
// 		go_up(1);
// 		printf("|");
// 		go_left(1);
// 	}
// }

void gfx_draw_stars(int frame) {
	int i, j;
	int randomX[5] = { 6, 62, 43, 34, 10 };
	int randomY[8] = { 6, 9, 2, 11, 7, 3, 6, 4 };
	fg_color(15);
	for (i = 0; i < 8; ++i) {
		for (j = 0; j < 4; ++j) {
			int posX = j * 64 + randomX[i];
			int posY = i * 13 - 104 + frame + randomY[i] - 1;

			if (frame == 0 && i == 0) {
				go_to_xy(posX, 103);
				printf(" ");
			}

			if (posY <= 104 && posY >= 0 &&
			        !(posX >= 64 && posX <= 192 &&
			          posY >= 17 && posY <= 80)
			   ) {
				go_to_xy(posX, posY - 1);
				printf(" ");
			}

			if (posY < 104 && posY > 0 &&
			        !(posX > 64 && posX < 192 &&
			          posY > 15 && posY < 80)
			   ) {
				go_to_xy(posX, posY);
				printf(".");
			}
		}
	}

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_game_over() {
	int i, j;
	go_to_xy(93, 47);
	fg_color(1);
	for (i = 0; i < 62; ++i) {
		for (j = 0; j <= 5; ++j) {
			printf("%c", game_over[j][i]);
			if (j == 5) {
				go_up(5);
			} else {
				go_down(1);
				go_left(1);
			}
		}
	}
#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_victory() {
	int i, j;
	go_to_xy(78, 47);
	fg_color(2);
	for (i = 0; i < 102; ++i) {
		for (j = 0; j <= 5; ++j) {
			printf("%c", game_victory[j][i]);
			if (j == 5) {
				go_up(5);
			} else {
				go_down(1);
				go_left(1);
			}
		}
	}
#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_score(PlayerData *playerData) {
	char str[9];;
	sprintf(str, "%8d", playerData->coins);
	gfx_draw_text(11, 224, 98, str);

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_thumb(int x, int y, int thumb) {
	int i, j;

	fg_color(thumb + 9);

	for (i = 0; i < 15; ++i) {
		go_to_xy(x, y + i);
		for (j = 0; j < 16; ++j) {
			printf("%c", mapThumbs[thumb][i][j]);
		}
	}

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_small_title(int x, int y) {
	int i, j;
	fg_color(6);
	go_to_xy(x, y);
	for (i = 0; i < 85 ; ++i) {
		for (j = 0; j <= 4; ++j) {
			printf("%c", small_title[j][i]);
			if (j == 4) {
				go_up(4);
			} else {
				go_down(1);
				go_left(1);
			}
		}
	}
#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_title(int x, int y) {
	int i, j;
	fg_color(6);
	go_to_xy(x, y);
	for (i = 0; i < 164 ; ++i) {
		for (j = 0; j <= 8; ++j) {
			printf("%c", title[j][i]);
			if (j == 8) {
				go_up(8);
			} else {
				go_down(1);
				go_left(1);
			}
		}
	}
#ifdef GCC
	fflush(stdout);
#endif
}
