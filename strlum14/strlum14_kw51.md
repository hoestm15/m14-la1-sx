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

