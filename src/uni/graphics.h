#include "util.h"
#include "game_engine.h"

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

void gfx_draw_ball(GameData *gameData);

void gfx_draw_striker(GameData *gameData);

void gfx_erase_striker(GameData *gameData);

void gfx_draw_all_blocks(GameData *gameData);

void gfx_draw_block(int x, int y, int type);

void gfx_erase_block(int x, int y);

void gfx_window(int x1, int y1, int x2, int y2);

void gfx_draw_text(int x, int y, char *str);

void gfx_draw_btn(int x, int y, char *str, int focus);

void gfx_draw_btn_focus(int x, int y, char * str, int focus);

void gfx_draw_item(int x, int y, int item);

void gfx_draw_meter(int x, int y, int val);

void gfx_draw_energy_meter(int val);

void gfx_update_energy_meter(int val);

void gfx_draw_bullet(int x, int newY, int oldY, int type);

void gfx_draw_stars(int frame);

#endif