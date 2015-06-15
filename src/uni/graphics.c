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

#define width 256
#define height 96
#define striker_height 92

int _strikerSize;

void gfx_draw_bounds() {
	int i;

	hide_scr();
	clr_scr();

	go_to_xy(0, 0);
	printf("%c", 201);  // top left corner
	spacer(width - 2, 205); // top line
	printf("%c", 187);

	// print sides
	for (i = 1; i < height - 1; i++) {
		go_to_xy(0, i);
		printf("%c", 186);
		go_to_xy(255, i);
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
}

void gfx_set_striker_size(int size) {
	_strikerSize = size;
}

void gfx_draw_bars() {
	int numberOfBars = 15;
	int i, j;

	for (i = 0; i < numberOfBars; ++i) {
		fg_color(1);	// For ´testing
		//fg_color(i);
		for (j = 0; j < numberOfBars; ++j) {
			go_to_xy(10 + j * 16, 4 + i * 4);
			spacer(10, 178);
			go_to_xy(10 + j * 16, 5 + i * 4);
			spacer(10, 178);
		}
	}

	fg_color(15);

#ifdef GCC
	fflush(stdout);
#endif
}

void gfx_erase_bar(int x, int y) {
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