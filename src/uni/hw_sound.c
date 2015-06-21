#if defined(_Z8F6403)
#include <ez8.h>
#include "hw_time.h"
#include "sound_lib.h"

int _soundIndex;
int _musicIndex;
char _soundNext;
char _soundMode;
char _soundId;

#pragma interrupt
void ISR_T3() {
	_soundNext = 1;
}

void hw_sound_init() {
	_soundIndex = 0;
	_soundNext = 0;
	_musicIndex = 0;
	_soundMode = 0;
	_soundId = 0;

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

	// Setup timer3
	// TEN: 0, TPOL: 0, PRES: 7 (128), TMODE: 1 (cont)
	T3CTL |= 0x39;

	// Reset
	T3H = 0;
	T3L = 0;

	// Reload at (16 Hz)
	T3RH   = 0x23;
	T3RL   = 0x28;

	// Enable timer3 interrupt
	IRQ2 |= 0x80;

	// Set priority to HIGH
	IRQ2ENH |= 0x80;
	IRQ2ENL |= 0x80;

	// Enable timer3
	T3CTL |= 0x80;

	SET_VECTOR(TIMER3, ISR_T3);
	EI();
}

void hw_sound_update() {
	if (_soundNext) {
		_soundNext = 0;

		if (_soundMode) {
			if (soundFX[_soundId][_soundIndex][0]) {
				T2CTL  = 0xBB; // enable sound generator
				T2H = 0;
				T2L = 0;
				T2RH   = soundFX[_soundId][_soundIndex][1];
				T2RL   = soundFX[_soundId][_soundIndex][2];
				T2PWMH = soundFX[_soundId][_soundIndex][3];
				T2PWML = soundFX[_soundId][_soundIndex][4];
			} else {
				T2CTL = 0x3B; // disable sound generator
			}


			++_soundIndex;
			if (_soundIndex == 7) {
				_soundMode = 0;
			}
		} else {
			if (bossTheme[_soundId][_soundIndex][0]) {
				T2CTL  = 0xBB; // enable sound generator
				T2H = 0;
				T2L = 0;
				T2RH   = bossTheme[_soundId][_soundIndex][1];
				T2RL   = bossTheme[_soundId][_soundIndex][2];
				T2PWMH = bossTheme[_soundId][_soundIndex][3];
				T2PWML = bossTheme[_soundId][_soundIndex][4];
			} else {
				T2CTL = 0x3B; // disable sound generator
			}
		}

		++_musicIndex;
		_musicIndex &= 0x7F;
	}
}

void hw_sound_play(int which) {
	_soundId = which;
	_soundMode = 1;
	_soundIndex = 0;
}

#endif

#if defined(__APPLE__) || defined(__WIN32__)
void hw_sound_init() {};

void hw_sound_update() {};

void hw_sound_play(int which);

#endif