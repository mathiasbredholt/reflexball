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

char _ballSpeed, _bouncedStriker;
unsigned int * _strikerPos;
int _strikerSize;

void phy_simulate(TVector_8_8 *pos, TVector_0_7 *vel) {
	unsigned char x, y, sp;
	pos->x += (signed int) (_ballSpeed * vel->x);
	pos->y += (signed int) (_ballSpeed * vel->y);
	x = (unsigned char) (pos->x >> 8);
	y = (unsigned char) (pos->y >> 8);
	if (y == 1) {
		vel->y = -vel->y;
	} else if (!_bouncedStriker && y == 91 && x > (*_strikerPos >> 8) - _strikerSize - 1 && x < (*_strikerPos >> 8) + _strikerSize + 1 && !(vel->y & 0x80)) {
		_bouncedStriker = 1;
		sp = (unsigned char) (*_strikerPos >> 8);
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
	} else if (y > 94) {
		//Lost ball
		pos->x = 128 << 8;
		pos->y = 90 << 8;
		vel->y = -vel->y;
	} else if (vel->y == 0) {
		// Ball will be stuck - so we turn it slighly upwards
		vel->y = -1;
	} else {
		_bouncedStriker = y >= 91;
	}
	if (x == 1 || x == 253) {
		vel->x = -vel->x;
	}


}

void phy_set_striker(unsigned int * pos, int width) {
	_strikerPos = pos;
	_strikerSize = (width >> 1);
}

void phy_set_ball_speed(int speed) {
	_ballSpeed = (char) speed;
}