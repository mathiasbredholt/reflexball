/*
 ###    ####   ####   #      ####   #   #  ####     #    #      #
 #  #   #      #      #      #       # #   #   #   # #   #      #
 #  #   ###    ###    #      ###      #    ####   #   #  #      #
 ###    #      #      #      #       # #   #   #  #####  #      #
 #  #   #      #      #      #       # #   #   #  #   #  #      #
 #  #   ####   #      ####   ####   #   #  ####   #   #  ####   ####
 */

#include "game_data.h"
#include "game_engine.h"

#if defined(_Z8F6403)
void main()
#else
int main()
#endif
{
	///////////////////
	// gui variables //
	///////////////////
	int mode;
	int focus;
	char lastKey;

	// Counters for star animation in start menu
	int animFrame1;
	int animFrame2;

	PlayerData playerData;
	GameData gameData;
	AnimationData animationData;

	init(&mode, &focus, &lastKey, &animFrame1, &animFrame2, &playerData, &gameData);

	while (1) {
		if (mode == 0) {
			// Start menu
			menu_init();
			while (mode == 0) menu_update(&mode, &lastKey, &focus, &animFrame1, &animFrame2, &playerData);
		}
		if (mode == 1) {
			// Level select
			map_init(&playerData, &focus);
			while (mode == 1) map_update(&mode, &lastKey, &focus, &gameData, &playerData);
		}
		if (mode == 2) {
			// Level info page
			map_info_init(&gameData);
			while (mode == 2) map_info_update(&mode, &lastKey);
		}
		if (mode == 3) {
			// Game
			game_init(&gameData, &playerData, &animationData);
			while (mode == 3) game_update(&mode, &lastKey, &gameData, &playerData, &animationData);
		}
		if (mode == 4) {
			// Shop
			shop_init(&playerData);
			while (mode == 4) shop_update(&mode, &lastKey, &focus, &playerData, &gameData);
		}

#if defined(__APPLE__) || defined(__WIN32__)
		if (mode == 6) break;	// Exit
#endif
	}
#if defined(__APPLE__) || defined(__WIN32__)
	return 0; // only for computer
#endif
}
