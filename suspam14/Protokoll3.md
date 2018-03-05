# Protokoll 3: Microcontroller
Name: Patrick Schuster  
Klasse: 4AHME  
Gruppe: 3    
Anwesend: Reinbacher, Ruffenacht, Sackl, Sackl, Sammer, Schmuck, Schuster  
Abwesend: keiner

## Wiederholung der 2. Einheit
Zu Beginn der Stunde haben wir die einzelnen Funktionen des Prozessorfensters in Atmel Studio, die CPU Register und Dissambly wiederholt.  
### CPU-Register
Register | Verwendung
--- | ---
R1 | hat immer den Wert 0x00  
R8 - R25 | für Parameter und Rückgabewerte  
R26 & R27 | X-register  
R28 & R29 | Y-Register  
R30 & R31 | Z-Register  

### Prozessorfenster
Das Prozessorfenster enthält:  
* Program Counter
* Cyclic Counter
* Stackpointer
* Inhalt der Register
* Frequenz
### Disassembly
Das/Der Disassembly enthält:
* Maschinenbefehl 
* Assembler Befehl
* Speicheradressen der Befehle 

[Protokoll der 2. Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/suspam14/suspam14/Protokoll2.md)

## deklarieren, definieren und initialisieren
* **deklarieren** Es wird eine Variable benannt und dem Compiler bekannt gegeben.
* **definieren** Es wird der Variable ein Speicherbereich zugewiesen
* **initialisieren** Es wird der Variable ein initialer Anfangswert zugewiesen

## Schlüsselwörter für Datentypen
* Mit **volatile**  wird verhindert das der Compiler beim kompilieren diese Variable "wegoptimiert". 
> Dies wurde bei unseren Übungen benötigt damit der Compiler die Gleichungen nicht selber löst, sondern wir den Rechenverlauf im Dissassembly nachvollziehen können. 
* Mit **unsigned** wird eine Variable nicht vorzeichenbehaftet. In dem Datentyp ``` char ``` kann man somit einen Wert zwischen 0 und 255 statt von -128 bis 127 speichern.

## Übungsbeispiele

### Übung 1: Zuweisen einer Konstante

```
int main (void)  
{  
  volatile unsigned char x;   
  x = 10 + 23; 
  
  return x;  
} 
```
Maschinenbefehl | Assembler Befehl | Beschreibung
--- | --- | ---
cf.93 | PUSH R28 | R28 wird am Stack abgelegt, weil die XYZ- Register nicht während eines Funktionaufruf geändert werden dürfen
df.93 | PUSH R29 | R29 wird am Stack abgelegt, weil die XYZ- Register nicht während eines Funktionaufruf geändert werden dürfen
1f.92 | PUSH R1 | Stackpointer wird um 1 erhöht um Platz für eine variable zu schaffen
cd.b7 | IN R28,0x3D | Der Stackpointer wird in R28 geladen (Y- Register)
de.b7 | IN R29,0x3E | Der Stackpointer wird in R29 geladen (Y- Register)
81.e2 | LDI R24,0x21 | Die Konstante 33 wird in R24 geschrieben
89.83 | STD Y+1,R24 | Die Konstante aus R24 wird am Stack abgelegt (aufgrund von volatile)
89.81 | LDD R24,Y+1 | Die Konstante wird aus dem Stack geladen 
90.e0 | LDI R25,0x00 | Rückgabewert
0f.90 | POP R0 | Variable wird freigegeben
df.91 | POP R29 | Y Register wird vom Stack zurückgeholt
cf.91 | POP R28 | Y Register wird vom Stack zurückgeholt
08.95 | RET | Programmende


### Übung 2: Addition von zwei Variablen

```
int main(void)
{
	volatile unsigned char a=10;  
	volatile unsigned char b=20;  
	volatile int e=a+b;  
	return e;  
}
```

Maschinenbefehl | Assembler Befehl| Beschreibung  
--- | --- | --- 
cf.93 | PUSH R28 | R28 wird am Stack abgelegt, weil die XYZ- Register nicht während eines Funktionaufruf geändert werden dürfen
df.93 | PUSH R29 | R29 wird am Stack abgelegt, weil die XYZ- Register nicht während eines Funktionaufruf geändert werden dürfen
00.d0 | RCALL PC+0x0001 | Zum Weiterspringen wird die Rücksprungadresse wird am Stack abgelegt
00.d0 | RCALL PC+0x0001 | Zum Weiterspringen wird die Rücksprungadresse wird am Stack abgelegt  
cd.b7 | IN R28,0x3d | Der Stackpointer wird in R28 geladen (Y- Register)  
de.b7 | IN R29,0x3e | Der Stackpointer wird in R29 geladen (Y- Register) 
8a.e0 | LDI R24,0x0A | Die Konstante  10 wird in R24 geschrieben
89.83 | STD Y+1,R24 | R24 wird am Stack, an der Stelle Stackpointer +1, abgelegt Variable a 
84.e1 | LDI R24,0x14 | Die Konstante 20 wird in R24 geschrieben.
8a.83 | STD Y+2,R24 | R24 wird am Stack, an der Stelle Stackpointer +2, abgelegt Variable b  
29.81 | LDD R18,Y+1 | Variable a wird in R18 geladen 
8a.81 | LDD R24,Y+2 | Variable b wird in R24 geladen 
90.e0 | LDI R25, 0x00 | Der Wert 0 wird in R25 geschrieben  
82.0f | ADD R24,R18 | R18 & R24 werden ohne Berücksichtigung des C-Flags addiert und in R24 gespeichert
91.1d | ADC R25,R1 | R1 & R24 werden mit Berücksichtigung des C-Flags addiert     
9c.83 | STD Y+4,R25| Ergebnis der zweiten Addition wird der Variable e im Stack zugewiesen   
8b.83 | STD Y+3,R24| Ergebnis der ersten Addition wird der Variable e im Stack zugewiesen
2b.81 | LDD R18, Y+3 | Die Variable e wird vom Stack in R18 geladen (aufgrund von volatile)
3c.81 | LDD R19, Y+4 | Die Variable e wird vom Stack in R19 geladen (aufgrund von volatile) 
82.2f | MOV R24,R18 | Die Variable e wird nach R24 verschoben  
93.2f | MOV R25,R19 | Die Variable e wird nach R25 verschoben. 
0f.90 | POP R0 | Variable e wird freigegeben 
0f.90 | POP R0 | Variable e wird freigegeben  
0f.90 | POP R0 | Variable b wird freigegeben  
0f.90 | POP R0 | Variable a wird freigegeben  
df.91 | POP R29 | R29 wird freigegeben   
cf.91 | POP R28 | R28 wird freigegeben  
|| RET| Return to Subroutine  

### Übung 3: Addition mit einer Schleife

```
int main(void)
{
	unsigned char i;
	volatile int x=0;
	for(i=0;i<10;i++)
	{
		x+=10;
	}
	return 0;
}
```
> In dieser Tabelle befindet sich nur die Schleife des Programms. Der Startup Code und das Ende wurde weggelassen da diese Teile des Programms nichts neues beinhalten.  

Maschinenbefehl | Assembler Befehl| Beschreibung  
--- | --- | --- 
89.81 | LDD R24,Y+1 | Variable x wird in R24 geladen
9a.81 | LDD R25,Y+2 | Variable x wird in R25 geladen
0a.96 | ADIW R24,0x0A | Zur Variable x wird 10 addiert
9a.83 | STD Y+2,R25 | R25 wird am Stack, an der Stelle Stackpointer +,2 abgelegt
89.83 | STD Y+1,R24 | R24 wird am Stack, an der Stelle Stackpointer +,2 abgelegt
21.50 | SUBI R18,0x01 | Vom Zähler der Schleife wird 1 abgezogen. Der Zähler wird in R18 gespeichert
c9.f7 | BRNE PC-0x06 | Wenn der Zähler nicht 0 ist springt das Programm 6 Schritte zurück (Schleife)

Um eine Schleife zu bauen wird der Assembler Befehl **BRNE (Branch if not equal)** benötigt. Dieser führt eine Befehlskette so lange aus bis eine gewisse Bedienung erfüllt ist. Diese Bedienung ist in der Regel das im Zählerregister 0 steht. Der Befehl vergleicht das Zero-Flag, wenn dieses gesetzt ist verlässt er die Schleife.


## Prozessorgeschwindigkeit
Testen der Prozessorgeschwindigkeit für verschiedene Rechenoperationen und Datentypen

Rechenoperation | Datentyp | benötigte Takte
--- | --- | ---
Addition | 8 bit int | 46
Multiplikation | 8 bit int |47
Division | 8 bit int | 123
Addition | 32 bit int | 92
Multiplikation | 32 bit int |165
Division | 32 bit int| 701
Addition | float | 911
Multiplikation | float |1763
Division | float| 1380
Addition | double | 911
Multiplikation | double |1763
Division | double| 1380

Es ist zu erkennen das der Prozessor für Rechenoperationen mit float und double exakt gleich lange braucht. Das liegt daran das der avr-gcc Compiler beim kompilieren keine doppeltgenauen Fließkommazahlen zulässt und statt diesen float verwendet.
