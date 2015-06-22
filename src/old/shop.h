#ifndef _SHOP_H_
#define _SHOP_H_

#include "game_data.h"

void shop_show(PlayerData *playerData);

void shop_update(int *mode, char *lastKey, int *focus, PlayerData *playerData);

#endif