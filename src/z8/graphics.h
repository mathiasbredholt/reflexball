#include <sio.h>
#include "ansi.h"
#include "util.h"

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

void gfx_draw_bounds();

void gfx_draw_ball(int x, int y);

void gfx_draw_striker(int x, int y);

void gfx_window(int x1, int y1, int x2, int y2, char *title);

#endif