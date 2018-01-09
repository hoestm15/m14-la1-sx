# Laborprotokoll KW51
## Übersetzung mit make

### Theorie:


Bei der c-Programmierung verwendet man im normalfall eine Integrated Development Environment(IDE) 
wie Netbeans oder Codeblocks um eine Übersetzung vorzunehmen. Diese Entwicklungsumgebungen greifen 
auf Make als Übersetzungstool zurück.

Ruft man make auf, so wird eine Steuerdatei Namens  **Makefile** aufgerufen ! 
In dieser Datei sind alle relevanten Informationen zu finden -->

-->  was ist das Ziel der Übersetzung?  
--> aus welchen Dateien (Files) besteht das Projekt?  
--> welche Abhängigkeiten zwischen den Dateien sind gegegeben?  
--> welche Tools (Compiler, Linker, ...) werden wie und zu welchem Zeitpunkt aufgerufen?  


#### Welche Übersetzungsschritte sind erforderlich ?

Eigentlich besteht ein C-Projekt aus mehreren C-Quelltextdateien 
  --> .c Dateien und den dazu passenden Header-Dateien --> .h Dateien !

**Schritt 1:** Compilieren der Quelltextdateien zu Objektdateien --> .o Dateien

Beim Atmel megaAVR µController wird hierfür der GNU-Compiler avr-gcc verwendet. Dabei muss
man folgendes beachten: 

--> Mit -c wird nur compiliert, der Linker wird nicht gestartet.  
--> Mit der Option -mmu wir der µC Typ mitgteilt.  
--> für eine warnungsfreie Compilierung muss eine Optimierungsoption angegeben werden.  
--> Manche Bibliotheksfunktionen wie zb. _delayms(..) benötigt man ein #define F_CPU ...  
    um die Taktfrequenz mitzuteilen. Solche defines können im Quelltext oder beim Compiler
    aufruf angegeben werden. 

**Schritt 2:**

Linken der beiden Dateien main.o und utils.o zu der Programmdatei prog.elf .
Mit der Option -o wird der  Name der zu erstellenden Programmdatei angeben. Wenn diese Datei 
fehlt, wird eine Datei a.out erzeugt.


**Schritt 3:** 

Erzeugen der Programmerdatei prog.hex aus prog.elf

**Schritt 4:**

Wäre die Ausgabe zusätzlicher Programminfos , ist aber nicht zwingend nötig.


### Übung am PC

Ziel der Übung war, es zu verstehen wie die Übersetzung mit Hilfe der Übersetzungstools make funktioniert.
--> Hier einige Ausschnitte der Übung .

### Makefile 

flash: main.hex bootloader.hex
       avrdude -c usbasp -p atmega328p -e -U flash:w:main.hex:i -U flash:w:boot
       #avrdude -c usbasp -p atmega328p  -U flash:w:bootloader.hex:i


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
       
## Quelltext-C

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main()
{

      DDRB |=(1 << PB5);
      while(1)
      {
              PORTB ^= (1 <<PB5);
              _delay_ms(200);
      }

      return 0;
}

### Übersetzung mit make

Die Übersetzung kann auch mit einem einzigen Aufruf make erfolgen. In diesem Fall muss sich im Projektverzeichnis die Datei Makefile befinden --> siehe oben !

Makefiles bestehen immer aus 1 oder mehreren Targets, das Ende vom Namen wird mit 
einem Doppelpunkt gekennzeichnet. Unter den Targets stehen die Anweisungen die ausgeführt werden
müssen, um das Ziel zu erreichen. Damit Anweisungen als solche erkannt werden, ist es nötig, dass sie 
mithilfe eines echten Tabulator eingerückt werden. 

Rechts neben den Makefile-Namen stehen die Abhängigkeiten --> Depencies , sind mehrere vorhanden, müssen
sie mit Leerzteichen getrennt sein. 

Abhängigkeiten wären :
                       --> andere Targets
                       --> Dateien
                       
Mithilfe des Targets clean ist es möglich, alle Daten zu löschen. 
Ruft man also make clean auf --> alle erzeugten Daten werden gelöscht.



