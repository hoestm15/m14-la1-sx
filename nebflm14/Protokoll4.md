# Protokoll der 4. Einheit (06.02.2018)

## Thema: Compilieren, Makefile

Name:     Florian Nebel  
Klasse:   4AHME  
Gruppe:   2  

Anwesend: Köhler Marcel, Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: ---

## Der Compiliervorgang
Im ersten Schritt wird die Datei `main.c` in eine `main.o` Datei umgewandelt. Der Präprozessor bindet die Header-Dateien ein. Beim Compilieren wird der Quelltext in Assemblerbefehle umgewandelt, welche mithilfe des Assemblers in Maschinenbefehle übersetzt werden können.
* avr-gcc -mmcu="atmega328p" -Os -c -DF_CPU=16000000L main.c
  * `avr-gcc` Gnu Compiler Collection der AVR-Mikrocontroller
  * `-mmcu="atmega328p"` betroffenes System
  * `-Os`
  * `-c` Linker nicht starten (nur compilieren)
  * `-DF_CPU=16000000L` Taktfrequenz
  * `main.c` ausgewählte Datei

Der zweite Schritt liegt darin, die Datei `main.o` in eine `main.elf` Datei umzuwandeln. Beim Linken werden die tatsächlichen Programmadressen eingebunden. Dadurch wird eine ausführbare Datei erzeugt.
* avr-gcc -o main.elf main.o
  * `avr-gcc` Gnu Compiler Collection der AVR-Mikrocontroller
  * `-o` nur linken
  * `main.elf` Zieldatei
  * `main.o` Quelldatei

Im dritten Schritt wird die Datei in eine `main.hex` Datei umgewandelt. Das Konvertieren ist nur bei Systemen notwendig, welche nicht in der Lage sind main.elf-Dateien auszuführen.
* avr-objcopy -O ihex main.elf main.hex
  * `avr-objcopy` umwandeln des Dateiformates
  * `-O ihex` Objektformat Intel HEX
  * `main.elf` Quelldatei
  * `main.hex` Zieldatei

## Makefile
IDEs greifen zum Übersetzen von C-Dateien auf das Übersetzungstool **make** zurück. Dieses Tool ist der Gruppe der **Build-Management-Tools** untergeordnet. Das Hilfsprogramm, welches Teil des **POSIX-Standards** ist, wird zur Umwandlung von Quellcode in ausführbare Programme verwendet. Es ist von großem Nutzen, da es alle Arbeitsschritte automatisiert.  
siehe auch: [wikipedia.org](https://de.wikipedia.org/wiki/Make)

### Syntax
```
Ziel 1: Voraussetzung 1, ...  
[Tab] Kommando 1  
[Tab] ...

Ziel 2: Voraussetzung 1, ...
[Tab] Kommando 1  
[Tab] ... 
```

### Aufruf
Mit dem Kommando `make` wird die das Makefile aufgerufen. Um so effektiv wie möglich zu arbeiten, vergleicht das File vor dem Ausführen der Befehle die Zeitstempel der zu bearbeitenden Dateien und entscheidet dann, ob der Vorgang notwendig ist.

## Übung 1
Erstellen eines lauffähigen C-Programms mithilfe eines Makefiles.

### C-Programm
```c
#include <avr/io.h>
#include <util/delay.h>

int main()
{
        DDRB = (1<<PB5);
        while(1)
        {
                PORTB=(1<<PB5);
                _delay_ms(500);
                PORTB = 0;
                _delay_ms(500);
        }
        return 0;
}
```

### Makefile
```
main.hex: main.elf
        avr-objcopy -O ihex main.elf main.hex

main.elf: main.o
        avr-gcc -o main.elf main.o

main.o: main.c
        avr-gcc -mmcu="atmega328p" -Os -c -DF_CPU=16000000L main.c

clean:
        -rm main.o
        -rm main.elf
        -rm main.hex
```

`clean` bedeutet, dass alle angegebenen Dateien aus dem Verzeichnis gelöscht werden. In diesem Fall werden die, bei der Compilierung erstellten Dateien wieder entfernt. Sollte eine angegebene Datei nicht vorhanden sein würde das Makefile abbrechen. Das wird durch das `-` verhindert.

Es kann nicht nur das ganze File mittels `make` ausgeführt werden, sondern auch einzelne Befehle wie zum Beispiel das löschen der Dateien durch `make clean`.

## Übung 2
Nun sollte auch die Initialisierung des "bootloaders" und des "flash" in das Makefile eingebunden werden.

Um diese Befehle hinzuzufügen, war es notwendig, die Datei, in welcher sich diese befanden, ausfindig zu machen. Dies geschah durch das Kommando `which`. In der Datei **/usr/bin/flashbootloader** welche wir mit dem Kommando `less` im Terminal ausgaben konnten wir den Befehl finden und im Makefile ergänzen.

```
flash: main.hex
        avrdude -c usbasp -p atmega328p -e -U flash:w:bootloader.hex:i
        touch flash
```

`touch flash` aktualisiert den Zeitstempel der Datei. Dieser Befehl ist notwendig, da das Makefile nur dann einen Befehl ausführt, wenn sich in einer Datei etwas geändert hat bzw. der Zeitstempel aktualisiert hat.

Um den bootloader und das Programm gemeinsam zu initialisieren mussten wir die main.hex-Datei und den bootloader in eine Datei zusammenführen. Nachdem wir den bootloader mit `which` ausfindig gemacht haben, mit `cp /usr/share/htl-aiit-tools/boards/arduinoNanoV3/bootloader.hex ./` in das aktuelle Verzeichnis kopiert haben und die Dateien mit `cat` zusammengefügt haben, mussten wir die letzte Zeile des ersten Programms entfernen, um zu verhindern, dass das Programm an dieser Stelle beendet wird.
