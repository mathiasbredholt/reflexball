#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "hw_time.h"

#ifndef _hw_INPUT_H_
#define _hw_INPUT_H_

void hw_init();

void hw_ROM_to_RAM(char *dest, rom char *src);

char hw_read_key();

char hw_keys();

char hw_wait_for_key();

#endif