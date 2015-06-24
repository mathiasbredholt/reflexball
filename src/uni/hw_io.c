/*
 #  #     #    ###    ###    #   #    #    ###    ####          ###    #  #   ###    #  #   #####
 #  #    # #   #  #   #  #   #   #   # #   #  #   #              #     ## #   #  #   #  #     #
 ####   #   #  #  #   #  #   # # #  #   #  #  #   ###            #     # ##   #  #   #  #     #
 #  #   #####  ###    #  #   # # #  #####  ###    #              #     #  #   ###    #  #     #
 #  #   #   #  #  #   #  #   ## ##  #   #  #  #   #              #     #  #   #      #  #     #
 #  #   #   #  #  #   ###    #   #  #   #  #  #   ####          ###    #  #   #       ##      #
*/

#ifdef __WIN32__
#define GCC
#include <conio.h>
#include <stdio.h>
void hw_init() {}
#endif

#ifdef __APPLE__
#define GCC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

struct termios orig_termios;	// Used for emulating the way buttons work on the board

void reset_terminal_mode()
{
	tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
	struct termios new_termios;

	/* take two copies - one for now, one for later */
	tcgetattr(0, &orig_termios);
	memcpy(&new_termios, &orig_termios, sizeof(new_termios));

	/* register cleanup handler, and set the new terminal mode */
	atexit(reset_terminal_mode);
	cfmakeraw(&new_termios);
	tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
	struct timeval tv = { 0L, 0L };
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	return select(1, &fds, NULL, NULL, &tv);
}

int getch()
{
	int r;
	unsigned char c;
	if ((r = read(0, &c, sizeof(c))) < 0) {
		return r;
	} else {
		return c;
	}
}

void hw_init() {
	set_conio_terminal_mode();
}
#endif

#if defined(_Z8F6403)

// hw_input.c

#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "hw_io.h"
#include "hw_time.h"

#define DEBOUNCE_INTERVAL 15  // ms

// Global variables used for debouncing to avoid having to pass pointers to placeholders for hardware specific variables all the way from main
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
	PHDD |= 0x0F;
	PDDD |= 4;
	input |= PHIN & 0xF;
	input |= ~PFIN >> 3 & 0x10;
	input |= ~PFIN & 0x20;
	input |= ~PDIN << 3 & 0x40;
	return input;
}

// Debounces input keys and returns the keys pressed
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

void hw_ADC_init() {
	PBADDR = 0x02; // selects the alternate function of the B register
	PBAF = 0x01; // Enables alternate function for inputs 0-7.
	ADCCTL = 0x90; // initates the ADC, for continous conversion of input 0.
	while (!(ADCCTL & 0x80)); // waits for the output to be ready
}

unsigned char hw_read_analog() {
	return ADCD_H;
}

#endif

#ifdef GCC

// void hw_ROM_to_RAM(char *dest, rom char *src) {}

char hw_read_key() {    // Returns state of push buttons on bit 0-2
	char input = 0;
	if (kbhit()) {	// A key is pressed
		//if (getch() == 224) { // if the first value is esc
		switch (getch()) { // the real value
		case 97:
			// arrow left
			input = 2;
			break;
		case 100:
			// arrow right
			input = 1;
			break;
		//} else {
		// Any other key is 3rd key
		//	input = 4;
		//}
		default:
			input = 4;
			break;
		}
	}
	return input;
}

// Debounces input keys and returns the keys pressed since last call
char hw_keys() {
	return hw_read_key();
}

char hw_wait_for_key() {
	while (hw_read_key() == 0);
	return hw_read_key();
}

void hw_ADC_init() {
}

unsigned char hw_read_analog() {
	return 175;
}

void hw_ROM_to_RAM(char *dest, const char *src) {
	while (*src) *dest++ = *src++;
	*dest = '\0';
}


#endif