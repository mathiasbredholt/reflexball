#include "game_engine.h"
#include "levels.h"

int main() {
	int i;
	game_init();

	lvl_create_menu();

	lvl_create_lvl1();
	game_init_player();

	while (1) {
		for (i = 0; i < 99999; ++i) continue;
		game_update();
	}

	return 0;
}
