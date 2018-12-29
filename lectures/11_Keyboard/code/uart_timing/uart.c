/*
 * Hardware abstractions for a serial port (UART). This
 * is a slight variation from the standard libpi version,
 * it allows you to set the baudrate. This is used in the
 * Keyboard lecture to show UART timing.
 *
 * PLEASE DO NOT REPLACE THIS WITH THE STANDARD LIBPI VERSION.
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Date:   May 10, 2018
 */

#include "gpio.h"
#include "uart.h"

struct UART {
    unsigned data; // I/O Data
    unsigned ier;  // Interrupt enable
    unsigned iir;  // Interrupt identify and fifo enables/clears
    unsigned lcr;  // line control register
    unsigned mcr;  // modem control register
    unsigned lsr;  // line status register
    unsigned msr;  // modem status register
    unsigned scratch;
    unsigned cntl; // control register
    unsigned stat; // status register
    unsigned baud; // baud rate register
} ;

// AUX bits
#define AUX_ENABLES 0x20215004
#define AUX_ENABLE  0x00000001

// Mini UART
#define MINI_UART_BASE 0x20215040

#define MINI_UART_IIR_RX_FIFO_CLEAR  0x00000002
#define MINI_UART_IIR_TX_FIFO_CLEAR  0x00000004
#define MINI_UART_IIR_RX_FIFO_ENABLE 0x00000080
#define MINI_UART_IIR_TX_FIFO_ENABLE 0x00000040

#define MINI_UART_LCR_8BIT       0x00000003

#define MINI_UART_LSR_RX_READY   0x00000001
#define MINI_UART_LSR_TX_READY   0x00000010
#define MINI_UART_LSR_TX_EMPTY   0x00000020

#define MINI_UART_CNTL_TX_ENABLE 0x00000002
#define MINI_UART_CNTL_RX_ENABLE 0x00000001

static volatile struct UART *uart = (struct UART*) MINI_UART_BASE;


/* Key detail from the Broadcom Peripherals data sheet p.10
 *
 * GPIO pins should be set up first the before enabling the UART. 
 * The UART core is build to emulate 16550 behaviour. 
 * So when it is enabled any data at the inputs will immediately be received .
 * If the UART1_RX line is low (because the GPIO pins have not been set-up yet) 
 * that will be seen as a start bit and the UART will start receiving 0x00-characters.
 * [...] The result will be that the FIFO is full and overflowing in no time flat.
 */

void uart_init(unsigned int baud) 
{
    gpio_set_function(GPIO_TX, GPIO_FUNC_ALT5);
    gpio_set_function(GPIO_RX, GPIO_FUNC_ALT5);

    int *aux = (int*)AUX_ENABLES;
    *aux |= AUX_ENABLE; // must enable mini-uart before accessing registers

    uart->ier  = 0;
    uart->cntl = 0;
    uart->lcr  = MINI_UART_LCR_8BIT;
    uart->mcr  = 0;
    uart->ier  = 0;
    uart->iir  = MINI_UART_IIR_RX_FIFO_CLEAR |
                 MINI_UART_IIR_RX_FIFO_ENABLE |
                 MINI_UART_IIR_TX_FIFO_CLEAR |
                 MINI_UART_IIR_TX_FIFO_ENABLE;

    unsigned baud_val = ((250000000)/baud)/8 - 1;
    uart->baud =  baud_val; // Should be 270 for 115200

    uart->cntl = MINI_UART_CNTL_TX_ENABLE | MINI_UART_CNTL_RX_ENABLE;
}

int uart_getchar(void) {
    while (!(uart->lsr & MINI_UART_LSR_RX_READY)) ;
    return uart->data & 0xFF;
}

int uart_putchar(int ch) {
    // convert newline to CR LF sequence by inserting CR
    if (ch == '\n') {
        uart_putchar('\r');
    }
    while (!(uart->lsr & MINI_UART_LSR_TX_EMPTY)) ;
    uart->data = ch;
    return ch;
}

void uart_flush(void) {
    while (!(uart->lsr & MINI_UART_LSR_TX_EMPTY)) ;
}

int uart_haschar(void) {
    return (uart->lsr & MINI_UART_LSR_RX_READY);
}
