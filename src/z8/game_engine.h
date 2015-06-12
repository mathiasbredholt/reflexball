// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include "hw_time.h"
#include "hw_input.h"
#include "hw_LED.h"
#include "levels.h"
#include "graphics.h"
// #include "sounds.h"
// #include "physics.h"

#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

void game_init();

void game_update();

void game_init_player();

#endif  // _GAME_ENGINE_H_
