#include "util.h"

#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#define NUMBER_OF_ITEMS 8

typedef struct PlayerData {
	unsigned char energy;
	unsigned int coins;
	unsigned char items[NUMBER_OF_ITEMS];
} PlayerData;

typedef struct GameData {
	unsigned char blockData[4][15][2];
	TVector_8_8 ballOldPos, ballPos;
	TVector_0_7 ballVel;
	unsigned int strikerOldPos, strikerPos;
	char strikerSize, redraw, bouncedStriker;
	int blockHit, ballSpeed;
} GameData;

void game_init(GameData *gameData, PlayerData *playerData);

void game_update(GameData *gameData, PlayerData *playerData);

void game_init_player(GameData *gameData);

void game_wait_for_input();

#endif  // _GAME_ENGINE_H_
