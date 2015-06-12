#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "hw_input.h"
#include "hw_time.h"

#define DEBOUNCE_INTERVAL 15  // ms

char debounce_flag;

void HW_init() {
	init_uart(_UART0, _DEFFREQ, 115200);  // set-up UART0 to 115200, 8n1 bør flyttes
	debounce_flag = 1;
}

void HW_ROMtoRAM(char *dest, rom char *src) {
	while (*src) *dest++ = *src++;
	*dest = '\0';
}

char HW_readkey() {    // Returns state of push buttons on bit 0-2
	char input = 0;
	PFDD |= 0xC0;
	PDDD |= 4;
	input |= ~PFIN >> 7 & 1;
	input |= ~PFIN >> 5 & 2;
	input |= ~PDIN >> 1 & 4;
	return input;
}

// Debounces input keys and returns the keys pressed since last call
char HW_updateKeys(char *lastInput, char *lastKeys) {
	char rising;
	char currentInput = HW_readkey();
	if (hw_time_millis() & DEBOUNCE_INTERVAL == DEBOUNCE_INTERVAL) {
		if (debounce_flag) {
			*lastKeys = *lastInput & currentInput;
			rising = currentInput & ~*lastInput;
			*lastInput = currentInput;
			debounce_flag = 0;
			return rising;
		}
	} else {
		debounce_flag = 1;
	}
	return 0;
}

char HW_waitForKey() {
	int i;
	char oldKeys;
	char keys = HW_readkey();
	while (1) {
		oldKeys = keys;
		keys = HW_readkey();
		if (keys & ~oldKeys) {
			for (i = 0; i < 25000; ++i) continue;
			keys = HW_readkey();
			if (keys & ~oldKeys) {
				return keys & ~oldKeys;
			}
		}
	}
}