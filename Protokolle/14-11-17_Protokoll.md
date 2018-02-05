# Protokoll: Marcel Köhler
## 3.Einheit
## Thema: Analyse von Volatile Variablen
Klasse: 4AHME
Anwesend: Marcel Köhler, Michael Mörth, Florian Nebel, Lorenz Muri, Moritz Martinak, Andreas Platzer, Mario Nabernik, Gerhard Mandl
Abwesend: niemand

## Wiederholung der letzten Einheit u. benotung der Protokolle
Als erstes wurden die Protokolle beurteilt danach begann die Wiederholung der [letzten Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/koemam13/Protokolle/7-11-17_Protokoll.md).
Wir besprachen:
* Atmega 328P
* Assembler Befehle
* Atmel Studio

## Volatile:
Das Schlüsselwort `volatile` verhindert das beim Compilieren die Optimierung eines Rechenprozesses.  
Da es vorkommen kan das durch das Optimieren dieses Prozesses das Prozesergebnis falsch ist.

Quelle: [Wikipedia](https://de.wikipedia.org/wiki/Volatile_(Informatik))

## Erste Analyse:
### Quellcode
```c
int main (void)
{
	volatile unsigned char x;
	x = 12;
	
	return x;
}
```
### Assemblerbefehle
Maschinenbefehl | In Assembler | Beschreibung
--------------- | --------- | ---------
cf.93 | PUSH R28 | Wert von R28 auf den Stack legen.
df.93 | PUSH R29 | Wert von R29 auf den Stack legen.
1f.92 | PUSH R1 | Wert von R1 auf den Stack legen.
cd.b7 | IN R28,0x3D | Wert von 0x3D auf das I/O Register R28 laden.
de.b7 | IN R29,0x3E | Wert von 0x3E auf das I/O-Register R29 laden.
8c.e0 | LDI R24,0x0C | Die Konstante 0x0C wird in das Register R24 gelegt.
89.83 | STD Y+1,R24 | Die Konstante aus R24 wird im Stack abgelegt. Y+1 zeigt auf den nächsten freien Speicherplatz im Y-Register 
89.81 | LDD R24,Y+1 | Die Variable von Y+1 wird in das Register R24 geladen.
90.e0 | LDI R25,0x00 | Rückgabewert wird in das Register R25 gespeichert.
0f.90 | POP R0 | Variable wird freigegeben.
df.91 | POP R29 | Enfernt das Register R29 vom Stack.
cf.91 | POP R28 | Enfernt das Register R28 vom Stack.

R29 wird vor R28 gelöscht bzw. entfernt da der Stack nur von oben nach unten gelesen werden kann.  
Für weitere Informationen: [Stapelspeicher](https://de.wikipedia.org/wiki/Stapelspeicher)

## Zweite Analyse
### Quellcode
```c
int main (void)
{
	volatile unsigned char a = 12;
	volatile unsigned char b = 8;
	
	return a+b;
}
```

### Assemblerbefehle

Maschinenbefehl | In Assembler | Beschreibung
--------------- | --------- | ---------
cf.93 | PUSH R28 | Wert von R28 auf den Stack legen
df.93 | PUSH R29 | Wert von R29 auf den Stack legen. 
00.d0 | RCALL PC+0x0001 | Sprung zum nächsten Befehl.
cd.b7 | IN R28,0x3D | Wert von 0x3D auf das I/O Register R28 laden.
de.b7 | IN R29,0x3E | Wert von 0x3E auf das I/O-Register R29 laden.
8c.c0 | LDI R24,0x0C | Die Konstante 0x0C wird in das Register R24 gelegt.
89.83 | STD Y+1,R24 | Wert von R24  am Stack abgelegen. (Speicheradresse ist die Adresse der Variable a) 
88.e0 | LDI R24,0x08 | Wert 8 auf Register R24 ablegen.
89.83 | STD Y+2,R24 | Wert von R24 am Stack ablegen (Speicheradresse ist die Adresse der Variable b) 
89.81 | LDD R24,Y+1 | Wert von Variable a in das Register R24 laden.
2a.81 | LDD R18,Y+2 | Wert von Variable b in das Register R18 laden.
30.e0 | LDI R19, 0x00 | Rückgabewert in das Register R19 laden.
28.0f | ADD R18,R24 | Addition der beiden Register. [Carry-Flag](https://de.wikipedia.org/wiki/Statusregister) wird nicht berücksichtigt.
31.1d | ADC R19,R1 | Addition unter Berücksichtigung des [Carry-Flag](https://de.wikipedia.org/wiki/Statusregister)s.
0f.90 | POP R0 | Entfernt Variable b vom Stack.
0f.90 | POP R0 | Entfernt Variable a vom Stack.
df.91 | POP R29 | Enfernt das Ragister R29 vom Stack.
cf.91 | POP R28 | Enfernt das Register R28 vom Stack.

## Ermitteln der Zeit von verschiedenen Rechenoperationen.

### Beispiel eines Quelltextes:

```c
int main (void)
{
	volatile unsigned double a = 102.66;
	volatile unsigned double b = 1732.165;
	
	return a/b;
}
```

### Unterschiedliche Zeiten:
Datentyp | Operation| Anzahl der benötigten Takte | Zeit in µs | Bemerkungen
---|---|---|---|---
8 Bit + 8 Bit | Addition| 46 Takte | 2,89
8 Bit * 8 Bit | Multiplikation| 47 Takte | 2,96 | Eigener Befehl vorhanden. Dadurch kaum unterschied zu Addition.
8 Bit / 8 Bit | Division| 123 Takte |  7,77 | Kein Eigener Befehl vorhande. Dadurch wird mit Schleifen gearbeitet.
32 Bit + 32 Bit | Addition|192 Takte |  12,09 |
32 Bit * 32 Bit | Multiplikation| 165 Takte| 10,39 |
32 Bit / 32 Bit | Division| 701 Takte | 44,16 |
float + float | Addition| 905 Takte | 57,01 |
float * float | Multiplikation| 1763 Takte | 111,06 |
float / float | Division| 1380 Takte | 86,94 | Dauert Normalerweiße länger als das Multiplizieren. Kann aber sein das die gewählten werte einfach zu Dividieren waren.
double / double | Division| 1380 Takte | 86,94 | Kein Unterschied zu float. Da float und double vom  da der µC diese gleich behandelt. 


## Resümee
Das Schlüsselwort volatile verhindert, das der Compiler das Programm verkürzt (optimiert).
Unter anderem muss man darauf achten das man bei Echtzeitfähigen geräten möglichst kleine Datentypen zu verwendet, 
da es passieren kann das manche Operationen zu lange brauchen und dadurch die Echtzeitfähigkeit verloren geht.

