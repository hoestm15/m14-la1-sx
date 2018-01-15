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

Das Schlüssselwort volatile ermöglicht die genaue Einsicht in den Vorgang der Erstellung einer Variable. Ohne dieses Schlüsselwort ist die Einsicht nur vereinfacht möglich.

<br>
Obiges Programm wurde gestartet und im Debugging-Modus aufgerufen.
Danach wurde das Programm disassembliert um eine Auflistung aller durchzuführenden Maschinenbefehle zu erhalten:
<br>

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
   volatile unsigned char b = 8; <br> <br>
   return a+b; <br>
} <br> <br>
Auch bei diesem Programm wurde die selbe Vorgehensweise verwendet. <br>
Folgende neue Maschinenbefehle kamen hinzu:
<br>

