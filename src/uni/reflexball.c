// reflexball.c

#include "game_engine.h"
#include "hw_time.h"
#include "hw_input.h"
#include "hw_sound.h"
#include "hw_LED.h"
#include "levels.h"
#include "intro.h"
#include "graphics.h"
#include "menu.h"
#include "shop.h"

#if defined(_Z8F6403)
void main()
#endif

#if defined(__APPLE__) || defined(__WIN32__)
int main()
#endif
{
	// gui variables

	int mode = 0;
	int focus = 0;
	char lastKey = 0;

	int animFrame1 = 0;
	int animFrame2 = 104;

	PlayerData playerData;
	GameData gameData;

	// Hardware initialize
	int i;
	hw_init();
	hw_time_init();
	hw_ADC_init();
	//hw_sound_init();

	//LED_init();
	//LED_set_string("Welcome");


	for (i = 0; i < NUMBER_OF_ITEMS; ++i) {
		playerData.items[i] = 0;
	}

	playerData.coins = 0;

	gameData.strikerSize = 48;


	while (1) {
		if (mode == 0) {
			menu_show();
			while (mode == 0) menu_update(&mode, &lastKey, &focus, &animFrame1, &animFrame2);
		}
		if (mode == 1) {
			lvl_create_lvl1(&gameData, &playerData);
			game_init(&gameData, &playerData);
			while (mode == 1) game_update(&mode, &gameData, &playerData);
		}
		if (mode == 2) {
			shop_show(&playerData);
			while (mode == 2) shop_update(&mode, &lastKey, &focus, &playerData);
		}
		if (mode == 3) {
			while (mode == 3) {	
				hw_sound_update();
			}
		}

#if defined(__APPLE__) || defined(__WIN32__)
		if (mode == 4) break;
#endif
	}
#if defined(__APPLE__) || defined(__WIN32__)
	return 0; // only for computer
#endif
}
