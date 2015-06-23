#if defined(_Z8F6403)
#include <sio.h>
#else
#include <stdio.h>
#endif

#include "graphics.h"
#include "hw_input.h"
#include "charset.h"

void intro_play() {
	int y;
	gfx_window(1, 5, 16 + 22, 119 , 101 - 12);
	gfx_window(0, 139, 16 + 22, 252 , 101 - 12);
	gfx_draw_title(47, 3 + 22);
// story info, window to the left

	y = 39;
	gfx_draw_text(9, 8 , y, "welcome to the glorious");
	gfx_draw_text(9, 8, y + 3, "tale of commander boss");
	gfx_draw_text(9, 8, y + 6, "a grand adventurer");
	gfx_draw_text(9, 8, y + 9, "pilot of the striker");
	gfx_draw_text(9, 8, y + 12, "a ship capable of bouncing");
	gfx_draw_text(9, 8, y + 15, "balls made of pure energy");
	gfx_draw_text(9, 8, y + 18, "a ship that supports the ");
	gfx_draw_text(9, 8, y + 21, "most advanced weaponry");
	gfx_draw_text(9, 8, y + 24, "in the universe");
	gfx_draw_text(9, 8, y + 27, "if you can pay");
	gfx_draw_text(9, 8, y + 33, "unfortunately");
	gfx_draw_text(9, 9, y + 36, "you are dirt poor");
	gfx_draw_text(9, 9, y + 39, "better go mining and hope");
	gfx_draw_text(9, 9, y + 42, "for some treasure");

	gfx_draw_text(9, 9, y + 45, "theres gold in them blocks");

// Meta info,
#if defined(_Z8F6403)
	gfx_draw_text(9, 143, y, "use the command stick");
#else
	gfx_draw_text(9, 143, y, "use a and d");
#endif

	gfx_draw_text(9, 143, y + 3, "to control the striker");
	gfx_draw_text(9, 143, y + 6, "to navigate the menus");
#if defined(_Z8F6403)
	gfx_draw_text(9, 143, y + 9, "use the buttons");
#else
	gfx_draw_text(9, 143, y + 9, "use a and d");
#endif
	gfx_draw_text(9, 143, y + 12, "buy upgrades for the");
	gfx_draw_text(9, 143, y + 15, "weapons and the striker");
	gfx_draw_text(9, 143, y + 18, "in the shop");
	gfx_draw_text(9, 143, y + 24, "be careful you dont");
	gfx_draw_text(9, 143, y + 27, "run out of energy");
	gfx_draw_text(9, 143, y + 33, "good luck");
	gfx_draw_text(9, 143, y + 39, "press any key to continue");
}

void intro_update(int *mode, char *lastKey) {
	char key;
	key = hw_read_key();
	if (key != *lastKey) {
		if (key != 0) *mode = 0;
	}
}