/*
 #  #     #    ###    ###    #   #    #    ###    ####           ##     ##    #  #   #  #   ###
 #  #    # #   #  #   #  #   #   #   # #   #  #   #             #  #   #  #   #  #   ## #   #  #
 ####   #   #  #  #   #  #   # # #  #   #  #  #   ###            #     #  #   #  #   # ##   #  #
 #  #   #####  ###    #  #   # # #  #####  ###    #               #    #  #   #  #   #  #   #  #
 #  #   #   #  #  #   #  #   ## ##  #   #  #  #   #             #  #   #  #   #  #   #  #   #  #
 #  #   #   #  #  #   ###    #   #  #   #  #  #   ####           ##     ##     ##    #  #   ###
*/

#if defined(_Z8F6403)
#include <ez8.h>
#include "hw_time.h"
#include "sound_lib.h"

// Global variables used to avoid having to pass pointers to placeholders for hardware specific variables all the way from main
int _soundIndex;	// How far we are in playing the current sound effect
int _musicIndex;	// How far we are in playing the current background music track
char _fxMode;	// Flag determining whether to play a sound effect (1) or the background music (0)
char _soundId;		// Which sound effect to play
char _musicId;		// Which music track to play
char _mute;         // Mutes music

#pragma interrupt
void ISR_T3() {
	if (_fxMode) {
		if (soundFX[_soundId][_soundIndex][0] == 1) {
			// Enable sound generator
			T2CTL  = 0xBB;
			// Reset
			T2H = 0;
			T2L = 0;
			// Set reload and PWM
			T2RH   = soundFX[_soundId][_soundIndex][1];
			T2RL   = soundFX[_soundId][_soundIndex][2];
			T2PWMH = soundFX[_soundId][_soundIndex][3];
			T2PWML = soundFX[_soundId][_soundIndex][4];
		} else if (soundFX[_soundId][_soundIndex][0] == 3) {
			_fxMode = 0;
		} else {
			// Disable sound generator
			T2CTL = 0x3B;
		}

		++_soundIndex;
		if (_soundIndex == 7) {
			// Switch to playing music upon reaching end of sound
			_fxMode = 0;
			T2CTL = 0x3B;
		}
	} else if (!_mute) {
		if (music[_musicId][_musicIndex][0] == 1) {
			// Enable sound generator
			T2CTL  = 0xBB;
			// Reset
			T2H = 0;
			T2L = 0;
			// Set reload and PWM
			T2RH   = music[_musicId][_musicIndex][1];
			T2RL   = music[_musicId][_musicIndex][2];
			T2PWMH = music[_musicId][_musicIndex][3];
			T2PWML = music[_musicId][_musicIndex][4];
		} else if (music[_musicId][_musicIndex][0] == 0) {
			// Disable sound generator
			T2CTL = 0x3B;
		}
	}

	++_musicIndex;
	// Apply modulus on music index to loop around
	_musicIndex &= 0x7F;
}

void hw_sound_init() {
	_soundIndex = 0;
	_musicIndex = 0;
	_fxMode = 0;
	_soundId = 0;
	_musicId = 0;

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

void hw_sound_play(int which) {
	_soundId = which;
	// Switch to playing sound and reset index
	_fxMode = 1;
	_soundIndex = 0;
}

void hw_sound_mute() {
	T2CTL = 0x3B;
	_mute = 1;
}

void hw_sound_set_music(int which) {
	_musicId = which;
	_musicIndex = 0;
	_mute = 0;
}

#else
void hw_sound_init() {};

void hw_sound_mute() {};

void hw_sound_play(int which) {};

void hw_sound_set_music(int which) {};

#endif