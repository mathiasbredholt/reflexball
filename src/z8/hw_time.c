// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <eZ8.h>
#include <sio.h>  // MOVE! 

unsigned long millis;
char _nextFrame = 0;

#pragma interrupt
void ISR_T0() {
    ++millis;
    _nextFrame = 1;
}

void hw_time_init() {
    init_uart(_UART0, _DEFFREQ, 115200);  // set-up UART0 to 115200, 8n1   // MOVE!
    millis = 0;

    // Setup timer
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

    // Set priority to LOW
    IRQ0ENH &= ~0x20;
    IRQ0ENL |= 0x20;

    // Enable timer0
    T0CTL |= 0x80;

    SET_VECTOR(TIMER0, ISR_T0);
    EI();
}

unsigned long hw_time_millis() {
    return millis;
}

char hw_time_get_nextframe() {
    return _nextFrame;
}

void hw_time_set_nextframe(char val) {
    _nextFrame = val;
}
