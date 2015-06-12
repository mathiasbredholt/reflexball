// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <eZ8.h>

#ifndef _HW_TIME_H_
#define _HW_TIME_H_

void hw_time_init();

unsigned long hw_time_millis();

char hw_time_get_nextframe();

void hw_time_set_nextframe(char val);

char hw_time_get_LEDflag();

void hw_time_set_LEDflag(char val);

#endif  // _HW_TIME_H_
