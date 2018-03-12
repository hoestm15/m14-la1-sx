# 4.Protokoll  
  
  **Name**:  *Sackl Roland*  
  **Datum:** *06.03.2018*  
  **Uhrzeit:** *9:40-12:25*  
  **Gruppe:** *3*  
  
  **Abwesend:**   Schmuck Martin   
  **Anwesend:**   Sackl Martin, Sackl Roland, Reinbacher Bernhard,Sammer Daniel,Ruffennacht Florian,Schuster Patrick


## Wiederholung: Übersetzungsvorgang eines Programmes  
Das gesamte Übersetzen eines Programmes versteht man im groben Sprachgebrauch  unter _Compelieren_ , jedoch ist das Compelieren nur ein Teil davon. Man benötigt für die gesamte Übersetzung eines Programmes folgende Schritte:    


 Name | Dateityp vorher | Dateityp nacher | Beschreibung
 ------- | --------  |------- | --------  
*Präprozessieren* | main.c | main.? | Hier wird das Programm vorbereitet. Bearbeitung von Anweisungen wie `#include`, `#define` und `#if`.  
*Compelieren* | main.? | main.a | Hier wird aus dem preprozessierten Code ein Assemblercode erzeugt.   
*Assemblieren* | main.a | main.o | Übersetzen des Assemblercode in Maschinencode.  
*Linken* | main.o | main.exe/ main.out |  Liner verbindet alle Programmteileund vereint sie zu  einen ausführbares Programm.  
*Umwandeln* | main.exe/main.out | z.B. main.hex | Die Datei wird in ein Format umgewandelt, das der Programmer versteht. (z.B. Hex)



## make-Tool
Der gesamte Übersetzungsvorgang wird durch das **make-Tool** übernommen. Dieses ruft sogenannte *Makefiles*  auf.
Im Normalfall wird der Übersetzungsvorgang durch das "make Tool" übernommen. Hierfür benötigt man ein *Makefile*.

Weitere Informationen:  
[Mikiwiki/make](http://mikiwiki.org/wiki/make)  
[Wikipedia/make](https://de.wikipedia.org/wiki/Make)    
   


### Makefile  
Ein Makefile wird mithilfe eines Texteditors geschrieben, worin die Information für das make Tool stehen. Es werden Ziele(targets), Abhängigkeiten(dependencis) und Kommandos(Commands) benötigt. In der Folgenden Grafik werden diese Ziele, Abhängigkeiten und Kommandos veranschaulicht.  
```
Ziel A: Abhängigkeiten  
*tab* Kommando 1  
*tab* Kommando 2   
*tab* Kommando 3 ...  
  
Ziel B: Abhängigkeiten  
*tab* Kommando 1  
*tab* Kommando 2  
*tab* Kommando 3 ...   
```  
Bei *tab* ist es wichtig einen richtigen Tabulator zu verwenden und ein Leerzeichen zwischen den Zielen zu setzen ansonsten funktioniert das gesamte Tool nicht.


Englisch | Deutsch
-------- | --------
_target_ | Ziel
_dependencies_ | Abhängigkeiten
_command_ | Anweisung, Regel  

 
## make im Terminal  
Im Terminal kann man mit dem Kommando make die Abarbeitung des Makefile's starten. Mit dem Befehl sucht er selbstständig ob die angegebenen Zieler erreicht werden.Es schaut auch ob alle Dateien auf den neuesten Stand sind. Wenn main.c einen jüngeren Zeistempel hat als die *main.o* dann wird alles neu compeliert und gelinkt.

### Zeitstempel
Der **Zeitstempel** gibt an wann eine Datei das letzte Mal verändert wurde.Der Zeitstempel ist auf Millisekunden genau.  

### Touch  
Den zeitstempel von Dateien ann man mit touch ändern(auf die aktuelle Zeit bringen). Falls noch keine Datei vorhanden ist, erzeugt touch eine neue leere Datei.    

## Übungen mit _Makefiles_  
### Übung 1: Übersetzen eines einfachen C-Programms  
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



Befehl | Beschreibung  
------ | ------------    
make clean | Alle Dateinen die von *make* erstellten würden werden gelöscht.   
make cleanAndBuild |  Alle Dateinen die von *make* erstellten würden werden gelöscht und danach wieder erstellt.  
make main.o | Der Programmiercode wird in Maschinenbefehlt übersetzt.

Es wurden folgende Kommandos verwendet:

Kommando | Beschreibung
---------| ------------
gcc -c | Es wird kompiliert, aber nicht gelinkt. Es entsteht die .o-Datei
gcc -o | Beei diesen Befehl wird gelinkt und der Name der Datei vergeben
-rm | Die Datei wird gelöscht. Durch das - wird der Befehl auch bei einem Fehler fortgesetzt.




### 2.Übung  
Ein C-Programm für den Arduino Nano schreiben, das die LED toggled lässt. Diese Funktion soll in in util.c geschrieben werden.  
**main.c**  
```  
#include <avr/io.h>
#include <util/delay.h>
#include "util.h"

int main(){

        DDRB = (1<<PB5);

        while(1){
           toggleLed();
           _delay_ms(200);
        }
        return 0;

}  
```  
**util.c**  
```  
#include <avr/io.h>

void toggleLed()
{
   PORTB ^=(1 << PB5);
}  
```  
**util.h**  
```  
#ifndef UTIL_H
#define UTIL_H

extern void toggleLed();

#endif  // UTIL_H
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
 ```  
 
Datei | Funktion  
----- | --------  
main.hex : main.elf | Die Executable File wird in eine Hex-Datei umgewandelt
util.c | Das *toggeln* der LED wird programmiert.  
util.h | Die Funktion *toggleLed()* wird deklariert.  
main.elf: main.o util.o | Mittels den Linker werden beide Dateien zuammengeführt  
util.o: util.c | Die Datei util.c wird in Maschinensprache übersetzt
clean: | Es werden alle Dateien mit der Endung .o, main.elf und main.hex gelöscht




