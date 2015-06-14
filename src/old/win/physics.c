#include "physics.h"
#include "util.h"

int ballSpeed;

void phy_simulate(TVector_8_8 *pos, TVector_0_7 *vel) {
	TVector_8_8 v = util_expand_vector(*vel);
	pos->x += FIX8_MULT(ballSpeed, v.x);
	pos->y += FIX8_MULT(ballSpeed, v.y);
}

void phy_set_ball_speed(int speed) {
	ballSpeed = speed;
}