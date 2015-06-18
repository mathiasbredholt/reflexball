#include "util.h"
#include "game_engine.h"

void phy_simulate(GameData *gameData);

void phy_move_striker(GameData *gameData, PlayerData *playerData, unsigned char input);

char phy_hit_block(GameData *gameData, int x, int y);
