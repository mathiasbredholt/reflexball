#include "util.h"

void phy_simulate(unsigned char blockData[4][15][2], TVector_8_8 *pos, TVector_0_7 *vel, unsigned int strikerPos, char * redraw, int * blockHit);

char phy_hit_block(unsigned char blockData[4][15][2], int * blockHit, int x, int y);

void phy_set_striker_size(int width);

void phy_set_ball_speed(int speed);
