# Protokoll der 3.Einheit (14.11.2017)

## Thema: Assembler

Name:     Florian Nebel  
Klasse:   4AHME  
Gruppe:   2  

Anwesend: Köhler Marcel, Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: ---

## Rückblick

Zu Beginn der Einheit besprachen wir die Themen, mit welchen wir uns in der [vorherigen Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/nebflm14/nebflm14/Protokoll2.md) beschäftigten.
* Atmel Studio
* Hardware
* Stack
* Maschinenbefehle

## Analyse
### Variable erstellen
```c
int main (void)
{
	volatile unsigned char x;
	x = 12;
	
	return x;
}
```

#### volatile
Das Schlüsselwort "volatile" kann als Zusatz bei der Deklaration von Variablen in C, C++, Java oder C# verwendet werden. Dieser "Typqualifikator" legt fest, dass sich der Wert, der Variable auch während einem laufenden Prozess ändern kann. Da bei der Quelltext bei der Generierung des Maschinen-Codes optimiert wird, kommt es zu Problemen. "volatile" verfügt, dass immer auf den tatsächlichen Wert zugegriffen wird, und dass Programm nicht beeinflusst wird.
*Quelle: [wikipedia.org](https://de.wikipedia.org/wiki/Volatile_(Informatik))*

### debuggen
Das Programm wurde von uns im Debugging Modus gestartet, um die Maschinenbefehle einzeln analysieren zu können. Mithilfe des Datenblatts, des [ATmega328p](http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf) konnten wir spezifische Informationen erlangen.

### Assemblerbefehle
In der linken Spalte befinden sich die, durch das Debuggen erlangten Maschinenbefehle in Hexadezimalzahlen. In der mittleren Spalte werden die Befehle in einer textuellen Form dargestellt, welche bereits die Funktion erahnen lässt, rechts die Beschreibung der Befehle.  

| Nr | Maschinenbefehl | in Worten | Kommentar |
| -- | --------------- | --------- | --------- |
| 01 | cf.93 | PUSH R28 | Inhalt von R28 auf Stack legen |
| 02 | df.93 | PUSH R29 | Inhalt von R29 auf Stack legen |
| 03 | 1f.92 | PUSH R1 | Inhalt von R1 auf Stack legen |
| 04 | cd.b7 | IN R28,0x3D | 0x3D in R28 laden |
| 05 | de.b7 | IN R29,0x3E | 0x3E in R29 laden |
| 06 | 8c.e0 | LDI R24,0x0C | 0x0C in R24 laden |
| 07 | 89.83 | STD Y+1,R24 | Inhalt von R24 auf nächsten freien Platz im Y-Register legen |
| 08 | 89.81 | LDD R24,Y+1 | Inhalt von Y+1 in R24 laden |
| 09 | 90.e0 | LDI R25,0x00 | Rückgabewert in R25 laden |
| 10 | 0f.90 | POP R0 | Variable freigeben |
| 11 | df.91 | POP R29 | R29 vom Stack entfernen |
| 12 | cf.91 | POP R28 | R28 vom Stack entfernen |

### Addieren zweier Variablen
```c
int main (void)
{
	volatile unsigned char a = 12;
	volatile unsigned char b = 8;
	
	return a+b;
}
```
  
| Nr | Maschinenbefehl | in Worten | Kommentar |
| -- | ------------------------------- | --------- | --------- |
01 | cf.93 | PUSH R28 | Inhalt von R28 auf Stack legen
02 | df.93 | PUSH R29 | Inhalt von R29 auf Stack legen
03 | 00.d0 | RCALL PC+0x0001 | zum nächsten Befehl springen, 2 Bytes auf Stack ablegen
04 | cd.b7 | IN R28,0x3D | 0x3D in R28 laden
05 | de.b7 | IN R29,0x3E | 0x3E in R29 laden
06 | 8c.c0 | LDI R24,0x0C | 0x0C in R24 laden
07 | 89.83 | STD Y+1,R24 | Inhalt von R24 auf nächsten freien Platz im Y-Register legen (lok. Variable)
08 | 88.e0 | LDI R24,0x08 | 0x08 in R24 laden
09 | 89.83 | STD Y+2,R24 | Inhalt von R24 auf Y-Register legen (lok. Variable)
10 | 89.81 | LDD R24,Y+1 | Inhalt von Y+1 in R24 laden
11 | 2a.81 | LDD R18,Y+2 | Inhalt von Y+2 in R18 laden
12 | 30.e0 | LDI R19,0x00 | 0x00 in laden
13 | 28.0f | ADD R18,R24 | addieren beider Register in R18 ohne berücksichtigung des Carry-Flags
14 | 31.1d | ADC R19,R1 | addieren beider Register in R19 mit berücksichtigung des Carry-Flags
15 | 0f.90 | POP R0 | Variable freigeben
16 | 0f.90 | POP R0 | Variable freigeben
17 | df.91 | POP R29 | R29 vom Stack entfernen
18 | cf.91 | POP R28 | R28 vom Stack entfernen


### Multiplizieren zweier Variablen
```c
int main (void)
{
	volatile unsigned double a = 192.23;
	volatile unsigned double b = 172.231;
	
	return a*b;
}
```
### Division zweier Variablen
```c
int main (void)
{
	volatile unsigned double a = 180;
	volatile unsigned double b = 18;
	
	return a/b;
}
```

## [Echtzeitfähigkeit](https://de.wikipedia.org/wiki/Echtzeitsystem)  

Befehl | Variablen | Takt | Dauer
------ | --------- | ---- | -----
Addition | 8 Bit + 8 Bit | 46 Takte | 2,89µs
Multiplikation | 8 Bit * 8 Bit | 47 Takte | 2,96µs
Division | 8 Bit / 8 Bit | 123 Takte | 7,77µs
  
Die bedeutend längere Dauer der Divison ergibt sich daraus, dass im Gegensatz zur Addition und zur Multiplikation kein eigener Befehl zur Verfügung steht, sondern mit Schleifen gearbeitet werden muss.  


Befehl | Variablen | Takt | Dauer
------ | --------- | ---- | -----
Addition | 32 Bit + 32 Bit | 192 Takte | 12,09µs
Multiplikation | 32 Bit * 32 Bit | 165 Takte| 10,39µs
Division | 32 Bit / 32 Bit | 701 Takte | 44,16µs
  
Beim Vergleichen der Operationen mit unterschiedlichen Datentypen konnten wir feststellen, dass es unbedingt notwendig ist Datentypen so klein wie möglich zu wählen, um nicht durch unnötigen Aufwand, die Echtzeitfähigkeit zu gefährden.
