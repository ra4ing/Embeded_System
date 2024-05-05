#ifndef __lcd__
#define __lcd__



void lcd_init(void);
void lcd_set_cursor(int, int);
void lcd_write(char*);
void lcd_clear(void);
void lcd_print_close(void);
void lcd_print_open(void);

#endif