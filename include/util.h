#include <sio.h>

#ifndef _UTIL_H_
#define _UTIL_H_

#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) ( (a)*(b) >> FIX14_SHIFT)
#define FIX14_DIV(a,b) ( ((a) << FIX14_SHIFT) / (b))

typedef struct TVector {
    long x,y;
} TVector;

int strlen(char * str);

void printFix(long i);

long expand(long i);

signed short sin(int x);

signed short cos(int x);

void rotate(struct TVector *v, int angle);

#endif