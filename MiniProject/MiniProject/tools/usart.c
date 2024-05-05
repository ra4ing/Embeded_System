#include <avr/io.h>

#define F_CPU 16000000UL
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

void usart_init(void){
	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8); //set baud rate
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //enable transmit
	UCSR0C = (3<<UCSZ00); //set 8-bit (default)
}
void usart_send(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0))); // check if data is sent
	UDR0 = data; // load new data to transmit
}

unsigned char usart_receive(void){
	while(!(UCSR0A & (1<<RXC0))); // Wait to receive data
	return UDR0; // Read data from UDR
}

void usart_send_string(char* str) {
	for (int i = 0; str[i]; i++) {
		usart_send(str[i]);
	}
}

void usart_receive_string(char* str) {
	char c;
	int i = 0;
	for (i=0; i<32; i++) {
		c = usart_receive();
		if (c == '#') break;
		str[i] = c;
	}
	str[i] = '\0';
	usart_send_string(str);
}