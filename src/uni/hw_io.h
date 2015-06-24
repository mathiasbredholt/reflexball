#ifndef _hw_INPUT_H_
#define _hw_INPUT_H_

void hw_init();

void hw_ROM_to_RAM(char *dest,

#if defined(_Z8F6403)
                   rom
#else
                   const
#endif
                   char *src);

char hw_read_key();

char hw_keys();

char hw_wait_for_key();

void hw_ADC_init();

unsigned char hw_read_analog();

#endif