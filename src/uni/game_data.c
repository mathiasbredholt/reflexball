#include "game_data.h"

#if defined(_Z8F6403)
rom unsigned char itemMax[NUMBER_OF_ITEMS] =
#else
const unsigned char itemMax[NUMBER_OF_ITEMS] =
#endif
{
	3,	// battery
	3,	// bounce
	3,	// move speed
	2,	// left laser
	2,	// right laser
	1	// rocket
};

#if defined(_Z8F6403)
rom unsigned char itemPrice[NUMBER_OF_ITEMS] =
#else
const unsigned char itemPrice[NUMBER_OF_ITEMS] =
#endif
{
	1,	// battery
	2,	// bounce
	3,	// move speed
	4,	// left laser
	4,	// right laser
	5	// rocket
};