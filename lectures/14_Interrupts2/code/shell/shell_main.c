#include "gpio.h"
#include "uart.h"
#include "keyboard.h"
#include "interrupts.h"
#include "gl.h"
#include "console.h"
#include "printf.h"
#include "shell.h"

/* This program tests the keyboard using the console.
 * Characters read from the keyboard and printed to the console.
 * If the keyboard is blocking it drops events.
 */

void main() {
    gpio_init();
    uart_init();

    keyboard_init();
    keyboard_use_interrupts();

    console_init(40, 80); // calls gl_init
    shell_init(console_printf);
    //shell_init(printf, uart_putchar);

    interrupts_global_enable();
    shell_run();
}
