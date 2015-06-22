#if defined(_Z8F6403)
#include <sio.h>
#else
#include <stdio.h>
#endif

#include "graphics.h"
#include "hw_input.h"
#include "story.h"
#include "charset.h"

void intro_play() {
	int i;
	gfx_window(1, 5, 16, 119, 101);
	gfx_draw_title(47, 3);
	// story info, window to the left
	for (i = 1; i < 24; ++i)
	{
		gfx_draw_text(9, 7 , 14 + i * 3, story[40 + i]);
	}
	// Meta info,
	gfx_window(0, 139, 16, 252, 101);
//	for (int i = 0; i < count; ++i)
//	{
//	}
}

void intro_update(int *mode, char *lastKey) {
	char key;
	key = hw_read_key();
	if (key != *lastKey) {
		//  if (*lastKey & 4) *mode = 0;
	}
}