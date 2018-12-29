APPLICATION = clock
MY_MODULES = timer.o gpio.o

CS107E = ../../../cs107e
CFLAGS = -Og -Wall -std=c99 -ffreestanding
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/lib
LDLIBS =

all : $(APPLICATION).bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o $(MY_MODULES) start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@
	arm-none-eabi-objdump --no-show-raw-insn -d $@ > $@.list

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@
	arm-none-eabi-objdump --no-show-raw-insn -d $@ > $@.list

%.o: %.s
	arm-none-eabi-as $< -o $@

install: $(APPLICATION).bin
	rpi-install.py $<

clean:
	rm -f *.o *.i *.bin *.elf *.list *~ clock.s gpio.s timer.s data.s

.PHONY: all clean install

.PRECIOUS: %.o %.elf

# empty recipe used to disable built-in rules for native build
%:%.c
%:%.o
%:%.s
