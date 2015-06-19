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
#include "game_engine.h"

#define width 256
#define height 96
#define striker_height 92
#define BTN_WIDTH 20

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
	fg_color(15);
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
	go_to_xy((gameData->strikerPos >> 8) - (gameData->strikerSize >> 1) + 1, striker_height);
	printf("%c", 204);
	spacer(gameData->strikerSize - 2, 205);
	printf("%c", 185);
}

void gfx_erase_striker(GameData *gameData) {
	unsigned char x = (char) (gameData->strikerPos >> 8);

	go_to_xy((int) ((gameData->strikerPos >> 8) - (gameData->strikerSize >> 1) + 1), striker_height);
	spacer(gameData->strikerSize, (int) ' ');

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_all_blocks(GameData *gameData) {
	char type, oldType, row, side, column, line;

	go_to_xy(0, 0);
	fg_color(1);
	ansi_save();
	oldType = 0;

	for (row = 0; row < 15; ++row) { // Rows
		for (line = 0; line < 4; ++line) { // Lines
			for (side = 0; side < 2; ++side) { // Left/right side (byte)
				for (column = 0; column < 8; ++column) { // Column (bit)
					for (type = 0; type < 4; ++type) { // Types
						if (gameData->blockData[type][row][side] & (0x80 >> column)) {	// Block exists
							if (type != oldType) {
								if (type == 0) {
									fg_color(1);
								} else if (type == 2) {
									fg_color(2);
								} else if (type == 5) {
									fg_color(3);
								} else if (type == 9) {
									fg_color(4);
								} else {
									fg_color(5);
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
						}
					}
				}
			}
			ansi_load();
			oldType = 0;
			go_down(line + (row << 2) + 1);
		}
	}

	fg_color(15);

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
		color = 5;
	}

	fg_color(color);

	go_to_xy(x, y);
	ansi_save();

	// Top
	printf("%c", 201);  // top left corner
	spacer(14, 203); // top line
	printf("%c", 187);	// top right corner

	// Sides
	ansi_load();

	go_down(1);
	printf("%c", 204);

	if (type == 1) {
		fg_color(6);
	}

	spacer(2, 206);

	fg_color(color);

	spacer(12, 206);
	printf("%c", 185);
	ansi_load();
	go_down(2);
	printf("%c", 204);
	spacer(14, 206);
	printf("%c", 185);

	fg_color(color);

	// Bottom
	ansi_load();
	go_down(3);
	printf("%c", 200);  // corner
	spacer(14, 202);
	printf("%c", 188);  // corner

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_erase_block(int x, int y) {
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
	fg_color(15);

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

void gfx_draw_text(int x, int y, char *str) {
	int i, j, k;
	int index;
	char length = util_strlen(str);
	char line[5];

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
	fg_color(15);

	// left corners
	go_to_xy(x, y);
	printf("%c", 201);
	go_to_xy(x, y + 5);
	printf("%c", 200);

	// right corners
	go_to_xy(x + BTN_WIDTH, y);
	printf("%c", 187);
	go_to_xy(x + BTN_WIDTH, y + 5);
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
	go_to_xy(x + BTN_WIDTH, y + 1);
	printf("%c", 186);
	go_to_xy(x + BTN_WIDTH, y + 2);
	printf("%c", 186);
	go_to_xy(x + BTN_WIDTH, y + 3);
	printf("%c", 186);
	go_to_xy(x + BTN_WIDTH, y + 4);
	printf("%c", 186);


	// top and bottom
	go_to_xy(x + 1, y);
	spacer(BTN_WIDTH - 1, 205);
	go_to_xy(x + 1, y + 5);
	spacer(BTN_WIDTH - 1, 205);

	gfx_draw_btn_focus(x, y, str, focus);

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_btn_focus(int x, int y, char * str, int focus) {
	int textW = util_strlen(str) * 4;
	int padding = BTN_WIDTH - textW;
	int i;

	fg_color(15);

	focus ? bg_color(3) : bg_color(0);

	for (i = 0; i < 4; ++i) {
		go_to_xy(x + 2, y + 1 + i);
		spacer(BTN_WIDTH - 3, 32);
	}

	gfx_draw_text(x + padding / 2 + 1, y + 1, str);

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

void gfx_draw_energy_meter() {
	char str[15];
	int i;

	color(0, 6);
	sprintf(str, "energy");
	gfx_draw_text(0, 98, str);

	go_to_xy(0, 101);
	spacer(63, 32);

	for (i = 98; i < 102; ++i) {
		go_to_xy(24, i);
		spacer(39, 32);
	}

	color(15, 0);
	go_to_xy(0, 102);
	spacer(63, 205);

	for (i = 98; i < 102; ++i) {
		go_to_xy(63, i);
		spacer(1, 186);
	}

	go_to_xy(63, 102);
	spacer(1, 188);

	for (i = 98; i < 102; ++i) {
		go_to_xy(-1, i);
		spacer(1, 186);
	}

	go_to_xy(-1, 102);
	spacer(1, 200);

	go_to_xy(-1, 97);
	spacer(1, 204);

	go_to_xy(63, 97);
	spacer(1, 203);
}

void gfx_update_energy_meter(PlayerData *playerData) {
	int level = (playerData->energy >> 9);
	int i;
	// go_to_xy(200, 10);
	// printf("%8d  %8d", level, playerData->energy);
	if (level >= 0 && (playerData->oldEnergy >> 9) - level > 0) {
		go_to_xy(level, 98 - 1);

		for (i = 0; i < 4; ++i) {
			go_down(1);
			printf(" ");
			go_left(1);
		}
	}
#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_bullet(int x, int newY, int oldY, int type) {
	int i;
	fg_color(1);
	go_to_xy(x >> 8, 90);
	for (i = 0; i < 80; ++i) {
		go_up(1);
		printf("|");
		go_left(1);
	}
}

void gfx_draw_stars(int frame) {
	int i, j;
	int randomX[5] = { 6, 62, 43, 34, 10 };
	int randomY[8] = { 6, 9, 2, 11, 7, 3, 6, 4 };
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
	char str[9];
	fg_color(15);
	sprintf(str, "%8d", playerData->coins);
	gfx_draw_text(224, 98, str);
}
