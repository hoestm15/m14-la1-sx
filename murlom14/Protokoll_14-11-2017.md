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
Die Ausgabe von AtmelStudio schaut wie folgt aus:
![Atmel-Studio-OUT](https://github.com/HTLMechatronics/m14-la1-sx/blob/murlom14/Atmel_Studio_OUT.jpg)

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
`cf.93` | PUSH R28 | Register R28 wird im Stack gespeichert
`df.93` | PUSH R29 | Register R29 wird im Stack gespeichert
`00.d0` | RCALL PC+0x0001 | Sprung zum nächsten Befehl, 2 Bytes werden am Stack für a und b reserviert
`cd.b7` | IN R28,0x3D | 0x3D wird in das Register R28 übertragen
`de.b7` | IN R29,0x3E | 0x3E wird in das Register R29 übertragen
`8c.c0` | LDI R24,0x0C | 0x0C (= 12, Konstante) wird in das Register R24 übertragen (Variable a)
`89.83` | STD Y+1,R24 | Register R24 wird in auf den reservierten Platz (für lokale Variablen) übertragen 
`88.e0` | LDI R24,0x08 | 0x08 (= 8, Konstante) wird in das Register R24 übertragen (Variable b)
`89.83` | STD Y+2,R24 | Register R24 wird in auf den reservierten Platz (für lokale Variablen) übertragen 
`89.81` | LDD R24,Y+1 | Variable a wird vom Stack in das Register R24 geladen.
`2a.81` | LDD R18,Y+2 | Variable b wird vom Stack in das Register R18 geladen.
`30.e0` | LDI R19, 0x00 |  0x00 (= 0, Konstante) wird in das Register R19 übertragen
`28.0f` | ADD R18,R24 | Register R18 wird mit R24 addiert --> Ergebnis wird in R18 gespeichert (ohne Carry-Flag)
`31.1d` | ADC R19,R1 | Register R19 wird mit R1 addiert --> Ergebnis wird in R19 gespeichert (mit Carry-Flag)
`0f.90` | POP R0 | Variable b wird vom Stack freigegeben
`0f.90` | POP R0 | Variable a wird vom Stack freigegeben
`df.91` | POP R29 | Das Register R29 wird vom Stack genommen (Freigabe)
`cf.91` | POP R28 | Das Register R28 wird vom Stack genommen (Freigabe)

Quelle: [Assemblerbefehle](http://andremueller.gmxhome.de/befehle.html)

## Verwendete Ausdrücke
### volatile
Durch das Scglüsselwort ``volatile`` werden alle Assemblerbefehle, zur Erstellung von Variablen angezeigt und es wird immer auf den echten "Hardwarewert" zugegriffen.

### unsigned char
Um nur Zahlen zwischen 0 und 255 darzustellen verwenden wir ``unsigned char``. (nicht Vorzeichenbehaftet)


