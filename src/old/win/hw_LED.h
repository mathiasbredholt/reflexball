#ifndef __APPLE__
#ifndef __win32__

#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "charset.h"
#include "util.h"
#include "hw_time.h"

#endif
#endif

#ifndef _hw_LED_H_
#define _hw_LED_H_

void LED_init();

void LED_display_column(int val, int col, int disp);

void LED_update_video_buffer();

void LED_set_string(char *str);

void LED_update();

#endif