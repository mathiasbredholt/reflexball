#ifdef __APPLE__
#define GCC
#endif

#ifdef __WIN32__
#define GCC
#endif

// reflexball.c

#include "game_engine.h"
#include "levels.h"
#include "intro.h"
#include "graphics.h"
#include "menu.h"
#include "shop.h"

#ifndef GCC

void main() {
	int mode = 0;
	char items[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	char lives = 3;
	int points = 0;
	unsigned char blockData[4][15][2];

	int focus = 0;
	char lastKey = 0;

	game_init();
	// intro_play();
	// game_wait_for_input();

	while (1) {
		if (mode == 0) {
			menu_show();
			while (mode == 0) menu_update(&mode, &lastKey, &focus);

		}
		if (mode == 1) {
			lvl_create_lvl1(blockData);
			game_init_player();
			while (mode == 1) game_update(blockData, &lives, &points);
		}
		if (mode == 2) {
			shop_show(items);
			while (mode == 2) shop_update(&mode, &lastKey, &focus, items);
		}
	}
}

#endif

// for gcc compilation

#ifdef GCC

int main() {
	int mode = 0;
	char items[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	char lives = 3;
	int points = 0;
	unsigned char blockData[4][15][2];

	int focus = 0;
	char lastKey = 0;

	game_init();
	// intro_play();
	// game_wait_for_input();

	while (1) {
		if (mode == 0) {
			menu_show();
			while (mode == 0) menu_update(&mode, &lastKey, &focus);

		}
		if (mode == 1) {
			lvl_create_lvl1(blockData);
			game_init_player();
			while (mode == 1) game_update(blockData, &lives, &points);
		}
		if (mode == 2) {
			shop_show(items);
			while (mode == 2) shop_update(&mode, &lastKey, &focus, items);
		}
		if (mode == 4) break;
	}

	return 0;
}

#endif