#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "hw_input.h"
#include "charset.h"
#include "util.h"

#define DEBOUNCE_INTERVAL 10  // ms

unsigned long millis;

#pragma interrupt
void ISR_T1() {
	++millis;
}

void HW_init() {
	init_uart(_UART0, _DEFFREQ, 115200);  // set-up UART0 to 115200, 8n1
	SET_VECTOR(TIMER0, ISR_T0);
	EI();
	millis = 0;
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

void HW_keysListener() {
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
char HW_updateKeys(char *lastInput, char *lastKeys) {
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

char HW_waitForKey() {
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