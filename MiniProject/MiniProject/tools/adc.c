#include <stdio.h>
#include <avr/io.h>
#include "../include/usart.h"

#define F_CPU 16000000UL
#include "util/delay.h"
#define LIGHT_SENSOR_CHANNEL 0
#define THRESHOLD 365

void adc_init() {
	usart_init();
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read(uint8_t channel) {
	ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADC;
}

char buffer[32];
int adc_coverd() {
	
	uint16_t sensorValue = adc_read(LIGHT_SENSOR_CHANNEL);
	sprintf(buffer, "adc: %u\n", sensorValue);
	usart_send_string(buffer);
	if (sensorValue < THRESHOLD) {
		return 1;
	} else {
		return 0;	
	}
}