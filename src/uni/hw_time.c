#ifdef __APPLE__
#define GCC

#include <unistd.h>

void mySleep(int sleepMs) {
    usleep(sleepMs);
}

#endif

#ifdef __WIN32__
#define GCC

#include <windows.h>

void mySleep(int sleepMs) {
    Sleep(sleepMs);
}

#endif

// hw_time.c

#ifndef GCC

#include <eZ8.h>

unsigned long _millis;
char _nextFrame;
char _LEDflag;

#pragma interrupt
void ISR_T0() {
    ++_millis;
    _LEDflag = 1;
}

#pragma interrupt
void ISR_T1() {
    _nextFrame = 1;
}

void hw_time_init() {
    // Setup timer 0 (millis)
    // TEN: 0, TPOL: 0, PRES: 0 (1), TMODE: 1 (cont.)
    T0CTL = 0x01;
    // T0CTL = 0x39;

    // Begin timer at 0
    T0H = 0;
    T0L = 0;

    // End timer at 1843 (1 kHz)
    T0RH = 0x48;
    T0RL = 0x00;

    // Enable TIMER0 interrupt
    IRQ0 |= 0x20;

    // Set priority to HIGH
    IRQ0ENH |= 0x20;
    IRQ0ENL |= 0x20;

    // Enable timer0
    T0CTL |= 0x80;

    _millis = 0;
    _nextFrame = 0;
    _LEDflag = 0;


    // Setup timer 1 (game loop)
    // TEN: 0, TPOL: 0, PRES: 7 (128), TMODE: 1 (cont.)
    T1CTL = 0x39;

    // Begin timer at 0
    T1H = 0;
    T1L = 0;

    // End timer at 4777 (30 Hz)
    T1RH = 0x12;
    T1RL = 0xA9;

    // Enable TIMER0 interrupt
    IRQ0 |= 0x40;

    // Set priority to LOW
    IRQ0ENH &= ~0x40;
    IRQ0ENL |= 0x40;

    // Enable timer1
    T1CTL |= 0x80;

    SET_VECTOR(TIMER0, ISR_T0);
    SET_VECTOR(TIMER1, ISR_T1);
    EI();

    _millis = 0;
    _nextFrame = 0;
    _LEDflag = 0;
}

unsigned long hw_time_millis() {
    return _millis;
}

char hw_time_get_next_frame() {
    return _nextFrame;
}

void hw_time_set_next_frame(char val) {
    _nextFrame = val;
}

char hw_time_get_LEDflag() {
    return _LEDflag;
}

void hw_time_set_LEDflag(char val) {
    _LEDflag = val;
}

#endif

#ifdef GCC

void hw_time_init() {};

unsigned long hw_time_millis() { return 0; };

char hw_time_get_next_frame() {
    mySleep(75);
    return 1;
};

void hw_time_set_next_frame(char val) {};

char hw_time_get_LEDflag() { return 0; };

void hw_time_set_LEDflag(char val) {};

#endif