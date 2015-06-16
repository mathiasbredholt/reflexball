#ifdef __APPLE__
#define GCC
#endif

#ifdef __WIN32__
#define GCC
#endif

#ifndef GCC
#include <sio.h>
#endif

#ifdef GCC
#include <stdio.h>
#endif

#include "physics.h"
#include "util.h"

#define width 256
#define height 96
#define striker_height 92

char _ballSpeed, _bouncedStriker;
int _strikerSize;

void phy_simulate(unsigned char blockData[4][15][2], TVector_8_8 *pos, TVector_0_7 *vel, unsigned int strikerPos, int * redraw, int * blockHit) {
	unsigned char x, y, sp;
	pos->x += shift_fix_int_right((int) (_ballSpeed * vel->x * 8), 2);
	pos->y += shift_fix_int_right((int) (_ballSpeed * vel->y * 5), 2);
	x = (unsigned char) (pos->x >> 8);
	y = (unsigned char) (pos->y >> 8);
	if (y == 0) {
		vel->y = -vel->y;
		*redraw = 1;
	} else if (!_bouncedStriker && y == 91 && x >= (strikerPos >> 8) - _strikerSize && x <= (strikerPos >> 8) + _strikerSize && !(vel->y & 0x80)) {
		_bouncedStriker = 1;
		*redraw = 1;
		sp = (unsigned char) (strikerPos >> 8);
		vel->y = -vel->y;
		//printf("vel_x=%d, vel_y=%d,  sw=%d,   sw>>2=%d,  x=%d,  sp=%d,   l >= %d, ml >= %d, c > %d, mr > %d", (int) vel->x, (int) vel->y, _strikerSize, _strikerSize >> 2, (int) x, (int) sp, (int) (x + _strikerSize - (_strikerSize >> 2) - 1), (int) (x + _strikerSize - (_strikerSize >> 1) - 1), (int) (x - _strikerSize + (_strikerSize >> 1) - 1), (int) (x - _strikerSize + (_strikerSize >> 2) - 1));
		if (x <= sp - _strikerSize + (_strikerSize >> 2) + 1) {
			// Far left
			// printf("  left");
			util_rotate(vel, -43);	// ~30 deg
		} else if (x <= sp - _strikerSize + (_strikerSize >> 1) + 1) {
			// Middle left
			// printf("  middle left");
			util_rotate(vel, -21);	// ~15 deg
		} else if (x < sp + _strikerSize - (_strikerSize >> 1) + 1) {
			// Center
			// printf("  center");
		} else if (x < sp + _strikerSize - (_strikerSize >> 2) + 1) {
			// Middle right
			// printf("  middle right");
			util_rotate(vel, 21);	// ~15 deg
		} else {
			// Far right
			// printf("  right");
			util_rotate(vel, 43);	// ~30 deg
		}
		if (vel->y > 0)	{
			vel->y = -vel->y;
		}
	} else if (y > height) {
		//Lost ball
		pos->x = 128 << 8;
		pos->y = 90 << 8;
		vel->y = -vel->y;
	} else if (vel->y == 0) {
		// Ball will be stuck - so we turn it slighly upwards
		vel->y = -1;
	} else {
		_bouncedStriker = y >= 91;

		if (y <= 60) {	// We already know that y!=0
			if ((y & 3) == 0) {
				// Touching lower edge of block
				if (phy_hit_block(blockData, blockHit, redraw, x >> 4, (y >> 2) - 1)) {
					vel->y = -vel->y;
					if ((x & 15) == 15) {
						// Hitting corner of right block because ball is two pixels wide
						phy_hit_block(blockData, blockHit, redraw, (x >> 4) + 1, (y >> 2) - 1);
					}
				} else if ((x & 15) == 15 && phy_hit_block(blockData, blockHit, redraw, (x >> 4) + 1, (y >> 2) - 1)) {
					// Hitting corner of right block because ball is two pixels wide
					vel->y = -vel->y;
				}
				if ((x & 15) == 1) {
					// Left corner
					if (phy_hit_block(blockData, blockHit, redraw, (x >> 4) - 1, y >> 2)) {
						vel->x = -vel->x;
					}
				} else if ((x & 15) == 14) {
					// Right corner
					if (phy_hit_block(blockData, blockHit, redraw, (x >> 4) + 1, y >> 2)) {
						vel->x = -vel->x;
					}
				} else if ((x & 15) == 15) {
					if (phy_hit_block(blockData, blockHit, redraw, (x >> 4) + 1, y >> 2)) {
						vel->x = -vel->x;
					}
				}
			} else if ((y & 3) == 3) {
				// printf("upper");
				// Touching upper edge of block
				// *redraw = 1;
				if (phy_hit_block(blockData, blockHit, redraw, x >> 4, (y >> 2) + 1)) {
					vel->y = -vel->y;
				}
				if ((x & 15) == 1) {
					// Left corner
					if (phy_hit_block(blockData, blockHit, redraw, (x >> 4) - 1, y >> 2)) {
						vel->x = -vel->x;
					}
				} else if ((x & 15) == 14) {
					// Right corner
					if (phy_hit_block(blockData, blockHit, redraw, (x >> 4) + 1, y >> 2)) {
						vel->x = -vel->x;
					}
				}
			} else if ((x & 15) == 1) {
				// Right edge
				if (phy_hit_block(blockData, blockHit, redraw, (x >> 4) - 1, y >> 2)) {
					vel->x = -vel->x;
				}
			} else if ((x & 15) == 14) {
				// Left edge
				if (phy_hit_block(blockData, blockHit, redraw, (x >> 4) + 1, y >> 2)) {
					vel->x = -vel->x;
				}
			}
		}
	}
	if (x == 0 || x == width - 2) {
		vel->x = -vel->x;
		*redraw = 1;
	}


}

char phy_hit_block(unsigned char blockData[4][15][2], int * blockHit, int * redraw, int x, int y) {
	int type;

	if (x > 15 || x < 0 || y > 14 || y < 0) {
		return 0;
	}

	for (type = 3; type >= 0; --type) {
		if (blockData[type][y][x >> 3] & 0x80 >> (x & 0x07)) {
			// if (type == 3)
			// {
			// 	printf("Type = %d   x & 0x07 = %d   0x80 >> (x & 0x07) = %d   blockData[type][y][x >> 3] = %d   blockData[type][y][x >> 3] & 0x80 >> (x & 0x07) = %d", type, (int) (x & 0x07), (int) (0x80 >> (x & 0x07)), (int) blockData[type][y][x >> 3], (int) (blockData[type][y][x >> 3] & 0x80 >> (x & 0x07)));
			// }
			// Block exists
			// printf("type=%d", type);
			blockData[type][y][x >> 3] &= ~(0x80 >> (x & 0x07));	// Delete block
			*blockHit = type << 8;
			// printf("     %d", *blockHit);
			*blockHit |= y << 4;
			// printf("          %d", *blockHit);
			*blockHit |= x;
			// printf("               %d", *blockHit);
			if (type) {	// type != 0
				blockData[type - 1][y][x >> 3] |= 0x80 >> (x & 0x07);	// Add block with lower type
			}
			*redraw = 1;
			return 1;
		}
	}
	return 0;
}

void phy_set_striker_size(int size) {
	_strikerSize = (size >> 1);
}

void phy_set_ball_speed(int speed) {
	_ballSpeed = (char) speed;
}