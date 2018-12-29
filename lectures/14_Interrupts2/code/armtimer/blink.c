#include "assert.h"
#include "pi.h"
#include "armtimer.h"
#include "gpio.h"
#include "uart.h"
#include "interrupts.h"
#include "printf.h"

volatile int counter = 0;

/* 
 * we have only enabled timer interrupts
 */
void timer_event(unsigned int pc) 
{
    armtimer_check_and_clear_interrupt();
    counter++;
}

void main(void) 
{
    gpio_init();
    gpio_set_output(PI_ACT_LED);
    gpio_set_output(GPIO_PIN20);

	uart_init();
    printf("Executing program '%s'\n", __FILE__);

    // number of usecs between interrupts
	armtimer_init(1000000); // 1s
    armtimer_enable();      // enable timer

    // enable interrupts from timer
    armtimer_enable_interrupts();

    // enable basic timer interrupts
    interrupts_enable_basic(INTERRUPTS_BASIC_ARM_TIMER_IRQ);

    // attach interrupt handler
    bool ok = interrupts_attach_handler(timer_event);
    assert(ok);

    interrupts_global_enable(); 

	int last = 0;
	while(1) {
		if (last != counter) {
			last = counter;
            pi_led_toggle(PI_ACT_LED);
            gpio_write(GPIO_PIN20,!gpio_read(GPIO_PIN20));
			printf("received %d interrupts\n", last);
		}
	}
}
