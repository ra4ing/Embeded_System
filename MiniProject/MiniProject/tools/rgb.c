#include <avr/io.h>
#define RED PINB2
#define BLUE PINB3
#define GREEN PINB4



void rgb_init() {
	DDRB |= 1 << RED;
	DDRB |= 1 << GREEN;
	DDRB |= 1 << BLUE;
}

void rgb_off() {
	PORTB &= ~(1 << RED);
	PORTB &= ~(1 << GREEN);
	PORTB &= ~(1 << BLUE);
}

void rgb_red() {
	rgb_off();
	PORTB |= 1 << RED;
}

void rgb_green() {
	rgb_off();
	PORTB |= 1 << GREEN;
}

void rgb_blue() {
	rgb_off();
	PORTB |= 1 << BLUE;
}

