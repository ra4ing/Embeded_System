#define F_CPU 16000000UL
#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTB0
#define EN eS_PORTB1


#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "../include/lcd_library.h"




void lcd_init() {
	DDRD = 0xFF;
	DDRB = 0xFF;
	Lcd8_Init();
}

void lcd_set_cursor(int row, int col) {
	Lcd8_Set_Cursor(row, col);
}

void lcd_write(char* str) {
	Lcd8_Write_String(str);
}

void lcd_clear() {
	Lcd8_Clear();
}

void lcd_print_close() {
	lcd_clear();
	lcd_set_cursor(0, 0);
	lcd_write("   <(- _ -)>   ");
	lcd_set_cursor(2, 0);
	lcd_write("state: close");
}

void lcd_print_open() {
	lcd_clear();
	lcd_set_cursor(0, 0);
	lcd_write("  (O ^ _ ^ O) ");
	lcd_set_cursor(2, 0);
	lcd_write("state: open");
}