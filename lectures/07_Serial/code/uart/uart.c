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
#define MINI_UART_IIR_RX_FIFO_ENABLE 0x00000008
#define MINI_UART_IIR_TX_FIFO_ENABLE 0x00000004

#define MINI_UART_LCR_8BIT       0x00000003

#define MINI_UART_LSR_RX_READY   0x00000001
#define MINI_UART_LSR_TX_READY   0x00000010
#define MINI_UART_LSR_TX_EMPTY   0x00000020

#define MINI_UART_CNTL_TX_ENABLE 0x00000002
#define MINI_UART_CNTL_RX_ENABLE 0x00000001

static volatile struct UART *uart = (struct UART*) MINI_UART_BASE;

void uart_init(void) {
    volatile int *aux = (volatile int*)AUX_ENABLES;

    *aux = AUX_ENABLE; // turn on mini-uart

    uart->ier  = 0;
    uart->cntl = 0;
    uart->lcr  = MINI_UART_LCR_8BIT;
    uart->mcr  = 0;
    uart->ier  = 0;
    uart->iir  = MINI_UART_IIR_RX_FIFO_CLEAR |
                 MINI_UART_IIR_RX_FIFO_ENABLE |
                 MINI_UART_IIR_TX_FIFO_CLEAR |
                 MINI_UART_IIR_TX_FIFO_ENABLE;

    uart->baud =  270; // baud rate ((250,000,000/115200)/8)-1 = 270
    
    /*
    ** from gpio.h
    **
    ** #define GPIO_TX 14
    ** #define GPIO_RX 15
    */
    gpio_set_function(GPIO_TX, GPIO_FUNC_ALT5);
    gpio_set_function(GPIO_RX, GPIO_FUNC_ALT5);

    uart->cntl = MINI_UART_CNTL_TX_ENABLE | MINI_UART_CNTL_RX_ENABLE;
}

int uart_getchar(void) {
    while (!(uart->lsr & MINI_UART_LSR_RX_READY)) ;
    return uart->data & 0xFF;
}

int uart_putchar(int c) {
    if (c == '\n')
        uart_putchar('\r');
    while (!(uart->lsr & MINI_UART_LSR_TX_EMPTY)) ;
    uart->data = c;
    return c;
}

void uart_flush(void) {
    while (!(uart->lsr & MINI_UART_LSR_TX_EMPTY)) ;
}
