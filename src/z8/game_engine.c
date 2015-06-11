// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include "game_engine.h"
#include "hw_time.h"
#include "hw_input.h"
#include "hw_LED.h"
#include "sounds.h"
#include "levels.h"
#include "graphics.h"
#include "physics.h"

#define FRAME_INTERVAL 63;

unsigned long lastFrame;
char * str = "0";
char val = 0;

void game_init() {
    hw_time_init();
    lastFrame = 0;
}

void game_update() {
    if ((hw_time_millis() & FRAME_INTERVAL) == FRAME_INTERVAL) {
        // levels_redraw();
        str[0] = ++val;
        gfx_window(0, 0, 20, 20, str);
    }
}
