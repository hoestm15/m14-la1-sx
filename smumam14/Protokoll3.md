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
int main(void)  
{  
  volatile unsigned char x;   
  x= 10 + 23; 
  
  return x;  
}  
```  
  
  
```c
int main(void)  
{  
  volatile unsigned char a = 10;  
  volatile unsigned char b = 20;  
  volatile unsigned char e = a + b;  
  
  return e;  
} 
```

Die entsprechenden Maschinenbefehle dazu sind: 



[siehe auch: ATMEL Instruction Set Manual](http://www.atmel.com/images/Atmel-0856-AVR-Instruction-Set-Manual.pdf)
