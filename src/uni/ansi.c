/*
   #    #  #    ##    ###
  # #   ## #   #  #    #
 #   #  # ##    #      #
 #####  #  #     #     #
 #   #  #  #   #  #    #
 #   #  #  #    ##    ###
 */

#include <stdio.h>
#include "ansi.h"

#define ESC 0x1B

// Set foreground color
void fg_color(int foreground) {
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

// Set background color
void bg_color(int background) {
  /*Value      Color
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

// combination of fg_color() and bg_color() - uses less bandwidth
void color(int foreground, int background) {
  int type = 22;             // normal text
  if (foreground > 7) {
    type = 1;                // bold text
    foreground -= 8;
  }
  printf("%c[%d;%d;%dm", ESC, type, foreground + 30, background + 40);
}

// gray on black text, no underline, no blink, no reverse
void reset_bg_color() {
  printf("%c[m", ESC);
}

// Clear screen
void clr_scr() {
  reset_bg_color();
  printf("%c[2J", ESC);
}

// Hides cursor
void hide_csr() {
  printf("%c[?25l", ESC);
}

// Clears to end of line
void clear_eol() {
  printf("%c[K", ESC);
}

// Moves cursor to coordinates
void go_to_xy(int x, int y) {
  printf("%c[%d;%df", ESC, y + 2, x + 2); //Ignore frame
}

// Set bold face on/off
void bold(char on) {
  printf("%c[%dm", ESC, on != 0 ? 1 : 21);
}

// Set cursor blink on/off
void blink(char on) {
  printf("%c[%dm", ESC, on != 0 ? 5 : 25);
}

// Reverse foreground and background color
void reverse(char on) {
  printf("%c[%dm", ESC, on != 0 ? 7 : 27);
}

// Functions to move cursor n positions
void go_horiz(int n) {
  if (n > 0) {
    go_right(n);
  } else if (n < 0) {
    go_left(-n);
  }
}

void go_vert(int n) {
  if (n > 0) {
    go_down(n);
  } else if (n < 0) {
    go_up(-n);
  }
}

void go_up(int n) {
  printf("%c[%dA", ESC, n);
}
void go_down(int n) {
  printf("%c[%dB", ESC, n);
}

void go_right(int n) {
  printf("%c[%dC", ESC, n);
}

void go_left(int n) {
  printf("%c[%dD", ESC, n);
}

void ansi_save() {
  printf("%c[s", ESC);
}

void ansi_load() {
  printf("%c[u", ESC);
}

// Prints the char, corresponding to c, n times. Uses int instead of char because of compiler bug when passing char as argument.
void spacer(int n, int c) {
  int i;
  char str[259];
  for (i = 0; i < n; i++) printf("%c", (char) c);

}