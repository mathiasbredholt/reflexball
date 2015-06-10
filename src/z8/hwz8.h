#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>

typedef struct Time {
	char hour, min, sec, cent;
} Time;

char readkey();

char waitForKey();

char updateKeys(char *lastInput, char *lastKeys);

void keysListener();

void displayColumn(int val, int col, int disp);

void LEDinit();

void LEDsetString(char string[]);

void LEDupdate();

void initTimer();

void startTimer();

void stopTimer();

void HWinit();

Time getTime();

void resetTimer();