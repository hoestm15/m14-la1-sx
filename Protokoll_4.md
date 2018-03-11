# **3. Laborprotokoll** 

*von Florian Ruffenacht*

Datum: 05.12.2017 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

Abwesend: Schmuck Martin

#Wiederholung: Übersetzungvorgang eines C-Programms
Um den C-Code in eine ausführbahre Datei umzuwandeln sind folgende Schritte notwendig:

Name|Dateityp vorher | Dateityp nacher | Beschreibung
*Präprozessieren*| main.c | main.? | Bearbeitung von Anweisungen wie #include, #define und #if. Da diese Datei im Normalfall nicht wirklich entsteht, gitb es  auch keine eigene Endung.
*Compelieren*| main.? | main.a | Der durch den Präprozzessor bearbeitete Code wird in Assmeblercode umgewandelt
*Assemblieren*| main.a | main.o | Der Assemblercode wird in Maschinencode übersetzt
*Linken* | main.o | main.exe/ main.out |  Alle Programmteile werden durch den Linker vereint. Daraus entstht ein ausführbares Programm
*Umwandeln* | | | Die ausführbare Datei wird in ein Format umgewandelt, das der Programmer versteht. (z.B. Hex)

Im Sprachgebrauch werden meist die Schritte des Vorgangs bis zum entstehen einer Beispiel.o-Datei als 
