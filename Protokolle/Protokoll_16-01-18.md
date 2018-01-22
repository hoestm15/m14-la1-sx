# Protokoll: Knappitsch Robert

## 4. Einheit: Make Files
* Klasse: 4AHME (Gruppe 1)
* Datum: 16.01.2018
* Anwesend: Berger Emil, Bullner Jeremy, Böcksteiner Jakob, Ehmann Julian, Enzi Gert, Kobor Markus, Knappitsch Robert
* Abwesend: -
### Make Files
#### Verwendungszweck
Make Files werden zum Steuern des Übersetzungsvorgangs und zum kontrollierten Aufrufen von Befehlen und Programmen eingesetzt.

#### Aufbau
Eine Make File ist eine Textdatei mit dem Namen "Makefile". Darin werden die gewünschten Ziele mit den zugehörigen Abhängigkeiten
und Kommandos aufgelistet.
```
Ziel (target): Abhängigkeit(en) (dependencies)
  Kommando(s) (commands)
```
* Vor einem Kommando muss ein echter Tabulator (keine Leerzeichen) stehen. 
* Das Ziel ist von den Abhängigkeiten mit einem Doppelpunkt getrennt. 
* Ein Ziel muss nicht immer Dateien als Abhängigkeiten haben. Wenn keine Datei vorhanden ist, werden Symbole verwendet. Dadurch werden die zugehörigen Befehle immer ausgeführt. Wenn jedoch keine Datei und kein Symbol vorhanden ist, kommt es zu einem Fehler.
* Steht ein "-" vor einem Kommando, wird es auch bei einer Fehlermeldung ausgeführt.

#### Konsolenbefehl
```
make <Ziel>
```
Eine Steuerdatei mit dem Namen "Makefile" muss vorhanden sein.

#### Zeitstempel
Die Makefile schaut auf den Zeitstempel der Dateien. Damit kann man sehen, wann eine Datei zuletzt geöffent / verändert wurde. Da stehts versucht wird für das Ziel möglichst wenig Zeit aufzuwenden, werden die Zeitstempel von Ziel und Abhängigkeit verglichen. Wenn die Ziel-Datei "jünger" als die Abhängigkeits-Datei ist, ist das Ziel bereits auf dem neuesten Stand und es muss nichts getan werden.

#### Beispiel 1
##### Makefile:
Mit dem Befehl `make` werden die main.c kompiliert und mit Hilfe des Programmers auf den Arduino Nano geflasht. Der Befehl `make clear` löscht alle, durch `make` erstellten Dateien.
Mit `make cleanandbuild` werden die Dateien gelöscht und neu kompiliert.
Mit `make prog` wird das Programm auf den Arduino Nano geflasht.
Die restlichen Targets kompilieren die main.c zu main.hex. (main.c --> main.o --> main.elf --> main.hex)
```
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
	-rm prog
  ```
##### main.c
Die main.c sorgt dafür, dass eine LED auf dem Arduino Nano, mit einem Delay von 500ms zu blinken beginnt, indem sie mit einer Endlosschleife dauerhaft getoggled wird.
```
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main () {
	DDRB = (1 << PB5);
	while (1) {
		PORTB ^= (1 << PB5);
		_delay_ms(500);
	}

	return 0;
}
```
  
#### Beispiel 2
##### Makefile:
Hier werden main.c und util.c zu einer einzigen main.hex kompiliert.
(main.c, util.c --> main.o, util.o --> main.elf --> main.hex)

```
all: build

build: main.hex

cleanandbuild: clean build

prog: main.hex
	avrdude -c usbasp -p atmega328p -e -U flash:w:main.hex:i
	touch prog

main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

main.elf: main.o util.o
	avr-gcc -mmcu=atmega328p -Os -o main.elf main.o util.o

main.o: main.c util.h
	avr-gcc -mmcu=atmega328p -Os -c main.c

util.o: util.c
	avr-gcc -mmcu=atmega328p -Os -c util.c

clean:
	-rm *.o 
	-rm main.elf
	-rm main.hex
	-rm prog
```

##### main.c
Dieses Programm erfüllt dieselbe Funktion wie in Beispiel 1, nur dass hier auf eine zweite Datei "util.c" zugegriffen wird. 
```
define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main () {
	DDRB = (1 << PB5);
	while (1) {
		toggleLED();
	}

	return 0;
}
```

##### util.c
Die util.c übernimmt das Togglen der LED.
```
#include <avr/io.h>

void toggleLED () {
	PORTB ^= (1 << PB5);
}
```
