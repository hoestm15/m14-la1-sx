# Laborprotokoll  
Dritte Einheit am 05. Dez. 2017  
Martin Schmuck  
4AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: niemand 

## Thema der Einheit: µC - Atmel Studio

#### Wiederholung der 2. Einheit  
###### CPU - Register  
Hierbei handelt es sich um die internen Arbeitsregister der CPU (Register = Speicherbaustein, meist aus D-Flip-Flops bestehend). Diese sind jedoch nicht mit den (externen) I/O-Registern zu verwechseln.

###### Atmel Studio   
Im Prozessorfenster findet man:  
* Wert des Program Counters  
* Inhalt der einzelnen Register 
* Frequenz  
* Cyclic Counter 

Im Disassembly findet man:  
* Maschinenbefehl (hexadezimal codiert)
* Assemblerbefehl
* Speicheradressen der Maschinenbefehle
* evtl. kurze Beschreibung des Assemblerbefehls
__________________________________________________
#### Modifizierer
Modifizierer | Auswirkung
-------------|-----------
volatile | Verhindert, dass diese Variable durch einen festen Wert ersetzt wird. Dies ist zum Beispiel erforderlich, wenn die Variable zwar im Programm nicht verändert wird, aber durch äußere Einflüsse (Interrupts, etc.) verändert werden kann. Dadurch muss man diese Variable wie eine Variable behandeln, auch wenn es sich dabei auf den ersten Blick um einen Festwert handelt. Damit darf die Variable nicht mehr vom Code-Optimierer wegoptimiert werden.
unsigned | Zeigt an, dass es sich um eine vorzeichenlose Zahl handelt. Dadurch lässt sich im positiven Bereich mit `unsigned int` ein größerer Zahlenbereich abdecken als mit `(signed) int`
____________________
#### 1. und 2. Übung

Aufgabe war es, folgende Programme zu analysieren:
```c
int main (void)  
{  
  volatile unsigned char x;   
  x = 10 + 23; 
  
  return x;  
}  
```  
  
  
```c
int main (void)  
{  
  volatile unsigned char a = 10;  
  volatile unsigned char b = 20;  
  volatile unsigned char e = a + b;  
  
  return e;  
} 
```

Die entsprechenden Maschinenbefehle dazu sind:

Assemblerbefehl | Beschreibung
--------------- | ------------ 
`PUSH` | Der Inhalt eines internen Registers wird am Stack abgelegt
`RCALL` | Eine Subroutine wird aufgerufen, die Rücksprungadresse wird am Stack abgelegt
`IN` | Der Inhalt eines I/O-Registers wird in ein internes Register geladen
`LDI` | Ein Zahlenwert wird in ein internes Register geladen
`STD` | Der Inhalt eines Registers wird gespeichert
`LDD` | Der mit `STD` abgelegte Wert wird wieder in ein Register eingelesen
`ADD` | Addieren ohne Rücksicht auf das Carry-Flag
`ADC` | Addieren mit Rücksichtnahme auf das Carry-Flag 
`POP` | Variable vom Stack nehmen (Speicherplatz freigeben)
`RET` | Rücksprung von der Subroutine zum rufenden Maschienenbefehl

[siehe auch: ATMEL Instruction Set Manual](http://www.atmel.com/images/Atmel-0856-AVR-Instruction-Set-Manual.pdf)
______________________________________________________
#### Geschwindigkeitstest
Operation | Takte | Anmerkungen
----------|-------|------------
8 Bit + 8 Bit | 46 | -
8 Bit x 8 Bit | 47 | -
8 Bit / 8 Bit | 123 | Längere Dauer, da es keinen eigenen Maschinenbefehl zum dividieren gibt. Hier wird nämlich z.B. rotiert und subtrahiert, und das alles in Schleifen (wie händisch dividieren). Dadurch ist die lange Dauer zu erklären.
32 Bit + 32 Bit | 92 | -
32 Bit x 32 Bit | 165 | -
32 Bit / 32 Bit | 701 | Hier gilt das selbe wie für die 8-Bit-Division
float + float | 905 | -
float x float | 1763 | -
float / float | 1380 | Normalerweise ist eine Multiplikation immer schneller als eine Division. Hier liegt offensichtlich eine Ausnahme vor, welche darin begründet sein mag, dass sich unsere zufällig gewählten Werte sehr leicht dividieren ließen
double / double | 1380 | kein Unterschied zu float, da der µC keine doppeltgenauen Fließkommazahlen kennt, und deshalb, auch wenn double im Quellcode steht, intern nur mit einfacher Genauigkeit rechnet
_________________________________________________________
#### 3. Übung (Schleifen)

```c
int main (void)  
{  
  volatile int i;  
  volatile int a;  
  
  for (i = 0; i < 10; i ++)  
  {  
    a += 10;  
  }
  
  return a;
}  
```
Hier ist der Befehl `BRNE` ( = Branch if Not Equal) ausschlaggebend. Er vergleicht den Inhalt des Registers, in dem die Laufvariable der Schleife steht, mit dem Z-Flag und bricht ab, sobald diese gleich sind. 
