#include "util.h"

#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#define NUMBER_OF_ITEMS 8

typedef struct PlayerData {
	int energy;
	int coins;
	unsigned char items[NUMBER_OF_ITEMS];
} PlayerData;

typedef struct GameData {
	unsigned char blockData[4][15][2];
	TVector_8_8 ballOldPos, ballPos;
	TVector_0_7 ballVel;
	unsigned int strikerOldPos, strikerPos;
	char strikerSize, redraw, bouncedStriker;
	int blockHit[2];
	int ballSpeed;
} GameData;

void game_init(GameData *gameData, PlayerData *playerData);

void game_update(int *mode, GameData *gameData, PlayerData *playerData);

#endif  // _GAME_ENGINE_H_
