# Protokoll 1

## Thema: Git und Github

Datum: 10.10.2017
Abwesend: Niemand

Git ist eine Datenverwaltungssoftware, die im Gegensatz zu SVN auch offline Datenbanken 
speichert und somit das Offline-Arbeiten ermöglicht. 
Zudem gibt es die Möglichkeit von mehreren Branches in einem Repository.
Ein Branch ist ein von den restlichen Daten unabhängiger Zweig des Repository, in dem man arbeiten kann, ohne die Arbeiten in anderen Branches zu stören.
Man kann mehrere Branches auch "mergen", Dass bedeutet man führt die Branches zusammen. Z.B.: Einen Workbranch in dem man Dateien aktualisiert hat, mit dem Master-Branch.

Im Git gibt es 5 Speicherebenen:
* Remote repository (Die Onlinedatenbank)
* Local repository (Die auf dem lokalen Rechner gespeicherte Datenbank)
* Index (Zwischenstufe, in der man die Daten noch bearbeiten kann, ohne dass sie auf dem Repository landen)
* Workspace (Die aktuelle Arbeitskopie der Dateien)
* Stash (Zwischenspeicher für noch nicht abgeschlossene Arbeiten, die man aber erst zu einem späteren Zeitpunkt beenden will)

Github ist der bedeutenste Online Gitdienst-Anbieter. Die Benutzung ist vollkommen kostenlos, solange alles für jeden zugäglich bleibt.

### Git-Kommandos

* git stash apply (Daten vom Stash in den Workplace ziehen)
* git add (Daten vom Workplace in den Index verschieben)
* git commit (Daten vom Index ins Local repository übertragen)
* git push (Local repository auf einen Git-Server hochladen)
* git clone (Aktueller Stand des Remote repository werden in den Workspace kopiert)
* git checkout (Das Local Repository wird mit dem Remote repository synchronisiert)
* git stash (Daten vom Workspace werden in den Stash verschoben)
