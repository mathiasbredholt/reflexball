// generated with http://patorjk.com/software/taag/#p=display&h=3&f=Alpha&t=Reflexball


#if defined(__APPLE__) || defined(__WIN32__)
#include <stdio.h>
#endif

#if defined(_Z8F6403)
#include <sio.h>
#endif

#include "ansi.h"
#include "hw_time.h"
#include "hw_input.h"

void intro_play() {
  // int i, index = 0;
  // string title
  // rom char title[42][8] = {
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aazxcggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aaasdggt",
  //   "aazxcggt"
  // };
//  char title[21][203];
//*title = {
// rom char title1  [] = "        _____                   _____                   _____                   _____    _____                                          _____                   _____                   _____    _____  ";
// rom char title2  [] = "         /\\    \\                 /\\    \\                 /\\    \\                 /\\    \\  /\\    \\                ______                  /\\    \\                 /\\    \\                 /\\    \\  /\\    \\ ";
// rom char title3  [] = "        /::\\    \\               /::\\    \\               /::\\    \\               /::\\____\\/::\\    \\              |::|   |                /::\\    \\               /::\\    \\               /::\\____\\/::\\____\\";
// rom char title4  [] = "       /::::\\    \\             /::::\\    \\             /::::\\    \\             /:::/    /::::\\    \\             |::|   |               /::::\\    \\             /::::\\    \\             /:::/    /:::/    /";
// rom char title5  [] = "      /::::::\\    \\           /::::::\\    \\           /::::::\\    \\           /:::/    /::::::\\    \\            |::|   |              /::::::\\    \\           /::::::\\    \\           /:::/    /:::/    / ";
// rom char title6  [] = "     /:::/\\:::\\    \\         /:::/\\:::\\    \\         /:::/\\:::\\    \\         /:::/    /:::/\\:::\\    \\           |::|   |             /:::/\\:::\\    \\         /:::/\\:::\\    \\         /:::/    /:::/    /  ";
// rom char title7  [] = "    /:::/__\\:::\\    \\       /:::/__\\:::\\    \\       /:::/__\\:::\\    \\       /:::/    /:::/__\\:::\\    \\          |::|   |            /:::/__\\:::\\    \\       /:::/__\\:::\\    \\       /:::/    /:::/    /   ";
// rom char title8  [] = "   /::::\\   \\:::\\    \\     /::::\\   \\:::\\    \\     /::::\\   \\:::\\    \\     /:::/    /::::\\   \\:::\\    \\         |::|   |           /::::\\   \\:::\\    \\     /::::\\   \\:::\\    \\     /:::/    /:::/    /    ";
// rom char title9  [] = "  /::::::\\   \\:::\\    \\   /::::::\\   \\:::\\    \\   /::::::\\   \\:::\\    \\   /:::/    /::::::\\   \\:::\\    \\        |::|   |          /::::::\\   \\:::\\    \\   /::::::\\   \\:::\\    \\   /:::/    /:::/    /     ";
// rom char title10 [] = " /:::/\\:::\\   \\:::\\____\\ /:::/\\:::\\   \\:::\\    \\ /:::/\\:::\\   \\:::\\    \\ /:::/    /:::/\\:::\\   \\:::\\    \\ ______|::|___|___ ____ /:::/\\:::\\   \\:::\\ ___\\ /:::/\\:::\\   \\:::\\    \\ /:::/    /:::/    /      ";
// rom char title11 [] = " /:::/  \\:::\\   \\:::|    /:::/__\\:::\\   \\:::\\____/:::/  \\:::\\   \\:::\\____/:::/____/:::/__\\:::\\   \\:::\\____|:::::::::::::::::|    /:::/__\\:::\\   \\:::|    /:::/  \\:::\\   \\:::\\____/:::/____/:::/____/       ";
// rom char title12 [] = " \\::/   |::::\\  /:::|____\\:::\\   \\:::\\   \\::/    \\::/    \\:::\\   \\::/    \\:::\\    \\:::\\   \\:::\\   \\::/    |:::::::::::::::::|____\\:::\\   \\:::\\  /:::|____\\::/    \\:::\\  /:::/    \\:::\\    \\:::\\    \\       ";
// rom char title13 [] = " \\/____|:::::\\/:::/    / \\:::\\   \\:::\\   \\/____/ \\/____/ \\:::\\   \\/____/ \\:::\\    \\:::\\   \\:::\\   \\/____/ ~~~~~~|::|~~~|~~~      \\:::\\   \\:::\\/:::/    / \\/____/ \\:::\\/:::/    / \\:::\\    \\:::\\    \\      ";
// rom char title14 [] = "       |:::::::::/    /   \\:::\\   \\:::\\    \\              \\:::\\    \\      \\:::\\    \\:::\\   \\:::\\    \\           |::|   |          \\:::\\   \\::::::/    /           \\::::::/    /   \\:::\\    \\:::\\    \\     ";
// rom char title15 [] = "       |::|\\::::/    /     \\:::\\   \\:::\\____\\              \\:::\\____\\      \\:::\\    \\:::\\   \\:::\\____\\          |::|   |           \\:::\\   \\::::/    /             \\::::/    /     \\:::\\    \\:::\\    \\    ";
// rom char title16 [] = "       |::| \\::/____/       \\:::\\   \\::/    /               \\::/    /       \\:::\\    \\:::\\   \\::/    /          |::|   |            \\:::\\  /:::/    /              /:::/    /       \\:::\\    \\:::\\    \\   ";
// rom char title17 [] = "       |::|  ~|              \\:::\\   \\/____/                 \\/____/         \\:::\\    \\:::\\   \\/____/           |::|   |             \\:::\\/:::/    /              /:::/    /         \\:::\\    \\:::\\    \\  ";
// rom char title18 [] = "       |::|   |               \\:::\\    \\                                      \\:::\\    \\:::\\    \\               |::|   |              \\::::::/    /              /:::/    /           \\:::\\    \\:::\\    \\ ";
// rom char title19 [] = "       \\::|   |                \\:::\\____\\                                      \\:::\\____\\:::\\____\\              |::|   |               \\::::/    /              /:::/    /             \\:::\\____\\:::\\____\\";
// rom char title20 [] = "        \\:|   |                 \\::/    /                                       \\::/    /\\::/    /              |::|___|                \\::/____/               \\::/    /               \\::/    /\\::/    /";
// rom char title21 [] = "         \\|___|                  \\/____/                                         \\/____/  \\/____/                ~~                      ~~                      \\/____/                 \\/____/  \\/____/ ";

//
  hide_csr();
//
//  while (index < 203) {
//    if (hw_time_get_next_frame()) {
//      hw_time_set_next_frame(0);
//
//      for (i = 0; i < 21; ++i) {
//        go_to_xy(26 + index, 38 + i);
//        printf("%c", title[i][index]);
//        printf("%c", title[i][index + 1]);
//        printf("%c", title[i][index + 2]);
//        printf("%c", title[i][index + 3]);
//      }
//
//      index += 4;
//
//
#ifdef GCC
  fflush(stdout);
#endif
//    }
//  }
}