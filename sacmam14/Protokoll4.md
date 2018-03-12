# 4. Protokoll  
## Thema: Makefiles  
**Name:** Sackl Martin   
**Klasse** 4ahme    
**Gruppe:** 3

Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schuster   
Abwesend: Schmuck  
*******************************************************************************************************************************************  
### Wiederholung: Wie wird ein C-Programm übersetzt?  
Um ein C-Programm übersetzen zu können, müssen folgende Schritte durchgeführt werden:  

Schritte | Funktion  
------- | --------  
**Präprozessieren** | main.c wird hier vorbereitet  
**Compelieren** | Assemblercode wird erzeugt, aus main.c wird main.a    
**Assemblieren** | Assemblercode wird in Maschinensprache übersetzt, aus main.a wird main.o  
**Linken** | Programmteile werden miteinander verbunden, ausführbares Programm mit der Endung main.exe oder main.out (Windows oder Ubuntu)  
**Umwandeln** | Ausführbares Programm wird in ein Format umgewandelt, dass der Programmer versteht (Hex, ...)    

Je gröber der Sprachgebrauch ist, desto eher werden alle Schritte zu einem Schritt, **Compelieren**, zusammengefasst.  
*******************************************************************************************************************************************  
### Make-Tool  
Es ist ein Build-Management Tool, das gewisse Kommandos in Abhängigkeiten von Bedingungen ausführt. Dieses Tool übernimmt den gesamten Übersetzungsvorgang und liest **Makefiles**.  

### Makefiles  
Ein Makefile teilt dem Programm make mit was und wie es etwas tun soll. In einem Makefile sind die Abhängigkeiten des Übersetzungsprozesses von Programmen erfasst.  
#### Aufbau von Makefiles:  
```  
Ziel 1: Abhängigkeiten  
  ->  Kommando A  
  ->  Kommando B  
  -> ...  

Ziel 2: Abhängigkeiten  
  ->  Kommando A  
  ->  Kommando B  
  -> ...  
```  
**Für "->" muss ein echter Tabulator gesetzt werden!**  

### Kommando "make"  
Mit dem Kommando `make` wird die Abarbeitung der Makefiles gestartet. Das make-Tool erkennt ob Ziele schon abgearbeitet sind oder noch ausgeführt werden müssen. Wenn der Zeitstempel nicht passt, muss alles neu compeliert und gelinkt werden. Mit dem Befehl `touch` kann man den Zeitstempel im nachhinein ändern.  

Kommando | Beschreibung  
-------- | ------------  
make clean | generierte Dateien werden gelöscht  
make cleanAndBuild | generierte Dateien werden zuerst gelöscht und anschließend neu erzeugt  
make main.o | C-Code wird in Maschinensprache übersetzt    

### Zeitstempel  
Er sagt aus zu welchen Zeitpunkt die Datei geschrieben oder verändert wurde.  
*************************************  
### Übungen mit Makefiles  
