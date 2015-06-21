#ifndef _MAP_H_
#define _MAP_H_

#include "game_engine.h"

void map_show(PlayerData *playerData);

void map_update(int *mode, char *lastKey, int *focus, GameData *gameData, PlayerData *playerData);

void map_info(int *mode, char *lastKey);

void map_info_show(int *map);
#endif