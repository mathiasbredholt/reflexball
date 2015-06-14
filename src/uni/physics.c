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

char ballSpeed;
unsigned int * strikerPos;
int strikerWidth;

void phy_simulate(TVector_8_8 *pos, TVector_0_7 *vel) {
	unsigned char x, y, sp;
	pos->x += (signed int) (ballSpeed * vel->x);
	pos->y += (signed int) (ballSpeed * vel->y);
	x = (unsigned char) (pos->x >> 8);
	y = (unsigned char) (pos->y >> 8);
	if (y == 1) {
		vel->y = -vel->y;
	} else if (y == 91 && x > (*strikerPos >> 8) - strikerWidth - 1 && x < (*strikerPos >> 8) + strikerWidth + 1) {
		sp = (unsigned char) (*strikerPos >> 8);
		vel->y = -vel->y;
		printf("vel_x=%d, vel_y=%d,  sw=%d,   sw>>2=%d,  x=%d,  sp=%d,   l >= %d, ml >= %d, c > %d, mr > %d", (int) vel->x, (int) vel->y, strikerWidth, strikerWidth >> 2, (int) x, (int) sp, (int) (x + strikerWidth - (strikerWidth >> 2) - 1), (int) (x + strikerWidth - (strikerWidth >> 1) - 1), (int) (x - strikerWidth + (strikerWidth >> 1) - 1), (int) (x - strikerWidth + (strikerWidth >> 2) - 1));
		if (x <= sp - strikerWidth + (strikerWidth >> 2) + 1) {
			// Far left
			printf("  left");
			util_rotate(vel, -43);	// ~30 deg
		} else if (x <= sp - strikerWidth + (strikerWidth >> 1) + 1) {
			// Middle left
			printf("  middle left");
			util_rotate(vel, -21);	// ~15 deg
		} else if (x < sp + strikerWidth - (strikerWidth >> 1) + 1) {
			// Center
			printf("  center");
		} else if (x < sp + strikerWidth - (strikerWidth >> 2) + 1) {
			// Middle right
			printf("  middle right");
			util_rotate(vel, 21);	// ~15 deg
		} else {
			// Far right
			printf("  right");
			util_rotate(vel, 43);	// ~30 deg
		}
	} else if (y > 94) {
		//Lost ball
		pos->x = 128 << 8;
		pos->y = 90 << 8;
		vel->y = -vel->y;
	}
	if (x == 1 || x == 254) {
		vel->x = -vel->x;
	}
}

void phy_set_striker(unsigned int * pos, int width) {
	strikerPos = pos;
	strikerWidth = (width >> 1);
}

void phy_set_ball_speed(int speed) {
	ballSpeed = (char) speed;
}