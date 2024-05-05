#include <avr/io.h>
#include <avr/interrupt.h>

#define READ_PIN1 PINC5
#define READ_PIN2 PINC4

void button_init() {
	PORTC &= ~(1 << READ_PIN1); 
	DDRC &= ~(1 << READ_PIN1);
	
	PORTC &= ~(1 << READ_PIN2);
	DDRC &= ~(1 << READ_PIN2);
}

int button_wait() {
	if (PINC & (1 << READ_PIN1)) {
		return 1;
	}
	return 0;
}

int pin_wait() {
	if (PINC & (1 << READ_PIN2)) {
		return 1;
	}
	return 0;
}