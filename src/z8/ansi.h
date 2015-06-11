// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <sio.h>

#ifndef _ANSI_H_
#define _ANSI_H_

#define ESC 0x1B

void fgcolor(int foreground);

void bgcolor(int background);

void color(int foreground, int background);

void resetbgcolor();

void clrscr();

void hidecsr();

void clreol();

void gotoxy(int x, int y);

void underline(char on);

void blink(char on);

void reverse(char on);

void up(int n);

void down(int n);

void right(int n);

void left(int n);

void spacer(int n, int c);

#endif