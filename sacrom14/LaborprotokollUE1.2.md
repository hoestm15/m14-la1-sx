# 1.Protokoll  
  
  **Name**:  *Sackl Roland*  
  **Datum:** *06.03.2018*  
  **Uhrzeit:** *9:40-12:25*  
  **Gruppe:** *3*  
  
  **Abwesend:**   Schmuck Martin   
  **Anwesend:**   Sackl Martin, Sackl Roland, Reinbacher Bernhard,Sammer Daniel,Ruffennacht Florian,Schuster Patrick


## Wiederholung: Übersetzungsvorgang eines Programmes  
Das gesamte Übersetzen eines Programmes versteht man im groben Sprachgebrauch  unter _Compelieren_ , jedoch ist das Compelieren nur ein Teil davon. Man benötigt für die Gesamte Übersetzung eines Programmes folgende Schritte:    


 Name | Dateityp vorher | Dateityp nacher | Beschreibung
 ------- | --------  |------- | --------  
*Präprozessieren* | main.c | main.? | Hier wird das Programm vorbereitet. Bearbeitung von Anweisungen wie `#include`, `#define` und `#if`.  
*Compelieren* | main.? | main.a | Hier wird aus dem preprozessierten Code ein Assemblercode erzeugt.   
*Assemblieren* | main.a | main.o | Übersetzen des Assemblercode in Maschinencode.  
*Linken* | main.o | main.exe/ main.out |  Liner verbindet alle Programmteileund vereint sie zu  einen ausführbares Programm.  
*Umwandeln* | main.exe/main.out | z.B. main.hex | Die Datei wird in ein Format umgewandelt, das der Programmer versteht. (z.B. Hex)


