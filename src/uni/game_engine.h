#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

void game_init();

void game_update(char blockData[4][15][2], char *lives, int *points);

void game_init_player();

void game_wait_for_input();

#endif  // _GAME_ENGINE_H_
