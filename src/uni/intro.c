#if defined(_Z8F6403)
#include <sio.h>
#else
#include <stdio.h>
#endif

#include "graphics.h"
#include "hw_input.h"
#include "charset.h"

void intro_play() {
	int i;
	gfx_window(1, 5, 16, 119, 101);
	gfx_draw_title(47, 3);
	// story info, window to the left

	gfx_draw_text(9, 8 , 14, "welcome to the glorious");
	gfx_draw_text(9, 8, 14 + 3, "tale of commander boss");
	gfx_draw_text(9, 8, 14 + 6, "a grand adventurer");
	gfx_draw_text(9, 8, 14 + 9, "pilot of the striker");
	gfx_draw_text(9, 8, 14 + 12, "a ship capable of bouncing");
	gfx_draw_text(9, 8, 14 + 15, "balls made of pure energy");
	gfx_draw_text(9, 8, 14 + 18, "a ship that supports the ");
	gfx_draw_text(9, 8, 14 + 21, "most advanced weaponry");
	gfx_draw_text(9, 8, 14 + 24, "");


	// Meta info,
	gfx_window(0, 139, 16, 252, 101);

	gfx_draw_text(9, 143, 14 + i * 3, "still testing");

}

void intro_update(int *mode, char *lastKey) {
	char key;
	key = hw_read_key();
	if (key != *lastKey) {
		if (key != 0) *mode = 0;
	}
}