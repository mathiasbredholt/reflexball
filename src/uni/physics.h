#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "util.h"
#include "game_data.h"

void phy_simulate(GameData *gameData, char *lostBall);

void phy_move_striker(GameData *gameData, PlayerData *playerData, unsigned char input);

char phy_hit_block(GameData *gameData, int x, int y,  char *justHitBlock);

#endif