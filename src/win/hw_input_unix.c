// EDITED FOR USE IN WINDOWS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

struct termios orig_termios;

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