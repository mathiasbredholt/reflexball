// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <sio.h>
#include "lut.h"

#ifndef _UTIL_H_
#define _UTIL_H_

#define FIX8_SHIFT 8
#define FIX8_MULT(a,b) ( (a)*(b) >> FIX8_SHIFT)
#define FIX8_DIV(a,b) ( ((a) << FIX8_SHIFT) / (b))

typedef struct TVector_8_8 {
	// Vector in 8.8 unsigned fixed point notation
	unsigned int x, y;
} TVector_8_8;

typedef struct TVector_0_7 {
	// Vector in 0.7 signed fixed point notation
	signed char x, y;
} TVector_0_7;

int util_strlen(char * str);

void util_printfix(long i);

long util_expand(long i);

TVector_8_8 util_expand_vector(TVector_0_7 v);

signed short util_sin(int x);

signed short util_cos(int x);

void util_rotate(struct TVector_0_7 *v, int angle);

#endif