# **3. Laborprotokoll** 

*von Florian Ruffenacht*

Datum: 05.12.2017 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

Abwesend: -

## CPU-Register
Die folgende Register werden für spezielle Zwecke verwendet:

Register | Verwendung 
|---|---|
`R1`| ist immer mit 0x00 beschrieben
`R8 - R25`| für Parameter und Rückgabewerte
`R26 + R27`| X- Register für Adressen
`R28 + R29`| Y- Register für Adressen
`R30 + R31` | Z- Register für Adressen

## Der Unterschied zwischen "deklarieren", "definieren" und "initialisieren"



**Deklaration:** Dem Compiler wird eine Variable bekannt gegeben

**Definition:** Der Variable wird ein Speicherbereich zugeteilt

**Initialisierung:** Der Variable wird ein Wert zugewiesen

[Weitere Informationen](http://www.c-howto.de/tutorial/variablen/deklaration/)

## Analysieren von Assembler-Befehlen
  Wie bereits in der [letzten Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/Protkoll_2.md) analysierten wir einfache C-Programme mit AtmelStudio.
  
### Informationen zur Übung:

  **volatile**
  
  Mit dem Schlüsselwort `volatile` wir dem Compiler bei der Varaiblendeklaration bekannt gegeben, dass die Variable auch durch analoge Signale von außen verändert werden kann. Das Schlüsselwort wurde verwendet um den Compiler davon abzuhalten,
  die einfachen Gleichungen unserer Programme selber zu lösen und im Programm nur mehr zurückzugeben.
  
  **unsignede char**
  
  Den Datentyp `unsigned char` verwenden wir um mit 1 Byte vorzeichenunbehaftete Zahlen zwischen 0 und 255 darstellen zu können. 
  Die Datentypen `char` und `signed char` sind vorzeichenbehaftet.
  
  **Startup Code**
  
  Der Startup-Code ist dafür zuständig, den Mikroprozessor in ein solchen Zustand zu bringen, dass der restlich Code Fehlerlos abgearbeitet werden kann.  

 ### Zuweisen eines Konstanten Wertes
  Es wurde folgendes Programm analysiert:
  
  ![Bild C- Code Programm1](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/BildE3P1C.JPG)
  
  Dabei ergab sich nach dem Debuggen und Kompilieren folgender Maschinencode:
  
  ![Bild Assembler-Code Programm1](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/BildE3P1A.JPG)
  
  Analyse des Maschinenecodes:
  
  Maschinenbefehl | in Worten | Beschreibung
--- | --- | ---
`cf.93` | PUSH R28 | Register R28 wird auf den Stack gelegt, weil sich die Register R26-R31 während einer Funktion nicht verändern dürfen.
`df.93` | PUSH R29 | Register R29 wird auf den Stack gelegt, weil sich die Register R26-R31 während einer Funktion nicht verändern dürfen.
`1f.92` | PUSH R1 | Register R1 wird auf den Stack gelegt. Somit wird auf dem Stack der Speicher für die lokale Variable reserviert.
`cd.b7` | IN R28,0x3D | Der Stackpointer (0x3D) wird aus dem I/O Register in R28 (Y-Register) geladen.
`de.b7` | IN R29,0x3E | Der Stackpointer (0x3E) wird aus dem I/O-Register in R29 (Y-Register) geladen.
`81.e2` | LDI R24,0x21 | Konstante (0x21 = 12) wiDer Stackpointer (0x3D) wird aus dem I/O-Register in R28 (Y-Registerrd im Register R24 abgelegt.
`89.83` | STD Y+1,R24 | Konstante aus R24 wird am vorhin reservierten Speicherplatz des Stacks abgelegt. Das ist aufgrund des Schlüsselweortes 'volatile' nötig, weil die Variable ja von außen verändert werden kann.
`89.81` | LDD R24,Y+1 | Die Variable wird ins Register R24 geladen. Das ist aufgrund des Schlüsselwortes 'volatile' nötig, weil die Variable ja von außen verändert werden kann.
`90.e0` | LDI R25,0x00 | Rückgabewert
`0f.90` | POP R0 | Variable wird freigegeben.
`df.91` | POP R29 | Register R29 wird vom Stack wieder zurückgeholt.
`cf.91` | POP R28 | Register R28 wird vom Stack wieder zurückgeholt. 

### Addition zweier Variablen
Es wurde folgendes Programm analysiert:

![Bild C-Code Programm 2](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/BildE3P2C.JPG)

Dabei ergab sich nach dem Debuggen und Kompilieren folgender Maschinencode:
**
![Bild Assembler-Code Programm 2](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/BildE3P2A.JPG)

Analyse des Maschinencodes:

Maschinenbefehl | in Worten | Beschreibung
--------------- | --------- | ---------
`cf.93` | PUSH R28 | Register R28 wird auf den Stack gelegt.
`df.93` | PUSH R29 | Register R29 wird auf den Stack gelegt.
`00.d0` | RCALL PC+0x0001 | Zum Weiterspringen auf die nächste Adresse mit RCALL wir einer Rücksprungadresse im Stackk angelegt. Diese zwei Bytes können jzum speichern jeweils einer Variable verwendet werden.
`00.d0` | RCALL PC+0x0001 | Zum Weiterspringen auf die nächste Adresse mit RCALL wir einer Rücksprungadresse im Stackk angelegt. Diese zwei Bytes können jzum speichern jeweils einer Variable verwendet werden.
`cd.b7` | IN R28,0x3d | Der Stackpointer (0x3D) wird aus dem I/O Register in R28 (Y-Register) geladen.
`de.b7` | IN R29,0x3e | Der Stackpointer (0x3E) wird aus dem I/O Register in R28 (Y-Register) geladen.
`8a.e0` | LDI R24,0x0A | Konstante (0x0A=10) wird im Register R24 abgelegt.
`89.83` | STD Y+1,R24 | Konstante aus R24 wird am Speicherplatz des Stacks der ersten lokalen Variable (a) abgelegt.
`84.e1` | LDI R24,0x14 | Konstante (0x14 = 8) wird im Register R24 abgelegt.
`8a.83` | STD Y+2,R24 | Konstante aus R24 wird am Speicherplatz des Stacks der zweiten lokalen Variable (b) abgelegt.
`29.81` | LDD R18,Y+1 | Variable a wird in Register R24 geladen.
`8a.81` | LDD R24,Y+2 | Variable b wird in Register R18 geladen.
`90.e0` | LDI R25, 0x00 | Konstante 0x00 wird am Register R19 abgelegt.
`82.0f` | ADD R24,R18 | Die beiden Register werden addiert, ohne Berücksichtigung des Carry-Flags. Das Endergebnis wird in R24 gespeichert.
`91.1d` | ADC R25,R1 | Addition mit Berücksichtigung des Carry-Flags. Das Carry-Flag enthält den Übertrag einer Addition. 
`9c.83` | STD Y+4,R25| Ergebnis der Addition wird der Variable e im Stack zugewiesen
`8b.83` | STD Y+3,R24| Ergebnis der Addition wird der Variable e im Stack zugewiesen
`2b.81` | LDD R18, Y+3 | Die Variable e wird ins CPU-Register geladen. Das ist nötig, das sie sich aufgrund des Schlüsslwortes   `volotaile` verändern hätte können.
`3c.81` | LDD R19, Y+4 | Die Variable e wird ins CPU-Register geladen. Das ist nötig, das sie sich aufgrund des Schlüsslwortes `volotaile` verändern hätte können.
`82.2f` | MOV R24,R18 | Die Variable e wird aufgrund interner Arbeitmuster in die Register R24/R25 verschoben.
`93.2f` | MOV R25,R19 | Die Variable e wird aufgrund interner Arbeitmuster in die Register R24/R25 verschoben.
`0f.90` | POP R0 | Variable a wird freigegeben.
`0f.90` | POP R0 | Variable b wird freigegeben.
`0f.90` | POP R0 | Variable e wird freigegeben.
`0f.90` | POP R0 | Variable e wird freigegeben.
`df.91` | POP R29 | Register R29 wird vom Stack wieder zurückgeholt.
`cf.91` | POP R28 | Register R28 wird vom Stack wieder zurückgeholt.

Zum besseren Verständnis ist hier noch einmal der Aufbau des Stacks skizziert:

![Bild Stackaufbau E3](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/StackE3.svg)

## Testen der Prozessorgeschwindigkeit
Um zu erkennen, mit welchen Operationen der Mikroprozesser des Atmega328 wie lange braucht, haben wir in einfachen Programmen verschiedene Operationen mit verschiedenen Datentypen druchgeführt. Dabei wurde im AtmelStudio jeweils die rein zum Rechnen benötigte Zeit herausgelesen.

Operation| Datentyp und Operation | Anzahl der benötigten Takte | Kommentar
---|---|---|---
Addition| 8 Bit + 8 Bit | **46 Takte** |
Multiplikation| 8 Bit * 8 Bit | **47 Takte**| kaum ein Unterschied zur Addition, weil ein eigener Multiplikationsbefehl zur Vefügung steht
Division| 8 Bit / 8 Bit | **123 Takte** | deutlich mehr Takte als bei der Multiplikaton, weil die Operation mit einer Schleife ud keinem eigenen Befehl durchgeführt wird
Addition| 32 Bit + 32 Bit | **192 Takte** |
Multiplikation| 32 Bit * 32 Bit | **165 Takte**| 
Division| 32 Bit / 32 Bit | **701 Takte** | 
Addition| `float` + `float` | **905 Takte** |
Multiplikation| `float` * `float` | **1763 Takte**| 
Division| `float` / `float` | **1380 Takte** | Dass zum Dividieren weniger Takte gebraucht werden als beim Multiplizieren liegt wahrscheinlich an den Verwendeten Werten, die sich scheinbar schnell dividieren lassen.
Division| `double` / `double` | **1380 Takte** | Der Datentyp `double` wir von dem Kompiler als `float ` verarbeitet, da keine doppeltgenauen Fließkommazahlen für den Mikroprozessor zur Verfügung stehen

Die **Erkentnis** aus dem Test ist, dass es sich vor allem bei Echtzeitsystemen durchaus auszahlt, den __*kleinstmöglichen Datentyp*__ zu verwenden.
