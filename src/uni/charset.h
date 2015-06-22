#ifndef _CHARSET_H_
#define _CHARSET_H_

#if defined(_Z8F6403)

extern rom char character_data[95][5];
extern rom char font_mini[36][3][5];
extern rom char items[8][9][17];
extern rom char game_over[6][63];
extern rom char game_victory[7][103];
extern rom char mapThumbs[7][15][17];
extern rom char image[22][53];
extern rom char small_title[5][86];
extern rom char title[9][165];

#else

extern const char character_data[95][5];
extern const char font_mini[36][3][5];
extern const char items[8][9][17];
extern const char game_over[6][63];
extern const char game_victory[7][103];
extern const char mapThumbs[7][15][17];
extern const char image[22][53];
extern const char small_title[5][86];
extern const char title[9][165];

#endif

#endif /*! _CHARSET_H_ */