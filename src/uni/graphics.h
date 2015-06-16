#include "util.h"

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

void gfx_draw_bounds();

void gfx_draw_ball(TVector_8_8 oldPos, TVector_8_8 newPos);

void gfx_draw_striker(unsigned int oldX, unsigned int newX);

void gfx_change_striker_size(unsigned int x, int size);

void gfx_set_striker_size(int size);

void gfx_draw_all_blocks(unsigned char blockData[4][15][2]);

void gfx_draw_block(int x, int y, int type);

void gfx_erase_block(int x, int y);

void gfx_window(int x1, int y1, int x2, int y2,  int draw);

void gfx_draw_text(int x, int y, char *str);

void gfx_draw_btn(int x, int y, char *str, int focus);

void gfx_draw_btn_focus(int x, int y, char * str, int focus);

void gfx_draw_item(int x, int y, int item);

void gfx_draw_meter(int x, int y, int val);

#endif