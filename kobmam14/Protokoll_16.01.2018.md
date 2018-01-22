# Protokoll 16.01.2018

## 4. Einheit
## Thema: Makefiles

Name: Markus Kobor  <br>
Klasse: 4AHME  <br>
Datum 16.01.2017  <br>
Gruppe: 1  <br>
Anwesend: Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Enzi Gert, Knappitsch Robert, Kobor Markus  <br>
Abwesend: -  <br>

## Was sind Makefiles & wozu werden sie verwendet?

Makefiles sind Textdateien, welche häufig dazu verwendet werden einen Übersetzungsvorgang zu steuern. Sie können aber auch als Zusammenfassung von Befehlen und Programmen verwendet werden.

C Programme bestehen normalerweise aus vielen Quelltextdateien, welche vom C Compiler einzelt compiliert werden. Besteht ein Programm zum Beispiel aus 10 .c Dateien, muss der Compiler 10 mal aufgerufen werden. Man bekommt für jede .c Datei eine 
.o- Objektdatei, welche den erzeugten Binärcode enthält. Der Linker fügt dann die Objekt-Dateien zu einem ausführbaren Programm
zusammen.

Bei Mikrocontrollern wird vom Linker eine .hex Datei für den Programmieradapter erzeugt.
Die Aufgabe vom make Programm besteht darin, den Compilier- und den Link-Vorgang automatisch ablaufen zu lassen. Wird make verwendet, ist es nicht nötig, jede .c Datei einzeln zu compilieren.

**Makefiles versuchen so wenig Aufwand wie möglich zu betreiben, was besonders bei großen Programmen wichtig ist.** 

Dies wird unter anderem dadurch erreicht, dass vor jedem Durchlauf der **Zeitstempel** von allen Dateien überprüft wird und nur nicht aktuelle Aufgaben durchgeführt werden.
Der Zeitstempel gibt an, wann eine Datei zuletzt geändert wurde.

Früher konnten Compeliervorgänge auch Tage dauern.

## Wie werden Makefiles verwendet?

Um das Build-Management-Tool make benutzen zu können, wird eine Steuerdatei benötigt. Diese Datei kann einen beliebiigen Namen haben, wird aber normalerweise mit dem dafür bestimmten Namen "Makefile" benannt. (dabei muss die Großschreibung, beachtet werden, welche bei Unix-Dateisystemen unterschieden wird)

## Wie sind Makefiles aufgebaut und was ist zu beachten?

Makefiles bestehen aus Zielen (Targets), den Abhngigkeiten (Dependencies) und Kommandos (Commands). <br>
Zur veranschaulichung:

```
Ziel 1: Abhängigkeiten 
  ->  Kommando 1
  ->  Kommando 2
  ->  Kommando 3

Ziel 2: Abhängigkeiten
  ->  Kommando 1
  ->  Kommando 2
```
Wichtig ist, dass vor den Kommandos Tabulatoren verwendet werden, da sonst eine Fehlermeldung ausgegeben wird. Das ist vorallem zu beachten, wenn Text kopiert wird, da sich 8 Leerzeichen optisch nicht vom Tabulator unterscheiden.

Wird der Befehl make aufgerufen, wird das Makefile soweit durchlaufen, bist ein Fehler auftritt. Das bedeutet, dass alle nachfolgenden Schritte nicht abgewickelt werden. Somit ist es wichtig vor Befehlen, bei denen Fehler auftreten können entprechende Maßnahmen, wie z.B ein vorne hingesetzes "-", welches soviel wie "egal, mach weiter" bedeutet, zu setzen.

## Praktische Übung

