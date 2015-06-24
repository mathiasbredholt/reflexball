/*
 #  #   #####  ###    #
 #  #     #     #     #
 #  #     #     #     #
 #  #     #     #     #
 #  #     #     #     #
  ##      #    ###    ####
*/

#include <stdio.h>
#include "util.h"
#include "sin_lib.h"

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

TVector_8_8 util_expand_vector(TVector_0_7 v) {
    TVector_8_8 v2;
    v2.x = (unsigned int) (v.x << 1);
    v2.y = (unsigned int) (v.y << 1);
    return v2;
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

void util_rotate(TVector_0_7 *v, int angle) {
    int cosine, sine, x, y;
    cosine = shift_fix_int_right(util_cos(angle), 7);   // 0.7 representation
    sine = shift_fix_int_right(util_sin(angle), 7);   // 0.7 representation
    x = char_to_int(v->x);
    y = char_to_int(v->y);
    v->x = (char) (shift_fix_int_right(x * cosine, 7) - shift_fix_int_right(y * sine, 7));
    v->y = (char) (shift_fix_int_right(x * sine, 7) + shift_fix_int_right(y * cosine, 7));
}

int shift_fix_int_right(int x, int shift) {
    // Also works for negative numbers by filling in with the sign bit
    int i;
    int msb = x >> 15;
    x >>= shift;
    if (msb) {
        for (i = 0; i < shift; ++i) {
            x |= 0x8000 >> i;
        }
    }
    return x;
}

char shift_fix_char_right(int y, int shift) {
    // Also works for negative numbers by filling in with the sign bit. Takes an int because of compiler error
    char i;
    char x = (char) y;
    char msb = x >> 7;
    x >>= shift;
    if (msb) {
        for (i = 0; i < shift; ++i) {
            x |= 0x80 >> i;
        }
    }
    return x;
}

int char_to_int(int y) {
    // Also works for negative numbers by filling in with the sign bit.
    char i;
    char x = (char) y;
    char msb = x >> 7;
    if (msb) {
        for (i = 0; i < 8; ++i) {
            y |= 0x8000 >> i;
        }
    }
    return y;
}