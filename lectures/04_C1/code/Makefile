# Makefile to build program from single ASM or C file
# We will talk more about Makefiles soon!

CFLAGS = -g -Wall -Og -std=c99 -ffreestanding 
LDFLAGS = -nostdlib -T memmap

all : blink.bin cblink.bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

# link, memmap needed for text/data to
# be laid out as needed
%.elf: %.o
	arm-none-eabi-gcc $(LDFLAGS) $< -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $< -o $@

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean

.PRECIOUS: %.o %.elf
