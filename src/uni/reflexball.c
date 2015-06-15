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

#ifndef GCC

void main() {
	char blockData[4][15][2];

	game_init();
//	intro_play();
//	game_wait_for_input();
	game_init_player();
	lvl_create_lvl1(blockData);

	while (1) {
		game_update(blockData);
	}
}

#endif

// for gcc compilation

#ifdef GCC

int main() {
	char blockData[4][15][2];

	game_init();
	intro_play();
	game_wait_for_input();
	lvl_create_lvl1(blockData);
	game_init_player();

	while (1) {
		game_update(blockData);
	}

	return 0;
}

#endif