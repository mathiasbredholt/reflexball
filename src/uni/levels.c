/*

 #      ####   #  #   ####   #       ##
 #      #      #  #   #      #      #  #
 #      ###    #  #   ###    #       #
 #      #      ####   #      #        #
 #      #       ##    #      #      #  #
 ####   ####    ##    ####   ####    ##
*/

#if defined(_Z8F6403)
rom char levelData[6][15][8] =
#else
const char levelData[6][15][8] =
#endif
{
	{	// level 1, no impossible blocks, easygoing Asteroid belt
		{0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00},
		{0x00, 0xA1, 0xA0, 0x00, 0x00, 0x01, 0x61, 0x00},
		{0x0A, 0x11, 0x1A, 0x00, 0x00, 0x16, 0x66, 0x10},
		{0x0A, 0x11, 0x1A, 0x00, 0x00, 0x16, 0x66, 0x10},
		{0x00, 0xA1, 0xA0, 0x00, 0x06, 0x01, 0x61, 0x00},
		{0x00, 0x0A, 0x00, 0x00, 0x63, 0x60, 0x10, 0x00},
		{0x00, 0x30, 0x00, 0x06, 0x33, 0x36, 0x00, 0x00},
		{0x03, 0xA3, 0x00, 0x06, 0x33, 0x36, 0x00, 0x00},
		{0x3A, 0xAA, 0x30, 0x00, 0x63, 0x60, 0x00, 0x00},
		{0x3A, 0xAA, 0x30, 0x00, 0x06, 0x00, 0x00, 0x00},
		{0x03, 0xA3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13},
		{0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31}
	}, {	// first 'artpiece', 2nd level. nothing serious A wild alien appears
		{0x00, 0x03, 0x30, 0x00, 0x00, 0x00, 0x33, 0x00},
		{0x00, 0x03, 0x30, 0x00, 0x00, 0x00, 0x33, 0x00},
		{0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00},
		{0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00},
		{0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x60, 0x00},
		{0x00, 0x06, 0x11, 0x11, 0x11, 0x11, 0x16, 0x00},
		{0x00, 0x61, 0x16, 0x11, 0x11, 0x16, 0x11, 0x60},
		{0x00, 0x61, 0x16, 0x11, 0x11, 0x16, 0x11, 0x60},
		{0x03, 0x61, 0x11, 0x11, 0x11, 0x11, 0x11, 0x63},
		{0x03, 0x66, 0x11, 0x11, 0x11, 0x11, 0x66, 0x63},
		{0x03, 0x00, 0x61, 0x11, 0x11, 0x11, 0x60, 0x03},
		{0x03, 0x06, 0x66, 0x66, 0x66, 0x66, 0x66, 0x03},
		{0x03, 0x03, 0x30, 0x00, 0x00, 0x00, 0x33, 0x03},
		{0x03, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x03},
		{0x00, 0x00, 0x03, 0x33, 0x03, 0x33, 0x00, 0x00}
	}, {	// needs a bit more precise strikes, 3rd level Oh no it's a monster
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x01, 0x10, 0x00, 0x00, 0x01, 0x10, 0x00},
		{0x0A, 0x00, 0x11, 0x00, 0x00, 0x11, 0x00, 0xA0},
		{0x33, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x33},
		{0x33, 0x0A, 0xA1, 0xAA, 0xAA, 0x1A, 0xA0, 0x33},
		{0x33, 0x0A, 0x33, 0x31, 0x13, 0x33, 0xA0, 0x33},
		{0x33, 0x11, 0x36, 0x31, 0x13, 0x63, 0x3A, 0x33},
		{0x33, 0x33, 0x36, 0x3B, 0xB3, 0x63, 0x33, 0x33},
		{0x33, 0x33, 0x11, 0x33, 0x33, 0x11, 0x33, 0x33},
		{0x00, 0xA3, 0x31, 0x11, 0x11, 0x13, 0x3A, 0x00},
		{0x00, 0xA3, 0x3A, 0xAA, 0xAA, 0xA3, 0x3A, 0x00},
		{0x00, 0x03, 0x30, 0x00, 0x00, 0x03, 0x30, 0x00},
		{0x00, 0x03, 0x30, 0x00, 0x00, 0x03, 0x30, 0x00},
		{0x00, 0x33, 0x00, 0x00, 0x00, 0x00, 0x33, 0x00},
		{0x00, 0x33, 0x00, 0x00, 0x00, 0x00, 0x33, 0x00}
	}, {	//4th level holy hot dicks from hell it's darth vader
		{0x00, 0xAA, 0x00, 0x00, 0x00, 0xAA, 0xA0, 0x00},
		{0x0A, 0x6A, 0x00, 0x00, 0x00, 0x0A, 0x6A, 0x00},
		{0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xA0},
		{0xA6, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x6A},
		{0xA6, 0xA0, 0x00, 0xAA, 0x00, 0x00, 0x0A, 0x6A},
		{0xA6, 0xA0, 0x0A, 0xAA, 0xAA, 0x00, 0x0A, 0x6A},
		{0xA6, 0xAA, 0xAA, 0x66, 0x6A, 0xAA, 0xA1, 0x6A},
		{0xA6, 0x11, 0xA6, 0x16, 0x16, 0xAA, 0x11, 0x6A},
		{0xA6, 0x1A, 0xA6, 0x16, 0x16, 0x6A, 0xA1, 0x6A},
		{0xA6, 0xAA, 0xAA, 0x66, 0x66, 0xAA, 0x0A, 0x6A},
		{0xAA, 0x00, 0x0A, 0xAA, 0xAA, 0xA0, 0x00, 0xAA},
		{0xAA, 0x00, 0x00, 0x0A, 0xA0, 0x00, 0x00, 0xAA},
		{0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x0A, 0xA0},
		{0x0A, 0x6A, 0x00, 0x00, 0x00, 0x00, 0xA6, 0xA0},
		{0x00, 0xAA, 0xA0, 0x00, 0x00, 0x0A, 0xAA, 0x00}
	}, {	//5th level // the destruction of darth vaders ship caused a crash in the time-space continuum! Can you find you way back?
		{0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13},
		{0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31},
		{0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11},
		{0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11},
		{0x66, 0x6B, 0x11, 0x11, 0x11, 0x11, 0xB6, 0x66},
		{0x33, 0xB6, 0x36, 0x36, 0x36, 0x36, 0x3B, 0x33},
		{0x1B, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xB1},
		{0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0xA0, 0xA0, 0xBB, 0xBB, 0x0A, 0x0A, 0x00},
		{0x0A, 0x0A, 0x0A, 0x00, 0x00, 0xA0, 0xA0, 0xA0},
		{0x03, 0x03, 0x03, 0x03, 0x30, 0x30, 0x30, 0x30},
		{0x10, 0x10, 0x10, 0x10, 0x01, 0x01, 0x01, 0x01},
		{0xBA, 0xBA, 0xBA, 0xBA, 0xAB, 0xAB, 0xAB, 0xAB},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
	}, { 	// 6th level Oh noes! you're stuck at the edge of the universe! oh! What is that!? It's the public house at the edge of the universe.. and it's refusing service! Better destroy it!
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x01, 0x10, 0x01, 0x01, 0x01, 0x10, 0x00},
		{0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00},
		{0x00, 0x01, 0x16, 0x61, 0x61, 0x61, 0x16, 0x00},
		{0x00, 0x61, 0x66, 0x61, 0x61, 0x61, 0x61, 0x60},
		{0x06, 0x61, 0x66, 0x66, 0x16, 0x61, 0x16, 0x66},
		{0x06, 0x6A, 0x33, 0x33, 0x33, 0x33, 0xA6, 0x60},
		{0x00, 0x0A, 0x3A, 0x33, 0x31, 0x13, 0xA0, 0x00},
		{0x00, 0x0A, 0x3A, 0x33, 0x31, 0x13, 0xA0, 0x00},
		{0x01, 0x0A, 0x3A, 0x33, 0x33, 0x33, 0xA0, 0x00},
		{0x0A, 0x3A, 0x3A, 0x33, 0x33, 0x33, 0xA0, 0x00},
		{0x03, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBA, 0x00},
		{0x00, 0x16, 0xBB, 0xBB, 0xBB, 0xBB, 0x63, 0x00},
		{0x00, 0x00, 0x1A, 0xBA, 0xBB, 0xBA, 0x60, 0x00},
		{0x00, 0x00, 0x03, 0x60, 0x3B, 0xA1, 0x00, 0x00}
	}
};
