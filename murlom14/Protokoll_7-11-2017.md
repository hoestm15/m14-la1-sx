# Protokoll 07.11.2017
## 2. Einheit

Name: Muri Lorenz <br>
Klasse: 4AHME <br>
Gruppe: 2 <br>
Datum der Einheit: 07.11.2017 <br>
Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Moritz Martinak, Mario Nabernik, Muri Lorenz, Platzer Andreas, Marcel Köhler <br>
Abwesend: - <br>

## Thema: Atmel-Studio

### Atmel-Studio
Atmel Studio ist eine Entwicklungsumgebung zur Programmierung von [Atmel](http://www.atmel.com/) Mikrocontrollern. Sie besteht hauptsächlich aus drei Teilen: einem **Editor**, einem **Debugger** und verschieden **Werkzeugen**. Es können Programme in **C/C++ und Assembler** programmiert werden. <br>
Die Entwicklungsumgebung wird verwendet um Programme, simuliert auf Mikrocontrollern auszuführen. Außerdem werden alle Maschinenbefehle aufgelistet.

### CPU
Im folgenden Blockdiagramm ist der prinzipiellen Aufbau einer CPU dargestellt.
![CPU-Aufbau](https://github.com/HTLMechatronics/m14-la1-sx/blob/murlom14/murlom14/cpu.svg)

Quelle: [Mirkroprozessor-FIVU](https://lms.at/dotlrn/classes/informatik/610437.4AHME_FIVU.17_18/xolrn/EC743ABCF7AB5.symlink?resource_id=0-237409759&m=view#188315330)

### Speicher bei μ-Cs
Der **Speicher** bei Mikrocontrollern werden meist mit einem **[Stack](https://de.wikipedia.org/wiki/Stapelspeicher)** (Stapelspeicher) realiesiert. Er heißt deswegen Stapelspeicher weil er einfach alle Datein *übereinenaderstapelt* und jeder Datei wird durch den **Stackpointer** eine **Adresse zugewissen** (die nächste Adresse im Speicher). <br>
Wenn der reservierte **Speicher nicht ausreicht** wird von einem **Stack-Overflow** gesprochen. <br>

![Arbeitsspeciher-Atmega](https://github.com/HTLMechatronics/m14-la1-sx/blob/murlom14/murlom14/SRAM_Aufbau.PNG) <br>
Quelle: [Mirkroprozessor-FIVU](https://lms.at/dotlrn/classes/informatik/610437.4AHME_FIVU.17_18/xolrn/EC743ABCF7AB5.symlink?resource_id=0-237409759&m=view#189503049) <br>


### Arbeiten mit Atmel Studio

Wir haben ein sehr einfaches C-Programm geschreiben, welches wir anschließend mit Atmel Studio, auf dem Mikroprozessor Atmega328 simuliert haben. 

**Daten von [Atmega328](http://www.microchip.com/wwwproducts/en/ATmega328):**
 * 20MHZ Mikroprozessor
 * 2kB SRAM
 * 1kB EEPROM
 * 32kB Flash-Speicher
 * 32 Register 
 <br>

**C-Programm**
```c
int main ()
{
  return 0;
}
``` 
<br>

**Ausgabe von Atmel Studio**
![Atmel-Studio-OUT](https://github.com/HTLMechatronics/m14-la1-sx/blob/murlom14/murlom14/Atmel_Studio_OUT.jpg)

**Wichtige Assembler-Befehle**
* RJMP: Sprung zu einer Adresse
* CLR R1: Register 1 wird auf 0 gesetzt
* OUT 0x3F, R1: Daten werden von Register 1 ins I/O Register übertragen
* SER R28: Das Register R28 bekommt den Wert 0xFF
* LDI R29, 0x08: Läd einen konstanten Wert in ein Register







