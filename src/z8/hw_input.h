#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>

#ifndef _HW_INPUT_H_
#define _HW_INPUT_H_

void ISR_T1();

void HW_init();

void HW_ROMtoRAM(char *dest, rom char *src);

char HW_readkey();

void HW_keysListener();

char HW_updateKeys(char *lastInput, char *lastKeys);

char HW_waitForKey();

#endif