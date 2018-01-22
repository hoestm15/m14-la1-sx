# Protokoll 16.01.2018

## 4. Einheit
## Thema: Makefiles

Name: Markus Kobor  <br>
Klasse: 4AHME  <br>
Datum 16.01.2017  <br>
Gruppe: 1  <br>
Anwesend: Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Enzi Gert, Knappitsch Robert, Kobor Markus  <br>
Abwesend: -  <br>

## Was sind Makefiles & wozu werden sie verwendet?

**Makefiles sind Textdateien, welche häufig dazu verwendet werden einen Übersetzungsvorgang zu steuern.** Sie können aber auch als Zusammenfassung von Befehlen und Programmen verwendet werden.

C Programme bestehen normalerweise aus vielen Quelltextdateien, welche vom C Compiler einzelt compiliert werden. Besteht ein Programm zum Beispiel aus 10 .c Dateien, muss der Compiler 10 mal aufgerufen werden. Man bekommt für jede .c Datei eine 
.o- Objektdatei, welche den erzeugten Binärcode enthält. Der Linker fügt dann die Objekt-Dateien zu einem ausführbaren Programm
zusammen.

Bei Mikrocontrollern wird vom Linker eine .hex Datei für den Programmieradapter erzeugt.
Die Aufgabe vom make Programm besteht darin, den Compilier- und den Link-Vorgang automatisch ablaufen zu lassen. Wird make verwendet, ist es nicht nötig, jede .c Datei einzeln zu compilieren.

**Makefiles versuchen so wenig Aufwand wie möglich zu betreiben, was besonders bei großen Programmen wichtig ist.** 

Dies wird unter anderem dadurch erreicht, dass vor jedem Durchlauf der **Zeitstempel** von allen Dateien überprüft wird und nur nicht aktuelle Aufgaben durchgeführt werden.
Der Zeitstempel gibt an, wann eine Datei zuletzt geändert wurde.

Früher konnten Compeliervorgänge auch Tage dauern.

## Wie werden Makefiles verwendet?

**Um das Build-Management-Tool make benutzen zu können, wird eine Steuerdatei benötigt.** Diese Datei kann einen beliebiigen Namen haben, wird aber normalerweise mit dem dafür bestimmten Namen "Makefile" benannt. (dabei muss die Großschreibung, beachtet werden, welche bei Unix-Dateisystemen unterschieden wird)

## Wie sind Makefiles aufgebaut und was ist zu beachten?

**Makefiles bestehen aus Zielen (Targets), den Abhngigkeiten (Dependencies) und Kommandos (Commands).** <br>
Zur veranschaulichung:

```
Ziel 1: Abhängigkeiten 
  ->  Kommando 1
  ->  Kommando 2
  ->  Kommando 3

Ziel 2: Abhängigkeiten
  ->  Kommando 1
  ->  Kommando 2
```
**Wichtig ist, dass vor den Kommandos Tabulatoren verwendet werden**, da sonst eine Fehlermeldung ausgegeben wird. Das ist vorallem zu beachten, wenn Text kopiert wird, da sich 8 Leerzeichen optisch nicht vom Tabulator unterscheiden.

**Wird der Befehl make aufgerufen, wird das Makefile soweit durchlaufen, bist ein Fehler auftritt.** Das bedeutet, dass alle nachfolgenden Schritte nicht abgewickelt werden. Somit ist es wichtig vor Befehlen, bei denen Fehler auftreten können entprechende Maßnahmen, wie z.B ein vorne hingesetzes "-", welches soviel wie "egal, mach weiter" bedeutet, zu setzen.

## 1. Praktische Übung: Übersetzung eines Programmes mit hilfe von Makefiles

Ziel der 1. Übung war es ein C Programm mit hilfe vom Makefiles zu übersetzen.

```c
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

int main()
{
  DDRB = (1 << PB5);
  while (1)
  {
    PORTB ^= (1 << PB5);
    _delay_ms(500);
  }
  return 0;
}
```
Es wurde ein Blicklicht in C erstellt und dann wie folgt mit hilfe eines Makefiles übersetzt.  

```
all: build // wird durch "make all" aufgerufen -> alle Dateien werden erstellt

build: main.hex // -> wird durch "make build" aufgerufen

cleanandbuild: clean build

main.hex: main.elf
  ->  avr-objcopy -O ihex main.elf main.hex // -> Die .elf Datei wird in eine .hex Datei umgewandelt

main.elf: main.o
  ->  avr-gcc -mmcu=atmega328p -Os -o main.elf main.o // -> Linker: Die Adressen werden vergeben und die
                                                                    Hardware bekanntgegeben
  
main.o: main.c
  ->  avr-gcc -mmcu=atmega328p -Os -c main.c // -> Das C-Programm wird in eine Objektdatei umgewandelt
  
clean: // wird durch "make clean" aufgerufen -> Verzeichnet wird "bereingt", also in den Grundzustand
                                                                                             versetzt
  ->  -rm main.o 
  ->  -rm main.elf
  ->  -rm main.hex
  
```
Vor den Remove- befehlen (z.B -rm main.o) kann man das zuvor erwähnte "-" erkennen, welches in diesem Fall dafür sorgt, dass auch wenn die zu entfernende Datei nicht mehr vorhanden ist, die nachfolgenden Befehle trozdem ausgeführt werden.

## 2. Praktische Übung: Verbinden von zwei Programmen

Ziel der 2. Übung war es zwei verschiedene Programme mit hilfe von Makefiles zu verbinden.
Dafür wurden die Programme main.c sowie util.c erstellt.
Zusätzlich wurde noch die Headerdatei util.h erstellt welche dafür verwendet wurde um eine Funktion bekanntzugeben.

util.h:  
```c
#ifndef UTIL_H
#define UTIL_H

void toggleLED ();

#endif
```    
util.c:  
```c
#include <avr/io.h>

void toggleLED()
{
  PORTB ^= (1 << PB5);
}
``` 

main.c:  
```c
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "util.h"
int main()
{
  DDRB = (1 << PB5);
  while (1)
  {
    toggleLED();
    _delay_ms(500);
  }
  return 0;
}

```  
Makefile:
```
all: build

build: main.hex

cleanandbuild: clean build

prog: main.hex // -> Erstellen des Programms
        avrdude -c usbasp -p atmega328p -e -U flash:w:main.hex:i
        touch prog // -> Anpassen des Zeitstempels

main.hex: main.elf
        avr-objcopy -O ihex main.elf main.hex

main.elf: main.o util.o
        avr-gcc -mmcu=atmega328p -Os -o main.elf main.o util.o // -> Die beiden Programme werden verlinkt

main.o: main.c util.h // -> Die Headerdatei muss auch überprüft werden
        avr-gcc -mmcu=atmega328p -Os -c main.c

util.o: util.c
        avr-gcc -mmcu=atmega328p -Os -c util.c

clean:
        -rm *.o // -> Entfernen aller .o Dateien
        -rm main.elf
        -rm main.hex
        -rm prog
```  
Zuerst wurden aus beiden Programmen einzeln Objektdateien erstellt, wobei dem Ziel main.o noch die Headerdatei als Abhängigkeit vorgegben wurde, da auch diese überprüft werden muss.
Beim Linken werden beiden Programme als Abhängigkeiten festgelegt, da bei der Änderung von main.o oder util.o, der Schritt komplett neu durchgeführt werden muss.
