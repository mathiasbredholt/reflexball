#include "graphics.h"
#include "hw_time.h"
#include "hw_input.h"

// OBS - SKAL FLYTTES
char menuButtons[4][12] = { "play", "load game", "exit" };

void menu_show() {
	// Call drawing functions for GUI creation
	gfx_window(64, 16, 192, 80);
	gfx_draw_text(68, 18, "reflexball");

	gfx_draw_btn(108, 24, menuButtons[0], 1);
	gfx_draw_btn(108, 32, menuButtons[1], 0);
	gfx_draw_btn(108, 40, menuButtons[2], 0);
}

void menu_update(int *mode, char *lastKey, int *focus, int *animFrame1, int *animFrame2) {
	char key;

	// Wait for frame interrupt flag
	if (hw_time_get_next_frame()) {
		hw_time_set_next_frame(0);

		// Get current key reading
		key = hw_read_key();

		// If key is rising edge
		if (key != *lastKey) {
			*lastKey = key;

			// Select key is pressed
			if (*lastKey & 4) {
				*mode = *focus + 1;
				*focus = 0;
			}

			// Blur button currently in focus
			gfx_draw_btn_focus(108, 24 + 8 * *focus, menuButtons[*focus], 0);

			// If left or right key is pressed increment or decrement focus index
			if (*lastKey & 0x02) --(*focus);
			if (*lastKey & 0x01) ++(*focus);

			// Apply modulus to focus index to make sure it stays in range
			*focus %= 3;
			if (*focus < 0) *focus += 3;

			// Focus button at the new focus index
			gfx_draw_btn_focus(108, 24 + 8 * *focus, menuButtons[*focus], 1);
		}

		// Update background animation
		gfx_draw_stars(*animFrame1);
		gfx_draw_stars(*animFrame2);
		++*animFrame1;
		++*animFrame2;
		*animFrame1 %= 208;
		*animFrame2 %= 208;
	}
}
