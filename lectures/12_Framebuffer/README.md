---
released: true
---

GPU and CPU
  - split memory
  - share memory
  - memory management unit
  - gpu maps address "physical address" 0x20xxxxxx to "bus address" 0x7exxxxxx
    - peripheral addresses in the document are bus addresses

CPU
  - accesses to the same peripheral will always arrive and return inorder
  - when switching from one peripheral to another need access may arrive out of order
  - to guarantee in-order access
    - memory write barrier before the first write to a peripheral
    - memory read barrier before the first read from a peripheral

GPU framebuffer
  - different formats
  - see screen01
  - use these examples to illustrate pointers and casts

Bit fields in the following descriptions are little-endian.

32bpp mode:

bits 24-31: 0 or transparency
bits 16-23: blue
bits 8-15: green
bits 0-7: red

16bpp mode:

bit 15: 0 or transparency
bits 10-14: blue
bits 5-9: green
bits 0-4: red

Mailbox
- mailbox_write
  - read data is a combination of the address of the packet and the channel
  - there are 16 channels
    - channel 1 is to the GPU
    - this means that the address must be aligned to 16
  - write the address + 0x40000000
     this ensures that the GPU will not cache the result
- mailbox_read
  - returns 0 when it is happy
- memory problems
  - problem1
    - make sure that the data is actually written to memory
      - use volatile or GET32/SET32 to make sure the data is stored
  - problem2
    - memory system may not actually write the data
      - cache
      - write buffers
  - problem3
    - compiler can reoder code
      - reorder around volatile
      - not reorder around GET32/SET32
  - problem4
     - gpu contains a 128KB L2 cache
       - diagram of the actual memory system
       - find a good explanation of how caching works
         - make sure that GPU does not cache values
       - SDRAM is mapped into physical addresses in 4 places
         - use memory address trick
            0x00xxxxxx L1 and L2 cache
            0x40xxxxxx L2 cache coherent (non allocating)
            0x80xxxxxx L2 cached (only)
            0xC0xxxxxx uncached
  - see Dawson code

Framebuffer
struct{
- physical width
- physical height
- virtual width
- virtual height
    <= 4096
- GPU - returns pitch (bytes per row)
- depth - bits per pixel
   16 - high color mode (Red=5, Green=6, Blue=5)
   24 - RGB mode
   32 - RGBA mode
   <= 32
- x offset
- y offset
- GPU - returns pointer to framebuffer
- GPU - returns size of framebuffer
}
write a program that prints out what happens
