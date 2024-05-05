 #ifndef  __usart__ 
 #define __usart__

void usart_init(void);
void usart_send(unsigned char);
unsigned char usart_receive(void);
void usart_send_string(char*);
void usart_receive_string(char*);

#endif