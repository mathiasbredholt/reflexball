// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <stdio.h>
#include "util.h"
#include "ansi.h"
// #include "include/hwz8.h"

int main(int argc, char const *argv[]) {
    // HWinit();
    // LEDsetString("Hejsa Dette er en lang streng    #nemt");
    clrscr();
    window(0, 0, 15, 10, "Hello");
    printf("asdf\n");

    // while (1) {
    //     // LEDupdate();
    // }

    return 0;
}
