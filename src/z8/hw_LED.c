// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015
#ifndef __WIN32__
#ifndef __APPLE__

#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "charset.h"
#include "util.h"
#include "hw_time.h"
#include "hw_LED.h"


#define SCROLL_INTERVAL 30  // ms between change
#define LED_MAX_STR_LEN 128
#define LED_REFRESH_RATE 1 // 1st bit of millis, 1 kHz.

char _video_buffer[5][6];
char _LEDtext[LED_MAX_STR_LEN];
char _display_column, _scroll_index, _scroll_count, _text_index;

void LED_init() {
// 'resets' the LED displays.

	//Set data direction
	PEDD = 0x00;
	PGDD = 0x00;

	_display_column = 0;
	_scroll_index = 0;
	_scroll_count = 0;
}

void LED_display_column(int val, int col, int disp) {
	char clockval; //LED display clock

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

void LED_update_video_buffer() {
	int i, j;
	for (i = 0; i < 5; ++i) {
		for (j = 0; j < 5; ++j) {
			_video_buffer[i][j] = character_data[_LEDtext[_text_index + i] - 0x20][j];
		}
	}
}

void LED_set_string(char *str) {
	int i;
	for (i = 0; i < util_strlen(str) + 8; ++i) {
		// Copy string, padding with 4 spaces
		_LEDtext[i] = i < 4 || i >= util_strlen(str) + 4 ? ' ' : str[i - 4];
	}
	_LEDtext[util_strlen(str) + 8] = '\0';
}

void LED_update() {
	int i;
	if (hw_time_get_LEDflag()) {
		hw_time_set_LEDflag(0);
		++_scroll_count;
		for (i = 0; i < 4; ++i) {
			LED_display_column((int) * (&_video_buffer[i][0] + _display_column + _scroll_index), (int) _display_column, i);
		}

		// Change column
		_display_column == 4 ? _display_column = 0 : ++_display_column;

		if (_scroll_count >= SCROLL_INTERVAL) {
			if (_scroll_index >= 5) {
				_scroll_index = 0;
				_text_index >= util_strlen(_LEDtext) - 5 ? _text_index = 0 : ++_text_index;
				LED_update_video_buffer();
			}
			++_scroll_index;
			_scroll_count = 0;
		}
	}
}

#endif
#endif

#ifdef __WIN32__
void LED_init();

void LED_display_column(int val, int col, int disp);

void LED_update_video_buffer();

void LED_set_string(char *str);

void LED_update();
#endif

#ifdef __APPLE__
void LED_init();

void LED_display_column(int val, int col, int disp);

void LED_update_video_buffer();

void LED_set_string(char *str);

void LED_update();
#endif