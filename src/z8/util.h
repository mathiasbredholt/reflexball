// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <stdio.h>

#ifndef _UTIL_H_
#define _UTIL_H_

#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) ( (a)*(b) >> FIX14_SHIFT)
#define FIX14_DIV(a,b) ( ((a) << FIX14_SHIFT) / (b))

typedef struct TVector {
	long x, y;
} TVector;

int util_strlen(char * str);

void util_printfix(long i);

long util_expand(long i);

signed short util_sin(int x);

signed short util_cos(int x);

void util_rotate(struct TVector *v, int angle);

#endif