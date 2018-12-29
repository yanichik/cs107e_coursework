# Makefile to build program from single ASM or C file
# We will talk more about Makefiles soon!

CFLAGS = -O2 -g -Wall -std=c99 -ffreestanding 
LDFLAGS = -nostdlib -e main

all : cbutton.bin cbutton.list

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

install: cbutton.bin
	rpi-install.py $<

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean install
