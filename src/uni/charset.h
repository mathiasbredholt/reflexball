
/*** Supported ASCII characters ***

ASCII CHAR  ASCII CHAR  ASCII CHAR  ASCII CHAR  ASCII CHAR  ASCII CHAR
 0x20        0x30  0     0x40  @     0x50  P     0x60  `     0x70  p
 0x21  !     0x31  1     0x41  A     0x51  Q     0x61  a     0x71  q
 0x22  "     0x32  2     0x42  B     0x52  R     0x62  b     0x72  r
 0x23  #     0x33  3     0x43  C     0x53  S     0x63  c     0x73  s
 0x24  $     0x34  4     0x44  D     0x54  T     0x64  d     0x74  t
 0x25  %     0x35  5     0x45  E     0x55  U     0x65  e     0x75  u
 0x26  &     0x36  6     0x46  F     0x56  V     0x66  f     0x76  v
 0x27  '     0x37  7     0x47  G     0x57  W     0x67  g     0x77  w
 0x28  (     0x38  8     0x48  H     0x58  X     0x68  h     0x78  x
 0x29  )     0x39  9     0x49  I     0x59  Y     0x69  i     0x79  y
 0x2A  *     0x3A  :     0x4A  J     0x5A  Z     0x6A  j     0x7A  z
 0x2B  +     0x3B  ;     0x4B  K     0x5B  [     0x6B  k     0x7B  {
 0x2C  ,     0x3C  <     0x4C  L     0x5C  \     0x6C  l     0x7C  |
 0x2D  -     0x3D  =     0x4D  M     0x5D  ]     0x6D  m     0x7D  }
 0x2E  .     0x3E  >     0x4E  N     0x5E  ^     0x6E  n     0x7E  ~
 0x2F  /     0x3F  ?     0x4F  O     0x5F  _     0x6F  o

Note:
1. The ASCII character 0x20 is "SPACE" or a blank.
2. The ASCII character 0x7F(DEL) is not supported by the matrix below.

*/

#ifndef _CHARSET_H_
#define _CHARSET_H_

#if defined(__APPLE__) || defined(__WIN32__)
const char character_data[95][5] =
#endif

#if defined(_Z8F6403)
  rom char character_data[95][5] =
#endif
{
  {0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x5F, 0x5F, 0x00, 0x00},
  {0x00, 0x07, 0x00, 0x07, 0x00},
  {0x14, 0x7F, 0x14, 0x7F, 0x14},
  {0x24, 0x2A, 0x7F, 0x2A, 0x12},
  {0x23, 0x13, 0x08, 0x64, 0x62},
  {0x36, 0x49, 0x55, 0x22, 0x50},
  {0x00, 0x05, 0x03, 0x00, 0x00},
  {0x00, 0x1C, 0x22, 0x41, 0x00},
  {0x00, 0x41, 0x22, 0x1C, 0x00},
  {0x14, 0x08, 0x3E, 0x08, 0x14},
  {0x08, 0x08, 0x3E, 0x08, 0x08},
  {0x00, 0x50, 0x30, 0x00, 0x00},
  {0x08, 0x08, 0x08, 0x08, 0x08},
  {0x00, 0x60, 0x60, 0x00, 0x00},
  {0x20, 0x10, 0x08, 0x04, 0x02},
  {0x3E, 0x51, 0x49, 0x45, 0x3E},
  {0x00, 0x42, 0x7F, 0x40, 0x00},
  {0x42, 0x61, 0x51, 0x49, 0x46},
  {0x22, 0x49, 0x49, 0x49, 0x36},
  {0x18, 0x14, 0x12, 0x7F, 0x10},
  {0x2F, 0x49, 0x49, 0x49, 0x31},
  {0x3E, 0x49, 0x49, 0x49, 0x32},
  {0x03, 0x01, 0x71, 0x09, 0x07},
  {0x36, 0x49, 0x49, 0x49, 0x36},
  {0x26, 0x49, 0x49, 0x49, 0x3E},
  {0x00, 0x36, 0x36, 0x00, 0x00},
  {0x00, 0x56, 0x36, 0x00, 0x00},
  {0x08, 0x14, 0x22, 0x41, 0x00},
  {0x14, 0x14, 0x14, 0x14, 0x14},
  {0x00, 0x41, 0x22, 0x14, 0x08},
  {0x02, 0x01, 0x51, 0x09, 0x06},
  {0x32, 0x49, 0x79, 0x41, 0x3E},
  {0x7C, 0x0A, 0x09, 0x0A, 0x7C},
  {0x7F, 0x49, 0x49, 0x49, 0x36},
  {0x3E, 0x41, 0x41, 0x41, 0x22},
  {0x7F, 0x41, 0x41, 0x41, 0x3E},
  {0x7F, 0x49, 0x49, 0x49, 0x41},
  {0x7F, 0x09, 0x09, 0x09, 0x01},
  {0x3E, 0x41, 0x49, 0x49, 0x7A},
  {0x7F, 0x08, 0x08, 0x08, 0x7F},
  {0x00, 0x41, 0x7F, 0x41, 0x00},
  {0x30, 0x40, 0x40, 0x40, 0x3F},
  {0x7F, 0x08, 0x14, 0x22, 0x41},
  {0x7F, 0x40, 0x40, 0x40, 0x40},
  {0x7F, 0x02, 0x0C, 0x02, 0x7F},
  {0x7F, 0x02, 0x04, 0x08, 0x7F},
  {0x3E, 0x41, 0x41, 0x41, 0x3E},
  {0x7F, 0x09, 0x09, 0x09, 0x06},
  {0x3E, 0x41, 0x51, 0x21, 0x5E},
  {0x7F, 0x09, 0x09, 0x09, 0x76},
  {0x26, 0x49, 0x49, 0x49, 0x32},
  {0x01, 0x01, 0x7F, 0x01, 0x01},
  {0x3F, 0x40, 0x40, 0x40, 0x3F},
  {0x1F, 0x20, 0x40, 0x20, 0x1F},
  {0x3F, 0x40, 0x38, 0x40, 0x3F},
  {0x63, 0x14, 0x08, 0x14, 0x63},
  {0x03, 0x04, 0x78, 0x04, 0x03},
  {0x61, 0x51, 0x49, 0x45, 0x43},
  {0x7F, 0x41, 0x41, 0x00, 0x00},
  {0x02, 0x04, 0x08, 0x10, 0x20},
  {0x00, 0x41, 0x41, 0x7F, 0x00},
  {0x04, 0x02, 0x01, 0x02, 0x04},
  {0x40, 0x40, 0x40, 0x40, 0x40},
  {0x00, 0x01, 0x02, 0x04, 0x00},
  {0x20, 0x54, 0x54, 0x54, 0x78},
  {0x7F, 0x48, 0x44, 0x44, 0x38},
  {0x38, 0x44, 0x44, 0x44, 0x20},
  {0x38, 0x44, 0x44, 0x48, 0x7F},
  {0x38, 0x54, 0x54, 0x54, 0x18},
  {0x08, 0x7E, 0x09, 0x01, 0x02},
  {0x0C, 0x52, 0x52, 0x52, 0x3E},
  {0x7F, 0x08, 0x04, 0x04, 0x78},
  {0x00, 0x44, 0x7D, 0x40, 0x00},
  {0x20, 0x40, 0x44, 0x3D, 0x00},
  {0x7F, 0x10, 0x28, 0x44, 0x00},
  {0x00, 0x41, 0x7F, 0x40, 0x00},
  {0x7C, 0x04, 0x18, 0x04, 0x78},
  {0x7C, 0x08, 0x04, 0x04, 0x78},
  {0x38, 0x44, 0x44, 0x44, 0x38},
  {0x7C, 0x14, 0x14, 0x14, 0x08},
  {0x08, 0x14, 0x14, 0x18, 0x7C},
  {0x7C, 0x08, 0x04, 0x04, 0x08},
  {0x48, 0x54, 0x54, 0x54, 0x20},
  {0x04, 0x3F, 0x44, 0x40, 0x20},
  {0x3C, 0x40, 0x40, 0x20, 0x7C},
  {0x1C, 0x20, 0x40, 0x20, 0x1C},
  {0x3C, 0x40, 0x38, 0x40, 0x3C},
  {0x44, 0x28, 0x10, 0x28, 0x44},
  {0x0C, 0x50, 0x50, 0x50, 0x3C},
  {0x44, 0x64, 0x54, 0x4C, 0x44},
  {0x00, 0x08, 0x36, 0x41, 0x00},
  {0x00, 0x00, 0x7F, 0x00, 0x00},
  {0x00, 0x41, 0x36, 0x08, 0x00},
  {0x08, 0x04, 0x08, 0x10, 0x08}
};

#if defined(_Z8F6403)
rom char font_mini[36][3][5] =
#endif

#if defined(__APPLE__) || defined(__WIN32__)
  const char font_mini[36][3][5] =
#endif

//Alphabet for 'high res'
{
  {
    "    ",
    " /\\ ",
    "/--\\"
  }, {
    " _  ",
    "|_) ",
    "|_) "
  }, {
    " _  ",
    "/   ",
    "\\_  "
  }, {
    " _  ",
    "| \\ ",
    "|_/ "
  }, {
    " _  ",
    "|_  ",
    "|_  "
  }, {
    " _  ",
    "|_  ",
    "|   "
  }, {
    " __ ",
    "/__ ",
    "\\_| "
  }, {
    "    ",
    "|_| ",
    "| | "
  }, {
    "___ ",
    " |  ",
    "_|_ "
  }, {
    "    ",
    "  | ",
    "\\_| "
  }, {
    "    ",
    "|/  ",
    "|\\  "
  }, {
    "    ",
    "|   ",
    "|_  "
  }, {
    "    ",
    "|\\/|",
    "|  |"
  }, {
    "    ",
    "|\\ |",
    "| \\|"
  }, {
    " _  ",
    "/ \\ ",
    "\\_/ "
  }, {
    " _  ",
    "|_) ",
    "|   "
  }, {
    " _  ",
    "/ \\ ",
    "\\_X "
  }, {
    " _  ",
    "|_) ",
    "| \\ "
  }, {
    " __ ",
    "(_  ",
    "__) "
  }, {
    "___ ",
    " |  ",
    " |  "
  }, {
    "    ",
    "| | ",
    "|_| "
  }, {
    "    ",
    "\\  /",
    " \\/ "
  }, {
    "    ",
    "|  |",
    "\\/\\/"
  }, {
    "    ",
    "\\/  ",
    "/\\  "
  }, {
    "    ",
    "\\_/ ",
    " |  "
  }, {
    "__  ",
    " /  ",
    "/_  "
  }, {
    " _ ",
    "/ \\",
    "\\_/"
  }, {
    "    ",
    " /| ",
    "  | "
  }, {
    " _  ",
    "  ) ",
    " /_ "
  }, {
    " _  ",
    " _) ",
    " _) "
  }, {
    "    ",
    "|_| ",
    "  | "
  }, {
    " _  ",
    "|_  ",
    " _) "
  }, {
    " _  ",
    "|_  ",
    "|_) "
  }, {
    " __ ",
    "  / ",
    " /  "
  }, {
    " _  ",
    "(_) ",
    "(_) "
  }, {
    " _  ",
    "(_| ",
    "  | "
  }
};

#if defined(_Z8F6403)
rom char items[8][9][17] =
#endif

#if defined(__APPLE__) || defined(__WIN32__)
  const char items[8][9][17] =
#endif
{
  { //Battery
    "   _        _   ",
    " _| |______| |_ ",
    "|              |",
    "|              |",
    "|              |",
    "|              |",
    "|              |",
    "|______________|"
  },
  { //laser cannon
    "                ",
    "     _    _     ",
    "    | |  | |    ",
    "    | |  | |    ",
    "   _| |__| |_   ",
    "  /          \\  ",
    " /            \\ ",
    "/______________\\"
  },
  { //booster
    "                ",
    "~         _     ",
    " ~ ~ ~   | \\__  ",
    " ~~  ~~~ #    \\_",
    "~ ~ ~~~~ #     _",
    " ~~~ ~~~ #  __/ ",
    "  ~~ ~   |_/    ",
    " ~              "
  },
  { //radar
    "                ",
    "          |     ",
    "          |     ",
    "      o  /      ",
    "       \\/|      ",
    "   ____/||      ",
    "   _____||____  ",
    "  /___________\\ "
  },
  { //beam laser
    "     ______     ",
    "____/     /     ",
    "         /      ",
    "       <(~~~~~~~",
    "       <(~~~~~~~",
    "       <(~~~~~~~",
    "____     \\      ",
    "    \\_____\\     "
  },
  { //speedyball
    "                ",
    "          O     ",
    "         /      ",
    "  \\             ",
    "                ",
    "    \\ /         ",
    "     V          ",
    "|==============|"
  },
  { //multiball
    "       O   O    ",
    "        \\ /     ",
    "         v      ",
    "  \\     /       ",
    "                ",
    "    \\ /         ",
    "     V          ",
    "|==============|"
  },
  { //rocket
    "                ",
    "  |\\            ",
    "  | \\____|\\____ ",
    "~~)            \\",
    "~~)  ____  ____/",
    "  | /    |/     ",
    "  |/            ",
    "                "
  }
};

#if defined(_Z8F6403)
rom char game_over[6][63] =
#endif

#if defined(__APPLE__) || defined(__WIN32__)
  const char game_over[6][63] =
#endif

{
  "  _____          __  __ ______    ______      ________ _____  ",
  " / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ ",
  "| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |",
  "| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / ",
  "| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ ",
  " \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\"
};

#if defined(_Z8F6403)
rom char game_victory[7][103] =
#endif

#if defined(__APPLE__) || defined(__WIN32__)
  const char game_victory[7][103] =
#endif

{
  "  _____ ____  _   _  _____ _____         _______ _    _ _            _______ _____ ____  _   _  _____ ",
  " / ____/ __ \\| \\ | |/ ____|  __ \\     /\\|__   __| |  | | |        /\\|__   __|_   _/ __ \\| \\ | |/ ____|",
  "| |   | |  | |  \\| | |  __| |__) |   /  \\  | |  | |  | | |       /  \\  | |    | || |  | |  \\| | (___  ",
  "| |   | |  | | . ` | | |_ |  _  /   / /\\ \\ | |  | |  | | |      / /\\ \\ | |    | || |  | | . ` |\\___ \\ ",
  "| |___| |__| | |\\  | |__| | | \\ \\  / ____ \\| |  | |__| | |____ / ____ \\| |   _| || |__| | |\\  |____) |",
  " \\_____\\____/|_| \\_|\\_____|_|  \\_\\/_/    \\_\\_|   \\____/|______/_/    \\_\\_|  |_____\\____/|_| \\_|_____/ "
};

#if defined(_Z8F6403)
rom char mapThumbs[7][16][17] =
#endif

#if defined(__APPLE__) || defined(__WIN32__)
  const char mapThumbs[7][15][16] =
#endif

{
  {
    "   A        A  ",
    "  /#\\      /#\\ ",
    " /###\\    /###\\",
    " \\###/    \\###/",
    "  \\#/    A \\#/ ",
    "   V    /#\\ V  ",
    "  A    /###\\   ",
    " /#\\   \\###/   ",
    "/###\\   \\#/    ",
    "\\###/    V     ",
    " \\#/           ",
    "  V            ",
    "MWMWMWMWMWMWMWM",
    "WMWMWMWMWMWMWMW",
    "               ",
  }, {
    "   WW       WW  ",
    "     |     |    ",
    "     |_____|    ",
    "    /#######\\   ",
    "   /#########\\  ",
    "  /## #### ###\\ ",
    "  |## #### ###| ",
    " ###############",
    " ###############",
    " #  \\#######/  #",
    " # /MMMMMMMMM\\ #",
    " # ||       || #",
    " #  \\       /  #",
    "     \\MM MM/    ",
    "                "
  }, {
    "   ##      ##   ",
    " #  ##    ##  # ",
    "|| __|____|__ ||",
    "|| |HHHHHHHH| ||",
    "|| |HHH##HHH| ||",
    "|HVHH$H##H$HHVH|",
    "|HHHH$HUUH$HHHH|",
    "\\#HHOOHHHHOOHH#/",
    "  |HHOOOOOOHH|  ",
    "  \\11wwwwww11/  ",
    "   ||      ||   ",
    "   ||      ||   ",
    "  MM        MM  ",
    "  MM        MM  ",
    "                "
  }, {
    "  /|     \\#\\   ",
    " /#/      \\#\\  ",
    "/#/        \\#\\ ",
    "|#|         \\#\\",
    "|#|   /\\    |#|",
    "|#|__/AA\\___|#|",
    "|###GHHHHHD###|",
    "|##GHH$H$HHD##|",
    "|##GHH$H$HHD##|",
    "|#WWWHHHHH| \\#|",
    "||   \\VVVV/  ||",
    "||     \\/    ||",
    "\\#\\         // ",
    " \\#\\       /#/ ",
    "  \\#\\     /#/  "
  }, {
    "#$#$#$#$#$#$#$#$",
    "$#$#$#$#$#$#$#$#",
    "################",
    "################",
    "HHH=########=HHH",
    "$$=H$H$H$H$H$=$$",
    "#=H$H$H$H$H$H$=#",
    "=              =",
    "                ",
    "  W W ==== W W  ",
    " W W W    W W W ",
    " $ $ $ $$ $ $ $ ",
    "# # # #  # # # #",
    "=W=W=W=WW=W=W=W=",
    "                "
  }, {
    "                ",
    "   |=  | | |=   ",
    "   | )_|_|_| )  ",
    "   |=HH|H|H|<   ",
    "   |HHH|H|H|H)  ",
    "  /HHHHHUHH|/\\  ",
    " |HHHHHHHHHHHH| ",
    "   |H#HHH##H|   ",
    "   |H#HHH##H|   ",
    " #_|H#HHHHHH|   ",
    " #H#H#HHHHHH|   ",
    " \\===========|  ",
    "  \\#========#/  ",
    "   \\##=#===#/   ",
    "    \\/  \\=#/    "
  }
};

#if defined(_Z8F6403)
rom char image[22][53] =
#endif

#if defined(__APPLE__) || defined(__WIN32__)
  const char image[22][53] =
#endif
    // its an ufo
{
  "                        ;LL;                        ",
  "                    C@@q3  4$@@M                    ",
  "                   @6.        .@@                   ",
  "                 7@Y            r@j                 ",
  "               l@                 @;                ",
  "               @       X$4Gg       .@               ",
  "              @$      x$    ;@      a@              ",
  "              @       8x oO gx      @               ",
  "              4@      gm    3K      @C              ",
  "              Om      @     GC      Kp              ",
  "          omp4@@a@@@@66$   Y6g@@@@@g@@44N:          ",
  "     o0@@@@   @4       2@q@@,       3@  H@@@@Go     ",
  "  ,6@$C.      4Q     22;    C$;     G5      ,F$@@   ",
  " G@57.        .@M   @l        @    M@           K@Q ",
  " @             @@$FT@;        g2v5g@@            Y@ ",
  " @@L             ;TFKFCpQ22QpmFCmT;             7@9 ",
  "  @6G$4;                                    Yp$G@@  ",
  "   @7   @@gQQ47;                    ;743G$@@   C@   ",
  "    @@x       q6@@@@@89@@@@@@a@@@@@@6         @@    ",
  "      Yp@2                                  $@4     ",
  "        $@@                            @g6@@        ",
  "           #m@@82$6@6g$GGGGGq$a6@6$O6@@7            "
};

#endif /*! _CHARSET_H_ */