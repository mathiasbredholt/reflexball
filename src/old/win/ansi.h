// Copyright Daniel Mouritzen, Niels Bang and Mathias Bredholt 2015

#include <stdio.h>

#ifndef _ANSI_H_
#define _ANSI_H_

#define ESC 0x1B

void fg_color(int foreground);

void bg_color(int background);

void color(int foreground, int background);

void reset_bg_color();

void clr_scr();

void hide_scr();

void clear_eol();

void go_to_xy(int x, int y);

void underline(char on);

void blink(char on);

void reverse(char on);

void up(int n);

void down(int n);

void right(int n);

void left(int n);

void spacer(int n, int c);

#endif