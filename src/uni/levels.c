#if defined(__APPLE__) || defined(__WIN32__)
#include <stdio.h>
#endif

#if defined(_Z8F6403)
#include <sio.h>
#endif

#include "levels.h"
#include "game_engine.h"
#include "graphics.h"

void lvl_create_lvl1(GameData *gameData, PlayerData *playerData) {
	gameData->blockData[0] [0][0] = 0x00;
	gameData->blockData[0] [0][1] = 0x00;
	gameData->blockData[0] [1][0] = 0x00;
	gameData->blockData[0] [1][1] = 0x00;
	gameData->blockData[0] [2][0] = 0x00;
	gameData->blockData[0] [2][1] = 0x00;
	gameData->blockData[0] [3][0] = 0x00;
	gameData->blockData[0] [3][1] = 0x00;
	gameData->blockData[0] [4][0] = 0x00;
	gameData->blockData[0] [4][1] = 0x00;
	gameData->blockData[0] [5][0] = 0x00;
	gameData->blockData[0] [5][1] = 0x00;
	gameData->blockData[0] [6][0] = 0x00;
	gameData->blockData[0] [6][1] = 0x00;
	gameData->blockData[0] [7][0] = 0x00;
	gameData->blockData[0] [7][1] = 0x00;
	gameData->blockData[0] [8][0] = 0x00;
	gameData->blockData[0] [8][1] = 0x00;
	gameData->blockData[0] [9][0] = 0x00;
	gameData->blockData[0] [9][1] = 0x00;
	gameData->blockData[0][10][0] = 0x00;
	gameData->blockData[0][10][1] = 0x00;
	gameData->blockData[0][11][0] = 0x00;
	gameData->blockData[0][11][1] = 0x00;
	gameData->blockData[0][12][0] = 0x00;
	gameData->blockData[0][12][1] = 0x00;
	gameData->blockData[0][13][0] = 0xFF;
	gameData->blockData[0][13][1] = 0xFF;
	gameData->blockData[0][14][0] = 0xFF;
	gameData->blockData[0][14][1] = 0xFF;

	gameData->blockData[1] [0][0] = 0x00;
	gameData->blockData[1] [0][1] = 0x00;
	gameData->blockData[1] [1][0] = 0x00;
	gameData->blockData[1] [1][1] = 0x00;
	gameData->blockData[1] [2][0] = 0x00;
	gameData->blockData[1] [2][1] = 0x00;
	gameData->blockData[1] [3][0] = 0x00;
	gameData->blockData[1] [3][1] = 0x00;
	gameData->blockData[1] [4][0] = 0x00;
	gameData->blockData[1] [4][1] = 0x00;
	gameData->blockData[1] [5][0] = 0x00;
	gameData->blockData[1] [5][1] = 0x00;
	gameData->blockData[1] [6][0] = 0x00;
	gameData->blockData[1] [6][1] = 0x00;
	gameData->blockData[1] [7][0] = 0x00;
	gameData->blockData[1] [7][1] = 0x00;
	gameData->blockData[1] [8][0] = 0x00;
	gameData->blockData[1] [8][1] = 0x00;
	gameData->blockData[1] [9][0] = 0x00;
	gameData->blockData[1] [9][1] = 0x00;
	gameData->blockData[1][10][0] = 0xFF;
	gameData->blockData[1][10][1] = 0xFF;
	gameData->blockData[1][11][0] = 0xFF;
	gameData->blockData[1][11][1] = 0xFF;
	gameData->blockData[1][12][0] = 0xFF;
	gameData->blockData[1][12][1] = 0xFF;
	gameData->blockData[1][13][0] = 0x00;
	gameData->blockData[1][13][1] = 0x00;
	gameData->blockData[1][14][0] = 0x00;
	gameData->blockData[1][14][1] = 0x00;

	gameData->blockData[2] [0][0] = 0x00;
	gameData->blockData[2] [0][1] = 0x00;
	gameData->blockData[2] [1][0] = 0x00;
	gameData->blockData[2] [1][1] = 0x00;
	gameData->blockData[2] [2][0] = 0x00;
	gameData->blockData[2] [2][1] = 0x00;
	gameData->blockData[2] [3][0] = 0x00;
	gameData->blockData[2] [3][1] = 0x00;
	gameData->blockData[2] [4][0] = 0xFF;
	gameData->blockData[2] [4][1] = 0xFF;
	gameData->blockData[2] [5][0] = 0xFF;
	gameData->blockData[2] [5][1] = 0xFF;
	gameData->blockData[2] [6][0] = 0xFF;
	gameData->blockData[2] [6][1] = 0xFF;
	gameData->blockData[2] [7][0] = 0xFF;
	gameData->blockData[2] [7][1] = 0xFF;
	gameData->blockData[2] [8][0] = 0xFF;
	gameData->blockData[2] [8][1] = 0xFF;
	gameData->blockData[2] [9][0] = 0xFF;
	gameData->blockData[2] [9][1] = 0xFF;
	gameData->blockData[2][10][0] = 0x00;
	gameData->blockData[2][10][1] = 0x00;
	gameData->blockData[2][11][0] = 0x00;
	gameData->blockData[2][11][1] = 0x00;
	gameData->blockData[2][12][0] = 0x00;
	gameData->blockData[2][12][1] = 0x00;
	gameData->blockData[2][13][0] = 0x00;
	gameData->blockData[2][13][1] = 0x00;
	gameData->blockData[2][14][0] = 0x00;
	gameData->blockData[2][14][1] = 0x00;

	gameData->blockData[3] [0][0] = 0xFF;
	gameData->blockData[3] [0][1] = 0xFF;
	gameData->blockData[3] [1][0] = 0xFF;
	gameData->blockData[3] [1][1] = 0xFF;
	gameData->blockData[3] [2][0] = 0xFF;
	gameData->blockData[3] [2][1] = 0xFF;
	gameData->blockData[3] [3][0] = 0xFF;
	gameData->blockData[3] [3][1] = 0xFF;
	gameData->blockData[3] [4][0] = 0x00;
	gameData->blockData[3] [4][1] = 0x00;
	gameData->blockData[3] [5][0] = 0x00;
	gameData->blockData[3] [5][1] = 0x00;
	gameData->blockData[3] [6][0] = 0x00;
	gameData->blockData[3] [6][1] = 0x00;
	gameData->blockData[3] [7][0] = 0x00;
	gameData->blockData[3] [7][1] = 0x00;
	gameData->blockData[3] [8][0] = 0x00;
	gameData->blockData[3] [8][1] = 0x00;
	gameData->blockData[3] [9][0] = 0x00;
	gameData->blockData[3] [9][1] = 0x00;
	gameData->blockData[3][10][0] = 0x00;
	gameData->blockData[3][10][1] = 0x00;
	gameData->blockData[3][11][0] = 0x00;
	gameData->blockData[3][11][1] = 0x00;
	gameData->blockData[3][12][0] = 0x00;
	gameData->blockData[3][12][1] = 0x00;
	gameData->blockData[3][13][0] = 0x00;
	gameData->blockData[3][13][1] = 0x00;
	gameData->blockData[3][14][0] = 0x00;
	gameData->blockData[3][14][1] = 0x00;
}