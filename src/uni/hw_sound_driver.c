void hw_sound_init() {
#if defined(_Z8F6403)
	// Setup timer 2 (sound)
	// TEN: 0, TPOL: 0, PRES: 0 (1), TMODE: 3 (PWM)
	T2CTL = 0x03;

	// Begin timer at 0
	T2H = 0;
	T2L = 0;

	// End timer at 1843 (1 kHz)
	T2RH = 0x01;
	T2RL = 0x47;

	// Enable timer2
	T2CTL |= 0x80;

	// 50% duty cycle
	T2PWMH = 0xA4;
	T2PWML = 0x00;
#endif
}
