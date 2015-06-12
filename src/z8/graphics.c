#include <sio.h>
#include "ansi.h"
#include "util.h"
#include "graphics.h"

#define width 256
#define height 96
#define striker_height 92

void gfx_draw_bounds() {
	int i;

	hidecsr();
	
	gotoxy(0, 0);
	printf("%c", 201);  // top left corner
	spacer(width - 2, 205); // top line
	printf("%c", 187);

	// print sides
	for (i = 1; i < height - 1; i++) {
		gotoxy(0, i);
		printf("%c", 186);
		gotoxy(255, i);
		printf("%c", 186);
	}
}

void gfx_draw_ball(int oldX, int oldY, int newX, int newY) 	{
	// Erase old ball
	gotoxy(oldX, oldY);
	printf("  ");

	// Draw new ball
	gotoxy(newX, newY);
	printf("%c%c", 219, 219);
}

void gfx_draw_striker(int oldX, int newX) 	{
	gotoxy(oldX - 3, striker_height);
	spacer(8, (int) ' ');
	gotoxy(newX - 3, striker_height);
	printf("%c", 204);
	spacer(6, 205);
	printf("%c", 185);
}

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
