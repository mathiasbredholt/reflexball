#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "hw_input.h"
#include "hw_time.h"

#define DEBOUNCE_INTERVAL 15  // ms

char _debounce_flag, _keys, _lastInput;

void hw_init() {
	init_uart(_UART0, _DEFFREQ, 115200);  // set-up UART0 to 115200, 8n1 bør flyttes
	_debounce_flag = 1;
}

void hw_ROM_to_RAM(char *dest, rom char *src) {
	while (*src) *dest++ = *src++;
	*dest = '\0';
}

char hw_read_key() {    // Returns state of push buttons on bit 0-2
	char input = 0;
	PFDD |= 0xC0;
	PDDD |= 4;
	input |= ~PFIN >> 7 & 1;
	input |= ~PFIN >> 5 & 2;
	input |= ~PDIN >> 1 & 4;
	return input;
}

// Debounces input keys and returns the keys pressed since last call
char hw_keys() {
	char currentInput = hw_read_key();
	if ((hw_time_millis() & DEBOUNCE_INTERVAL) == DEBOUNCE_INTERVAL) {
		if (_debounce_flag) {
			_keys = _lastInput & currentInput;
			_lastInput = currentInput;
			_debounce_flag = 0;
		}
	} else {
		_debounce_flag = 1;
	}
	return _keys;
}

char hw_wait_for_key() {
	int i;
	char oldKeys;
	_keys = hw_read_key();
	while (1) {
		oldKeys = _keys;
		_keys = hw_read_key();
		if (_keys & ~oldKeys) {
			for (i = 0; i < 25000; ++i) continue;
			_keys = hw_read_key();
			if (_keys & ~oldKeys) {
				return _keys & ~oldKeys;
			}
		}
	}
}