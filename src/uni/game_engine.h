#include "game_data.h"

#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

void init(int *mode, int *focus, char *lastKey, int *animFrame1, int *animFrame2, PlayerData *playerData, GameData *gameData);

void menu_init();

void menu_update(int *mode, char *lastKey, int *focus, int *animFrame1, int *animFrame2, PlayerData *playerData);

void map_init(PlayerData *playerData, int *focus);

void map_update(int *mode, char *lastKey, int *focus, GameData *gameData, PlayerData *playerData);

void map_info(int *mode, char *lastKey);

void map_info_init(GameData *gameData);

void map_info_update(int *mode, char *lastKey);

void game_init(GameData *gameData, PlayerData *playerData, AnimationData *animationData);

void game_update(int *mode, char *lastKey, GameData *gameData, PlayerData *playerData, AnimationData *animationData);

void game_end(int *mode, int win, PlayerData *playerData, GameData *gameData);

void shop_init(PlayerData *playerData);

void shop_update(int *mode, char *lastKey, int *focus, PlayerData *playerData, GameData *gameData);

#endif  // _GAME_ENGINE_H_
