#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "../include/timer.h"

void buzzer_init() {
	DDRB |= 1 << PINB1;

	TCCR1A |= (1 << WGM11) | (1 << COM1A1);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS10);
}

void buzzer_alert() {
	for(int i = 650; i < 2000; i += 10) { // frequency up
		ICR1 = F_CPU / i;
		OCR1A = ICR1 / 2; // 50% 
		_delay_ms(2);
	}

	for(int i = 2000; i > 650; i -= 10) { // frequency down
		ICR1 = F_CPU / i;
		OCR1A = ICR1 / 2; // 50%
		_delay_ms(2);
	}
}

void buzzer_off() {
	TCCR1A &= ~(1 << COM1A1); // turn off PWM output
	PORTB |= (1 <<PINB1);
}

void buzzer_on(int sec) {
	TCCR1A |= (1 << COM1A1);
	timer_exec(buzzer_alert, sec);
	buzzer_off();
}



