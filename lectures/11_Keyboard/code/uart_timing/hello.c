#include "timer.h"
#include "uart.h"

void putchar(int c)
{
    uart_putchar(c);
}

void puts(char *s)
{
    while(*s)
        putchar(*s++);
}

void main (void)
{
    timer_init();
    uart_init(115200);

    while(1) {
        puts( "hello, laptop\n" );
        timer_delay(1);
    }
}
