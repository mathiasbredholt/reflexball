// #if defined(_Z8F6403)
// #include <ez8.h>
// #include "hw_time.h"

// int _soundCount;
// int _soundDuration;
// int _reload;
// int _PWM;

// #pragma
// void ISR_T3() {
// 	T3RH    = _reload >> 8;
// 	T3RL    = _reload & 0xFF;
// 	T3PWMH =  _PWM >> 8;
// 	T3PWML =  _PWM & 0xFF;
// 	T3CTL |=  0x80; // Enable PWM generator
// }

// void hw_sound_init() {
// 	_soundCount = 0;
// 	_soundDuration = 0;

// 	_reload = 20945; // 440 Hz
// 	_PWM = 10472; // 50% duty cycle

// 	// Setup timer 3 (sound generator)
// 	// TEN: 0, TPOL: 0, PRES: 1 (2), TMODE: 3 (PWM)
// 	T3CTL = 0x8B;

// 	T3H = 0;
// 	T3L = 0;
// 	T3RH   = _reload >> 8;
// 	T3RL   = _reload & 0xFF;
// 	T3PWMH =  _PWM >> 8;
// 	T3PWML =  _PWM & 0xFF;

// 	// Enable alternate function
// 	PDAF |= 0x02;

// 	// // Enable timer3 interrupt
// 	IRQ2 |= 0x80;

// 	// // Set priority to HIGH
// 	IRQ2ENH |= 0x80;
// 	IRQ2ENL |= 0x80;

// 	// // Enable timer3
// 	 T3CTL |= 0x80;

// 	SET_VECTOR(TIMER3, ISR_T3);
// 	EI();
// }

// void hw_sound_update() {
// 	if (hw_time_get_LEDflag()) {
// 		hw_time_set_LEDflag(0);
// 		++_soundCount;
// 		if (_soundCount > _soundDuration) {
// 			T3CTL &= 0x7F; // Disable PWM generator
// 		}
// 	}

// }

// void hw_sound_play(int freq, int width, int dur) {
// 	int reload = 9216000 / freq; // Calculate reload value from clock freq
// 	int pwm = reload * width / 100; // Calculate PWM reload


// 	_soundDuration = dur;
// 	_soundCount = 0;
// }

// #endif

// #if defined(__APPLE__) || defined(__WIN32__)
// void hw_sound_init() {};

// void hw_sound_update() {};

// void hw_sound_play(int freq, int width, int dur) {};
// #endif
