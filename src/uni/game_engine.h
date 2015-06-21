#include "game_data.h"

#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

void game_init(GameData *gameData, PlayerData *playerData);

void game_update(int *mode, GameData *gameData, PlayerData *playerData);

void game_end(int *mode, int win);

#endif  // _GAME_ENGINE_H_
