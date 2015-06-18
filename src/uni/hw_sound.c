#if defined(_Z8F6403)
#include <ez8.h>
#include "sound_lib.h"

char _soundNext;
int _soundIndex;

#pragma interrupt
void ISR_T3() {
	_soundNext = 1;
}

void hw_sound_init() {
	_soundNext = 0;
	_soundIndex = 0;

	// Setup timer 2 (sound generator)
	// TEN: 0, TPOL: 0, PRES: 7 (128), TMODE: 3 (PWM)
	T2CTL = 0x3B;

	// Begin timer at 0
	T2H = 0;
	T2L = 0;

	// End timer at 327 (440 Hz)
	T2RH = 0x01;
	T2RL = 0x47;

	// 50% duty cycle
	T2PWMH = 0x00;
	T2PWML = 0xA4;

	// Enable alternate function
	PCAF |= 0x80;

	// Enable timer2
	T2CTL |= 0x80;

	// Setup timer 3 (sound update)
	// TEN: 0, TPOL: 0, PRES: 7 (128), TMODE: 1 (cont.)
	T3CTL = 0x39;

	// Begin timer at 0
	T3H = 0;
	T3L = 0;

	// End timer at 2250 (64 Hz)
	T2RH = 0x08;
	T2RL = 0xCA;

	// Enable timer3 interrupt
	IRQ2 |= 0x80;

	// Set priority to LOW
	IRQ2ENH &= 0x7F;
	IRQ2ENL |= 0x80;

	// Enable timer1
	T3CTL |= 0x80;

	SET_VECTOR(TIMER3, ISR_T3);
	EI();
}

void hw_sound_update() {
	if (_soundNext) {
		_soundNext = 0;

		T2CTL  = chord[_soundIndex][0] ? 0xBB : 0x3B;
		T2H    = chord[_soundIndex][0];
		T2L    = chord[_soundIndex][0];
		T2PWMH = chord[_soundIndex][0];
		T2PWML = chord[_soundIndex][0];

		_soundIndex++;
		_soundIndex &= 0xF;
	}
}

#endif

#if defined(__APPLE__) || defined(__WIN32__)
void hw_sound_init() {};

void hw_sound_update() {};
#endif

