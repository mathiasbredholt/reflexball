#ifdef __APPLE__
#define GCC
#endif

#ifdef __win32__
#define GCC
#endif

#ifndef _hw_INPUT_H_
#define _hw_INPUT_H_

void hw_init();

#ifndef GCC
void hw_ROM_to_RAM(char *dest, rom char *src);
#endif

char hw_read_key();

char hw_keys();

char hw_wait_for_key();

#endif