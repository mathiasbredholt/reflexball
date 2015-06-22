
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include "util.h"
#include "game_data.h"

void gfx_draw_ball(GameData *gameData);

void gfx_init_ball(GameData *gameData);

void gfx_draw_striker(GameData *gameData);

void gfx_init_striker(GameData *gameData);

void gfx_erase_striker(GameData *gameData);

void gfx_update_animation(AnimationData *animationData);

void gfx_draw_all_blocks(GameData *gameData);

void gfx_draw_block(int x, int y, int type);

void gfx_erase_block(int x, int y);

void gfx_window(int x1, int y1, int x2, int y2);

void gfx_draw_text(int col, int x, int y, char *str);

void gfx_draw_btn(int x, int y, char *str, int focus);

void gfx_draw_btn_focus(int x, int y, char * str, int focus);

void gfx_draw_item(int x, int y, int item);

void gfx_draw_meter(int x, int y, int val);

void gfx_draw_energy_meter();

void gfx_update_energy_meter(PlayerData *playerData);

void gfx_draw_bullet(int x, int newY, int oldY, int type);

void gfx_draw_stars(int frame);

void gfx_draw_game_over();

void gfx_draw_victory();

void gfx_draw_score(PlayerData *playerData);

void gfx_draw_thumb(int x, int y, int thumb, int col);

void gfx_draw_title(int x, int y);

#endif