#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "hw_time.h"

#ifndef _hw_INPUT_H_
#define _hw_INPUT_H_

void hw_init();

void hw_ROMtoRAM(char *dest, rom char *src);

char hw_readkey();

char hw_keys();

char hw_waitForKey();

#endif