#if defined(_Z8F6403)
#include <ez8.h>
#include "hw_time.h"
#include "sound_lib.h"

char _soundIndex;

#pragma interrupt
void ISR_T3() {
	++_soundIndex;
}

void hw_sound_init() {
	_soundIndex = 0;

	// Setup timer 2 (sound generator)
	// TEN: 0, TPOL: 0, PRES: 7 (128), TMODE: 3 (PWM)
	T2CTL = 0x3B;

	// Reset
	T2H = 0;
	T2L = 0;

	// Reload at 327 (440 Hz)
	T2RH   = 0x01;
	T2RL   = 0x47;

	// 50% duty cycle at 440 Hz
	T2PWMH = 0x00;
	T2PWML = 0xA3;

	// Enable alternate function
	PCAF |= 0x80;

	// Enable timer3
	// TEN: 0, TPOL: 0, PRES: 7 (128), TMODE: 1 (cont)
	T3CTL |= 0x39;

	// Reset
	T3H = 0;
	T3L = 0;

	// Reload at
	T3RH   = 0x08;
	T3RL   = 0xCA;

	// Enable timer3 interrupt
	IRQ2 |= 0x80;

	// Set priority to HIGH
	IRQ2ENH |= 0x80;
	IRQ2ENL &= 0x7F;

	SET_VECTOR(TIMER3, ISR_T3);
	EI();
}

void hw_sound_update() {
	T2H = 0;
	T2L = 0;
	T2RH    = chord[_soundIndex][1];
	T2RL    = chord[_soundIndex][2];
	T2PWMH = chord[_soundIndex][3];
	T2PWML = chord[_soundIndex][4];
	T2CTL  = chord[_soundIndex][0] ? 0xBB : 0x3B;

	_soundIndex++;
	_soundIndex &= 0xF;
}

#endif

#if defined(__APPLE__) || defined(__WIN32__)
void hw_sound_init() {};

void hw_sound_update() {};
#endif