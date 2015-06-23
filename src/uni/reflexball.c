// reflexball.c

#include "game_engine.h"
#include "game_data.h"
#include "hw_time.h"
#include "hw_input.h"
#include "hw_sound.h"
#include "hw_LED.h"
#include "gui.h"
#include "hw_flash.h"
#include <sio.h>

#if defined(_Z8F6403)
void main()
#else
int main()
#endif
{
	///////////////////
	// gui variables //
	///////////////////
	int mode = 0;
	int focus = 0;
	char lastKey = 0;

	// Counters for star animation in start menu
	int animFrame1 = 0;
	int animFrame2 = 104;

	PlayerData playerData;
	GameData gameData;
	AnimationData animationData;

	/////////////////////////
	// Hardware initialize //
	/////////////////////////
	int i;
	hw_init();
	hw_time_init();
	hw_ADC_init();
	hw_sound_init();
	hw_flash_init();
	LED_init();
	//LED_display_column(0xFF, 0, 0);
	//LED_set_string("Welcome");

	///////////////////////
	// Reset player data //
	///////////////////////
	for (i = 0; i < NUMBER_OF_ITEMS; ++i) {
		playerData.items[i] = 0;
	}

	playerData.coins = 133;
	playerData.progress = 0;
	playerData.energyMax = 0x7FFF;

	WriteByteToFlash(128, playerData.coins);

	printf("WRITTEN\n");

	printf("LOADED %d", ReadByteFromFlash(128));

	while (1);

	gameData.strikerSize = 48;

	mode = 5;
	while (1) {
		if (mode == 0) {
			// Start menu
			menu_show();
			while (mode == 0) menu_update(&mode, &lastKey, &focus, &animFrame1, &animFrame2, &playerData);
		}
		if (mode == 1) {
			// Level select
			map_show(&playerData, &focus);
			while (mode == 1) map_update(&mode, &lastKey, &focus, &gameData, &playerData);
		}
		if (mode == 2) {
			// Level info page
			map_info_show(&gameData);
			while (mode == 2) map_info_update(&mode, &lastKey);
		}
		if (mode == 3) {
			// Game
			game_init(&gameData, &playerData, &animationData);
			while (mode == 3) game_update(&mode, &lastKey, &gameData, &playerData, &animationData);
		}
		if (mode == 4) {
			// Shop
			shop_show(&playerData);
			while (mode == 4) shop_update(&mode, &lastKey, &focus, &playerData, &gameData);
		}

		if (mode == 5) {
			intro_play();
			while (mode == 5) intro_update(&mode, &lastKey);
		}

#if defined(__APPLE__) || defined(__WIN32__)
		if (mode == 6) break;	// Exit
#endif
	}
#if defined(__APPLE__) || defined(__WIN32__)
	return 0; // only for computer
#endif
}
