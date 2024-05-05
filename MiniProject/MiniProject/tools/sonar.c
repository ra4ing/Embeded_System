#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#define F_CPU 16000000UL
#include "util/delay.h"
#include "../include/usart.h"
#include "../include/rgb.h"

#define LED_PIN PORTB5
#define TRIGGER_PIN PORTD6
#define ECHO_PIN PORTD2

char buffer[32];
volatile uint16_t overflow_count = 0;
volatile uint16_t distance = 0;

void signal_init() {
	DDRB |= (1 << LED_PIN); // set output
}

void signal_on() {
	PORTB |= (1 << LED_PIN);
}

void signal_off() {
	PORTB &= ~(1 << LED_PIN);
}

void sonar_init() {
	signal_init();
	rgb_init();
	usart_init();
	DDRD |= (1 << TRIGGER_PIN); // set trigger output
	DDRD &= ~(1 << ECHO_PIN); // set echo input
	PORTD |= (1 << ECHO_PIN); // set echo high as default

	EICRA |= (1 << ISC00);
	EIMSK |= (1 << INT0); // interrupt

	TCCR2B |= (1 << CS20); // not scale
	TIMSK2 |= (1 << TOIE2);
	
	sei(); // start interrupt
}

void sonar_trigger() {
	PORTD |= (1 << TRIGGER_PIN); // trigger sonar
	_delay_us(10);
	PORTD &= ~(1 << TRIGGER_PIN);
	_delay_ms(60);
}

char buffer[32];

ISR(INT0_vect) {
	if (PIND & (1 << ECHO_PIN)) {
		TCNT2 = 0; // reset timer
		overflow_count = 0;
	} else {
		uint16_t total_count = TCNT2 + overflow_count * 256;
		distance = total_count / 58; // calculate distance
		sprintf(buffer, "distance: %u\n", distance);
		usart_send_string(buffer);
		if (distance < 150) {
			rgb_blue();
			signal_on();
			//_delay_ms(5000);
		} else {
			signal_off();
		}
	}
}

ISR(TIMER2_OVF_vect) {
	overflow_count++; // Makes up for the insufficient number of bits in the TIMER0 register
}