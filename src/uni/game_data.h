
#ifndef _GAME_DATA_
#define _GAME_DATA_

#include "util.h"

#define NUMBER_OF_ITEMS 8
#define striker_height 92
#define game_width 256
#define game_height 96

typedef struct PlayerData {
	long energy;
	long energyMax;
	long oldEnergy;
	int coins;
	unsigned char items[NUMBER_OF_ITEMS];
	unsigned char itemPrice[NUMBER_OF_ITEMS];
	unsigned char itemMax[NUMBER_OF_ITEMS];
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
	char multiplier;
} GameData;

typedef struct AnimationData {
	int blockDestruction[4];
	unsigned char projectilePos[5][2];
	char projectileType[5];
	char eraseProjectile[5];
	char rocketHit[3];	// bit 0: x coord, bit 1: y coord, bit 2: flag (1 if rocket has hit)
} AnimationData;

#if defined(_Z8F6403)
rom unsigned char itemMax[NUMBER_OF_ITEMS] =
#else
const unsigned char itemMax[NUMBER_OF_ITEMS] =
#endif
{3, 3, 3, 3, 3, 3, 3, 3};

#if defined(_Z8F6403)
rom unsigned char itemPrice[NUMBER_OF_ITEMS] =
#else
const unsigned char itemPrice[NUMBER_OF_ITEMS] =
#endif
{3, 3, 3, 3, 3, 3, 3, 3};

#endif