// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <sio.h>
#include "util.h"
#include "lut.h"

int util_strlen(char * str) {
    int i;
    for (i = 0; str[i] != '\0'; i++);
    return i;
}

void util_printfix(long i) {
    // prints a signed 16.16 fixed point number
    if ((i & 0x80000000) != 0) { // handle negative numbers
        printf("-");
        i = ~i + 1;
    }
    printf("%ld.%04ld", i >> 16, 10000 * (unsigned long) (i & 0xffff) >> 16);
    // max 4 digits otherwise we get overflow
}

long util_expand(long i) {
    // converts an 18.14 to a 16.16
    return i << 2;
}

signed short util_sin(int x) {
    return SIN[x & 0x1FF];
}

signed short util_cos(int x) {
    return util_sin(x + 128);
}

// void initVector(struct TVector * v) {

//     v.y = 20;
// }

void util_rotate(TVector *v, int angle) {
    long temp = v->x;
    v->x = v->x * util_cos(angle) - v->y * util_sin(angle);
    v->y = temp * util_sin(angle) + v->y * util_cos(angle);
}