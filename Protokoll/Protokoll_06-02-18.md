# Protokoll der 4. Einheit

## 3. Einheit

* Name: Mario Nabernik  
* Klasse: 4AHME  
* Datum 06.02.2018  
* Gruppe: 2  
* Anwesend: Marcel Köhler, Michael Mörth, Florian Nebel, Lorenz Muri, Moritz Martinak, Andreas Platzer, Mario Nabernik, Gerhard Mandl  
* Abwesend: -  
* Thema: Atmel Studio

## Kompilieren
Schritte | Befehle | Erklärung  
--------------- | --------- | ---------  
`main.c`zu `main.o` | avr-gcc -mmcu="atmega328p" -Os -c -DF_CPU=16000000L main.c | `-mmcu` gibt das System an .`-c` sorgt dafür das nur kompiliert wird (ohne Linker). `-DF_CPU=16000000L` ist die Taktfrequenz.  
`main.o`zu `main.elf`| avr-gcc -o main.elf main.o | `-o` - es wird nur gelinkt. `main.elf` ist Zieldatei. `main.o` ist Quelldatei  
`main.elf` zu `main.hex` | avr-objcopy -O ihex main.elf main.hex | `ihex` Daten werden im Intel Hex Datei gespeichert. `main.hex` ist Zieldatei. `main.elf` ist Quelldatei.  

#### Zusammengefasst
Zunächst wird `main.c` zu `main.o` übersetzt. Dies ist eine ObjektDatei.  Beim __Compilen__ wird der Quelltext dann in Assemblerbefehle übersetzt. Durch das __Assemblieren__ wird der Assemblerquelltext dann in binäre Maschinenbefehle übersetzt.
Danach wird `main.o` zu `main.elf` übersetzt. Diese Datei ist executable (ausführbar).Sie ist deswegen ausführbar, da ale tatsächlichen Addressen eingetragen wurden. Den ganze Vorgang nennt man __Linken__.
Der letzte Schritt ist das __Konvertieren__. Dies wird benötigt, wenn das System die `main.elf` Datei nicht ausführen kann. Dadurch wird `main.elf` zu `main.hex`.
## Makefiles
C Programme werden in IDEs programmiert. Die Übersetzung dieser Files erfolgt dann mit dem Werkzeug `make`.

>Das Kompilieren von Quelltext-Dateien kann mit dem Programm make gesteuert werden. Dies ist vor allem dann sinnvoll, wenn es sich um ein großes Projekt handelt bei dem die Kompilierung aus vielen einzelnen Schritten und Abhängigkeiten besteht. Die einzelnen Schritte können zum Beispiel separate Kompilierungen oder andere Dateioperationen wie Kopieren und Löschen sein. Abhängigkeiten können zum Beispiel bedingte Kompilierungen sein. Diese Schritte und Abhängigkeiten werden in ein Makefile zusammengefasst, welches dann vom Programm make verarbeitet wird.  

Quelle: [C-HowTo](http://www.c-howto.de/tutorial/makefiles/)  

### Aufbau von Makefiles
```
Ziel 1: Voraussetzung 1, ... , Voraussetzung n  
[Tab] Kommando 1  
[Tab] ...  
[Tab] Kommando n  

Ziel 2: Voraussetzung 1, ... , Voraussetzung n  
[Tab] Kommando 1  
[Tab] ...  
[Tab] Kommando n  
```
Makeiles werden mit dem Befehl `make` aufgerufen. Dies geschieht im Terminal, da Makefile immer so effektiv wie möglich zu Arbeiten versucht, 
werden die Zeitstempel der Dateien immer verglichen- Daraufhin hin wird entschieden ob das Kommando ausgeführt werden muss.
Will man eine unveränderte Datei trotzdem aktualisieren, macht man dies mit dem Befehl `touch`.

## Aufgabe 1  
Übersetzung eines C-Programms mit Hilfe eines Makefiles. Die Lauffähigkeit auf dem Atmega 328p soll sicher gestellt sein.

### Quelltext Makefile
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

Befehl | Beschreibung
------ | ------------
`main.o: main.c` | main.c wird zu main.o übersetzt. In main.o stehen dann Maschinenbefehle.
`main.elf: main.o` | main.o wird gelinkt. Alle Addressen werden vergeben.
`main.hex: main.elf` | main.elf wird zu einer Hex-Datei main.hex umcodiert.
`clean:`| alle angegebenen Dateien werden aus dem Verzeichnis gelöscht.

Tritt ein Fehler auf, liefert das angegebene Kommando `rm` einen Rückgabewert != 0 zurück. Dies bedeutet __Fehler__. Das Programm wird abgebrochen. Mit einem "-" vor dem
`rm` wird dies verhindert.


#### Aufrufmöglickeiten im Terminal

Befehl | Beschreibung
------ | ------------
`make` | Führt die Kommandos des ersten Ziels aus.
`make clean` | Führt die Kommandos des Ziels `clean` aus.
`make main.o` | Compilen.
`make main.elf` | Trägt die Adressen im Maschinencode ein. Die Datei ist ausführbar.
`make main.hex` | Konvertieren.

## Aufgabe 2
Übersetzung eines C-Programms mit Hilfe eines Makefiles. Die Lauffähigkeit auf dem Atmega 328p soll sicher gestellt sein. Mit Hilfe des Makefiles soll außerdem der _flash_ und der _bootloader_ initialisiert werden.


**Quelltext des Makefiles**
```
main.hex: main.elf
        avr-objcopy -O ihex main.elf main.hex

main.elf: main.o
        avr-gcc -o main.elf main.o

main.o: main.c
        avr-gcc -mmcu="atmega328p" -Os -c -DF_CPU=16000000L main.c

flash: main.hex
        avrdude -c usbasp -p atmega328p -e -U flash:w:bootloader.hex:i
        touch flash
```
Befehl | Beschreibung
------ | ------------
`touch flash` | Flash wird nur dann initialisiert, wenn es eine Änderung gegeben hat.

Für die Realisierung des Programms, war es außerdem notwendig den Befehl zu finden, der unseren Flash initialisiert. Diesen konnten wir vorgefertigt in einer Datei, welche wir mit dem Befehl
`which` ausfindig machen konnten, finden.
