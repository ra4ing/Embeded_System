 #ifndef  __timer__
 #define __timer__


void timer_init();
void timer_exec(void (*func)(void), int);

#endif

