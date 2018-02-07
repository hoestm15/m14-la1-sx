main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

main.elf: main.o
	avr-gcc -o main.elf main.o

main.o: main.c
	avr-gcc -mmcu="atmega328p" -Os -c -DF_CPU=16000000L main.c

flash: main.hex
	avrdude -c usbasp -p atmega328p -e -U flash:w:bootloader.hex:i
	touch flash

flashfull: main-bl.hex
	avrdude -c usbasp -p atmega328p -e -U flash:w:main-bl.hex:i

flashfull2: main.hex
	avrdude -c usbasp -p atmega328p -e -U flash:w:bootloader.hex:i -U flash:w:main.hex:i

clean:
	-rm main.o
	-rm main.elf
	-rm main.hex
	-rm flash
