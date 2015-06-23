#if defined(__APPLE__) || defined(__WIN32__)
#include <stdio.h>
#endif

#if defined(_Z8F6403)
#include <sio.h>
#endif

#include "ansi.h"
#include "physics.h"
#include "util.h"
#include "game_data.h"
#include "hw_sound.h"

void phy_simulate(GameData *gameData, char *lostBall) {
	unsigned char x, y, sp;
	char justHitBlock, reverseX, reverseY;
	int dx, dy, halfSize;

	// Correct ball velocity by speed factor
	dx = (int) (gameData->ballSpeed * gameData->ballVel.x);
	dy = (int) (gameData->ballSpeed * gameData->ballVel.y);

	// Adjust for the rectangular 'pixels'
	gameData->ballPos.x += shift_fix_int_right(dx * 8, 4);
	gameData->ballPos.y += shift_fix_int_right(dy * 5, 4);

	// Round position to nearest pixel
	x = (unsigned char) (gameData->ballPos.x >> 8);
	y = (unsigned char) (gameData->ballPos.y >> 8);

	if (y == 0) {

		//////////////////////
		// Bounced top wall //
		//////////////////////

		hw_sound_play(0);

		if (!gameData->bouncedTop) {	// Only if it didn't already bounce the top in the last iteration
			gameData->ballVel.y = -gameData->ballVel.y;	// Reverse y velocity
			gameData->redraw = 1;	// Forces ball to be redrawn at current position, to make sure it is seen as close enough to the wall
			gameData->bouncedTop = 1;
		}

	} else {

		gameData->bouncedTop = 0;

		if (!gameData->bouncedStriker && y == striker_height - 1 && x >= (gameData->strikerPos >> 8) - (gameData->strikerSize >> 1) + 1 && x <= (gameData->strikerPos >> 8) + (gameData->strikerSize >> 1) && !(gameData->ballVel.y & 0x80)) {

			/////////////////////
			// Bounced striker //
			/////////////////////

			hw_sound_play(0);

			gameData->multiplier = 0;
			gameData->bouncedStriker = 1;	// Used to avoid hitting striker twice in a row
			gameData->redraw = 1;

			sp = (unsigned char) (gameData->strikerPos >> 8);	// Round striker position to nearest pixel
			halfSize = gameData->strikerSize >> 1;	// Half of the total striker length - this value is used a lot, so calculated here for efficiency and brevity

			// Bounce ball by reversing y coordinate
			gameData->ballVel.y = -gameData->ballVel.y;

			// Give the ball a boost upwards
			gameData->ballVel.y -= gameData->bouncinessFactor;

			if (gameData->ballVel.y < -(char)100) {
				// Velocity should not become grater that 100 (ballVel can store a range of -127 to 128)
				gameData->ballVel.y = -(char)100;
			}

			// Check striker zones:
			if (x <= sp - halfSize + (halfSize >> 2) + 1) {

				// Far left

				util_rotate(&gameData->ballVel, -43);	// rotate ~30 deg left

			} else if (x <= sp - halfSize + (halfSize >> 1) + 1) {

				// Middle left

				util_rotate(&gameData->ballVel, -21);	// rotate ~15 deg left

			} else if (x < sp + halfSize - (halfSize >> 1) + 1) {

				// Center - just bounce

			} else if (x < sp + halfSize - (halfSize >> 2) + 1) {

				// Middle right

				util_rotate(&gameData->ballVel, 21);	// rotate ~15 deg right

			} else {

				// Far right

				util_rotate(&gameData->ballVel, 43);	// rotate ~30 deg right

			}

			// Make sure ball goes upwards (might have rotated too much)
			if (gameData->ballVel.y > 0)	{
				gameData->ballVel.y = -gameData->ballVel.y;
			}

			// Make sure angle gets no less than approx. 15 degrees:
			if (gameData->ballVel.x > 0) {
				if (gameData->ballVel.x >> 2 > -gameData->ballVel.y) { // x vel is more than 4 times y vel
					gameData->ballVel.x = -gameData->ballVel.y << 2; // set x vel to 4 times y vel
				}
			} else if (-gameData->ballVel.x >> 2 > -gameData->ballVel.y) { // x vel is more than 4 times y vel
				gameData->ballVel.x = gameData->ballVel.y << 2; // set x vel to 4 times y vel
			}

		} else if (y == striker_height) {

			// Check if ball hit the striker on the side, and bounce it away - this can't save the ball but looks more realistic

			if (x == (gameData->strikerPos >> 8) - (gameData->strikerSize >> 1) || x == (gameData->strikerPos >> 8) + (gameData->strikerSize >> 1) + 1) {
				// Hit side of striker
				gameData->ballVel.x = -gameData->ballVel.x;
			}
		} else if (y > striker_height + 2) {

			///////////////
			// Lost ball //
			///////////////

			hw_sound_play(13);

			// Reset position to striker and decrease velocity
			gameData->ballPos.x = gameData->strikerPos;
			gameData->ballPos.y = 90 << 8;
			gameData->ballVel.x = gameData->ballVel.x >> 1;

			// Only decrease y velocity to a minumum of 32
			if (gameData->ballVel.y > 50) {
				gameData->ballVel.y = -(gameData->ballVel.y >> 1);
			} else {
				gameData->ballVel.y = -50;
			}

			*lostBall = 1;

		} else {

			// Reset bouncedStriker flag if ball is above striker
			gameData->bouncedStriker = y >= striker_height - 1;

			//////////////////////////
			// Check for block hits //
			//////////////////////////

			// Flags to reverse ball direction. These only have effect if the ball was not touching a block in the last iteration
			reverseX = 0;
			reverseY = 0;

			justHitBlock = 0;	// Flag to see if a block is touched in this iteration

			if (y <= 60) {	// Ball is inside the block area
				if ((y & 3) == 0) {

					// Potentially touching lower edge of block

					if (phy_hit_block(gameData, x >> 4, (y >> 2) - 1, &justHitBlock)) {

						go_to_xy(200, 30);
						printf("Lower                          ");

						// Hitting block

						reverseY = 1;

						if ((x & 15) == 15) {
							go_to_xy(200, 30);
							printf("Lower overlap both corners           ");

							// Also hitting corner of right block because ball is two pixels wide

							phy_hit_block(gameData, (x >> 4) + 1, (y >> 2) - 1, &justHitBlock);
						}
					} else if ((x & 15) == 15 && phy_hit_block(gameData, (x >> 4) + 1, (y >> 2) - 1, &justHitBlock)) {
						go_to_xy(200, 30);
						printf("Lower overlap to right                          ");

						// Hitting corner of right block because ball is two pixels wide

						reverseY = 1;
					}

					if ((x & 15) == 1) {
						go_to_xy(200, 30);
						printf("Lower corner to left                          ");

						// Left corner

						if (phy_hit_block(gameData, (x >> 4) - 1, y >> 2, &justHitBlock)) {
							go_to_xy(200, 30);
							printf("Lower corner to left - hit                          ");

							// Hitting left block

							reverseX = 1;
						}
					} else if ((x & 15) == 14) {
						go_to_xy(200, 30);
						printf("Lower corner to right                          ");

						// Right corner

						if (phy_hit_block(gameData, (x >> 4) + 1, y >> 2, &justHitBlock)) {
							go_to_xy(200, 30);
							printf("Lower corner to right - hit                          ");

							// Hitting right block

							reverseX = 1;
						}
					}

					//  else if ((x & 15) == 15) {

					// 	//

					// 	if (phy_hit_block(gameData, (x >> 4) + 1, y >> 2, &justHitBlock)) {
					// 		reverseX = 1;
					// 	}
					// }

				} else if ((y & 3) == 3) {

					// Potentially touching upper edge of block

					if (phy_hit_block(gameData, x >> 4, (y >> 2) + 1, &justHitBlock)) {
						go_to_xy(200, 30);
						printf("Upper                          ");

						// Hitting block

						reverseY = 1;

						if ((x & 15) == 15) {
							go_to_xy(200, 30);
							printf("Upper overlap both corners                          ");

							// Also hitting corner of right block because ball is two pixels wide

							phy_hit_block(gameData, (x >> 4) + 1, (y >> 2) + 1, &justHitBlock);
						}

					} else if ((x & 15) == 15 && phy_hit_block(gameData, (x >> 4) + 1, (y >> 2) + 1, &justHitBlock)) {
						go_to_xy(200, 30);
						printf("Upper overlap to right                          ");

						// Hitting corner of right block because ball is two pixels wide

						reverseY = 1;
					}

					if ((x & 15) == 1) {
						go_to_xy(200, 30);
						printf("Upper corner to left                         ");

						// Left corner

						if (phy_hit_block(gameData, (x >> 4) - 1, y >> 2, &justHitBlock)) {
							go_to_xy(200, 30);
							printf("Upper corner to left - hit                         ");
							reverseX = 1;
						}

					} else if ((x & 15) == 14) {
						go_to_xy(200, 30);
						printf("Upper corner to right                         ");

						// Right corner

						if (phy_hit_block(gameData, (x >> 4) + 1, y >> 2, &justHitBlock)) {
							go_to_xy(200, 30);
							printf("Upper corner to right - hit                         ");
							reverseX = 1;
						}

					}

				} else if ((x & 15) == 1) {
					go_to_xy(200, 30);
					printf("Right edge                         ");

					// Right edge

					if (phy_hit_block(gameData, (x >> 4) - 1, y >> 2, &justHitBlock)) {
						go_to_xy(200, 30);
						printf("Right edge - hit                         ");
						reverseX = 1;
					}

				} else if ((x & 15) == 14) {
					go_to_xy(200, 30);
					printf("Left edge                         ");

					// Left edge

					if (phy_hit_block(gameData, (x >> 4) + 1, y >> 2, &justHitBlock)) {
						go_to_xy(200, 30);
						printf("Left edge - hit                         ");
						reverseX = 1;
					}

				}

				// Reverse ball velocity in x and y directions according to the respective flags,
				// but only if the ball was not touching a block in the last iteration
				if (!gameData->blockHit[2]) {
					if (reverseY) {
						gameData->ballVel.y = -gameData->ballVel.y;
					}
					if (reverseX) {
						gameData->ballVel.x = -gameData->ballVel.x;
					}
				}

				// Set the blockHit flag according to whether or not the ball was touching a block in this iteration
				gameData->blockHit[2] = justHitBlock;
			}
		}

		if (x == 0 || x == game_width - 2) {

			///////////////////////
			// Bounced side wall //
			///////////////////////

			hw_sound_play(0);

			if (!gameData->bouncedSide) {	// Only if it didn't already bounce a side wall in the last iteration
				gameData->ballVel.x = -gameData->ballVel.x;
				gameData->redraw = 1;	// Forces ball to be redrawn at current position, to make sure it is seen as close enough to the wall
				gameData->bouncedSide = 1;
			}
		} else {
			gameData->bouncedSide = 0;
		}
	}
}

char phy_hit_block(GameData *gameData, int x, int y, char *justHitBlock) {

	// Takes the x and y position of a block in column/row format (i.e. not pixel position).
	// Returns 1 if the block exists, unless blockHis[2] from blockData is 1,
	// which means that a block was touched in the last iteration, so the function always returns 0.
	// If a block exists at the specified position, it is decremented (damaged) or destoyed,
	// according to its type, and the value of justHitBlock is set to 1,
	// indicating that at least one block was touched in this iteration.
	// Furthermore, one of the first two values in blockHit is encoded with the block data,
	// marking the block for removal/redrawing.

	int type, numBlock;

	if (x > 15 || x < 0 || y > 14 || y < 0) {
		// Outside block area
		return 0;
	}

	numBlock = gameData->blockHit[0] > 0;	// If there's already a block in blockHit[0] use index 1

	type = (x & 1) ? gameData->blockData[y][x >> 1] & 0xF : gameData->blockData[y][x >> 1] >> 4;	// Value corresponding to current block in blockData (each blockData byte stores two blocks, one in each nibble)

	if (type) {	// Block exists - damage or remove

		if (!gameData->blockHit[2]) {	// Only if a block was not hit last iteration

			hw_sound_play(2 + (gameData->multiplier > 6 ? 6 : gameData->multiplier));

			if (type != 11) {	// Only if block is destructible

				++gameData->multiplier;	// Increment multiplier

				if (type != 1 && type != 2 && type != 4 && type != 7) {	// Block has a hardened surface (only gets damaged)

					gameData->blockData[y][x >> 1] -= (x & 1) ? 0x01 : 0x10; 	// Decrements value on left or right block
					--type;

				} else {	// Mark for demolition

					gameData->blockData[y][x >> 1] &= (x & 1) ? 0xF0 : 0x0F; 	// Sets value on left or right block to zero (no block)
					type = 0;

				}

				// Encode block data in blockHit
				gameData->blockHit[numBlock] = type << 8; // Stores type value in blockHit bit 8-11
				gameData->blockHit[numBlock] |= y << 4; // Stores y coordinate in bit 4-7
				gameData->blockHit[numBlock] |= x; // Stores x coordinate in bit 0-3
			}
			gameData->redraw = 1; // Redraw ball for nice gfx!
		}

		*justHitBlock = 1;
		return !gameData->blockHit[2];
	}
	return 0;
}

void phy_update_bullets(GameData *gameData, AnimationData *animationData) {
	int i, j, k, blockX, blockY, blockType, numBlock;
	for (i = 0; i < 5; ++i) {
		if (animationData->projectileType[i] >= 0) {	// Bullet exists
			if (animationData->projectilePos[i][1] <= 60 // Bullet is inside the block area
			        && (animationData->projectilePos[i][1] & 3) == 0) {	// Bullet is potentially touching lower edge of block
				blockX = animationData->projectilePos[i][0] >> 4;
				blockY = (animationData->projectilePos[i][1] >> 2) - 1;
				blockType = (blockX & 1) ? gameData->blockData[blockY][blockX >> 1] & 0xF : gameData->blockData[blockY][blockX >> 1] >> 4;	// Value corresponding to current block in blockData
				numBlock = gameData->blockHit[0] > 0;	// If there's already a block in blockHit[0] use index 1

				if (blockType) {

					// Block exists

					if (animationData->projectileType[i] == 0) {

						/////////////////
						// Lvl 1 laser //
						/////////////////

						if (blockType != 11) {

							// Only if block is destructible

							if (blockType != 1 && blockType != 2 && blockType != 4 && blockType != 7) {

								// Block has a hardened surface (only gets damaged)

								gameData->blockData[blockY][blockX >> 1] -= (blockX & 1) ? 0x01 : 0x10; 	// Decrements value on left or right block
								--blockType;

							} else {

								// Mark for demolition

								gameData->blockData[blockY][blockX >> 1] &= (blockX & 1) ? 0xF0 : 0x0F; 	// Sets value on left or right block to zero (no block)
								blockType = 0;

							}
						}

						// Encode block data in blockHit
						gameData->blockHit[numBlock] = blockType << 8; // Stores type value in blockHit bit 8-11
						gameData->blockHit[numBlock] |= blockY << 4; // Stores y coordinate in bit 4-7
						gameData->blockHit[numBlock] |= blockX; // Stores x coordinate in bit 0-3

					} else if (animationData->projectileType[i] == 1) {

						/////////////////
						// Lvl 2 laser //
						/////////////////

						// Mark for demolition
						gameData->blockData[blockY][blockX >> 1] &= (blockX & 1) ? 0xF0 : 0x0F; 	// Sets value on left or right block to zero (no block)
						blockType = 0;

						// Encode block data in blockHit
						gameData->blockHit[numBlock] = blockType << 8; // Stores type value in blockHit bit 8-11
						gameData->blockHit[numBlock] |= blockY << 4; // Stores y coordinate in bit 4-7
						gameData->blockHit[numBlock] |= blockX; // Stores x coordinate in bit 0-3

					} else if (animationData->projectileType[i] == 2) {

						////////////
						// Rocket //
						////////////

						animationData->rocketHit[0] = blockX;
						animationData->rocketHit[1] = blockY;
						animationData->rocketHit[2] = 1;

						for (j = -1; j < 2; ++j) {
							if (blockX + j >= 0 && blockX + j < 16) {
								for (k = -1; k < 2; ++k) {
									if (blockY + k >= 0 && blockY + k < 15) {
										// Mark for demolition
										gameData->blockData[(blockY + k)][(blockX + j) >> 1] &= ((blockX + j) & 1) ? 0xF0 : 0x0F; 	// Sets value on left or right block to zero (no block)
									}
								}
							}
						}
					}

					hw_sound_play(14);

					animationData->eraseProjectile[i] = 1;
				}
			}
			if (animationData->projectilePos[i][1] < 2) {
				animationData->eraseProjectile[i] = 1;
			}
			--animationData->projectilePos[i][1];
		}
	}
}

void phy_move_striker(GameData * gameData, PlayerData * playerData, unsigned char input) {
	int analog = (((int) input - 127) << 1) - 96;
	if (analog < -(int)160) analog = -(int)160;
	else if (analog > -5 && analog < 5) analog = 0;
	analog *= gameData->strikerSpeed;
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
	playerData->energy -= analog < 0 ? -analog >> 6 : analog >> 6;
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