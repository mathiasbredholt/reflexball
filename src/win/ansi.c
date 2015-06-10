// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <stdio.h>
#include "ansi.h"
#include "util.h"

#define ESC 0x1B

void fgcolor(int foreground) {
  /*  Value      foreground     Value     foreground
      ------------------------------------------------
        0        Black            8       Dark Gray
        1        Red              9       Light Red
        2        Green           10       Light Green
        3        Brown           11       Yellow
        4        Blue            12       Light Blue
        5        Purple          13       Light Purple
        6        Cyan            14       Light Cyan
        7        Light Gray      15       White
  */
  int type = 22;             // normal text
  if (foreground > 7) {
    type = 1;                // bold text
    foreground -= 8;
  }
  printf("%c[%d;%dm", ESC, type, foreground + 30);
}

void bgcolor(int background) {
  /* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
     Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                  The designers of HyperTerminal, however, preferred black text on white background, which is why
                  the colors are initially like that, but when the background color is first changed there is no
                  way comming back.
     Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

      Value      Color
      ------------------
        0        Black
        1        Red
        2        Green
        3        Brown
        4        Blue
        5        Purple
        6        Cyan
        7        Gray
  */
  printf("%c[%dm", ESC, background + 40);
}

void color(int foreground, int background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  int type = 22;             // normal text
  if (foreground > 7) {
    type = 1;                // bold text
    foreground -= 8;
  }
  printf("%c[%d;%d;%dm", ESC, type, foreground + 30, background + 40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr() {
  printf("%c[2j", ESC);
}

void hidecsr() {
  printf("%c[?25l", ESC);
}

void clreol() {
  printf("%c[K", ESC);
}

void gotoxy(int x, int y) {
  printf("%c[%d;%df", ESC, y + 1, x + 1);
}

void underline(char on) {
  printf("%c[%dm", ESC, on != 0 ? 4 : 24);
}

void blink(char on) {
  printf("%c[%dm", ESC, on != 0 ? 5 : 25);
}

void reverse(char on) {
  printf("%c[%dm", ESC, on != 0 ? 7 : 27);
}

void up(int n) {
  printf("%c[%dA", ESC, n);
}
void down(int n) {
  printf("%c[%dB", ESC, n);
}

void right(int n) {
  printf("%c[%dC", ESC, n);
}

void left(int n) {
  printf("%c[%dD", ESC, n);
}

void spacer(int n, int c) {
  int i;
  for (i = 0; i < n; i++) printf("%c", (char) c);
}

void window(int x1, int y1, int x2, int y2, char *title) {
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
