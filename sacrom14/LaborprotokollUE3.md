# 3. Protokoll  

**Name:** Sackl Roland   
**Klasse** 4AHME  
**Gruppe:** 3

**Anwesend:** Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster   
**Abwesend:** -  

## Wiederholung der 2. Einheit  
### CPU-Register
Die folgende Register werden für spezielle Zwecke verwendet:

Register | Verwendung 
|---|---|
`R1`| ist immer mit 0x00 beschrieben
`R8 - R25`| für Parameter und Rückgabewerte
`R26 + R27`| X- Register für Adressen
`R28 + R29`| Y- Register für Adressen
`R30 + R31` | Z- Register für Adressen

### Was findet man im Prozessorfenster? Aufgaben der Bestamdteile?  
* program counter 
* frequenzy  
* X-/Y-/Z-Register
* stop watch  
* cyclic counter  
* stackpointer  

 ### Was findet man im disassembly?  
* Adressen der Befehle im Speicher  
* Abgekürzte Maschinenbefehl-Parameter und Namen 
* Maschinenbefehl in Hexadezimal



### Der Unterschied zwischen "deklarieren", "initialisieren" und "definieren"  

**Deklaration:** Dem Compiler wird eine Variable bekannt gegeben  
**Initialisierung:** Der Variable wird ein Wert zugewiesen  
**Definition:** Der Variable wird ein Speicherbereich zugeteilt  


## 1.Übungsbeispiel  
```
int main(void)  
{  
  volatile unsigned char x;  
  x=10+23;  
  return x;  
}  
```  


### Analyse des Maschinenecodes:
  
  **Befehl** | **in Worten** | **Beschreibung**
--- | --- | ---
`cf.93` | PUSH R28 | Register R28 wird auf den Stack gelegt  
`df.93` | PUSH R29 | Register R29 wird auf den Stack gelegt  
`1f.92` | PUSH R1 | Stackpointer wird auf 1 gesetzt 
`cd.b7` | IN R28,0x3D | Y-Register wird zum Stackpointer
`de.b7` | IN R29,0x3E | Der Stackpointer  wwird zum Y-Register
`81.e2` | LDI R24,0x21 | Konstante (0x21 = 12) wiDer Stackpointer (0x3D) wird aus dem I/O-Register in R28 (Y-Registerrd im Register R24 abgelegt.  
`89.81` | LDD R24,Y+1 | Die Variable wird ins Register R24 geladen. Das ist aufgrund des Schlüsselwortes 'volotaile' nötig, weil die Variable ja von außen verändert werden kann.
`89.83` | STD Y+1,R24 | Konstante aus R24 wird am vorhin reservierten Speicherplatz des Stacks abgelegt. Das ist aufgrund des Schlüsselweortes 'volotaile' nötig, weil die Variable ja von außen verändert werden kann.
`90.e0` | LDI R25,0x00 | Rückgabewert
`0f.90` | POP R0 | Variable wird freigegeben.
`df.91` | POP R29 | Register R29 wird vom Stack wieder zurückgeholt.
`cf.91` | POP R28 | Register R28 wird vom Stack wieder zurückgeholt. 



## 2.Übungsbeispiel  
 ```
int main(void)  
{  
  volatile unsigned char a = 10;  
  volatile unsigned char b= 20;  
  volatile unsigned char f=a+b;  
  return 0;  
}  
```  

**Befehl** | **in Worten** | **Beschreibung**
--------------- | --------- | ---------
`cf.93` | PUSH R28 | Register R28 wird auf den Stack gelegt.
`df.93` | PUSH R29 | Register R29 wird auf den Stack gelegt.  
`cd.b7` | IN R28,0x3d | Y-Register wird zum Stackpointer
`de.b7` | IN R29,0x3e | Y-Register wird zum Stackpointer
`8a.e0` | LDI R24,0x0A | Konstante (10) wird im Register R24 abgelegt.
`89.83` | STD Y+1,R24 | Konstante aus R24 wird am Speicherplatz des Stacks der ersten lokalen Variable (a) abgelegt.
`84.e1` | LDI R24,0x14 | Konstante (0x14 = 8) wird im Register R24 abgelegt.
`8a.83` | STD Y+2,R24 | Konstante aus R24 wird am Speicherplatz des Stacks der zweiten lokalen Variable (b) abgelegt.
`29.81` | LDD R18,Y+1 | Der Wert von Stackpointer+1 wird geladen
`8a.81` | LDD R24,Y+2 | Der Wert von Stackpointer+2 wird geladen
`90.e0` | LDI R25, 0x00 | Konstante 0x00 wird am Register R19 abgelegt.
`82.0f` | ADD R24,R18 | Die beiden Register werden addiert, ohne Berücksichtigung des Carry-Flags.  
`91.1d` | ADC R25,R1 | Addition mit Berücksichtigung des Carry-Flags. Das Carry-Flag enthält den Übertrag einer Addition. 
`9c.83` | STD Y+4,R25| Ergebnis der Addition wird der Variable e im Stack zugewiesen
`8b.83` | STD Y+3,R24| Ergebnis der Addition wird der Variable e im Stack zugewiesen
`2b.81` | LDD R18, Y+3 | Die Variable e wird ins CPU-Register geladen.  
`3c.81` | LDD R19, Y+4 | Die Variable e wird ins CPU-Register geladen.  
`82.2f` | MOV R24,R18 | Die Variable e wird aufgrund interner Arbeitmuster in die Register R24/R25 verschoben.
`93.2f` | MOV R25,R19 | Die Variable e wird aufgrund interner Arbeitmuster in die Register R24/R25 verschoben.
`0f.90` | POP R0 | Variable a wird freigegeben.  
`df.91` | POP R29 | Register R29 wird vom Stack wieder zurückgeholt.
`cf.91` | POP R28 | Register R28 wird vom Stack wieder zurückgeholt.


#### Addieren, multiplizieren & dividieren mit unterschiedlichen Datentypen der Variablen  
8 Bit + 8 Bit: *add; 46 Takte; 2,9µs*  
8 Bit x 8 Bit: *mul; 47 Takte*  
8 Bit / 8 Bit: *123 Takte; benötigt mehr Takte, weil es keinen eigenen Divisions-Maschinenbefehl gibt*  
32 Bit + 32 Bit: *add; 92 Takte; mehr Takte aufgrund größerer Daten*  
32 Bit x 32 Bit: *mul; 165 Takte; ca 10µs*  
32 Bit / 32 Bit: *701 Takte; ca 44µs*  
float + float: *9 11Takte*  
float x float: *1763 Takte; ca 110µs*  
float / float: *1380 Takte*  
double / double: *1380 Takte*  



## 3. Übungsbeispiel   
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
Der Befehl *BRNE* ist der wichtigste Maschinenebefehl. BRNE bedeutet Branch if not equal.Er führt die Operation solange aus, bis eine festgelegte Bedindung erfüllt ist. Es wird hier von 10 nach 0 gezählt.  

## Taktverbrauch bei Rechenoperationen  
Rechnung | Takte   
-------- | -----  
8 + 8 Bit | 46  
8 * 8 Bit | 47  
8 / 8 Bit | 123     
32 + 32 Bit | 92  
32 * 32 Bit | 165  
32 / 32 Bit | 701  
float + float | 911 
float * float | 1763  
float / float | 1380  
double / double | 1380


