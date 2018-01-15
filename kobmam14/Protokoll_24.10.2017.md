# Protokoll 24.10.2017

## 3. Einheit
## Thema: Atmel Studio

Name: Markus Kobor  <br>
Klasse: 4AHME  <br>
Datum 24.10.2017  <br>
Gruppe: 1  <br>
Anwesend: Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Enzi Gert, Knappitsch Robert, Kobor Markus  <br>
Abwesend: -  <br>

### Wiederholung

Die erste Stunde wurde damit verbracht, alle durchbesprochenen Befehle und theoretisches wie zum Beispiel die Funktion des Stackspeichers oder den Aufbau eines Mikrocontrollers zu wiederholen. <br>
siehe [2. Protokoll](https://github.com/HTLMechatronics/m14-la1-sx/edit/kobmam14/kobmam14/Protokoll_17.10.2017.md)

### Fortsetzung mit Atmel Studio

Wie begannen damit die folgende Funktion zu erstellen und zu analysieren. <br> <br>
int main (void) <br>
{ <br>
   volatile unsigned char x; <br>
   x = 12; <br>
   return x; <br>
} <br> <br>
Es wurde eine Variable **"x"** mit dem Datentyp **"unsigned char"**, welche mit dem Schlüsselwort **"volatile"** versehen wurde, im Stackspeicher angelegt. <br>
Daraufhin bekommt diese den Wert **12** zugewiesen. <br>
Im Anschluss wird die Variable x, nach einem Typecast auf "int", zurückgegeben.

#### unsigned char

Dieser Datentyp ermöglicht es mit einem Byte, im Gegensatz zu char oder signed char, welche vozeichenbehaftet sind, vorzeichenlose Zahlen von 0 bis 255 darzustellen.

#### volatile

Das Schlüssselwort volatile ermöglicht die genaue Einsicht in den Vorgang der Erstellung einer Variable
Ohne dieses Schlüsselwort ist die Einsicht nur vereinfacht möglich.

<br>
Obiges Programm wurde gestartet und im Debugging-Modus aufgerufen.
Danach wurde das Programm disassembliert um eine Auflistung aller durchzuführenden Maschinenbefehle zu erhalten:
<br> <br>

Maschinenbefehl | Geschrieben | Funktion
--------------- | --------- | ---------
`cf.93` | PUSH R28 | Register R28 wird auf den Stack gelegt.
`df.93` | PUSH R29 | Register R29 wird auf den Stack gelegt.
`1f.92` | PUSH R1 | Register R1 wird auf den Stack gelegt.
`cd.b7` | IN R28,0x3D | 0x3D wird aus dem I/O-Register in R28 geladen.
`de.b7` | IN R29,0x3E | 0x3E wird aus dem I/O-Register in R29 geladen.
`8c.e0` | LDI R24,0x0C | Die Konstante 0C wird im Register R24 abgelegt.
`89.83` | STD Y+1,R24 | Konstante aus R24 wird am Speicherplatz des Stacks der lokalen Variable abgelegt.
`89.81` | LDD R24,Y+1 | Die Variable wird in Register R24 geladen.
`90.e0` | LDI R25,0x00 | Rückgabewert
`0f.90` | POP R0 | Variable wird freigegeben.
`df.91` | POP R29 | Register R29 wird vom Stack entfernt.
`cf.91` | POP R28 | Register R28 wird vom Stack entfernt.

<br>

#### Addition

int main (void) <br>
{ <br>
   volatile unsigned char a = 12; <br>
   volatile unsigned char b = 8; <br>
   return a+b; <br>
} <br> <br>
Auch bei diesem Programm wurde die selbe Vorgehensweise verwendet. <br>
Folgende neue Maschinenbefehle kamen hinzu:
<br>

Maschinenbefehl | Geschrieben | Funktion
--------------- | --------- | ---------
`00.d0` | RCALL PC+0x0001 | Springt zum nächsten Befehl.
`88.e0` | LDI R24,0x08 | Die Konstante 08 wird im Register R24 abgelegt.
`2a.81` | LDD R18,Y+2 | Variable b wird in Register R18 geladen.
`30.e0` | LDI R19, 0x00 | Konstante 0x00 wird am Register R19 abgelegt.
`28.0f` | ADD R18,R24 | Die beiden Register werden addiert, ohne Berücksichtigung des Carry-Flags. Das Endergebnis wird in R18 gespeichert.
`31.1d` | ADC R19,R1 | Addition mit Berücksichtigung des Carry-Flags.

<br>

**Es folgen weitere besprochene  Quellcodes:**

#### Schleife  

int main (void)   <br>
{   <br>
   volatile a = 10;  <br> 
   uint8_t b;   <br>

   for (b=0; b<10; b++)   <br>
   {   <br>
   }   <br>
   return 0; <br>
}
	
#### Multiplikation  

int main (void) <br>
{   <br>
   volatile unsigned char a = 12;   <br>
   volatile unsigned char b = 8;   <br>
	  
   return a*b;  <br> 
}  

#### Division  

int main (void)   <br>
{  <br> 
   volatile unsigned char a = 12;   <br>
   volatile unsigned char b = 8;   <br>
	
   return a/b;  <br> 
} 

*Für Rechenoperationen wie das Addieren, die Subtraktion und die Multiplikation hat der AT328P eigene Befehle/Tabellen und kann sie daher schnell ausführen.*

*Für eine Division braucht der Prozessor deutlich länger, da ihm dort keine Tabellen zur Verfügung stehen.*

### Heartbleed-Bug

Der Heartbleed-Bug ist ein schwerwiegender Programmfehler in älteren Versionen der Open-Source-Bibliothek OpenSSL, durch den private Daten von Clients und Servern ausgelesen werden können. Der Fehler betrifft die OpenSSL-Versionen 1.0.1 bis 1.0.1f und wurde mit Version 1.0.1g am 7. April 2014 behoben. Bei der Sicherheitslücke handelt es sich um einen lesenden Zugriff über die Grenzen eines Datenpuffers (buffer over-read). Anders als bei einem Pufferüberlauf werden keine Daten außerhalb von Puffergrenzen geschrieben. Es wurde ein unabsichtlicher Programmierfehler begangen und die Prüfung einer Eingabevariable versäumt, in der die Länge des zurückzuliefernden Puffers mitgeteilt wird.
