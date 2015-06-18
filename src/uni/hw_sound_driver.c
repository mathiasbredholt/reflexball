#if defined(_Z8F6403)
#include <ez8.h>

void hw_sound_init() {

	// Setup timer 2 (sound)
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
}
#endif
