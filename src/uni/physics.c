#if defined(__APPLE__) || defined(__WIN32__)
#include <stdio.h>
#endif

#if defined(_Z8F6403)
// #include <sio.h>
#endif

#include "physics.h"
#include "util.h"

#define width 256
#define height 96
#define striker_height 92

void phy_simulate(GameData *gameData) {
	unsigned char x, y, sp;
	int dx, dy;
	// gameData->ballPos.x += (int) (gameData->ballSpeed * gameData->ballVel.x);// * 8
	// gameData->ballPos.y += (int) (gameData->ballSpeed * gameData->ballVel.y);// * 5
	dx = (int) (gameData->ballSpeed * gameData->ballVel.x);
	dy = (int) (gameData->ballSpeed * gameData->ballVel.y);
	// printf("%d   %d   %d   %d", (int) gameData->ballSpeed, (int) gameData->ballVel.x, dx * 8, shift_fix_int_right((int) (gameData->ballSpeed * gameData->ballVel.x) * 8, 2));
	// printf(",   %d   %d   %d   %d", (int) gameData->ballSpeed, (int) gameData->ballVel.y, dy * 5, shift_fix_int_right((int) (gameData->ballSpeed * gameData->ballVel.y) * 5, 2));
	gameData->ballPos.x += shift_fix_int_right(dx * 8, 4);
	gameData->ballPos.y += shift_fix_int_right(dy * 5, 4);
	x = (unsigned char) (gameData->ballPos.x >> 8);
	y = (unsigned char) (gameData->ballPos.y >> 8);
	if (y == 0) {
		gameData->ballVel.y = -gameData->ballVel.y;
		gameData->redraw = 1;
	} else if (!gameData->bouncedStriker && y == 91 && x >= (gameData->strikerPos >> 8) - gameData->strikerSize && x <= (gameData->strikerPos >> 8) + gameData->strikerSize && !(gameData->ballVel.y & 0x80)) {
		gameData->bouncedStriker = 1;
		gameData->redraw = 1;
		sp = (unsigned char) (gameData->strikerPos >> 8);
		gameData->ballVel.y = -gameData->ballVel.y;
		//printf("vel_x=%d, vel_y=%d,  sw=%d,   sw>>2=%d,  x=%d,  sp=%d,   l >= %d, ml >= %d, c > %d, mr > %d", (int) gameData->ballVel.x, (int) gameData->ballVel.y, gameData->strikerSize, gameData->strikerSize >> 2, (int) x, (int) sp, (int) (x + gameData->strikerSize - (gameData->strikerSize >> 2) - 1), (int) (x + gameData->strikerSize - (gameData->strikerSize >> 1) - 1), (int) (x - gameData->strikerSize + (gameData->strikerSize >> 1) - 1), (int) (x - gameData->strikerSize + (gameData->strikerSize >> 2) - 1));
		if (x <= sp - gameData->strikerSize + (gameData->strikerSize >> 2) + 1) {
			// Far left
			// printf("  left");
			util_rotate(&gameData->ballVel, -43);	// ~30 deg
		} else if (x <= sp - gameData->strikerSize + (gameData->strikerSize >> 1) + 1) {
			// Middle left
			// printf("  middle left");
			util_rotate(&gameData->ballVel, -21);	// ~15 deg
		} else if (x < sp + gameData->strikerSize - (gameData->strikerSize >> 1) + 1) {
			// Center
			// printf("  center");
		} else if (x < sp + gameData->strikerSize - (gameData->strikerSize >> 2) + 1) {
			// Middle right
			// printf("  middle right");
			util_rotate(&gameData->ballVel, 21);	// ~15 deg
		} else {
			// Far right
			// printf("  right");
			util_rotate(&gameData->ballVel, 43);	// ~30 deg
		}
		if (gameData->ballVel.y > 0)	{
			gameData->ballVel.y = -gameData->ballVel.y;
		}
	} else if (y > height) {
		//Lost ball
		gameData->ballPos.x = 128 << 8;
		gameData->ballPos.y = 90 << 8;
		gameData->ballVel.y = -gameData->ballVel.y;
	} else if (gameData->ballVel.y == 0) {
		// Ball will be stuck - so we turn it slighly upwards
		gameData->ballVel.y = -1;
	} else {
		gameData->bouncedStriker = y >= 91;

		if (y <= 60) {	// We already know that y!=0
			if ((y & 3) == 0) {
				// Touching lower edge of block
				if (phy_hit_block(gameData, x >> 4, (y >> 2) - 1)) {
					gameData->ballVel.y = -gameData->ballVel.y;
					if ((x & 15) == 15) {
						// Hitting corner of right block because ball is two pixels wide
						phy_hit_block(gameData, (x >> 4) + 1, (y >> 2) - 1);
					}
				} else if ((x & 15) == 15 && phy_hit_block(gameData, (x >> 4) + 1, (y >> 2) - 1)) {
					// Hitting corner of right block because ball is two pixels wide
					gameData->ballVel.y = -gameData->ballVel.y;
				}
				if ((x & 15) == 1) {
					// Left corner
					if (phy_hit_block(gameData, (x >> 4) - 1, y >> 2)) {
						gameData->ballVel.x = -gameData->ballVel.x;
					}
				} else if ((x & 15) == 14) {
					// Right corner
					if (phy_hit_block(gameData, (x >> 4) + 1, y >> 2)) {
						gameData->ballVel.x = -gameData->ballVel.x;
					}
				} else if ((x & 15) == 15) {
					if (phy_hit_block(gameData, (x >> 4) + 1, y >> 2)) {
						gameData->ballVel.x = -gameData->ballVel.x;
					}
				}
			} else if ((y & 3) == 3) {
				// printf("upper");
				// Touching upper edge of block
				// gameData->redraw = 1;
				if (phy_hit_block(gameData, x >> 4, (y >> 2) + 1)) {
					gameData->ballVel.y = -gameData->ballVel.y;
				}
				if ((x & 15) == 1) {
					// Left corner
					if (phy_hit_block(gameData, (x >> 4) - 1, y >> 2)) {
						gameData->ballVel.x = -gameData->ballVel.x;
					}
				} else if ((x & 15) == 14) {
					// Right corner
					if (phy_hit_block(gameData, (x >> 4) + 1, y >> 2)) {
						gameData->ballVel.x = -gameData->ballVel.x;
					}
				}
			} else if ((x & 15) == 1) {
				// Right edge
				if (phy_hit_block(gameData, (x >> 4) - 1, y >> 2)) {
					gameData->ballVel.x = -gameData->ballVel.x;
				}
			} else if ((x & 15) == 14) {
				// Left edge
				if (phy_hit_block(gameData, (x >> 4) + 1, y >> 2)) {
					gameData->ballVel.x = -gameData->ballVel.x;
				}
			}
		}
	}
	if (x == 0 || x == width - 2) {
		gameData->ballVel.x = -gameData->ballVel.x;
		gameData->redraw = 1;
	}


}

char phy_hit_block(GameData *gameData, int x, int y) {
	int type;

	if (x > 15 || x < 0 || y > 14 || y < 0) {
		return 0;
	}

	for (type = 3; type >= 0; --type) {
		if (gameData->blockData[type][y][x >> 3] & 0x80 >> (x & 0x07)) {
			// if (type == 3)
			// {
			// 	printf("Type = %d   x & 0x07 = %d   0x80 >> (x & 0x07) = %d   gameData->blockData[type][y][x >> 3] = %d   gameData->blockData[type][y][x >> 3] & 0x80 >> (x & 0x07) = %d", type, (int) (x & 0x07), (int) (0x80 >> (x & 0x07)), (int) gameData->blockData[type][y][x >> 3], (int) (gameData->blockData[type][y][x >> 3] & 0x80 >> (x & 0x07)));
			// }
			// Block exists
			// printf("type=%d", type);
			gameData->blockData[type][y][x >> 3] &= ~(0x80 >> (x & 0x07));	// Delete block
			gameData->blockHit = type << 8;
			// printf("     %d", gameData->blockHit);
			gameData->blockHit |= y << 4;
			// printf("          %d", gameData->blockHit);
			gameData->blockHit |= x;
			// printf("               %d", gameData->blockHit);
			if (type) {	// type != 0
				gameData->blockData[type - 1][y][x >> 3] |= 0x80 >> (x & 0x07);	// Add block with lower type
			}
			gameData->redraw = 1;
			return 1;
		}
	}
	return 0;
}