#include <avr/io.h>

void servo_init() {
	DDRB |= 1 << PINB2; // Set pin 10 to output PWM
	TCCR1A |= (1 << WGM11) | (1 << COM1B1); // fast pwm mode
	TCCR1B |= (1 << WGM13) | (1 << WGM12) |(1 << CS11);

	ICR1 = 40000;
}

void  servo_open() {
	OCR1B = 2800;
}

void servo_close() {
	OCR1B = 1000;
}