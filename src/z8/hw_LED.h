#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "charset.h"
#include "util.h"
#include "hw_time.h"

#ifndef _hw_LED_H_
#define _hw_LED_H_

void LED_init();

void LED_displaycolumn(int val, int col, int disp);

void LED_updateVideoBuffer();

void LED_setString(char *str);

void LED_update();

#endif