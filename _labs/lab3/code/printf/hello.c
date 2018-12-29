#include "timer.h"
#include "uart.h"
#include "printf.h"

void main (void)
{
    uart_init();
    timer_delay(2);
    while(1) {
        printf( "hello, laptop\n" );
        timer_delay(1);
    }
}
