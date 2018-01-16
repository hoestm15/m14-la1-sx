# 4.Einheit: 16.01.2018

Gegenstand: LA1  
Name: Gert Enzi  
KN: 5  
Klasse: 4AHME  
Gruppe: 1  

# Makefiles  
## Was sind Makefiles?  
Makefiles sind Textdateien, die dazu verwendet werden können einen Übersetzungsvorgang zu steuern. Man kann sie aber auch zu anderen
Zwecken nutzen. Kurz gesagt sind es Dateien, die das Arbeiten mit Befehlen oder Programmen einfacher und übersichtlicher gestalten können.  
  
## Verwendung von Makefiles  
Um den für Makefiles reservierten Befehl **make** nutzen zu können, benötigt man eine Steuerdatei. Diese hat in den meisten Fällen den
dafür vorgesehenen Namen *Makefile*, kann aber auch andere Namen haben (muss man jedoch als Information hinzufügen).  

### Aufbau eines Makefiles  
**Makefile**
```
Ziel1: Abhängigkeiten 
  ->  Kommando 1
  ->  Kommando 2
  ->  ..........

Ziel2: Abhängigkeiten
  ->  Kommando 1
  ->  Kommando 2
  ->  ..........
```
Die Ziele (Targets) und Abhängigkeiten (Dependencies) können Dateien sein (in unserem Fall z.B.: main.c, main.o ...), müssen es aber nicht
sein. Man kann ebenso Symbole dafür verwenden.  
Beispiel:
```
clean:            - ist nun ein Symbol ohne Abhängigkeiten
  ->  rm main.o   - in diesem Fall wird die Datei main.o "removed" also entfernt
```
Für die Kommandos (Commands) ist es wichtig, dass man davor wie oben gezeigt einen Tabulator verwendet, sonst kommt es zu einer 
Fehlermeldung und die Befehle können nicht weiter ausgeführt werden.  

### Wie arbeitet ein Makefile?
Beim Aufruf des Befehls **make** wird das komplette Makefile einmal durchlaufen. Dabei zu beachten ist, dass ab einem Fehler der Abbruch
des Vorgangs stattfindet. Darum ist es wichtig bei Befehlen oder Aufgaben die unbedingt erfüllt werden müssen entsprechende Zeichen vor 
das Kommando gesetzt werden (genauere Beschreibung später).
