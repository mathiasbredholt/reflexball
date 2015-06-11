// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "hw_LED.h"
#include "charset.h"
#include "util.h"


#define SCROLL_INTERVAL 30  // ms between change
#define LED_MAX_STR_LEN 128

char _video_buffer[5][6];
char _LEDtext[LED_MAX_STR_LEN];
char _display_column, _scroll_index, _scroll_count, _text_index, _LEDinterrupt;


#pragma interrupt
void ISR_T0() {
	_LEDinterrupt = 1;
	++_scroll_count;
	// printf("%d\n", (int) _display_column);
}

void LED_init() {

	//initializes the use of the LED screens as well as sets up the 1 kHz timer for the screens and enables interrupts.

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

	SET_VECTOR(TIMER0, ISR_T0);
	EI();
}

void LED_displaycolumn(int val, int col, int disp) {
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

void LED_updateVideoBuffer() {
	int i, j;
	for (i = 0; i < 5; ++i) {
		for (j = 0; j < 5; ++j) {
			_video_buffer[i][j] = character_data[_LEDtext[_text_index + i] - 0x20][j];
		}
	}
}

void LED_setString(char *str) {
	int i;
	for (i = 0; i < util_strlen(str) + 8; ++i) {
		// Copy string, padding with 4 spaces
		_LEDtext[i] = i < 4 || i >= util_strlen(str) + 4 ? ' ' : str[i - 4];
	}
	_LEDtext[util_strlen(str) + 8] = '\0';
}

void LED_update() {
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