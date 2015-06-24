/*
  ##      #    #   #  ####          ###      #    #####    #
 #  #    # #   ## ##  #             #  #    # #     #     # #
 #      #   #  # # #  ###           #  #   #   #    #    #   #
 # ##   #####  # # #  #             #  #   #####    #    #####
 #  #   #   #  #   #  #             #  #   #   #    #    #   #
  ##    #   #  #   #  ####          ###    #   #    #    #   #
*/

#include "game_data.h"

#if defined(_Z8F6403)
rom unsigned char itemMax[NUMBER_OF_ITEMS] =
#else
const unsigned char itemMax[NUMBER_OF_ITEMS] =
#endif
{
	3,	// battery
	3,	// bounce
	3,	// ship upgrade
	2,	// left laser
	2,	// right laser
	1	// rocket
};

#if defined(_Z8F6403)
rom int itemPrice[NUMBER_OF_ITEMS] =
#else
const int itemPrice[NUMBER_OF_ITEMS] =
#endif
{
	1200,	// battery
	1500,	// bounce
	2250,	// ship upgrade
	4375,	// left laser
	4375,	// right laser
	15000	// rocket
};