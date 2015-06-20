#if defined(_Z8F6403)
#include <ez8.h>
#include "hw_time.h"
#include "sound_lib.h"

int _soundCount;
int _soundDuration;

void hw_sound_init() {
	_soundCount = 0;
	_soundDuration = 0;

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
	// T2PWMH = 0x00;
	// T2PWML = 0xA4;

	// Enable alternate function
	PCAF |= 0x80;

	// Enable timer2
	// T2CTL |= 0x80;

	// // Setup timer 3 (sound update)
	// // TEN: 0, TPOL: 0, PRES: 7 (128), TMODE: 1 (cont.)
	// T3CTL = 0x39;

	// // Begin timer at 0
	// T3H = 0;
	// T3L = 0;

	// // End timer at 2250 (64 Hz)
	// T3RH = 0x11;
	// T3RL = 0x94;

	// // Enable timer3 interrupt
	// IRQ2 |= 0x80;

	// // Set priority to LOW
	// IRQ2ENH &= 0x7F;
	// IRQ2ENL |= 0x80;

	// // Enable timer1
	// T3CTL |= 0x80;

	// SET_VECTOR(TIMER3, ISR_T3);
	// EI();
}

void hw_sound_update() {
	if (_LEDflag) {
		++_soundCount;
		if (_soundCount > _soundDuration) {
			T2CTL = 0x3B; // Disable PWM generator
		}
	}

}

void hw_sound_play(int freq, int width, int dur) {
	int reload = 144000 / freq; // Calculate reload value from clock freq
	int pwm = reload * width / 100; // Calculate PWM reload

	T2CTL  = 0xB9; // Enable PWM generator
	T2RH    = reload >> 8;
	T2RL    = reload & 0xFF;
	T2PWMH = pwm >> 8;
	T2PWML = pwm & 0xFF;

	_soundDuration = dur;
	_soundCount = 0;
}

#endif

#if defined(__APPLE__) || defined(__WIN32__)
void hw_sound_init() {};

void hw_sound_update() {};

void hw_sound_play(int freq, int width, int dur) {};
#endif

