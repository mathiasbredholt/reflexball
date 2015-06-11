#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>

#ifndef _HW_LED_H_
#define _HW_LED_H_

void ISR_T0();

void LED_init();

void LED_displaycolumn(int val, int col, int disp);

void LED_updateVideoBuffer();

void LED_setString(char *str);

void LED_update();

#endif