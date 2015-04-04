name=pov

all: $(name).hex

$(name).hex: $(name).elf 
	avr-objcopy -j .text -j .data -O ihex $^ $@

$(name).elf: $(name).c
	avr-gcc -mmcu=atmega328 -Wall -Os -o $@ $^

up: $(name).hex
	sudo avrdude -p m328 -c usbtiny -e -U flash:w:$^
