// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include "game_engine.h"
#include "levels.h"

void main() {
	game_init();
	lvl_create_lvl1();
	game_init_player();

	while (1) {
		game_update();
	}
}
