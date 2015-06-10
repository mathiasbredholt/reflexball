#include <sio.h>
#include <uart.h>
#include "ansi.h"
#include "util.h"
#include "car.h"
#include "hwz8.h"

void main() {
	HWinit();
	LEDsetString("Hejsa Dette er en lang streng    #nemt");

	printf("%d,   %d,   %d\n", sizeof (int), sizeof (long), sizeof (long long));

	while (1) {
		LEDupdate();
	}
}