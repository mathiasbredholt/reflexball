// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <sio.h>
#include "ansi.h"
#include "util.h"
#include "hwz8.h"

void main() {
    HWinit();
    LEDsetString("Hejsa Dette er en lang streng    #nemt");

    while (1) {
        LEDupdate();
    }
}
