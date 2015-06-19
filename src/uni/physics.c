#if defined(__APPLE__) || defined(__WIN32__)
#include <stdio.h>
#endif

#if defined(_Z8F6403)
#include <sio.h>
#endif

#include "ansi.h"
#include "physics.h"
#include "util.h"

#define width 256
#define height 96
#define striker_height 92
#define striker_speed 4

void phy_simulate(GameData *gameData) {
	unsigned char x, y, sp;
	char justHitBlock;
	int dx, dy, size;
	dx = (int) (gameData->ballSpeed * gameData->ballVel.x);
	dy = (int) (gameData->ballSpeed * gameData->ballVel.y);
	gameData->ballPos.x += shift_fix_int_right(dx * 8, 4);
	gameData->ballPos.y += shift_fix_int_right(dy * 5, 4);
	x = (unsigned char) (gameData->ballPos.x >> 8);
	y = (unsigned char) (gameData->ballPos.y >> 8);
	if (y == 0) {
		gameData->ballVel.y = -gameData->ballVel.y;
		gameData->redraw = 1;
	} else if (!gameData->bouncedStriker && y == striker_height - 1 && x >= (gameData->strikerPos >> 8) - (gameData->strikerSize >> 1) + 1 && x <= (gameData->strikerPos >> 8) + (gameData->strikerSize >> 1) && !(gameData->ballVel.y & 0x80)) {
		gameData->bouncedStriker = 1;
		gameData->redraw = 1;
		sp = (unsigned char) (gameData->strikerPos >> 8);
		size = gameData->strikerSize >> 1;
		gameData->ballVel.y = -gameData->ballVel.y;
		if (x <= sp - size + (size >> 2) + 1) {
			// Far left
			util_rotate(&gameData->ballVel, -43);	// ~30 deg
		} else if (x <= sp - size + (size >> 1) + 1) {
			// Middle left
			util_rotate(&gameData->ballVel, -21);	// ~15 deg
		} else if (x < sp + size - (size >> 1) + 1) {
			// Center
		} else if (x < sp + size - (size >> 2) + 1) {
			// Middle right
			util_rotate(&gameData->ballVel, 21);	// ~15 deg
		} else {
			// Far right
			util_rotate(&gameData->ballVel, 43);	// ~30 deg
		}
		if (gameData->ballVel.y > 0)	{
			gameData->ballVel.y = -gameData->ballVel.y;
		}
	} else if (y == striker_height) {
		if (x == (gameData->strikerPos >> 8) - (gameData->strikerSize >> 1) || x == (gameData->strikerPos >> 8) + (gameData->strikerSize >> 1) + 1) {
			// Hit side of striker
			gameData->ballVel.x = -gameData->ballVel.x;
		}
	} else if (y > striker_height + 2) {
		//Lost ball
		gameData->ballPos.x = 128 << 8;
		gameData->ballPos.y = 90 << 8;
		gameData->ballVel.y = -gameData->ballVel.y;
	} else if (gameData->ballVel.y == 0) {
		// Ball will be stuck - so we turn it slighly upwards
		gameData->ballVel.y = -1;
	} else {
		gameData->bouncedStriker = y >= striker_height - 1;

		if (y <= 60 && !gameData->blockHit[2]) {	// We already know that y!=0
			justHitBlock = 0;
			if ((y & 3) == 0) {
				// Touching lower edge of block
				if (phy_hit_block(gameData, x >> 4, (y >> 2) - 1, &justHitBlock)) {
					gameData->ballVel.y = -gameData->ballVel.y;
					if ((x & 15) == 15) {
						// Hitting corner of right block because ball is two pixels wide
						phy_hit_block(gameData, (x >> 4) + 1, (y >> 2) - 1, &justHitBlock);
					}
				} else if ((x & 15) == 15 && phy_hit_block(gameData, (x >> 4) + 1, (y >> 2) - 1, &justHitBlock)) {
					// Hitting corner of right block because ball is two pixels wide
					gameData->ballVel.y = -gameData->ballVel.y;
				}
				if ((x & 15) == 1) {
					// Left corner
					if (phy_hit_block(gameData, (x >> 4) - 1, y >> 2, &justHitBlock)) {
						gameData->ballVel.x = -gameData->ballVel.x;
					}
				} else if ((x & 15) == 14) {
					// Right corner
					if (phy_hit_block(gameData, (x >> 4) + 1, y >> 2, &justHitBlock)) {
						gameData->ballVel.x = -gameData->ballVel.x;
					}
				} else if ((x & 15) == 15) {
					if (phy_hit_block(gameData, (x >> 4) + 1, y >> 2, &justHitBlock)) {
						gameData->ballVel.x = -gameData->ballVel.x;
					}
				}
			} else if ((y & 3) == 3) {
				// printf("upper");
				// Touching upper edge of block
				// gameData->redraw = 1;
				if (phy_hit_block(gameData, x >> 4, (y >> 2) + 1, &justHitBlock)) {
					gameData->ballVel.y = -gameData->ballVel.y;
				}
				if ((x & 15) == 1) {
					// Left corner
					if (phy_hit_block(gameData, (x >> 4) - 1, y >> 2, &justHitBlock)) {
						gameData->ballVel.x = -gameData->ballVel.x;
					}
				} else if ((x & 15) == 14) {
					// Right corner
					if (phy_hit_block(gameData, (x >> 4) + 1, y >> 2, &justHitBlock)) {
						gameData->ballVel.x = -gameData->ballVel.x;
					}
				}
			} else if ((x & 15) == 1) {
				// Right edge
				if (phy_hit_block(gameData, (x >> 4) - 1, y >> 2, &justHitBlock)) {
					gameData->ballVel.x = -gameData->ballVel.x;
				}
			} else if ((x & 15) == 14) {
				// Left edge
				if (phy_hit_block(gameData, (x >> 4) + 1, y >> 2, &justHitBlock)) {
					gameData->ballVel.x = -gameData->ballVel.x;
				}
			}
			gameData->blockHit[2] = justHitBlock;
		}
	}
	if (x == 0 || x == width - 2) {
		gameData->ballVel.x = -gameData->ballVel.x;
		gameData->redraw = 1;
	}
}

void phy_move_striker(GameData *gameData, PlayerData *playerData, unsigned char input) {
	int analog = (((int) input - 127) << 1) - 96;
	if (analog < -(int)160) analog = -(int)160;
	else if (analog > -5 && analog < 5) analog = 0;
	analog *= striker_speed;
	if (gameData->strikerPos < ((unsigned int) gameData->strikerSize << 7) - analog) {
		gameData->strikerPos = (unsigned int) (gameData->strikerSize - 1) << 7;
	} else if (gameData->strikerPos > 0xFFFF - analog - ((unsigned int) (gameData->strikerSize) << 7)) {
		gameData->strikerPos = 0xFFFF - ((unsigned int) (gameData->strikerSize) << 7);
	} else {
		gameData->strikerPos += analog;
	}
	// printf("%8d", (((int) input - 127) << 1) - 96);
	// gameData->strikerPos += (((int) input - 127) << 1) - 96;
	playerData->oldEnergy = playerData->energy;
	playerData->energy -= analog < 0 ? -analog >> 3 : analog >> 3;
}

char phy_hit_block(GameData *gameData, int x, int y, char *justHitBlock) {
	int type, numBlock;

	if (x > 15 || x < 0 || y > 14 || y < 0) {
		return 0;
	}

	numBlock = gameData->blockHit[0] > 0;	// If there's already a block in blockHit[0] use index 1

	type = x & 1 ? gameData->blockData[y][x >> 1] & 0xF : gameData->blockData[y][x >> 1] >> 4;

	if (type) {	// Block exists - damage or remove
		if (type != 11) {	// Block is destructible
			if (type != 1 && type != 2 && type != 4 && type != 7) {	// Block has a hardened surface (only gets damaged)
				gameData->blockData[y][x >> 1] -= x & 1 ? 0x01 : 0x10; 	// Decrements value on left or right block
				--type;
			} else {	// Mark for demolition
				gameData->blockData[y][x >> 1] &= x & 1 ? 0xF0 : 0x0F; 	// Sets value on left or right block to zero (no block)
				type = 0;
			}
			gameData->blockHit[numBlock] = type << 8; // Stores type value in blockHit bit 8-11
			gameData->blockHit[numBlock] |= y << 4; // Stores y coordinate in bit 4-7
			gameData->blockHit[numBlock] |= x; // Stores x coordinate in bit 0-3
		}

		gameData->redraw = 1; // Redraw ball for nice gfx!
		*justHitBlock = 1;
		return 1;
	}
	return 0;
}

// char phy_hit_block(GameData *gameData, int x, int y) {
// 	int type, numBlock;

// 	if (x > 15 || x < 0 || y > 14 || y < 0) {
// 		return 0;
// 	}

// 	numBlock = gameData->blockHit[0] > 0;	// If there's already a block in blockHit[0] use index 1

// 	for (type = 10; type >= 0; --type) {
// 		if (gameData->blockData[type][y][x >> 3] & 0x80 >> (x & 0x07)) {
// 			// if (type == 3)
// 			// {
// 			// 	printf("Type = %d   x & 0x07 = %d   0x80 >> (x & 0x07) = %d   gameData->blockData[type][y][x >> 3] = %d   gameData->blockData[type][y][x >> 3] & 0x80 >> (x & 0x07) = %d", type, (int) (x & 0x07), (int) (0x80 >> (x & 0x07)), (int) gameData->blockData[type][y][x >> 3], (int) (gameData->blockData[type][y][x >> 3] & 0x80 >> (x & 0x07)));
// 			// }
// 			// Block exists
// 			// printf("type=%d", type);
// 			if (type != 10) {
// 				gameData->blockData[type][y][x >> 3] &= ~(0x80 >> (x & 0x07));	// Delete block
// 				if (type != 0 && type != 1 && type != 3 && type != 6) {	// type != 0
// 					gameData->blockData[type - 1][y][x >> 3] |= 0x80 >> (x & 0x07);	// Add block with lower type
// 				} else {
// 					type = 0;
// 				}
// 				gameData->blockHit[numBlock] = type << 8;
// 				// printf("     %d", gameData->blockHit[numBlock]);
// 				gameData->blockHit[numBlock] |= y << 4;
// 				// printf("          %d", gameData->blockHit[numBlock]);
// 				gameData->blockHit[numBlock] |= x;
// 				// printf("               %d", gameData->blockHit[numBlock]);
// 			}

// 			gameData->redraw = 1;
// 			return 1;
// 		}
// 	}
// 	return 0;
// }