
# **3. Laborprotokoll** 

*von Florian Ruffenacht*

Datum: 05.12.2017 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

Abwesend: Schmuck Martin

# Wiederholung: Übersetzungvorgang eines C-Programms
Um den C-Code in eine ausführbahre Datei umzuwandeln sind folgende Schritte notwendig:

 Name | Dateityp vorher | Dateityp nacher | Beschreibung
 ------- | --------  |------- | --------  
*Präprozessieren* | main.c | main.? | Bearbeitung von Anweisungen wie `#include`, `#define` und `#if`. Da diese Datei im Normalfall nicht wirklich entsteht, gibt es auch keine eigene Endung.
*Compelieren* | main.? | main.a | Der durch den Präprozzessor bearbeitete Code wird in Assmeblercode umgewandelt
*Assemblieren* | main.a | main.o | Der Assemblercode wird in Maschinencode übersetzt
*Linken* | main.o | main.exe/ main.out |  Alle Programmteile werden durch den Linker vereint. Daraus entsteht ein ausführbares Programm

*Umwandeln* | | | Die ausführbare Datei wird in ein Format umgewandelt, das der Programmer versteht. (z.B. Hex)

Im Sprachgebrauch werden meist die Schritte des Vorgangs bis zum entstehen einer Beispiel.o-Datei als "**compelieren**" bezeichnet. Ganz grob werden teilweise auch alle hier angeführten Schritte als "**compilieren**" verstanden.

##make-Tool
Der gesamte Übersetzungsvorgang wird im Normalfall durch das **make-Tool** übernommen. Dieses ruft sogenannte *Makefiles*  auf.

# Makefiles
Makefiles werden in einem Texteditor geschrieben und beinhalten die Anweisungen für das make-Tool. Sie können nicht nur für den Übersetzungsvorgang von Programmen eingesetzt werden, sondern sie sind auch für andere Anwendungen, in denen die zeitliche Abhängigkeit von Dateien ein Rolle spielt, nützlich. Makefiles sind aus **Zielen**, **Abhängigkeiten** und **Kommandos** aufgebaut.

## Aufbau von Makefiles
```
Ziel 1: Abhängigkeiten 
  ->  Kommando A
  ->  Kommando B
  ->  Kommando C

Ziel 2: Abhängigkeiten
  ->  Kommando A
  ->  Kommando B
```
__*Anmerkung*:__ Für den Tabulator vor den Kommandos müssen echte Tabulatoren verwendet werden, da sonst eine Fehlermeldung ausgegeben wird. Das ist vorallem dann zu beachten, wenn Text kopiert wird, da sich ein Tabulator optisch nicht von Leerzeichen unterscheidet.

## Funktionsweise von Makefiles
Beim Aufruf des Makefiles wird zuerst das erste Ziel aufgerufen. Die Abhängigkeiten werden dabei zuerst auf andere Ziele und dann auf Datein untersucht. Bei **anderen Zielen als Abhängigkeit** werden zuerst die abhängigen Ziele  abgearbeitet. Bei **Datein als Abhängigkeit** wird der Zeitstempel von dem Ziel und der Datei verglichen um zu erfassen, ob ein neuerliches Durchführen der Kommandos überhaupt nötig ist. 

Der **Zeitstempel** gibt an wann eine Datei das letzte Mal verändert wurde. Mit dem Befehl `touch <Datei>` kann dieser Zeitstempel auf Linux-Systemen aktualisiert werden.

[Weitere Informmationen zum touch-Befehl](https://wiki.ubuntuusers.de/touch/)  

Wenn das Makefile aufgerufen wird, läuft das Makefile soweit durch, bis ein **Fehler** auftritt. Das bedeutet, dass alle nachfolgenden Schritte nicht abgewickelt werden. Um das bei Befehlen, bei denen Fehler auftreten können, zu verhindern kann ein vor dem jeweiligen Kommando ein `-` eingefügt werden. 

Ob ein **Fehler** aufgetreten ist lässt sich über die Rückgabewerte der Kommandos erfahren. Ist der Rückgabewert ungleich 0, so wird ein Fehler ausgegeben. In der Konsole kann der Rückgabewert des letzten Kommandors mit dem Befehle `echo $?`ausgeben:



#  1. Praktische Übung: Übersetzung eines Programmes durch ein Makefile

Diese kleine C-Programm soll "Guten Morgen" ausgeben. Es wurde die Datei main.c mithilfe des `nano`-Befehls erstellt:

```c
#include <stdio.h>

int main()
{
printf("Guten Morgen");
return 0;
}

```
Dazu wurde folgendes Makefile erstellt:
```
# Das ist ein Kommentar

test1: main.o
	gcc -o test1 main.o

main.o: main.c
	gcc -c main.c

cleanAndBuild: clean test1


clean:  
	-rm main.o
	-rm test1
 
```
Dieses einfach Makefile lässt sich in der Konsole durch den `make`- Befehl als Ganzes ausführen. Es können aber auch einzelne Ziele
in der Konsole aufgerufen werden:

Kommando | Beschreibung
-------- | ------------
make clean | Die erstellten Dateien werden gelöscht
make cleanAndBuild | Die erstellten  Dateien werden gelöscht und anschließend neu erzeugt
make main.o |Der C-Code wird in Maschinencode übersetzt
  
Es wurden folgende Kommandos verwendet:

Kommando | Beschreibung
---------| ------------
gcc -c | Es wird kompiliert, aber noch nicht gelinkt. Dabei entsteht die .o-Datei
gcc -o | Hier kann zusätzlich noch der Name der .o -Datei vergeben werden
-rm | Die Datei wird gelöscht. Durch das `-` wird aber auch bei einem Fehler fortgesetzt.

