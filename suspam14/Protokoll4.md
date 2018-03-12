# Protokoll 4: Makefiles
Name: Patrick Schuster  
Klasse: 4AHME  
Gruppe: 3    
Anwesend: Reinbacher, Ruffenacht, Sackl, Sackl, Sammer, Schmuck, Schuster  
Abwesend: Schmuck Martin

# Wiederholung: C Übersetzungsvorgang
Um eine Hochsprache (wie z.B. C, C++ oder Java) ausführen zu können muss diese zuerst in Maschinencode übersetzt. Diesen Vorgang nennt man Umgangssprachlich kompilieren. Wenn man es genau nimmt ist das kompilieren nur ein Zwischenschritt.
## nötige Schritte für den Übersetzungsvorgang  
Schritt | Dateiendung | Beschreibung  
--- | --- | ---  
Präprozessieren | .i | Präprozessoranweisungen (#include, #define, #ifdef,...) werden verarbeitet  
Kompilieren | .s | C Anweisungen werden in Assembler übersetzt  
Assemblieren | .o | Assembler Befehle werden in ein binäres Maschinenbefehlsmuster übersetzt   
Linken | .out | Es werden alle Maschinenbefehle und Bibliotheken aus verschiedenen Objektdateien zusammengeführt und Speicheradressen vergeben   

Um das übersetzte Programm für einen Mikrocontroller zu verwenden muss das Programm noch in ein Format übersetzt werden das der Programmer verwenden kann. In unserem Fall eine Hex-Datei (.hex).  

![Übersetzungsvorgang ](https://github.com/suspam14/la1/blob/master/C_Uebersetzungsvorgang.svg)  
Quelle: Mikrocontroller Skript von Professor Steiner  

# Makefiles
Für den Übersetzungsvorgang von C-Programmen greifen IDEs üblicherweise auf das Übersetzungungstool *make* zurück. 
Wenn dieses Tool aufgerufen wird greift es auf eine Steuerdatei, die sogenannte *Makefile*, zurück und steuert den Übersetzungsvogang. 
Ein Eintrag in der Makefile besteht aus den **Zielen**, den **Abhängigkeiten** und den **Befehlen**.

### Syntax einer Makefile  
```
Ziel A: Abhängigkeit 1, Abhängigkeit 2,...  
[Tab] Kommando   
[Tab] Kommando  
...

Ziel B: Abhängigkeit 1, ...   
[Tab]   Kommando  
...  
```
## Funktionsweise einer Makefile
Wenn man die Makefile mit dem Befehl *make* aufruft wird aufruft wird das erste Ziel aufgerufen und auf jegliche Abhängigkeiten überprüft. Falls hinter dem Befehl *make* noch ein Ziel angegeben wird (wie z.B. make clean), dann wird bei diesem Ziel begonnen. Falls es eine Abhängigkeit auf ein Ziel gibt wird dieses überprüft. Falls die Datei bereits exestiert wird der Zeitstempel verglichen und entschieden ob ein erneutes ausführen der Kommandos überhaupt nötig ist. Falls die Datei nicht exestiert werden die Befehle abgearbeitet.
### Besondere Ziele einer Makefile  
#### So gut wie jede Makefile besitzt besondere Ziele, die in jeder Makefile gleich heißen.  
Name | Beschreibung    
--- | ---  
clean | löscht alle Dateien die durch das Übersetzen des programms entstehen  
cleanAndBuild | führt einen clean aus und übersetzt das programm neu  

### Fehler beim Abarbeiten der Befehle  
Falls beim Abarbeiten von Befehlen in der Makefile Fehler auftreten bricht der Vorgang ab. Um zu kontrollieren ob im vorherigen Befehl ein Fehler aufgetreten ist, kann man in der lokalen Variable der Shell namens `$?` mit dem Befehl `echo $?` nachschauen. Wenn in dieser eine 0 steht ist kein Fehler aufgetreten, wenn eine 1 steht schon.
Fehler können zum Beispiel beim Ziel *clean* auftreten, wenn Dateien gelöscht werden sollen die nicht exestieren. Dieses Problem kann umgangen werden in den man vor den Befehl ein `-` setzt. Das bezweckt dass das make Tool weiter arbeitet falls ein Fehler auftritt.

### Zeitstempel ändern
Falls ein Ziel bereits exestiert wird der Zeitstempel verglichen um zu bestimmen ob ein erneutes ausführen der Befehle nötig ist. Ist der Zeitstempel von main.c aktueller als der von main.o muss main.o neu erstellt werden, umgekehrt hingegen nicht. Um diesen zu ändern gibt es den shell Befehl `touch <Dateiname>`.

# Übung 1
In der ersten Übung haben wir ein Programm erstellt das den Text *Guten Morgen* ausgeben soll.  
```c
#include <stdio.h>

int main()
{
printf("Guten Morgen");
return 0;
}
```
Makefile zur Übersetung des Beispielprogramms:
```
# Das ist ein Kommentar

test1: main.o
	gcc -o test1 main.o

main.o: main.c
	gcc -c main.c

cleanAndBuild: clean test1


clean:  
	-rm main.o
	-rm test1
 
```
Als Kompiler haben wir den GCC Compiler verwendet.  
#### Verwendete Kommandos
Kommando | Beschreibung
--- | ---
gcc - c | Präprozessieren, kompilieren und assemblieren ohne zu linken. Es entsteht eine Objektdatei (.o)
gcc -o | das Programm wird gelinkt
-rm | Datei wird gelöscht  
# Übung 2
In der zweiten Übung haben wir ein Programm für den Arduino Nano geschrieben das die On-Board LED blinken lassen soll. Dieses Programm besteht aus mehreren Dateien, somit ist die Makefile komplexer.

**main.c**
```c
#include <avr/io.h>
#include <util/delay.h>
#include "util.h"

int main ()
{
	DDRB = (1 << PB5);
	while (1)
		{
			toggleLed();
			_delay_ms(500);
		}
	return 0;
}
```

**util.c**
```c
#include <avr/io.h>

void toggleLed () {
	PORTB^= (1<<PB5);
}
```

**util.h**

```c
ifndef UTIL_H
#define UTIL_H

void toggleLed();

#endif //UTIL_H
```
**Makefile**

```
main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

main.elf: main.o util.o
	avr-gcc -o main.elf main.o util.o

main.o: main.c util.h
	avr-gcc -mmcu=atmega328p -Os -DF_CPU=16000000 -c main.c

util.o: util.c
	avr-gcc -mmcu=atmega328p -Os -DF_CPU=16000000 -c util.c

clean: 
	-rm *.o
	-rm main.elf
	-rm main.hex
  
cleanAndBuild: clean main.hex

```
Um das Programm für den Arduino verwenden zu können haben wir den AVR-GCC Kompiler anstatt des GCC Kompilers verwendet. 

### Anmerkung:
Der größe Unterschied zwischen der ersten und der zweiten Übung bestand darin, dass die zweite aus mehreren Datein bestand. Diese mussten richtig zusammengeführt werden.
