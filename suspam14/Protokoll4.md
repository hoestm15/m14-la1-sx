# Protokoll 4: Makefiles
Name: Patrick Schuster  
Klasse: 4AHME  
Gruppe: 3    
Anwesend: Reinbacher, Ruffenacht, Sackl, Sackl, Sammer, Schmuck, Schuster  
Abwesend: Schmuck Martin

# Wiederholung: C Übersetzungsvorgang
Um eine Hochsprache (wie z.B. C, C++ oder Java) ausführen zu können muss diese zuerst in Maschinencode übersetzt. Diesen Vorgang nennt man Umgangssprachlich kompilieren. Wenn man es genau nimmt ist das kompilieren nur ein Zwischenschritt.
## nötige Schritte für den Übersetzungsvorgang  
Schritt | Dateiendung | Beschreibung  
--- | --- | ---  
Präprozessieren | .i | Präprozessoranweisungen (#include, #define, #ifdef,...) werden verarbeitet  
Kompilieren | .s | C Anweisungen werden in Assembler übersetzt  
Assemblieren | .o | Assembler Befehle werden in ein binäres Maschinenbefehlsmuster übersetzt   
Linken | .out | Es werden alle Maschinenbefehle und Bibliotheken aus verschiedenen Objektdateien zusammengeführt und Speicheradressen vergeben   

Um das übersetzte Programm für einen Mikrocontroller zu verwenden muss das Programm noch in ein Format übersetzt werden das der Programmer verwenden kann. In unserem Fall eine Hex-Datei (.hex).  

![Übersetzungsvorgang ](https://github.com/suspam14/la1/blob/master/C_Uebersetzungsvorgang.svg)  
Quelle: Mikrocontroller Skript von Professor Steiner  

# Makefiles
Für den Übersetzungsvorgang von C-Programmen greifen IDEs üblicherweise auf das Übersetzungungstool *make* zurück. 
Wenn dieses Tool aufgerufen wird greift es auf eine Steuerdatei, die sogenannte *Makefile*, zurück und steuert den Übersetzungsvogang. 
Ein Eintrag in der Makefile besteht aus den **Zielen**, den **Abhängigkeiten** und den **Befehlen**.

### Syntax einer Makefile  
```
Ziel A: Abhängigkeit 1, Abhängigkeit 2,...  
[Tab] Kommando   
[Tab] Kommando  
...

Ziel B: Abhängigkeit 1, ...   
[Tab]   Kommando  
...  
```
## Funktionsweise einer Makefile
Wenn man die Makefile mit dem Befehl *make* aufruft wird aufruft wird das erste Ziel aufgerufen und auf jegliche Abhängigkeiten überprüft. Falls hinter dem Befehl *make* noch ein Ziel angegeben wird (wie z.B. make clean), dann wird bei diesem Ziel begonnen. Falls es eine Abhängigkeit auf ein Ziel gibt wird dieses überprüft. Falls die Datei bereits exestiert wird der Zeitstempel verglichen und entschieden ob ein erneutes ausführen der Kommandos überhaupt nötig ist. Falls die Datei nicht exestiert werden die Befehle abgearbeitet.
### Besondere Ziele einer Makefile  
#### So gut wie jede Makefile besitzt besondere Ziele, die in jeder Makefile gleich heißen.  
Name | Beschreibung    
--- | ---  
clean | löscht alle Dateien die durch das Übersetzen des programms entstehen  
cleanAndBuild | führt einen clean aus und übersetzt das programm neu  

### Fehler beim Abarbeiten der Befehle  
Falls beim Abarbeiten von Befehlen in der Makefile Fehler auftreten bricht der Vorgang ab. Um zu kontrollieren ob im vorherigen Befehl ein Fehler aufgetreten ist, kann man in der lokalen Variable der Shell namens `$?` mit dem Befehl `echo $?` nachschauen. Wenn in dieser eine 0 steht ist kein Fehler aufgetreten, wenn eine 1 steht schon.
Fehler können zum Beispiel beim Ziel *clean* auftreten, wenn Dateien gelöscht werden sollen die nicht exestieren. Dieses Problem kann umgangen werden in den man vor den Befehl ein `-` setzt. Das bezweckt dass das make Tool weiter arbeitet falls ein Fehler auftritt.

### Zeitstempel ändern
Falls ein Ziel bereits exestiert wird der Zeitstempel verglichen um zu bestimmen ob ein erneutes ausführen der Befehle nötig ist. Ist der Zeitstempel von main.c aktueller als der von main.o muss main.o neu erstellt werden, umgekehrt hingegen nicht. Um diesen zu ändern gibt es den shell Befehl `touch <Dateiname>`.

# Übung 
