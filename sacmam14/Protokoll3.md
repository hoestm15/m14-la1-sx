# 3. Protokoll  
## Thema: Assembler Befehle analysieren  
**Name:** Sackl Martin   
**Klasse** 4ahme    
**Gruppe:** 3

Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster   
Abwesend: -  

### Wiederholung der 2. Einheit  
#### CPU - Register  
Register | Verwendung 
--- | ---  
R1 | immer mit 0x00 beschrieben  
R8 - R25 | für Parameter und Rückgabewerte  
R26 + R27 | X- Register  
R28 + R29 | Y- Register  
R30 + R31 | Z- Register  

X-, Y-, Z- Register sind da um Zeiger zu speichern.  

#### Atmel Studio Fenster   
Im Prozessorfenster findet man:  
* program counter  
* X, Y, Z - Register  
* frequenzy  
* cyclic counter  

Im disassembly findet man:  
* Speicheradressen der Befehle  
* Gekürzte Maschinenbefehle  
* Maschinenbefehle werden dort in hexadezimaler Darstellung abgebildet  
-------------------------------------------------------------------------  
### Datentypen  
**Datentyp** | **Beschreibung**  
--- | ---  
`unsigned` | Modifierzt den eigentlichen Datentyp. In unserem Fall ist es der Datentyp `int`. Steht vor dem `int` `unsigned` dann deckt man alle Zahlen im Bereich von 0 bis 2³² ab.  
`volatile` | In C und C++ wird durch diesen Typqualifikator spezifiziert, dass sich der Wert der Variable jederzeit ändern kann, beispielsweise durch andere Prozesse, Threads oder sogar externe Hardware. Bei der Generierung des Maschinen-Codes aus einem in C oder C++ geschriebenen Programm verhindert die Kennzeichnung einer Variablen als volatile eine in diesem Fall die Funktionalität beeinträchtigende Optimierung, so dass das Programm immer auf den tatsächlich in der Hardware vorhandenen Wert zugreift. Quelle: [Wikipedia 09.12.2017](https://de.wikipedia.org/wiki/Volatile_(Informatik))  

### Übung 1  
```
int main(void)  
{  
  volatile unsigned char x;  
  x = 10 + 23;  
  return x;  
}  
```  
Die Eklärungen folgender Maschinenbefehle können Sie im [2. Protokoll](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacmam14/sacmam14/Protokoll2.md) oder in der [Atmel Instruction Set Manual](http://www.atmel.com/images/Atmel-0856-AVR-Instruction-Set-Manual.pdf) nachlesen. 

Maschinenbefehl | | Beschreibung  
--- | --- | ---  
`cf.93` | PUSH R28 | Register R28 wird auf den Stack gelegt    
`df.93` | PUSH R29 | Register R29 wird auf den Stack gelegt   
`1f.92` | PUSH R1 | Register R1 wird auf den Stack gelegt. Stackpointer wird daher auf 1 gesetzt.    
`cd.b7` | IN R28, 0x3D | In das Register R28 wird der Stackpointer (0x3D) aus dem I/O-Register geladen.    
`de.b7` | IN R29, 0x3E | In das Register R29 wird der Stackpointer (0x3E) aus dem I/O-Register geladen.  
`81.e2` | LDI R24, 0x21 | Der Zahlenwert 33 wird in das Register R24 geschrieben.  
`89.83` | STD Y+1, R24 | Register R24 wird am Stack, an der Stelle Stackpointer +1, gespeichert.     
`89.81` | LDD R24, Y+1 | Der Inhalt an der Stelle Stackpointer +1 wird ins Register R24 geladen.  
`90.e0` | LDI R25, 0x00 | Rückgabewert  
`0f.90` | POP R0 | Variable wird freigegeben.    
`cf.91` | POP R28 | Register wird freigegeben.  
`df.91` | POP R29 | Register wird freigegeben.  
|| RET| Return to Subroutine  

### Übung 2  
```
int main(void)  
{  
  volatile unsigned char a = 10;  
  volatile unsigned char b = 20;  
  volatile unsigned char e = a + b;  
  return e;  
}  
```  

Maschinenbefehl | | Beschreibung  
--------------- | --------- | ---------  
`cf.93` | PUSH R28 | Register R28 wird auf den Stack gelegt.  
`df.93` | PUSH R29 | Register R29 wird auf den Stack gelegt.  
`00.d0` | RCALL PC+0x0001 | Es wird zum Weiterspringen auf doe nächste Adresse eine Rücksprungadresse im Stack gespeichert.  
`00.d0` | RCALL PC+0x0001 | Es wird zum Weiterspringen auf doe nächste Adresse eine Rücksprungadresse im Stack gespeichert.  
`cd.b7` | IN R28,0x3d | In das Register R28 wird der Stackpointer (0x3D) aus dem I/O-Register geladen.  
`de.b7` | IN R29,0x3e | In das Register R29 wird der Stackpointer (0x3E) aus dem I/O-Register geladen.  
`8a.e0` | LDI R24,0x0A | Der Zahlenwert 10 wird in das Register R24 geschrieben.  
`89.83` | STD Y+1,R24 | Register R24 wird am Stack, an der Stelle Stackpointer +1, gespeichert. (Variable a)  
`84.e1` | LDI R24,0x14 | Der Zahlenwert 20 wird in das Register R24 geschrieben.
`8a.83` | STD Y+2,R24 | Register R24 wird am Stack, an der Stelle Stackpointer +1, gespeichert. (Variable b)  
`29.81` | LDD R18,Y+1 | Variable a wird in Register R18 geladen.  
`8a.81` | LDD R24,Y+2 | Variable b wird in Register R24 geladen.  
`90.e0` | LDI R25, 0x00 | Der Zahlenwert 0 wird in das Register R25 geschrieben.  
`82.0f` | ADD R24,R18 | Ohne Berücksichtigung des C-Flags werden die beiden Register R24 & R18 addiert. Das Ergebnis wird im Register R24 gespeichert.  
`91.1d` | ADC R25,R1 | Addition mit Berücksichtigung des C-Flags.     
`9c.83` | STD Y+4,R25| Der Variable e wird im Stack das Ergebnis zugewiesen.   
`8b.83` | STD Y+3,R24| Der Variable e wird im Stack das Ergebnis zugewiesen.  
`2b.81` | LDD R18, Y+3 | Die Variable e wird ins CPU-Register geladen.  
`3c.81` | LDD R19, Y+4 | Die Variable e wird ins CPU-Register geladen.  
`82.2f` | MOV R24,R18 | Die Variable e wird in das Register R24 verschoben.  
`93.2f` | MOV R25,R19 | Die Variable e wird in das Register R25 verschoben.  
`0f.90` | POP R0 | Variable e wird freigegeben.  
`0f.90` | POP R0 | Variable e wird freigegeben.  
`0f.90` | POP R0 | Variable b wird freigegeben.  
`0f.90` | POP R0 | Variable a wird freigegeben.  
`df.91` | POP R29 | Register wird freigegeben.   
`cf.91` | POP R28 | Register wird freigegeben.  
|| RET| Return to Subroutine  

### Prozessorgeschwindigkeit testen  
Wir haben mit verschiedenen Datentypen addiert, multipliziert und dividiert.  

Operation| Datentyp | Takte | Kommentar  
--- | --- | --- | ---  
`add` | 8 Bit + 8 Bit | 46 Takte | -  
`mul` | 8 Bit * 8 Bit | 47 Takte | -  
dividiert | 8 Bit / 8 Bit | 123 Takte | da es keinen eigenen Divisions Befehl gibt, dauert es deutlich länger  
`add` | 32 Bit + 32 Bit | 192 Takte | -  
`mul` | 32 Bit * 32 Bit | 165 Takte | -   
dividiert | 32 Bit / 32 Bit | 701 Takte | da es keinen eigenen Divisions Befehl gibt, dauert es deutlich länger  
`add` | `float` + `float` | 905 Takte | -  
`mul` | `float` * `float` | 1763 Takte | -  
dividiert| `float` / `float` | 1380 Takte | es wurden Werte genommen die leicht zu dividieren sind, deswegen sind es weniger Takte als bei der Multiplikation  
dividiert | `double` / `double` | 1380 Takte | es gibt keinen `double` Datentyp bei unserem µC, deswegen werden alle `double` Datentypen als `float` Datentypen gewertet  

### Übung 3  
```
int main(void)  
{  
  volatile int x;  
  volatile int a;  
  for(i=0;x<10;i++)  
  {  
    a += 10;  
  }  
  return a;  
}  
```  
Der Maschinenbefehl `BRNE` (branch if not equal) bedeutet, dass er solange die Befehle ausführt, bis die Bedingung erfüllt ist. Der Befehl vergleicht das Register, indem die Variable x steht, mit dem Z-Flag und verlässt die Schleife erst wenn das Z-Flag dem Register entspricht.
