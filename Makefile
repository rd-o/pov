all: pov.hex

pov.hex: pov.elf 
	avr-objcopy -j .text -j .data -O ihex $^ $@

pov.elf: pov.c
	avr-gcc -mmcu=atmega328 -Wall -Os -o $@ $^

up: pov.hex
	sudo avrdude -p m328 -c usbtiny -e -U flash:w:$^
