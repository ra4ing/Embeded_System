#include <avr/io.h>
#define F_CPU 16000000UL

void timer_init() {
	uint16_t delay_ms = 1;
	TCCR0A = 0; // normal mode
	TCCR0B = (1 << CS02) | (1 << CS00); // scale = 1024

	uint8_t initial_count = 256 - ((delay_ms * F_CPU) / 1024);
	TCNT0 = initial_count;
}


void timer_exec(void (*func)(void), int sec) {
	timer_init();
	for (int i=0; i<sec; i++) {
		while((TIFR0 & (1 << TOV0)) == 0) {
			func();
		}
		TIFR0 = (1 << TOV0);
	}
}
