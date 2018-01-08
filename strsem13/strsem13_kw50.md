# *Protokoll*  
## *Thema: Makefiles*  
 Name:   Sebastian Strutz  
 Klasse: 4AHME  
 Datum: 26.09.2017  
 Anwesend: Strutz, Strauß, Zitz
 Abwesend: Tuttner, Uhl, Waltl, Wieser
 
### Die Übersetzung mit *make*  
Das Übersetzungstool *make* wird für die Übersetzung eines C-Programes verwendet. Normalerweise wird eine IDE (Integrated Development Enviroment) wie zum Beispiel Codeblocks oder Netbeans verwendet. Alle diese Entwicklungsumgebungen greifen bei der Übersetzung auf das Tool *make* zu. 

Wird der Befehl ausgeführt so wird eine Steuerdatei *Makefile* erstellt. In dieser Datei sind alle relevanten Inforamtionen zu finden:
* was ist das Ziel der Übersetzung?
* aus welchen Dateien besteht das Projekt?
* welche Abhängigkeiten sind gegeben?
* welche Tools (Compiler, Linker, ..) werden wie und zu welchem Zeitpunkt aufgerufen?  


Bei richtiger Erstellung von *Makefile* wird bei der Übersetzung nur das Nötigste gemacht. Das heißt bei bereits compilierten Dateien,  wenn der Quelltext nicht verändert wurde, wird es kein weiteres Mal compiliert.  

### Übersetzungsschritte  
#### Schritt 1: Compilieren der Quelltextdatei zur Objektdatei .o
Bei der Atmel megaAVR Familie, wird dafür der GNU-Compile avr-gcc verwendet.  
```
 avr-gcc -mmcu=atmega328p -Os -c main.c
 ```  
* Mit der Option *-mmcu* wird der MC-Typ mitgeteilt.  
* Mit -Os wird die Programmgröße optimiert.  
* Mit *-c* wird lediglich compiliert.  

#### Schritt 2: Linken der beiden Datein *main.o* und *utils.o* zu einer Programmdatei *prog.elf*
```
 avr-gcc -mmcu=atmega328p -Os -o main.elf main.o utils.o
 ``` 
 * Mit der Option -o wird der Name der zur erstellenden Datei festgelegt.  
 
#### Schritt 3: Erzeugen der Programmdatei  
 ```
  avr-objcopy -O ihex main.elf main.hex
 ```    
 * Aus der *.elf* Datei entsteht eine *i.hex* Datei.
