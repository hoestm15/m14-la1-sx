# 3. Protokoll

Name: Michael Mörth  
Klasse: 4AHME  
Gruppe: 2  

Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Moritz Martinak, Mario Nabernik, Muri Lorenz, Platzer Andreas, Marcel Köhler    
Abwesend: -

## Protokolle und Besprechung der letzten Einheit

Zu Beginn der Stunde begannen wir damit, unsere Protokolle der letzten Stunden zu besprechen. Anschließend begannen wir damit den Stoff der letzten Einheit zu besprechen.  
Folgende Dinge wurden besprochen:
* Aufbau des Atmega328p
* Atmel Studio
* Assembler Befehle

Für genauere Informationen zu den besprochenen Themen können Sie [hier](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll2_7.11.2017.md) finden.

## Fortführung der Analyse von der Abarbeitung von Programmen
Wie in der letzten Einheit haben in der heutigen Einheit die Abarbeitungen von Programmen analysiert.

### Wichtige Informationen zu Beginn der Stunde

#### Das Schlüsselwort volatile
> Volatile ist ein Zusatz bei der Deklaration von Variablen in Programmiersprachen wie C, C++, Java oder C#.  
> In C und C++ wird durch diesen Typqualifikator spezifiziert, dass sich der Wert der Variable jederzeit ändern kann, beispielsweise durch andere Prozesse, Threads oder sogar externe Hardware. Bei der Generierung des Maschinen-Codes aus einem in C oder C++ geschriebenen Programm verhindert die Kennzeichnung einer Variablen als volatile eine in diesem Fall die Funktionalität beeinträchtigende Optimierung, so dass das Programm immer auf den tatsächlich in der Hardware vorhandenen Wert zugreift.

*Quelle: [Wikipedia](https://de.wikipedia.org/wiki/Volatile_(Informatik))*

### Anlegen einer Variable
#### Quellcode
```c
int main (void)
{
	volatile unsigned char x;
	x = 12;
	
	return x;
}
```
Unsere Aufgabe war es nun, das Programm im Debugging-Modus zu starten. Anschließend waren die Maschinenbefehle zu analysieren und die Befehle im [Datasheet des ATmega328p](http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf) nachschlagen.
