# Makefile to build program from single ASM or C file
# We will talk more about Makefiles soon!

CFLAGS = -Og -g -Wall -std=c99 -ffreestanding 
LDFLAGS = -nostdlib -e main

all : cblink.bin blink.bin cblink.list blink.list

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o
	arm-none-eabi-gcc $(LDFLAGS) $< -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump --no-show-raw-insn -d $< > $@

install: cblink.bin
	rpi-install.py $<

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean
