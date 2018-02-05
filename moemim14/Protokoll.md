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
Wie beim Programm zuvor war es unsere Aufgabe, das Programm im Debugging-Modus zu starten und anschließend die Maschinenbefehle im [Datasheet des ATmega328p](http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf) nachzuschlagen und kurz zu beschreiben.

#### Assemblerbefehle
Maschinenbefehl | in Textform | Beschreibung
--------------- | --------- | ---------
cf.93 | PUSH R28 | [siehe](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll.md#assemblerbefehle)
df.93 | PUSH R29 | [siehe](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll.md#assemblerbefehle)
00.d0 | RCALL PC+0x0001 | Es wird zum nächsten Befehl gesprungen und es werden 2 Bytes auf dem Stack abgelegt.
cd.b7 | IN R28,0x3D | [siehe](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll.md#assemblerbefehle)
de.b7 | IN R29,0x3E | [siehe](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll.md#assemblerbefehle)
8c.c0 | LDI R24,0x0C | [siehe](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll.md#assemblerbefehle)
89.83 | STD Y+1,R24 | Wert aus dem Register R24 wird am Stack abgelegt (Speicheradresse ist die Adresse der ersten Variable a) 
88.e0 | LDI R24,0x08 | Der Wert 8 wird im Register R24 abgelegt.
89.83 | STD Y+2,R24 | Wert aus dem Register R24 wird am Stack abgelegt (Speicheradresse ist die Adresse der ersten Variable b) 
89.81 | LDD R24,Y+1 | Der Wert der Variable a wird in das Register R24 geladen
2a.81 | LDD R18,Y+2 | Der Wert der Variable b wird in das Register R18 geladen
30.e0 | LDI R19, 0x00 | Der Wert 0x00 wird ins Register R19 geladen.
28.0f | ADD R18,R24 | Addition der beiden Register. R18 ist der Speicherort. Das Carry-Flag wird nicht berrücksichtigt.
31.1d | ADC R19,R1 | Addition mit Berücksichtigung des Carry-Flags. [Weitere Informationen zum Carry-Flag](https://de.wikipedia.org/wiki/Übertragsbit)
0f.90 | POP R0 | Die Variable b wird freigegeben.
0f.90 | POP R0 | Die Variable a wird freigegeben.
df.91 | POP R29 | [siehe](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll.md#assemblerbefehle)
cf.91 | POP R28 | [siehe](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll.md#assemblerbefehle)

### Testen der Geschwindigkeiten von bestimmten Operationen
Ziel dieser Übung war es, zu erkennen wie lange bestimmte Operationen zur Ausführung brauchen. Das geteste System war wie immer der Atmega328p.
#### Beispiel für einen der angewandten Quelltexte
```c
int main (void)
{
	volatile unsigned double a = 192,23;
	volatile unsigned double b = 172,231;
	
	return a*b;
}
```


Operation| Datentyp | Anzahl der benötigten Takte | in µs | Bemerkungen
---|---|---|---|---
Addition| 8 Bit + 8 Bit | 46 Takte | 2,89
Multiplikation| 8 Bit * 8 Bit | 47 Takte | 2,96 | kaum ein Unterschied zur Addition (Grund: eigener Multiplikationsbefehl vorhanden)
Division| 8 Bit / 8 Bit | 123 Takte | 7,77 | Da kein eigener Befehl zur Verfügung steht, wird mit Schleifen gearbeitet -> Darum längere Zeit als bei der Multiplikation
Addition| 32 Bit + 32 Bit | 192 Takte | 12,09 |
Multiplikation| 32 Bit * 32 Bit | 165 Takte| 10,39 |
Division| 32 Bit / 32 Bit | 701 Takte | 44,16 |
Addition| float + float | 905 Takte | 57,01 |
Multiplikation| float * float | 1763 Takte | 111,06 |
Division| float / float | 1380 Takte | 86,94 | Normalerweiße benötigt der Prozess des Dividierens länger als der Prozess zum Multiplizieren. Eine mögliche Ursache für die Kürze Zeit wäre eventuell, dass sich die gewählten Werte einfacher dividieren lassen.
Division| double / double | 1380 Takte | 86,94 | Kein Unterschied zu float da der Datentyp double wie der Datentyp float vom µP behandelt wird.

#### Erkentnisse des Tests
In Systemen in der Echtzeit erforderlich ist, ist es sehr wichtig, immer den kleinstmöglichen Datentyp zu verwenden. Wie man bei der Division von zwei float Werten erkennen kann, können dadurch lange Verzögerungen entstehen und die Echtzeit kann unter Umständen nicht mehr gewährleistet werden.

### Resümee
Die Verwendung des Schlüsselwortes volatile führt dazu, das der Compiler das Programm nicht verkürzt und "unnötige" Befehle nicht ausführt. In manchen Anwendungen ist die Verwendung von volatile allerdings dringend nötig.
Wie bereits [hier](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll.md#erkentnisse-des-tests) erwähnt kann die Wahl von zu großen Datentypen zum Verlust der Echtzeit führen.
