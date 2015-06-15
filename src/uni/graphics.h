#include "util.h"

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

void gfx_draw_bounds();

void gfx_draw_ball(TVector_8_8 oldPos, TVector_8_8 newPos);

void gfx_draw_striker(unsigned int oldX, unsigned int newX);

void gfx_change_striker_size(unsigned int x, int size);

void gfx_set_striker_size(int size);

void gfx_draw_bars();

void gfx_window(int x1, int y1, int x2, int y2,  int draw);

#endif