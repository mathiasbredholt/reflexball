#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "hw_time.h"

#ifndef _HW_INPUT_H_
#define _HW_INPUT_H_

void HW_init();

void HW_ROMtoRAM(char *dest, rom char *src);

char HW_readkey();

char HW_updateKeys(char *lastInput, char *lastKeys);

char HW_waitForKey();

#endif