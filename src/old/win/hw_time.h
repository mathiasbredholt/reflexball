#ifndef __win32__
#ifndef __APPLE__

#include <eZ8.h>

#endif
#endif

#ifndef _hw_TIME_H_
#define _hw_TIME_H_

void hw_time_init();

unsigned long hw_time_millis();

char hw_time_get_next_frame();

void hw_time_set_next_frame(char val);

char hw_time_get_LEDflag();

void hw_time_set_LEDflag(char val);

#endif  // _hw_TIME_H_
