#ifndef UART_H
#define UART_H

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


/*
 * Initialize the UART code module. The init function should be called
 * once before any calls to other functions. Note that the UART uses 
 * GPIO pins 14 (transmit) and 15 (receive).
 */
void uart_init(unsigned int baud);

/*
 * Obtains the next input character from the serial port and returns it.
 * If receive buffer is empty, will block until next character is received.
 *
 * @return    the character read or EOF on error
 */
int uart_getchar(void);

/*
 * Outputs a character to the serial port.
 * If send buffer is full, will block until space available.
 *
 * @param ch   the character to write to the serial port
 * @return     the character written or EOF on error
 */
int uart_putchar(int ch);

/*
 * Flushes any output characters pending in the send buffer.
 */
void uart_flush(void);

/*
 * Returns 1 if there is a character ready to be read, 0 otherwise.
 */
int uart_haschar(void);

#endif
