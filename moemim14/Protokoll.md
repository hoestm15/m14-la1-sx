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

#### Assemblerbefehle
Maschinenbefehl | in Textform | Beschreibung
--------------- | --------- | ---------
cf.93 | PUSH R28 | Der Wert des Registers R28 wird auf den Stack gelegt.
df.93 | PUSH R29 | Der Wert des Registers R29 wird auf den Stack gelegt.
1f.92 | PUSH R1 | Der Wert des Registers R1 (*immer 0*) wird auf den Stack gelegt. 
cd.b7 | IN R28,0x3D | Der Wert 0x3D wird aus dem I/O-Register in das Register R28 geladen.
de.b7 | IN R29,0x3E | Der Wert 0x3E wird aus dem I/O-Register in das Register R29 geladen.
8c.e0 | LDI R24,0x0C | Die Konstante 0C (0C =^ dezimal 12) wird im Register R24 abgelegt.
89.83 | STD Y+1,R24 | Konstante aus dem REgister R24 wird am Speicherplatz des Stacks der lokalen Variable abgelegt. Die Angabe Y+1 entspricht dem nächsten freien Speicherplatz im Y-Register ([siehe Y-Register](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll2_7.11.2017.md#xyz-register))
89.81 | LDD R24,Y+1 | Die Variable wird in Register R24 geladen.
90.e0 | LDI R25,0x00 | Ins Register R25 wird der Rückgabewert geladen.
0f.90 | POP R0 | Variable wird freigegeben.
df.91 | POP R29 | Das Register R29 wird vom Stack entfernt.
cf.91 | POP R28 | Das Register R28 wird vom Stack entfernt.

#### Frage während der Stunde
Während der Stunde kam die Frage auf, wieso das Register R29 vor dem Register R28 entfernt wird. Die Antwort ist ganz einfach: Der Stack kann nur von oben nach unten gelesen werden. Genauere Informationen können [hier](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll2_7.11.2017.md#stack) gefunden werden.

### Addition von zwei Variablen
#### Quellcode
```c
int main (void)
{
	volatile unsigned char a = 12;
	volatile unsigned char b = 8;
	
	return a+b;
}
```
Wie beim Programm zuvor war es unsere Aufgabe, die Maschinenbefehle im [Datasheet des ATmega328p](http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf) nachzuschlagen und kurz zu beschreiben.


