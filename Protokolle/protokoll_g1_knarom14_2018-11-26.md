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

### Klassen

#### main.ts
``` TypeScript
import { Server } from './server';

class Main {
    public static main() {
        new Server(4711).start();
    }
}
Main.main();
```

Als Erstes wird die Klasse Server mit `import` importiert. In der Main-Methode wird ein Objekt der importierten Klasse erzeugt. Als Parameter wird der Port 4711 übergeben. Um den Server zu starten muss man allerdings noch `Main.main()` aufrufen, da die Klasse main(), anders als in java, nicht standartmäßig ausgeführt wird. Der Server ist unter `localhost:4711` erreichbar.

#### server.ts
``` TypeScript
import * as express from 'express';
import { Database } from './database';

export class Server {
    private port: number;
    private server: express.Express;

    constructor (port: number) {
        this.port = port;
        this.server = express();
        // this.server.get('/data', this.handleGetData.bind(this));
        this.server.get('/data', (req, res, next) => this.handleGetData(req, res, next));
        this.server.get('/dataset', (req, res, next) => this.handleGetDataSet(req, res, next));
    }

    start() {
        this.server.listen(this.port);
        console.log('Server auf Port ' + this.port + ' gestartet.');
    }

    private handleGetData(req: express.Request, res: express.Response, next: express.NextFunction) {
        console.log('Server ' + this.port);
        res.json({temp: 23.4, power: 120, unit: 'W'});
    }

    private handleGetDataSet (req: express.Request, res: express.Response, next: express.NextFunction) {
        res.json(Database.getInstance().getAll());
    }
}
```
Zuerst werden die Klasse Database und das Framework Express importiert. 

Das Schlüsselwort `express` wird verwendet, um die Klasse an einem anderen Ort importieren zu können. 

Zwei private Varialen(port, server) werden erstellt. Im Konstruktor wird `port` der übergebene Wert aus der Klasse `main()` zugewiesen. Außerdem werden die beiden Handler-Methoden für `/data` und `/dataset` aufgerufen. In diesen ist definiert, wie der Server auf gewisse Anfragen reagieren soll. 

Die Methode `start()` start mit Hilfe der Methode `listen()` den Server.


#### database.ts
``` Typescript
import { Value } from './value';

export class Database {
    public static getInstance(): Database {
        if (!this.getInstance) {
            this.instance = new Database();
        }
        return this.instance;
    }

    private static instance: Database;

    private data: Value [] = [];

    private constructor () {
        this.add(new Value(23.4, 100));
        this.add(new Value(23.5, 120));
        this.add(new Value(23.6, 150));
        this.add(new Value(23.7, 200));
    }

    public size (): number {
        return this.data.length;
    }

    public get (index: number) {
        return this.data[index];
    }

    public add (value: Value) {
        this.data.push(value);
    }

    public remove (index: number) {
        this.data.splice(index, 1);
    }

    public getAll (): Value [] {
        return [].concat(this.data);
    }
}
```

Die Klasse Database ist eine Datenbank, welche mehrere Objekte der Klasse Value enthält.

Methoden:
* size(): gibt die Anzahl der gespeicherten Elemente zurück
* get(): gibt das Element vom übergebenen Index zurück
* add(): fügt ein Element hinzu
* remove(): entfernt das Element an der Position `index`
* getAll(): gibt alle gespeicherten Elemente in einem neuen Feld zurück

#### value.ts
``` Typescript
export class Value {
    time: Date;
    temp: number;
    power: number;
    powerUnit: string;
    tempUnit: string;

    constructor(tempCelsius: number, powerWatt: number) {
        this.time = new Date();
        this.temp = tempCelsius;
        this.tempUnit = '°C';
        this.power = powerWatt;
        this.powerUnit = 'W';
    }
}
```

Die Klasse Value ist eine einfache Datenhaltungsklasse in der fünf Variablen definiert sind. Anders als in Java werden in Typescript keine Getter-Methoden benötigt. Die Variablen sind `public`.

