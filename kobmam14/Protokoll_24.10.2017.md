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

# unsigned char

Dieser Datentyp ermöglicht es mit einem Byte, im Gegensatz zu char oder signed char, welche vozeichenbehaftet sind, vorzeichenlose Zahlen von 0 bis 255 darzustellen.

# volatile

Das Schlüssselwort volatile ermöglicht die genaue Einsicht in den Vorgang der Erstellung einer Variable. Ohne dieses Schlüsselwort ist die Einsicht nur vereinfacht möglich.

Obiges Programm wurde gestartet und im Debugging-Modus aufgerufen.
Danach wurde das Programm disassembliert um eine Auflistung aller durchzuführenden Maschinenbefehle zu erhalten.

