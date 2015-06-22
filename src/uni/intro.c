#if defined(_Z8F6403)
#include <sio.h>
#else
#include <stdio.h>
#endif

#include "graphics.h"
#include "hw_input.h"
#include "lore.h"
// #include "charset.h"

void intro_play() {
	gfx_window(6, 16, 75, 90);
	gfx_draw_title(47, 3);
	gfx_draw_text(9, 7, 17, lore[43]);
}

void intro_update(int *mode, char *lastKey) {
	char key;
	key = hw_read_key();
	if (key != *lastKey) {
		//  if (*lastKey & 4) *mode = 0;
	}
}