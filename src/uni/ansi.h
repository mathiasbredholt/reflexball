#ifndef _ANSI_H_
#define _ANSI_H_

#define ESC 0x1B

void fg_color(int foreground);

void bg_color(int background);

void color(int foreground, int background);

void reset_bg_color();

void clr_scr();

void hide_csr();

void clear_eol();

void go_to_xy(int x, int y);

void bold(char on);

void blink(char on);

void reverse(char on);

void go_up(int n);

void go_down(int n);

void go_right(int n);

void go_left(int n);

void spacer(int n, int c);

void ansi_save();

void ansi_load();

#endif