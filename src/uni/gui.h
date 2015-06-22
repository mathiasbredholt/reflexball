#ifndef _GUI_H_
#define _GUI_H_

#include "game_engine.h"

void menu_show();

void menu_update(int *mode, char *lastKey, int *focus, int *animFrame1, int *animFrame2);

void map_show(PlayerData *playerData, int *focus);

void map_update(int *mode, char *lastKey, int *focus, GameData *gameData, PlayerData *playerData);

void map_info(int *mode, char *lastKey);

void map_info_show(GameData *gameData);

void map_info_update(int *mode, char *lastKey);

void shop_show(PlayerData *playerData);

void shop_update(int *mode, char *lastKey, int *focus, PlayerData *playerData);

#endif