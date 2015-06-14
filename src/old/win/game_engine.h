// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <stdio.h>
#include "hw_time.h"
#include "hw_LED.h"
#include "hw_input.h"
#include "levels.h"
#include "graphics.h"
// #include "sounds.h"
// #include "physics.h"

#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

void game_init();

void game_update();

void game_init_player();

void game_wait_for_input();

#endif  // _GAME_ENGINE_H_
