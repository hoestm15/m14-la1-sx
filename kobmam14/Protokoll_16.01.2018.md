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

## Wie werden Makefiles verwendet?

Um das Build-Management-Tool make benutzen zu können, wird eine Steuerdatei benötigt. Diese Datei kann einen beliebiigen Namen haben, wird aber normalerweise mit dem dafür bestimmten Namen: Makefile benannt. (dabei muss die Großschreibung, beachtet werden, welche bei Unix-Dateisystemen unterschieden wird)

## Wie sind Makefiles aufgebaut?

Makefiles bestehen aus Zielen (Targets), den Abhngigkeiten (Dependencies) und Kommandos (Commands).
Zur veranschaulichung:
