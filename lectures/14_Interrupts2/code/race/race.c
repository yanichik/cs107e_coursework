#include "timer.h"
#include "gpio.h"
#include "uart.h"
#include "armtimer.h"
#include "interrupts.h"
#include "assert.h"
#include "printf.h"

static volatile unsigned int n_timer_interrupts = 0;
static volatile unsigned int a = 0;
static volatile unsigned int b = 0;

void timer_event(unsigned int pc) {
    armtimer_check_and_clear_interrupt();
    n_timer_interrupts++;
    a++;
    b++;
    if (a != b) {
        printf("VIOLATION (%06d): a=%d,b=%d,pc=%x\n", n_timer_interrupts, a, b, pc);
        timer_delay(3);
    }
}

void main() {
    timer_init();
    gpio_init();
    uart_init();

    armtimer_init(2000);
    armtimer_enable();

    bool ok = interrupts_attach_handler(timer_event);
    assert(ok);

    armtimer_enable_interrupts();
    interrupts_enable_basic(INTERRUPTS_BASIC_ARM_TIMER_IRQ);
    interrupts_global_enable();

    while (1) {
        //interrupts_global_disable();
        a++;
        b++;
        //interrupts_global_enable();
    }
}
