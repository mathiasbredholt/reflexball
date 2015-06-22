#if defined(__APPLE__) || defined(__WIN32__)
#include <stdio.h>
#endif

#if defined(_Z8F6403)
#include <sio.h>
#endif

#include "graphics.h"
#include "hw_input.h"
// #include "lore.h"
// #include "charset.h"

void intro_play() {
	gfx_window(6, 4, 50, 50);
	gfx_draw_title(86, 5);
}

void intro_update(int *mode, char *lastKey) {
	char key;
	key = hw_read_key();
	if (key != *lastKey) {
		//	if (*lastKey & 4) *mode = 0;
	}
}