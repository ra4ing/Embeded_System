/*
 * MiniProject.c
 *
 * Created: 2023/11/2 16:36:54
 * Author : ra4ing
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include "util/delay.h"
#include "include/servo.h"
#include "include/usart.h"
#include "include/lcd.h"
#include "include/buzzer.h"
#include "include/rgb.h"
#include "include/button.h"
#include "include/sonar.h"
#include "include/adc.h"

void monitor_init() {
	buzzer_init();
	sonar_init();
	adc_init();
}

void monitor_work() {
	
	monitor_init();
	while (1) {
		sonar_trigger();
		
		if (adc_coverd()) {
			rgb_red();
			buzzer_on(2);
		} else {
			rgb_green();
			buzzer_off();
		}
	}
	
}

void litter_bin_init() {
	button_init();
	servo_init();
	lcd_init();
	
	servo_close();
	lcd_clear();
	lcd_print_close();
	
}

void litter_bin_work() {
	litter_bin_init();
	
	int is_open = 0;
	while (1) {
		/* ============== button ============== */
		if (button_wait()) {
			if (is_open) {
				servo_close();
				is_open = 0;
				lcd_print_close();
			} else {
				servo_open();
				is_open = 1;
				lcd_print_open();
			}
			_delay_ms(500);
		}
		
		/* ============== sonar ============== */
		if (pin_wait()) {
			servo_open();
			is_open = 1;
			lcd_print_open();
		}
		
		_delay_ms(100);
		
	}
}


//int main() {
	//int monitor = 1; 
	//
	//if (monitor) {	// used for monitor
		//monitor_work();
		//} else {	// used for trash bin
		//litter_bin_work(); 
	//}
	//
	//return 0;
//}

#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_Init() {
	ADMUX = (1 << REFS0); // 选择AVcc作为ADC参考
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (7 << ADPS0); // 使能ADC，使能ADC中断，设置预分频
}

ISR(ADC_vect) {
	uint16_t adc_value = ADC; // 读取ADC值
	// 处理ADC值...
}

int main(void) {
	ADC_Init(); // 初始化ADC
	sei(); // 全局使能中断
	ADCSRA |= (1 << ADSC); // 启动ADC转换

	while (1) {
		// 主循环
	}
}
