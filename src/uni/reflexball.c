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
	game_init();
//	intro_play();
//	game_wait_for_input();
	lvl_create_lvl1();
	game_init_player();

	while (1) {
		game_update();
	}
}

#endif

// for gcc compilation

#ifdef GCC

int main() {
	game_init();
	intro_play();
	game_wait_for_input();
	lvl_create_lvl1();
	game_init_player();

	while (1) {
		game_update();
	}

	return 0;
}

#endif