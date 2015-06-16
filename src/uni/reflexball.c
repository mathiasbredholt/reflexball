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
	int i;

	// gui variables

	int focus = 0;
	char lastKey = 0;
	int mode = 0;
	int animFrame = 0;


	PlayerData playerData;
	unsigned char blockData[4][15][2];

	game_init(blockData, &playerData);

	while (1) {
		if (mode == 0) {
			menu_show();
			while (mode == 0) menu_update(&mode, &lastKey, &focus, &animFrame);
		}
		if (mode == 1) {
			lvl_create_lvl1(blockData);
			game_init_player();
			while (mode == 1) game_update(&mode, blockData, &playerData);
		}
		if (mode == 2) {
			shop_show(&playerData);
			while (mode == 2) shop_update(&mode, &lastKey, &focus, &playerData);
		}
	}
}

#endif

// for gcc compilation

#ifdef GCC

int main() {
	// gui variables

	int focus = 0;
	char lastKey = 0;
	int mode = 0;
	int animFrame = 0;


	PlayerData playerData;
	unsigned char blockData[4][15][2];

	game_init(blockData, &playerData);

	while (1) {
		if (mode == 0) {
			menu_show();
			while (mode == 0) menu_update(&mode, &lastKey, &focus, &animFrame);

		}
		if (mode == 1) {
			lvl_create_lvl1(blockData, &playerData);
			game_init_player();
			while (mode == 1) game_update(&mode, blockData, &playerData);
		}
		if (mode == 2) {
			shop_show(&playerData);
			while (mode == 2) shop_update(&mode, &lastKey, &focus, &playerData);
		}
		if (mode == 4) break;
	}

	return 0;
}

#endif