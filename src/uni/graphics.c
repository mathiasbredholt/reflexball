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
	go_to_xy(10 + x * 16, 4 + y * 4);
	spacer(10, ' ');
	go_to_xy(10 + x * 16, 5 + y * 4);
	spacer(10, ' ');

	fg_color(15);

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_window(int x1, int y1, int x2, int y2, int draw) {
	int w = x2 - x1;
	int h = y2 - y1;
	int i;

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

void gfx_draw_text(int x, int y, char *str, int ul) {
	int i, j, k;
	for (i = 0; i < util_strlen(str); ++i) {
		if (str[i] != 32) {
			for (j = 0; j < 3; ++j) {
				for (k = 0; k < 4; ++k) {
					go_to_xy(x + k + i * 4, y + j);
					if (ul && j == 2) underline(1);
					printf("%c", font_mini[(int) str[i] - 97][j][k]);
					if (ul) underline(0);
				}
			}
		}
	}

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_draw_button(int x, int y, char *str) {
	int textW = util_strlen(str) * 4;
	int w = textW + 7;

	// left corners
	go_to_xy(x, y);
	printf("%c", 201);
	go_to_xy(x, y + 5);
	printf("%c", 200);

	// right corners
	go_to_xy(x + w, y);
	printf("%c", 187);
	go_to_xy(x + w, y + 5);
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
	go_to_xy(x + w, y + 1);
	printf("%c", 186);
	go_to_xy(x + w, y + 2);
	printf("%c", 186);
	go_to_xy(x + w, y + 3);
	printf("%c", 186);
	go_to_xy(x + w, y + 4);
	printf("%c", 186);


	// top and bottom
	go_to_xy(x + 1, y);
	spacer(w - 1, 205);
	go_to_xy(x + 1, y + 5);
	spacer(w - 1, 205);

	gfx_draw_text(x + 4, y + 1, str, 0);


#ifdef GCC
	fflush(stdout);
#endif
}