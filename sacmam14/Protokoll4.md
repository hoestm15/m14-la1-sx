# 4. Protokoll  
## Thema: Makefiles  
**Name:** Sackl Martin   
**Klasse** 4ahme    
**Gruppe:** 3

Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schuster   
Abwesend: Schmuck  
*******************************************************************************************************************************************  
### Wiederholung: Wie wird ein C-Programm übersetzt?  
Um ein C-Programm übersetzen zu können, müssen folgende Schritte durchgeführt werden:  

Schritte | Funktion  
------- | --------  
**Präprozessieren** | main.c wird hier vorbereitet  
**Compelieren** | Assemblercode wird erzeugt, aus main.c wird main.a    
**Assemblieren** | Assemblercode wird in Maschinensprache übersetzt, aus main.a wird main.o  
**Linken** | Programmteile werden miteinander verbunden, ausführbares Programm mit der Endung main.exe oder main.out (Windows oder Ubuntu)  
**Umwandeln** | Ausführbares Programm wird in ein Format umgewandelt, dass der Programmer versteht (Hex, ...)    

Je gröber der Sprachgebrauch ist, desto eher werden alle Schritte zu einem Schritt, **Compelieren**, zusammengefasst.  
*******************************************************************************************************************************************  
### Make-Tool  
Es ist ein Build-Management Tool, das gewisse Kommandos in Abhängigkeiten von Bedingungen ausführt. Dieses Tool übernimmt den gesamten Übersetzungsvorgang und liest **Makefiles**.  

### Makefiles  
Ein Makefile teilt dem Programm make mit was und wie es etwas tun soll. In einem Makefile sind die Abhängigkeiten des Übersetzungsprozesses von Programmen erfasst.  
#### Aufbau von Makefiles:  
```  
Ziel 1: Abhängigkeiten  
  ->  Kommando A  
  ->  Kommando B  
  -> ...  

Ziel 2: Abhängigkeiten  
  ->  Kommando A  
  ->  Kommando B  
  -> ...  
```  
**Für "->" muss ein echter Tabulator gesetzt werden!**  

### Kommando "make"  
Mit dem Kommando `make` wird die Abarbeitung der Makefiles gestartet. Das make-Tool erkennt ob Ziele schon abgearbeitet sind oder noch ausgeführt werden müssen. Wenn der Zeitstempel nicht passt, muss alles neu compeliert und gelinkt werden. Mit dem Befehl `touch` kann man den Zeitstempel im nachhinein ändern.  

Kommando | Beschreibung  
-------- | ------------  
make clean | Dateien werden gelöscht  
make cleanAndBuild | Dateien werden zuerst gelöscht und anschließend neu erzeugt  
make main.o | C-Code wird in Maschinensprache übersetzt    

### Zeitstempel  
Er sagt aus zu welchen Zeitpunkt die Datei geschrieben oder verändert wurde.  
*************************************  
### Übungen mit Makefiles  
#### Übung 1
Wir haben ein Programm geschrieben, dass im Terminal "Guten Morgen" ausgeben sollte.  
**main.c** 
```  
#include <stdio.h>  

int main()  
{
printf("Guten Morgen\n");  
return 0;  
}  
```  
**Dazugehörige Makefile:**  
```  
test1: main.o  
	gcc -o test1 main.o  

main.o: main.c  
	gcc -c main.c  

cleanAndBuild: clean test1  

clean:  
	-rm main.o  
	-rm test1  
```  
Beschreibung der Kommandos: 

Kommando | Beschreibung  
-------- | ------------  
gcc -o test1 main.o | Compeliervorgang, .o Datei entsteht  
gcc -c main.c | Linkvorgang, Name der Datei wird vergeben  
-rm ... | Datei wird gelöscht, durch das `-` wird bei einem Fehler, der Fehler ignoriert und der Löschvorgang wird fortgesetzt  

#### Übung 2  
Es soll ein C-Programm für den Arduino Nano geschrieben und übersetzt werden. Das Programm soll eine Led togglen. Die Funktion toggleLed() soll in util.c programmiert werden.  

**main.c** -> hier wird das eigentliche Programm programmiert  
```  
#include <avr/io.h>  
#include <util/delay.h>  
#include "util.h"  

int main ()  
{
 DDRB = (1<<PB5);  
 while (1)  
 {  
  toggleLed();  
	_delay_ms(200);  
 }  
 return 0;  
 }  
```  
  
**util.c**  -> hier die Funktion toggleLed() programmiert  
```  
#include <avr/io.h>  

void toggleLed ()  
{  
PORTB ^= (1<<PB5);  
}  
```  
  
**util.h**  -> Funktion toggleLed() wird hier deklariert  
```
#ifndef UTIL_H  
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
	avr-gcc -mmcu="atmega328p" -Os -DF_CPU=16000000 -c main.c  

util.o: util.c  
	avr-gcc -mmcu="atmega328p" -Os -DF_CPU=16000000 -c util.c  

clean:  
	-rm *.o  
	-rm main.elf  
	-rm main.hex  
```  

Ziel | Beschreibung  
---- | ------------  
main.hex | Umwandlung in .hex Datei  
main.elf | C-Programme werden gelinkt  
main.o | Headerdatei util.h wird eingebunden, main.c wird in Maschinencode übersetzt  
util.o | util.c wird in Maschinencode übersetzt  

**Clean** -> alle Dateien mit der Endung .o, sowie main.elf und main.hex werden gelöscht  
**Wichtig:** Es müssen die richtigen `avr-` Kommandos mit den entsprechenden Optionen verwendet werden, damit das Programm für den Arduino Nano funktioniert.  
