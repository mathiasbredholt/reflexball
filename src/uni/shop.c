#include "graphics.h"

void shop_show(char *items) {
	gfx_window(16, 16, 240, 80, 1);

	gfx_draw_text(24, 18, "welcome to my shop", 0);
	gfx_draw_text(24, 21, "what does your heart desire", 0);

	gfx_draw_button(24, 28, "buy");
}