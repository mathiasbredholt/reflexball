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
#include "shop.h"

#ifndef GCC

void main() {
	char *items;
	char *lives = (char *) 3;
	int *points = 0;

	unsigned char blockData[4][15][2];

	game_init();
//	intro_play();
//	game_wait_for_input();
	game_init_player();
	lvl_create_lvl1(blockData);

	while (1) {
		game_update(blockData, lives, points);
	}
}

#endif

// for gcc compilation

#ifdef GCC

int main() {
	char *items = "dfgss";
	char *lives = (char *) 3;
	int *points = 0;
	unsigned char blockData[4][15][2];

	game_init();
	// intro_play();
	// game_wait_for_input();
	// lvl_create_lvl1(blockData);
	shop_show(items);
	// game_init_player();

	while (1) {
		// game_update(blockData, lives, points);
	}

	return 0;
}

#endif