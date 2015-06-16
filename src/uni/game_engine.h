#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#define NUMBER_OF_ITEMS 8

typedef struct PlayerData {
	unsigned char energy;
	unsigned int coins;
	unsigned char items[NUMBER_OF_ITEMS];
} PlayerData;

void game_init(unsigned char blockData[4][15][2], PlayerData *playerData);

void game_update(int *mode, unsigned char blockData[4][15][2], PlayerData *playerData);

void game_init_player();

void game_wait_for_input();

#endif  // _GAME_ENGINE_H_
