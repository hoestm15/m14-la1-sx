# Protokoll
## 3. Einheit
  Name: Jakob Boecksteiner  
  Klasse: 4AHME, Gruppe 1  
  Datum: 24.10.2017  
  Anwesend: Berger, Böcksteiner, Bullner, Enzi, Ehmann, Kobor, Knappitsch  
  Abwesend: niemand  
  
  ## Wiederholung
  
  Am anfang der Einheit haben wir die vorherigen Einheiten wiederholt. Besprochen wurde Atmel Studio und der µC. Genauere Infos zum µC im [2. Protokoll](https://github.com/HTLMechatronics/m14-la1-sx/blob/boejam13/boejam13/README_17.10.2017.md).
  
  ## Fortsetzung Atmel Studio
  ### Quellcode
  
  ```c
int main (void)
{
	volatile unsigned char x;
	x = 12;
	
	return x;
}
```
  Um die Übersicht der Maschinenbefhele zu erhalten muss man das Programm im Debugging-Modus starten und anschließend in den Disassambly-Modus gehen.
  ### Assambler
  
  Maschinenbefehl | Name | Erklärung
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

  
