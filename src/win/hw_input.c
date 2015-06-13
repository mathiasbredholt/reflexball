// EDITED FOR USE IN WINDOWS

#include <conio.h> // Provides getch() and kbhit()
#include <stdio.h>

void hw_init() {}

// void hw_ROM_to_RAM(char *dest, rom char *src) {}

char hw_read_key() {    // Returns state of push buttons on bit 0-2
	char input = 0;
	if (kbhit()) {	// A key is pressed
		if (getch() == 224) { // if the first value is esc
			switch (getch()) { // the real value
			case 75:
				// arrow left
				input = 2;
				break;
			case 77:
				// arrow right
				input = 1;
				break;
			}
		} else {
			// Any other key is 3rd key
			input = 4;
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