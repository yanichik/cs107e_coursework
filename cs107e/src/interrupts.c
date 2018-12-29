#include "interrupts.h"
#include <stdint.h>

// http://xinu.mscs.mu.edu/BCM2835_Interrupt_Controller
// BCM: p196
// This struct is declared to match memory layout of the interrupt registers
struct interrupt_t {
    uint32_t pending_basic;
    uint32_t pending[2];
    uint32_t fiq_control;
    uint32_t enable[2];
    uint32_t enable_basic;
    uint32_t disable[2];
    uint32_t disable_basic;
};

#define INTERRUPT_CONTROLLER_BASE 0x2000B200

static volatile struct interrupt_t * const interrupt = (struct interrupt_t *)INTERRUPT_CONTROLLER_BASE;

void interrupts_enable_basic(unsigned int n)
{
    if (n > 7) return;

    interrupt->enable_basic |= (1 << n);
}

void interrupts_disable_basic(unsigned int n)
{
    if (n > 7) return;

    interrupt->disable_basic |= (1 << n);
}

void interrupts_enable_source(unsigned int n)
{
    if (n < INTERRUPTS_AUX || n > INTERRUPTS_VC_UART) return;

    unsigned int bank = n / 32;
    unsigned int shift = n % 32;
    interrupt->enable[bank] |= 1 << shift;
}

void interrupts_disable_source(unsigned int n)
{
    if (n < INTERRUPTS_AUX || n > INTERRUPTS_VC_UART) return;

    unsigned int bank = n / 32;
    unsigned int shift = n % 32;
    interrupt->disable[bank] |= 1 << shift;
}

// Check if interrupt vector was installed into correct place
// (supposed to be done in cstart.c). Otherwise there is no
// point in attaching handler (if vector not installed, no
// way to call out)
static bool vector_is_installed(void)
{
    extern int _vectors;
    static unsigned int * const RPI_INTERRUPT_VECTOR_BASE = 0x0;
    return RPI_INTERRUPT_VECTOR_BASE[7] == (&_vectors)[7];
}

#define MAX_HANDLERS 32

static struct isr_t {
    void (*fn[MAX_HANDLERS])(unsigned int);
    int count;
} handlers;

bool interrupts_attach_handler(void (*isr)(unsigned int))
{
    if (!vector_is_installed()) return false;
    if (handlers.count >= MAX_HANDLERS) return false;
    handlers.fn[handlers.count++] = isr;
    return true;    
}

void interrupt_vector(unsigned int pc)
{
    for (int i = 0; i < handlers.count; i++)
        handlers.fn[i](pc);
}


// All of the other vectors are empty functions and declared as weak
// symbols ihere n libpi. Because they are weak, a strong symbol defined 
// by client will take precedence. This allows the client to supply their 
// own version of the vector if desired.

__attribute__ ((weak)) void reset_vector (unsigned int pc) {}
__attribute__ ((weak)) void undefined_instruction_vector (unsigned int pc) {}
__attribute__ ((weak)) void software_interrupt_vector (unsigned int pc) {}
__attribute__ ((weak)) void prefetch_abort_vector (unsigned int pc) {}
__attribute__ ((weak)) void data_abort_vector (unsigned int pc) {}
__attribute__ ((weak)) void fast_interrupt_vector (unsigned int pc) {}
