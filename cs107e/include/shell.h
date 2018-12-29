#ifndef SHELL_H
#define SHELL_H

/*
 * Interface to the CS107E shell. You implement the beginnings
 * of your shell in assignment 5 and complete it in assignment 7.
 *
 * Author: Julie Zelenski <zelenski@cs.stanford.edu>
 * Date: Februrary 2016
 */

typedef int (*formatted_fn_t)(const char *format, ...);

/*
 * shell_init
 * ==========
 *
 * Initialize the shell
 *
 * Takes a *function pointer* `printf_fn` that is used
 * to configure where the shell directs its output.
 *
 * Arguments:
 *   * `printf_fn` - used for the formatted output
 *
 * Example usage:
 *   * `shell_init(printf)`
 *   * `shell_init(console_printf)`
 */
void shell_init(formatted_fn_t print_fn);

/*
 * shell_readline
 * ==============
 *
 * Reads a single line of input from the user. Store the characters typed on
 * the keyboard and stores them into a buffer `buf` of size `bufsize`. Reading
 * stops when the user types enter (\n).
 *
 * When the user types backspace (\b):
 *   If there are any characters currently in the buffer, deletes the last one.
 *   Otherwise, calls `shell_bell`.
 */
void shell_readline(char buf[], int bufsize);

/*
 * shell_evaluate
 * ==============
 *
 * Parses a line as follows:
 *   * If the line is empty, does nothing
 *   * Otherwise, tokenizes the line. A token is a sequence of non-space
 *     characters.
 *   * Looks up the command function associated with the command name (first token).
 *   * If the command does not exist, prints an error such as:
 *       error: no such command 'binky'.
 *   * Otherwise, executes the command function with the rest of the tokens,
 *     using the rest of the tokens as arguments
 */
int shell_evaluate(const char *line);

/* 
 * shell_run
 * =========
 *
 * Main function of the shell module, must be called after `shell_init`.
 * Enters a read, eval, print loop that uses the  `shell_readline`, and
 * `shell_evaluate`, `printf_fn` (argument to `shell_init`).
 */
void shell_run(void);


#endif
