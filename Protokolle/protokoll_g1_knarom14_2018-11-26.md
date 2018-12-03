# Protokoll: Knappitsch Robert
## 2. Einheit: REST-Server

* 5AHME (Gruppe 1)
* Datum: 26.11.2018
* Anwesend: Berger Emil, Böcksteiner Jakob, Ehmann Julian, Knappitsch Robert, Kobor Markus, Köhler Marcel
* Abwesend: Bullner Jeremy

## Visual Studio Code
VS Code ist ein freier Quelltext-Editor der Firma Microsoft und ist plattformunabhängig verfügbar. 
Basierend auf dem Framework Elektron bietet VS Code viele Funktionen, wie z.B. Syntaxhervorhebung, Debugging, 
Code-Faltung, Autovervollständigung und Versionsverwaltung.
Mit Visual Studio hat VS Code bis auf einige Funktionen nichts gemeinsam. Eine Vielzahl an Programmier- und 
Auszeichnungssprachen wird unterstützt. Durch Plug-Ins können auch weitere hinzugefügt werden.

Mit dem Konsolen-Befehl `code <Zielverzeichnis>` wird VS Code direkt im angegebenen Verzeichnis gestartet.

## Express.js
> Express.js ist ein serverseitiges Webframework für die JavaScript-basierte Plattform Node.js. 
Es erweitert Node.js um Werkzeuge, mit denen das Entwickeln moderner 
Webanwendungen einfacher gestaltet wird.

[Quelle: Wikipedia - Express.js](https://de.wikipedia.org/wiki/Express.js)

## Singleton
> Das Singleton (selten auch Einzelstück genannt) ist ein in der Softwareentwicklung eingesetztes 
Entwurfsmuster und gehört zur Kategorie der Erzeugungsmuster (engl. creational patterns). 
Es stellt sicher, dass von einer Klasse genau ein Objekt existiert. 
Dieses Singleton ist darüber hinaus üblicherweise global verfügbar. 

[Quelle: Wikipedia - Singleton (Entwurfsmuster)](https://de.wikipedia.org/wiki/Singleton_(Entwurfsmuster))

### Verwendung
* Wenn nur ein Objekt einer Klasse exixtieren darf und ein einfacher Zugriff benötigt wird.
* Wenn das einzige Objekt durch Unterklassenbildung spezialisiert werden soll.
* Globaler Zugriff auf das Objekt mit `getInstance()`

### Vorteile
Verbesserung gegenüber globalen Variablen:
* Zugriffskontrolle realisierbar
* durch Unterklassenbildung spezialisierbar
* Welche Unterklasse verwendet werden soll, kann zur Laufzeit entschieden werden.
* Die Einzelinstanz muss nur erzeugt werden, wenn sie benötigt wird.
* Sollten später mehrere Objekte benötigt werden, ist eine Änderung leichter möglich als bei globalen Variablen.

### Nachteile
* Es besteht die große Gefahr, durch exzessive Verwendung von Singletons quasi ein Äquivalent zu globalen Variablen 
zu implementieren und damit dann prozedural anstatt objektorientiert zu programmieren.
* ...

## Projekt - RestServer

### Ordner/Dateien im Projektverzeichnis
* **dist:** Hier befinden sich die Javascript Dateien, welche aus den Typescript-Dateien "transpiliert" wurden.
* **node_modules:** Enthält, von NPM installierte, Pakete.
* **src:** In diesem Ordner liegen die Typescript-Dateien (*.ts)
* **.vscode:** Hier befinden sich Konfigurations-Dateien, welche von VS Code benötigt werden.
* **gulpfile.json:** Zuständig für die Übersetzung
* **package.json:** Dient als eine Art Manifest
* **package-lock.json**
* **tsconfig.json:** Beinhaltet die Konfiguration des Typescript-Kompilers
* **tslint.json:** Enthält die Konfiguration für das Tool "Lint", welches den Code auf Lesbarkeit und 
Funktionsfehler prüft.

