// EDITED FOR USE IN WINDOWS

#include <curses.h> // Provides getch() and kbhit()


#ifndef _hw_INPUT_H_
#define _hw_INPUT_H_

void hw_init();

// void hw_ROM_to_RAM(char *dest, rom char *src);

char hw_read_key();

char hw_keys();

char hw_wait_for_key();

#endif