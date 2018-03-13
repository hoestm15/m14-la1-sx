# _Protokoll Vierte Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 06.03.2018**  
**Uhrzeit: 9:40-12:25**  
**Anwesend: Reinbacher B., Ruffenacht F., Sackl M., Sackl R., Sammer D., Schuster P.**  
**Abwesend: Schmuck Martin**  
  
-----------------------------------------------------------  
#### Wiederholung: Übersetzungsvorgang eines Programms  
![Protokoll Einheit 2](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/einheit4.jpg)  
Die meisten verwenden den Begriff _Kompilieren_ zusammenfassend für die Teilbereiche _Präprozessieren, Kompilieren_ und _Assemblieren_. Beim Kompilieren soll der Quellcode einer bestimmten Programmiersprache in eine für die Maschinen verständliche Sprache (Maschinensprache) übersetzt werden.   
Die Aufgabe vom Präprozessor ist es, Eingabedaten für folgende Programme vorzubereiten und diese weiterzugeben. Der daraus entstandene Code wird als Zwischencode bezeichnet.  
Der Assembler soll Code von Assemblersprache in Maschinensprache übersetzen (z.B. CLI -> 11111010).  
Der Linker hat die Aufgabe, verschiedene Programmmodule zu einem ausführbaren Programm (_executeable program_) verbinden.  

[Wikipedia/Compiler](https://de.wikipedia.org/wiki/Compiler)  
[Wikipedia/Präprozessor](https://de.wikipedia.org/wiki/Pr%C3%A4prozessor)  
[Wikipedia/Assembler](https://de.wikipedia.org/wiki/Assembler_(Informatik))  
[Wikipedia/Linker](https://de.wikipedia.org/wiki/Linker_(Computerprogramm))  

------------------------------------------------------------  
#### make  
_make_ ist ein Programm/Tool zum Übersetzen von Steuervorgängen. Es benötigt immer ein _Makefile_.  
>make (englisch für machen, erstellen) ist ein Build-Management-Tool, das Kommandos in Abhängigkeit von Bedingungen ausführt. Es wird hauptsächlich bei der Softwareentwicklung als Programmierwerkzeug eingesetzt.
>Genutzt wird es beispielsweise, um in Projekten, die aus vielen verschiedenen Dateien mit Quellcode bestehen, automatisiert alle Arbeitsschritte (Übersetzung, Linken, Dateien kopieren etc.) zu steuern, bis hin zum fertigen, ausführbaren Programm. 
>make ist jedoch so flexibel ausgelegt, dass es auch beliebige andere Aufgaben steuern kann, bei denen die zeitliche Abhängigkeit von Dateien eine Rolle spielt.  
Quelle: [Wikipedia/make](https://de.wikipedia.org/wiki/Make)  
-----------------------------------------------------------  
##### Makefile  
Ein Makefile ist dazu da, dem Programm make mitzuteilen, was es tun soll (_target_) und wie es es tun soll (_command_). Des weiteren kann man zu jedem _target_ angeben, von welchen anderen targets oder Dateien dieses abhängt.  
mehr dazu: [Makefile](http://www.ijon.de/comp/tutorials/makefile.html)  
  
###### Syntax  
```
<target 1>: dependencies  
<tab>command 1  
<tab>command 2  
<tab>command 3  
<tab>command n  

<target 2>: dependencies  
<tab>command 1  
<tab>command 2  
<tab>command 3  
<tab>command n  
```

Englisch | Deutsch
-------- | --------
_target_ | Ziel
_dependencies_ | Abhängigkeiten
_command_ | Anweisung, Regel  

--------------------------------------------------------  
##### Aufrufen von _make_  
Im Terminal kann man mittels dem Kommando _make_ die Abarbeitung des _Makefile_´s starten. Das _make_-Tool erkennt selbstständig, ob _targets_ überhaupt wieder erreicht werden müssen oder ob sie sich bereits im aktuellsten Zustand befinden. Zuerst wird geschaut, ob die Abhängigkeit (_dependency_) als Ziel (_target_) weiter unten im _Makefile_ befindet. Ist das nicht der Fall, dann wird der Zeitstempel des _targets_ mit dem des vorhandenen, gleichnamigen verglichen. Dadurch kann _make_ möglichst effektiv arbeiten.  
  
##### Zeitstempel  
Ausgangssituation: aus main.c eine main.o erstellen  
Beim ersten Aufruf von _make_ im Terminal werden die _commands_ (Regeln zum Erreichen des Ziels) abgearbeitet. Ruft man _make_ ein zweites Mal im Terminal auf, so vergleicht es die Zeitstempel. Ist der Zeitstempel von main.o aktueller als der von main.c, dann ist main.o aktuell und braucht nicht erneut erstellt werden. Hätte jemand in der Zwischenzeit main.c bearbeitet und ne gespeichert, dann ist der Zeitstempel von main.c aktueller und main.o muss neu erstellt werden.  
Der Zeitstempel ist auf Millisekunden genau.  

---------------------------------------------------------  
##### Übungen mit _Makefiles_  
###### Übung 1: Übersetzen eines einfachen C-Programms  
Das Programm soll mit Eingabe des _make test1_-Kommandos im Terminal den Text "_Guten Morgen!_" ausgeben.  
  
**main.c**  
```
#include <stdio.h>

int main()
{
printf("Guten Morgen!\n");
return 0;
}
```
**Makefile**  
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
target | dependencies | commands
------ | ------------ | ----------
test1 | main.o | gcc -o test1 main.o
main.o | main.c | gcc -c main.c
cleanAndBuild | clean test1 | -
clean | - | -rm main.o & -rm test1  

  
Das "-" vor rm bedeutet, dass wenn eine zu löschende Datei bereits gelöscht wurde, der ausgegebene Fehler ignoriert werden soll und die nachfolgenden Anweisungen ausgeführt werden sollen. Dies funktioniert über die  Rückgabewerte der Kommandos. Ist dieser ungleich 0, so  wird ein Fehler ausgegeben.  
  

gcc -c: kompiliere und assembliere, ohne zu linken, das Ergebnis sind Objektfiles  
gcc -o: gleich, nur das der resultierende Filename vegeben werden kann  
siehe: [gcc](https://www-user.tu-chemnitz.de/~hmai/gcc/Ausarbeitung_1/allg_opt.html)  
  
Mit dem Aufruf _make_ werden alle Kommandos ausgeführt. Es besteht aber auch die Möglichkeit, die Schritte einzeln aufzurufen:  
  
Kommando | Beschreibung
-------- | ------------
make clean | Die von _make_ generierten Dateien werden gelöscht
make cleanAndBuild | generierte Dateien werden gelöscht und anschließend neu erzeugt
make main.o | C-Programm wird in Maschinensprache übersetzt
  
-----------------------------------------------------------  
  
###### Übung 2: Zusammenführen von 2 C-Dateien mit Hilfe eines Makefiles  
Es soll für den Arduino Nano ein C-Programm mittels Makefiles übersetzt werden. Die LED soll getoggled werden. Die Funkion _toggleLed_ soll in einer zweiten C-Datei programmiert werden.  
  
**main.c**  
```
#include <avr/io.h>
#include <util/delay.h>
#include "util.h"

int main ()
{
	DDRB = (1<<PB5);

	while (1) {
		toggleLed();
		_delay_ms(200);
	}
	return 0;
}
```
  
**util.c**  
```
#include <avr/io.h>

void toggleLed ()
{
PORTB ^= (1<<PB5);
}
```
  
**util.h**  
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
  
Schritt | Erklärung
------- | ---------
main.hex : main.elf | Executable File wird in eine Hex-Datei umgewandelt
main.elf: main.o util.o | Beide C-Programme werden mittels Linker zusammengeführt
main.o: main.c util.h | main.c wird in Maschinensprache übersetzt, Einbindung der Header-Datei util.h
util.o: util.c | util.c wird in Maschinensprache übersetzt
clean: | Alle Dateien mit der Endung .o, main.elf und main.hex werden gelöscht
  
  

