all: build

build: main.hex

cleanandbuild: clean build

prog: main.hex
	avrdude -c usbasp -p atmega328p -e -U flash:w:main.hex:i
	touch prog

main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

main.elf: main.o
	avr-gcc -mmcu=atmega328p -Os -o main.elf main.o

main.o: main.c
	avr-gcc -mmcu=atmega328p -Os -c main.c

clean:
	-rm main.o
	-rm main.elf
	-rm main.hex

