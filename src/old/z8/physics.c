#include "physics.h"
#include "util.h"
#include <sio.h>

char ballSpeed;
unsigned int * strikerPos;
int strikerWidth;

void phy_simulate(TVector_8_8 *pos, TVector_0_7 *vel) {
	TVector_8_8 v;
	unsigned char x, y, sp;
	v = util_expand_vector(*vel);
	pos->x += (signed int) (ballSpeed * vel->x);
	pos->y += (signed int) (ballSpeed * vel->y);
	x = (unsigned char) (pos->x >> 8);
	y = (unsigned char) (pos->y >> 8);
	if (y == 1) {
		vel->y = -vel->y;
	} else if (y == 91 && x > (*strikerPos >> 8) - strikerWidth - 1 && x < (*strikerPos >> 8) + strikerWidth + 1) {
		sp = (unsigned char) (*strikerPos >> 8);
		vel->y = -vel->y;
		printf("%d, %d,  %d,   %d,  %d,   %d", (int) vel->x, (int) vel->y, strikerWidth, strikerWidth >> 2, (int) x, (int) sp);
		if (x < sp - strikerWidth + (strikerWidth >> 2)) {
			// Far left
			util_rotate(vel, 85);	// ~60 deg
		} else if (x < sp - strikerWidth + (strikerWidth >> 1)) {
			// Middle left
			util_rotate(vel, 43);	// ~30 deg
		} else if (x <= sp + strikerWidth - (strikerWidth >> 1)) {
			// Center
		} else if (x <= sp + strikerWidth - (strikerWidth >> 2)) {
			// Middle right
			util_rotate(vel, 427);	// ~300 deg
		} else {
			// Far right
			util_rotate(vel, 469);	// ~330 deg
		}
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