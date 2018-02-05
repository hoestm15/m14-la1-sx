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

## Beispiele

#### Quellcode zur Variablen Initaliesirung
```c
int main (void)
{
	volatile unsigned char x;
	x = 12;
	
	return x;
}
```

#### Assemblebefele zur Variablen Initaliesirung
Maschinenbefehl | in Worten | Bedeutung
--------------- | --------- | ---------
`cf.93` | PUSH R28 | Register R28 wird im Stack gespeichert
`df.93` | PUSH R29 | Register R29 wird im Stack gespeichert
`1f.92` | PUSH R1 | Register R1 (R1 besitzt immer der Wert 0) wird im Stack gespeichert reserviert Platz für lokale Variablen
`cd.b7` | IN R28,0x3D | 0x3D wird in das Register R28 übertragen
`de.b7` | IN R29,0x3E | 0x3E wird in das Register R29 übertragen
`8c.e0` | LDI R24,0x0C | 0x0C (= 12, Konstante) wird in das Register R24 übertragen
`89.83` | STD Y+1,R24 | Register R24 wird in auf den reservierten Platz (für lokale Variablen) übertragen (Y+1 bedeutet die Variable wird direkt nach dem Y-Register agelegt)
`89.81` | LDD R24,Y+1 | Die Variable wird in dAS Register R24 geladen
`90.e0` | LDI R25,0x00 | Der Rückgabewert wird in das Register R25 übertragen
`0f.90` | POP R0 | Die Variable wird vom Stack genommen (Freigabe)
`df.91` | POP R29 | Das Register R29 wird vom Stack genommen (Freigabe)
`cf.91` | POP R28 | Register R28 wird vom Stack genommen (Freigabe)

****************************************************************************************************************************************

#### Quellcode zur Addition zweier Variablen
```c 
int main (void)
{
	volatile unsigned char a = 12;
	volatile unsigned char b = 8;
	
	return a+b;
}
```

#### Assemblebefele zur Addition zweier Variablen
Maschinenbefehl | in Worten | Kommentar
--------------- | --------- | ---------
`cf.93` | PUSH R28 | Register R28 wird auf den Stack gelegt.
`df.93` | PUSH R29 | Register R29 wird auf den Stack gelegt.
`00.d0` | RCALL PC+0x0001 | Springt zum nächsten Befehl. *Durch den RCALL werden 2 Bytes auf dem Stack reserviert, die für die Variablen a & b verwendet werden.*
`cd.b7` | IN R28,0x3D | 0x3D wird aus dem I/O-Register in R28 geladen.
`de.b7` | IN R29,0x3E | 0x3E wird aus dem I/O-Register in R29 geladen.
`8c.c0` | LDI R24,0x0C | Konstante (0C = 12) wird im Register R24 abgelegt.
`89.83` | STD Y+1,R24 | Konstante aus R24 wird am Speicherplatz des Stacks der ersten lokalen Variable (a) abgelegt.
`88.e0` | LDI R24,0x08 | Konstante (08 = 8) wird im Register R24 abgelegt.
`89.83` | STD Y+2,R24 | Konstante aus R24 wird am Speicherplatz des Stacks der zweiten lokalen Variable (b) abgelegt.
`89.81` | LDD R24,Y+1 | Variable a wird in Register R24 geladen.
`2a.81` | LDD R18,Y+2 | Variable b wird in Register R18 geladen.
`30.e0` | LDI R19, 0x00 | Konstante 0x00 wird am Register R19 abgelegt.
`28.0f` | ADD R18,R24 | Die beiden Register werden addiert, ohne Berücksichtigung des Carry-Flags. Das Endergebnis wird in R18 gespeichert.
`31.1d` | ADC R19,R1 | Addition mit Berücksichtigung des Carry-Flags. *Das Carry-Flag enthält den Übertrag einer Addition. [Weitere Informationen](https://de.wikipedia.org/wiki/Übertragsbit)
`0f.90` | POP R0 | Variable b wird freigegeben.
`0f.90` | POP R0 | Variable a wird freigegeben.
`df.91` | POP R29 | Register R29 wird vom Stack entfernt.
`cf.91` | POP R28 | Register R28 wird vom Stack entfernt.





