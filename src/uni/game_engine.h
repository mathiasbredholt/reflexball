#include "game_data.h"

#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

void game_init(GameData *gameData, PlayerData *playerData, AnimationData *animationData);

void game_update(int *mode, char *lastKey, GameData *gameData, PlayerData *playerData, AnimationData *animationData);

void game_end(int *mode, int win);

#endif  // _GAME_ENGINE_H_
