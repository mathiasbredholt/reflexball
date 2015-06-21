#include "util.h"

#ifndef _GAME_DATA_
#define _GAME_DATA_

#define NUMBER_OF_ITEMS 8

typedef struct PlayerData {
	int energy;
	int oldEnergy;
	int coins;
	unsigned char items[NUMBER_OF_ITEMS];
} PlayerData;

typedef struct GameData {
	unsigned char blockData[15][8];
	TVector_8_8 ballOldPos, ballPos;
	TVector_0_7 ballVel;
	unsigned int strikerOldPos, strikerPos;
	char strikerSize, redraw, bouncedStriker, bouncedTop, bouncedSide;
	int blockHit[3];
	int ballSpeed;
	char level;
} GameData;

typedef struct AnimationData {
	int blockDestruction[4];
	unsigned char projectiles[5];
} AnimationData;

#endif