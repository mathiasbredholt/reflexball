// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <stdio.h>
#include "include/ansi.h"
#include "include/util.h"
#include "include/hwz8.h"

void main() {
    HWinit();
    LEDsetString("Hejsa Dette er en lang streng    #nemt");

    while (1) {
        LEDupdate();
    }
}
