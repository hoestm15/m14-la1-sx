# Protokoll 14.11.2017
## 3. Einheit

Name: Muri Lorenz <br>
Klasse: 4AHME <br>
Gruppe: 2 <br>
Datum der Einheit: 14.11.2017 <br>
Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Moritz Martinak, Mario Nabernik, Muri Lorenz, Platzer Andreas, Marcel Köhler <br>
Abwesend: - <br>

## C-Programme - Atmel-Studio
In dieser Einhat haben wir einfache C-Programme geschrieben und mit Atmel-Studio ausgeführt und anschließend die Assembler Befehle durchbesprochen. <br>

### Atmel-Studio
[Atmel-Studio](https://www.microchip.com/avr-support/atmel-studio-7) ist ein Programm mit desssen Hilfe man zum Beispiel C Programme schreiben kann. Die Besonderheit ist, dass Atmel-Studio nicht nur das geschrieben Programm ausführt sondern auch die Maschienen/Assemblerbefehle auflistet.

### 1. Beispiel

**Quellcode** 
```c
int main (void)
{
	volatile unsigned char x;
	x = 12;
	
	return x;
}
```

**Assemblebefele**
Maschinenbefehl | in Worten | Kommentar
--------------- | --------- | ---------
`cf.93` | PUSH R28 | Register R28 wird auf den Stack gelegt.
`df.93` | PUSH R29 | Register R29 wird auf den Stack gelegt.
`1f.92` | PUSH R1 | Register R1 wird auf den Stack gelegt. *Register R1 ist immer "0", es wird auf dem Stack der Speicher für die lokale Variable reserviert.*
`cd.b7` | IN R28,0x3D | 0x3D wird aus dem I/O-Register in R28 geladen.
`de.b7` | IN R29,0x3E | 0x3E wird aus dem I/O-Register in R29 geladen.
`8c.e0` | LDI R24,0x0C | Konstante (0C = 12) wird im Register R24 abgelegt.
`89.83` | STD Y+1,R24 | Konstante aus R24 wird am Speicherplatz des Stacks der lokalen Variable abgelegt. *R28 & R29 beschreiben das Y-Register. Da die Variable genau nach dem Y-Register auf den Stack gelegt wurde, ist die Adresse im Stack "Y+1"* Die Variable wird gespeichert.
`89.81` | LDD R24,Y+1 | Die Variable wird in Register R24 geladen.
`90.e0` | LDI R25,0x00 | Rückgabewert
`0f.90` | POP R0 | Variable wird freigegeben.
`df.91` | POP R29 | Register R29 wird vom Stack entfernt.
`cf.91` | POP R28 | Register R28 wird vom Stack entfernt. *(R29 muss zuerst enfernt werden, da im Stack nur von oben nach unten gelesen werden kann. Gespeichert kann hingegen nur von unten nach oben werden. Weiteres ist ebenfalls im [Protokoll der zweiten Einheit](/beremm14/README_2017-10-17.md) zu finden.)*
