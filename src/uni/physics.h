#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "util.h"
#include "game_data.h"

void phy_simulate(GameData *gameData, PlayerData *playerData, char *lostBall);

void phy_move_striker(GameData *gameData, PlayerData *playerData, int input);

void phy_update_bullets(GameData *gameData, AnimationData *animationData);

#endif