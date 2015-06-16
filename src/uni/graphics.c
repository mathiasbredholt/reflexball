#ifdef __APPLE__
#define GCC
#endif

#ifdef __WIN32__
#define GCC
#endif

#ifndef GCC
#include <sio.h>
#endif

#ifdef GCC
#include <stdio.h>
#endif

// graphics.c

#include "ansi.h"
#include "util.h"
#include "graphics.h"
#include "charset.h"

#define width 256
#define height 96
#define striker_height 92
#define BTN_WIDTH 20

int _strikerSize;

void gfx_draw_bounds() {
	int i;

	hide_csr();
	clr_scr();

	go_to_xy(-1, -1);
	printf("%c", 201);  // top left corner
	spacer(width, 205); // top line
	printf("%c", 187);

	// print sides
	for (i = 0; i < height; i++) {
		go_to_xy(-1, i);
		printf("%c", 186);
		go_to_xy(256, i);
		printf("%c", 186);
	}

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_ball(TVector_8_8 oldPos, TVector_8_8 newPos) 	{
	unsigned char newX = (unsigned char) (newPos.x >> 8);
	unsigned char newY = (unsigned char) (newPos.y >> 8);
	unsigned char oldX = (unsigned char) (oldPos.x >> 8);
	unsigned char oldY = (unsigned char) (oldPos.y >> 8);

	fg_color(15);

	if (oldX != newX || oldY != newY) {
		// Erase old ball
		go_to_xy((int) oldX, (int) oldY);
		printf("  ");
	}
	// Draw new ball
	go_to_xy((int) newX, (int) newY);
	printf("%c%c", 219, 219);

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_striker(unsigned int oldX, unsigned int newX) 	{
	char dX ;
	fg_color(15);
	oldX >>= 8;
	newX >>= 8;
	dX = (char) newX - (char) oldX;
	if (dX > 0) {
		go_to_xy(oldX - (_strikerSize >> 1) + 1, striker_height);
		spacer(dX, (int) ' ');
		printf("%c", 204);
		spacer(_strikerSize - 2, 205);
		printf("%c", 185);
	} else if (dX < 0) {
		go_to_xy(newX - (_strikerSize >> 1) + 1, striker_height);
		printf("%c", 204);
		spacer(_strikerSize - 2, 205);
		printf("%c", 185);
		spacer(-dX, (int) ' ');
	}

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_change_striker_size(unsigned int x, int size) {
	x >>= 8;

	go_to_xy(x - (_strikerSize >> 1) + 1, striker_height);
	spacer(_strikerSize, (int) ' ');

	_strikerSize = size;
	go_to_xy(x - (_strikerSize >> 1) + 1, striker_height);
	printf("%c", 204);
	spacer(_strikerSize - 2, 205);
	printf("%c", 185);

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_set_striker_size(int size) {
	_strikerSize = size;
}

void gfx_draw_all_blocks(unsigned char blockData[4][15][2]) {
	char i, j, k, l;

	for (j = 0; j < 15; ++j) {
		fg_color(i + 1);
		for (i = 0; i < 4; ++i) {
			for (k = 0; k < 2; ++k) {
				for (l = 0; l < 8; ++l) {
					if (blockData[i][j][k] & (0x80 >> l)) {
						gfx_draw_block((int)((k << 3) + l), (int) j, (int) i);
					}
				}
			}
		}
	}

	fg_color(15);

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_block(int x, int y, int type) {
	fg_color(type + 1);

	x = x << 4;
	y = y << 2;

	// Top
	go_to_xy(x, y);
	printf("%c", 201);  // top left corner
	spacer(14, 203); // top line
	printf("%c", 187);	// top right corner

	// Sides
	go_to_xy(x, y + 1);
	printf("%c", 204);
	spacer(14, 206);
	printf("%c", 185);
	go_to_xy(x, y + 2);
	printf("%c", 204);
	spacer(14, 206);
	printf("%c", 185);

	// Bottom
	go_to_xy(x, y + 3);
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
	spacer(16, ' '); // top line
	go_to_xy(x, y + 1);
	spacer(16, ' '); // middle line
	go_to_xy(x, y + 2);
	spacer(16, ' '); // middle line
	go_to_xy(x, y + 3);
	spacer(16, ' '); // bottom line

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_window(int x1, int y1, int x2, int y2, int draw) {
	int w = x2 - x1;
	int h = y2 - y1;
	int i;

	clr_scr();
	hide_csr();
	fg_color(15);

	if (draw) {
		reverse(0);
		go_to_xy(x1, y1);

		// print top line
		printf("%c", 201);  // corner
		spacer( w - 2, 205);
		printf("%c", 187);  // corner

		// print sides
		for (i = 1; i < h - 1; i++) {
			go_to_xy(x1, y1 + i);
			printf("%c", 186);
			go_to_xy(x2 - 1, y1 + i);
			printf("%c", 186);
		}

		// print bottom line
		go_to_xy(x1, y2 - 1);
		printf("%c", 200);  // corner
		spacer(w - 2, 205);
		printf("%c", 188);  // corner
	}
	else {
		for (i = 0; i < h; ++i) {
			go_to_xy(x1, y1 + i);
			spacer(w, 32);
		}
	}

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_text(int x, int y, char *str) {
	int i, j, k;
	for (i = 0; i < util_strlen(str); ++i) {
		if (str[i] != 32) {
			for (j = 0; j < 3; ++j) {
				for (k = 0; k < 4; ++k) {
					go_to_xy(x + k + i * 4, y + j);
					printf("%c", font_mini[(int) str[i] - 97][j][k]);
				}
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

void gfx_draw_item(int x, int y, int item) {
	int i;

	fg_color(15);

	for (i = 0; i < 8; ++i) {
		go_to_xy(x, y + i);
		printf("%s", items[item][i]);
	}

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_meter(int x, int y, int val) {
	fg_color(2);
	go_to_xy(x, y);
	spacer(val, 221);

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_number(int x, int y, int val) {
	int i, j, k;
	char str[10];

	fg_color(15);
	bold(1);

	sprintf(str, "%d", val);

	for (i = 0; i < util_strlen(str); ++i) {
		for (j = 0; j < 3; ++j) {
			for (k = 0; k < 4; ++k) {
				go_to_xy(x + k + i * 4, y + j);
				printf("%c", font_mini[(int) str[i] - 48 + 26][j][k]);
			}
		}
	}

	bold(0);

#ifdef GCC
	fflush(stdout);
#endif
}