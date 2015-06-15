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

void phy_simulate(unsigned char blockData[4][15][2], TVector_8_8 *pos, TVector_0_7 *vel, unsigned int strikerPos) {
	unsigned char x, y, sp;
	pos->x += (signed int) (_ballSpeed * vel->x);
	pos->y += (signed int) (_ballSpeed * vel->y);
	x = (unsigned char) (pos->x >> 8);
	y = (unsigned char) (pos->y >> 8);
	if (y == 0) {
		vel->y = -vel->y;
	} else if (!_bouncedStriker && y == 91 && x >= (strikerPos >> 8) - _strikerSize && x <= (strikerPos >> 8) + _strikerSize && !(vel->y & 0x80)) {
		_bouncedStriker = 1;
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

		if (y <= 62) {
			if (y & 0x01) {
				// Touching lower edge of block

			} else if (y & 0x00) {
				// Touching upper edge of block
			}
		}
	}
	if (x == 0 || x == width - 1) {
		vel->x = -vel->x;
	}


}

void phy_set_striker_size(int size) {
	_strikerSize = (size >> 1);
}

void phy_set_ball_speed(int speed) {
	_ballSpeed = (char) speed;
}