#include "game_engine.h"
#include "levels.h"

void main() {
	game_init();
	lvl_create_lvl1();
	game_init_player();

	while (1) {
		//LED_update();
		game_update();
	}
}
