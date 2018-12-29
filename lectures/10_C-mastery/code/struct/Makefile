APPLICATION = struct

CS107E = ../../../../cs107e
CFLAGS = -g -O0 -I$(CS107E)/include -Wall -std=c99 -ffreestanding -Wpointer-arith
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/lib
LDLIBS = -lpi

all : $(APPLICATION).bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $< -o $@

install: $(APPLICATION).bin
	rpi-install.py -s $<

clean:
	rm -f *.o *.i *.bin *.elf *.list *~ clock.s gpio.s timer.s data.s

.PHONY: all clean install

.PRECIOUS: %.o %.elf

# empty recipe used to disable built-in rules for native build
%:%.c
%:%.o
%:%.s
