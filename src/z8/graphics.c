#include <sio.h>
#include "ansi.h"
#include "util.h"
#include "graphics.h"

void gfx_window(int x1, int y1, int x2, int y2, char *title) {
	int w = x2 - x1;
	int h = y2 - y1;
	int padding = w - util_strlen(title) - 8;
	int i;

	if (padding < 0) {
		title[util_strlen(title) + padding] = '\0';
	}

	reverse(0);
	gotoxy(x1, y1);

	// print top line
	printf("%c", 201);  // corner
	spacer(padding / 2, 205);  // padding
	printf("%c", 185);  // title start
	reverse(1);
	printf("  %s  ", title);
	reverse(0);
	printf("%c", 204);  // title end
	spacer((padding + 1) / 2, 205);  // padding
	printf("%c", 187);  // corner

	// print sides
	for (i = 1; i < h - 1; i++) {
		gotoxy(x1, y1 + i);
		printf("%c", 186);
		gotoxy(x2 - 1, y1 + i);
		printf("%c", 186);
	}

	// print bottom line
	gotoxy(x1, y2 - 1);
	printf("%c", 200);  // corner
	spacer(w - 2, 205);
	printf("%c", 188);  // corner
}
