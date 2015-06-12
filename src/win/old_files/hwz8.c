// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "hwz8.h"
#include "charset.h"
#include "util.h"

#define DEBOUNCE_INTERVAL 10  // ms

#define SCROLL_INTERVAL 30  // ms between change
#define LED_MAX_STR_LEN 128

Time time;
unsigned long millis;

char _video_buffer[5][6];
char _LEDtext[LED_MAX_STR_LEN];
char _display_column, _scroll_index, _scroll_count, _text_index, _LEDinterrupt;

#pragma interrupt
void ISR_T0() { //copied and renamed
    _LEDinterrupt = 1;
    ++_scroll_count;
    // printf("%d\n", (int) _display_column);
}

// #pragma interrupt
// void ISR_T0() {
//  ++time.cent;
//  if (time.cent >= 100) {
//      ++time.sec;
//      time.cent = 0;

//      if (time.sec >= 60) {
//          ++time.min;
//          time.sec = 0;

//          if (time.min >= 60) {
//              ++time.hour;
//              time.min = 0;
//          }
//      }
//  }
// }

#pragma interrupt
void ISR_T1() {//copied and renamed
    ++millis;
}

void hwinit() { //copied and renamed
    init_uart(_UART0, _DEFFREQ, 115200);  // set-up UART0 to 115200, 8n1
    LEDinit();
    SET_VECTOR(TIMER0, ISR_T0);
    EI();
    millis = 0;

    // keysListener();
}

// void resetTimer() {
//  time.hour = 0;
//  time.min = 0;
//  time.sec = 0;
//  time.cent = 0;
//  initTimer();
// }

// Time getTime() {
//  Time t;
//  DI();
//  t = time;
//  EI();
//  return t;
// }

// Key input handling

char readkey() {    // Returns state of push buttons on bit 0-2 //copied and renamed
    char input = 0;
    PFDD |= 0xC0;
    PDDD |= 4;
    input |= ~PFIN >> 7 & 1;
    input |= ~PFIN >> 5 & 2;
    input |= ~PDIN >> 1 & 4;
    return input;
}

void keysListener() { //copied and renamed
    DI();

    // TEN: 0, TPOL: 0, PRES: 7 (128), TMODE: 1 (cont.)
    T1CTL = 0x39;

    // Begin timer at 0
    T1H = 0;
    T1L = 0;

    // End timer at 144, 1 kHz
    T1RH = 0x00;
    T1RL = 0x90;

    // Enable TIMER1 interrupt
    IRQ0 |= 0x40;

    // Set priority to HIGH
    IRQ0ENH |= 0x40;
    IRQ0ENL |= 0x40;

    // Enable TIMER1
    T1CTL |= 0x80;

    SET_VECTOR(TIMER1, ISR_T1);

    EI();
}

// Debounces input keys and returns the keys pressed since last call
char updateKeys(char *lastInput, char *lastKeys) { //copied and renamed
    char rising;
    char currentInput = readkey();
    if (millis > DEBOUNCE_INTERVAL) {
        millis = 0;
        *lastKeys = *lastInput & currentInput;
        rising = currentInput & ~*lastInput;
        *lastInput = currentInput;
        return rising;
    }
    return 0;
}

char waitForKey() { //copied and renamed
    int i;
    char oldkeys;
    char keys = readkey();
    while (1) {
        oldkeys = keys;
        keys = readkey();
        if (keys & ~oldkeys) {
            for (i = 0; i < 25000; ++i) continue;
            keys = readkey();
            if (keys & ~oldkeys) {
                return keys & ~oldkeys;
            }
        }
    }
}

void displayColumn(int val, int col, int disp) { //copied and renamed
    char clockval;

    // Set column
    PEOUT &= ~(1 << (4 - col));
    PEOUT |= ~(1 << (4 - col)) & 0x1F;

    // Set row to val
    PGOUT |= val & 0x7F;
    PGOUT &= val | 0x80;

    // Clock Display
    if (disp == 1) {
        // Clock D2
        PGOUT &= 0x7F;  // Low
        PGOUT |= 0x80;  // High
        PGOUT &= 0x7F;  // Low
    } else {
        switch (disp) {
        case 0:
            // D1
            clockval = 0x7F;
            break;
        case 2:
            // D3
            clockval = 0xDF;
            break;
        default:
            // D4
            clockval = 0xBF;
            break;
        }
        PEOUT &= clockval;  // Low
        PEOUT |= ~clockval; // High
        PEOUT &= clockval;  // Low
    }
}

void LEDinit() { //copied and renamed
    //Set direction to out
    PEDD = 0x00;
    PGDD = 0x00;

    // TEN: 0, TPOL: 0, PRES: 0 (1), TMODE: 1 (cont.)
    T0CTL = 0x01;
    //T0CTL = 0x39;

    // Begin timer at 0
    T0H = 0;
    T0L = 0;

    // End timer at 1843 (1 kHz)
    T0RH = 0x48;
    T0RL = 0x00;
    //T0RH = 0xFF;
    //T0RL = 0xFF;

    // Enable TIMER0 interrupt
    IRQ0 |= 0x20;

    // Set priority to LOW
    IRQ0ENH &= ~0x20;
    IRQ0ENL |= 0x20;

    // Enable timer0
    T0CTL |= 0x80;

    // Set update flag to 0
    _LEDinterrupt = 0;
    _display_column = 0;
    _scroll_index = 0;
    _scroll_count = 0;
}

void ROMtoRAM(char *dest, rom char *src) { //copied and renamed
    while (*src) *dest++ = *src++;
    *dest = '\0';
}

void updateVideoBuffer() {//copied and renamed
    int i, j;
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            _video_buffer[i][j] = character_data[_LEDtext[_text_index + i] - 0x20][j];
        }
    }
}

void LEDsetString(char *str) {//copied and renamed
    int i;
    for (i = 0; i < util_strlen(str) + 8; ++i) {
        // Copy string, padding with 4 spaces
        _LEDtext[i] = i < 4 || i >= util_strlen(str) + 4 ? ' ' : str[i - 4];
    }
    _LEDtext[util_strlen(str) + 8] = '\0';
}

void LEDupdate() { //copied and renamed
    int i;
    if (_LEDinterrupt) {
        _LEDinterrupt = 0;
        for (i = 0; i < 4; ++i) {
            displayColumn((int) * (&_video_buffer[i][0] + _display_column + _scroll_index), (int) _display_column, i);
        }

        // Change column
        _display_column == 4 ? _display_column = 0 : ++_display_column;

        if (_scroll_count >= SCROLL_INTERVAL) {
            if (_scroll_index >= 5) {
                _scroll_index = 0;
                _text_index >= util_strlen(_LEDtext) - 5 ? _text_index = 0 : ++_text_index;
                updateVideoBuffer();
            }
            ++_scroll_index;
            _scroll_count = 0;
        }
    }
}

// void initTimer() {
//  // TEN: 0, TPOL: 0, PRES: 7 (128), TMODE: 1 (cont.)
//  T0CTL = 0x39;

//  // Begin timer at 0
//  T0H = 0;
//  T0L = 0;

//  // End timer at 1440, 100 Hz
//  T0RH = 0x05;
//  T0RL = 0xA0;

//  // Enable TIMER0 interrupt
//  IRQ0 |= 0x20;

//  // Set priority to HIGH
//  IRQ0ENH |= 0x20;
//  IRQ0ENL |= 0x20;
// }

// void stopTimer() {
//  // Disable timer0
//  T0CTL &= 0x7F;
// }

// void startTimer() {
//  // Enable timer0
//  T0CTL |= 0x80;
// }
