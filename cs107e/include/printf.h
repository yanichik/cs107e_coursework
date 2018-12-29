#ifndef PRINTF_H
#define PRINTF_H

/*
 * Functions for printing forrmatted strings.
 *
 * Author: Julie Zelenski <zelenski@cs.stanford.edu>
 * Sat Jan 27 11:27:13 PST 2018
 */
#include <stdarg.h>

/* These three functions from the printf family are used to produce 
 * formmatted output. The functions accept the same kinds of
 * format strings with the same conversions, but differ slightly in
 * how they are called or where they put the output, e.g.: whether
 * the output is written to the Raspberry Pi UART (printf) or stored
 * as a string in the client's buffer (snprintf and vsnsprintf).
 *
 * The format conversions support by this printf module are
 *   %c    for single characters
 *   %s    for strings
 *   %d    for signed decimal integers
 *   %x    for unsigned hexadecimal integers
 *   %p    for pointers (printed as addresses)
 *
 * The %d and %x formats allow an optional field width.
 * 
 * Other fancy features of printf (padding with spaces,
 * left versus right justification, precision, etc.) are not supported.
 */

/* 
 * `buf` is the destination of the formatted string.
 * `bufsize` is the size of `buf`
 * `format` is a character string which contains plain characters (copied to
 * `buf`), character escape sequences (converted and copied to `buf`), and form
 * specifications (cause copying of the next successive argument).
 *
 * Returns the number of characters written if it fits in the buffer, or the
 * number of characters it would have written if there were space.
 */
int vsnprintf(char *buf, int bufsize, const char *format, va_list args);

/* 
 * `buf` is the destination of the formatted string.
 * `bufsize` is the size of `buf`
 * `format` is a character string which contains plain characters (copied to
 * `buf`), character escape sequences (converted and copied to `buf`), and form
 * specifications (cause copying of the next successive argument).
 *
 * Returns the number of characters written if it fits in the buffer, or the
 * number of characters it would have written if there were space.
 */
int snprintf(char *buf, int bufsize, const char *format, ...) __attribute__ ((format (printf, 3, 4)));

/* `format` is a character string which contains plain characters (copied to
 * the UART), character escape sequences (converted and copied to the UART),
 * and form specifications (cause printing of the next successive argument).
 *
 * Returns the number of characters written to the output.
 */
int printf(const char *format, ...) __attribute__ ((format (printf, 1, 2)));

#endif
