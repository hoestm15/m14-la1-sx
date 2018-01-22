all: build

build: main.hex

cleanandbuild: clean build

prog: main.hex
	avrdude -c usbasp -p atmega328p -e -U flash:w:main.hex:i
	touch prog

main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

main.elf: main.o util.o
	avr-gcc -mmcu=atmega328p -o main.elf main.o util.o

main.o: main.c util.h
	avr-gcc -mmcu=atmega328p -Os -c main.c

util.o: util.c
	avr-gcc -mmcu=atmega328p -Os -c util.c


clean:
	-rm main.o
	-rm util.o
	-rm main.elf
	-rm main.hex
