#include "game_data.h"

#if defined(_Z8F6403)
rom unsigned char itemMax[NUMBER_OF_ITEMS] =
#else
const unsigned char itemMax[NUMBER_OF_ITEMS] =
#endif
{3, 3, 3, 3, 3, 3, 3, 3};

#if defined(_Z8F6403)
rom unsigned char itemPrice[NUMBER_OF_ITEMS] =
#else
const unsigned char itemPrice[NUMBER_OF_ITEMS] =
#endif
{3, 3, 3, 3, 3, 3, 3, 3};