#include "game_engine.h"
#include "levels.h"
#include "graphics.h"

int main() {
	int i;
	game_init();
	lvl_create_lvl1();
	game_init_player();

	while (1) {
		game_update();
	}

	return 0;
}
