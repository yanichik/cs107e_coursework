#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdbool.h>

/*
 * Module to configure interrupts for Raspberry Pi.
 *
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Author: Julie Zelenski <zelenski@cs.stanford.edu>
 *
 * Date:   Februrary 2018
 */


/*
 * `interrupts_global_enable`
 *
 * Turns on all enabled interrupts system-wide. 
 * Interrupts must be enabled before any interrupts will be generated.
 * Typical use is to configure all interrupt handlers while
 * global interrupts are not yet enabled, then call this function
 * to turn on interrupts when ready.
 */
void interrupts_global_enable(void);

/*
 * `interrupts_global_disable`
 *
 * Turns off all interrupts system-wide.
 * Typical use is to call this function as needed to temporarily
 * suspend interrupts during a critical region that needs to
 * operate atomically. To re-enable interrupts, use the
 * interrupts_global_enable function.
 */
void interrupts_global_disable(void);


/* 
 * `interrupts_enable_source`
 * `interrupts_disable_source`
 *
 * Enable/disable interrupts from a particular source identified by 
 * number. The valid interrupt source numbers are listed below
 * in the interrupt_source enumeration. Note that some interrupt
 * sources are shared (e.g. INTERRUPTS_GPIO0 is the interrupt
 * source for most of the low-number GPIO pins). The enable/disable
 * operation applies to all interrupts for a source.
 * Typical use is to enable a source after attaching the handler
 * as part of initial configuration.
 * If `n` is not a valid interrupt source, the function does nothing.
 */
void interrupts_enable_source(unsigned int n);
void interrupts_disable_source(unsigned int n);

/* 
 * `interrupts_enable_basic`
 * `interrupts_disable_basic`
 *
 * Enable/disable a basic interrupt identified by 
 * number. The valid interrupt basic numbers are listed below
 * in the interrupt_basic enumeration.
 * Typical use is to enable a basic interrupt after attaching 
 * the handler as part of initial configuration.
 * If `n` is not a valid basic interrupt, the function does nothing.
 */
void interrupts_enable_basic(unsigned int n);
void interrupts_disable_basic(unsigned int n);

/* 
 * `interrupts_attach_handler`
 *
 * Attach a handler function to be called when an interrupt is generated.
 * Supports attaching mutliple handlers. It is the responsibility of each 
 * handler function when called to check whether this particular 
 * interrupt is intended for this handler. If so, the handler should 
 * process and clear the interrupt. If not, the handler should do
 * nothing.
 *
 * Returns true if the handler was successfully attached, false otherwise.
 * A handler cannot be attached if the interrupt vectors were not
 * configured at program start by a proper cstart()
 */
bool interrupts_attach_handler(void (*handler)(unsigned int pc));


enum interrupt_source {
   INTERRUPTS_AUX             = 29,
   INTERRUPTS_I2CSPISLV       = 43,
   INTERRUPTS_PWA0            = 45,
   INTERRUPTS_PWA1            = 46,
   INTERRUPTS_CPR             = 47,
   INTERRUPTS_SMI             = 48,
   INTERRUPTS_GPIO0           = 49,
   INTERRUPTS_GPIO1           = 50,
   INTERRUPTS_GPIO2           = 51,
   INTERRUPTS_GPIO3           = 52,
   INTERRUPTS_VC_I2C          = 53,
   INTERRUPTS_VC_SPI          = 54,
   INTERRUPTS_VC_I2SPCM       = 55,
   INTERRUPTS_VC_UART         = 57,
};
/* Interrupt source numbers taken from table in BCM2835 Sec 7.5
 * I quote: "The table has many empty entries.
 * These should not be enabled as they will interfere with the GPU operation."
 */

enum interrupt_basic {
    INTERRUPTS_BASIC_ARM_TIMER_IRQ        = 0,
    INTERRUPTS_BASIC_ARM_MAILBOX_IRQ      = 1,
    INTERRUPTS_BASIC_ARM_DOORBELL_0_IRQ   = 2,
    INTERRUPTS_BASIC_ARM_DOORBELL_1_IRQ   = 3,
    INTERRUPTS_BASIC_GPU_0_HALTED_IRQ     = 4,
    INTERRUPTS_BASIC_GPU_1_HALTED_IRQ     = 5,
    INTERRUPTS_BASIC_ACCESS_ERROR_1_IRQ   = 6,
    INTERRUPTS_BASIC_ACCESS_ERROR_0_IRQ   = 7,
};

void interrupt_vector(unsigned int pc);
void reset_vector(unsigned int pc);
void undefined_instruction_vector(unsigned int pc);
void software_interrupt_vector(unsigned int pc);
void prefetch_abort_vector(unsigned int pc);
void data_abort_vector(unsigned int pc);
void fast_interrupt_vector(unsigned int pc);

#endif
