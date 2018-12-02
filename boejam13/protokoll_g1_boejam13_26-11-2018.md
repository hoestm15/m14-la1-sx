# Protokoll
  Böcksteiner Jakob  
  5AHME, Gruppe 1  
  26.11.18  
  Anwesend: Berger, Böcksteiner, Ehmann, Enzi, Kobor, Köhler, Knappitsch  
  Abwesend: Bullner  
  
## Visual Studio Code
### Allgemeines  
Visual Studio Code ist ein plattformunabhängiger Quelltext-Editor von Microsoft, der viele verschiedene Programmiersprachen unterstützt (C, C++, HTML, Java, Javascript, TypeScript, ...). Es lässt sich zwar wie jede andere Applikation öffnen, aber man kann auch komfortabel über den Konsolenbefehl `code` einsteigen. Mit `code .` gelangt man direkt in das aktuelle Projektverzeichnis.  
  
### Schnellstartleiste  
Die Schnellstartleiste in VS Code beinhaltet einen Dateiexplorer, eine Suchfunktion, eine Versionsverwaltung, einen Punkt, um in den Debug-Mode zu gelangen und die Möglichkeit, externe Plug-ins einzufügen. 
Wenn man im Dateiexplorer eine Datei mit einem einfachen Mausklick öffnet, dann wird der Dateiname kursiv dargestellt. Klickt man nun auf eine andere Datei, verschwindet der Tab der ersteren. Mit einem Doppelklick öffnet man Dateien dauerhaft.  
  
### Dateiexplorer übersichtlicher gestalten  
Um den Dateiexplorer übersichtlicher zu gestalten, legt man im Projektverzeichnis einen neuen Ordner `.vscode` an. In diesem Ordner erstellt man die Datei `settings.json`. Dort kann man alle für die Programmierung irrelevanten Dateien ausblenden lassen.

```json
{
	"files.exclude": {
	    "**/node_modules": true,
	    "**/dist": true,
	    "package-lock.json": true,
	    ".vscode": true
	}
}
```
  
### Lint
Lint ist dazu da, dass man eine Schönere formatierung hat, es zeigt Fehler an wie zb das man ein Leerzeichen zu viel hat. Die Datei tslint.json beschreibt welche Fehler gemeldet werden und welche nicht.

## Projekt Rest-Server

### main.ts

```typescript
import {Server} from './server';

class Main {

    public static main () {
        new Server(4711).start();
    }
}

Main.main();
```
In `main.ts` wird wird der `Server` importiert. In der main wird der Server auf dem Port 4711 gestartet. Das die funktion auch wirklich aufgerufen wird muss man am Ende noch `Main.main();` aufrufen, da Javascript genauso wie C von oben nach unten durchläuft.

## server.ts
```typescript
import * as express from 'express';
import { Database } from './database';

export class Server {

    private _port: number;
    private _server: express.Express;

    constructor (port: number) {
        this._port = port;
        this._server = express();

        // this._server.get('/data', this.handleGetData.bind(this));
        this._server.get('/data',
            (req, res, next) => this.handleGetData(req, res, next));
        this._server.get('/dataset',
            (req, res, next) => this.handleGetDataSet(req, res, next));
    }

    start () {
        this._server.listen(this._port);
        console.log('Server auf Port ' + this._port + ' gestartet');
    }

    private handleGetData(req: express.Request, res: express.Response, next: express.NextFunction) {
        console.log('Server ' + this._port);
        res.json({temp: 23.4, power: 120, unit: 'W'});
    }

    private handleGetDataSet(req: express.Request, res: express.Response, next: express.NextFunction) {
        res.json(Database.getInstance().getAll());
    }
}
```
  In der Klasse `server.ts` wird `express` importiert, diese Modul ermöglicht die verwendung von http und https. Auch die Klasse Database wird improtiert. Da der Server in der Main Klasse importtiert wird braucht man des Schlüselwort `export`.  
  Da die Klasse `Server` in `Main` importiert wird, muss vor der Klasse das Schlüsselwort `export` geschrieben werden.  
Mit der Methode `start();`startet der Server.

## value.ts
```typescript
export class Value {

    time: Date;
    temp: number;
    power: number;
    powerUnit: String;
    tempUnit: String;

    constructor (tempCelsius: number, powerWatt: number) {
        this.time = new Date();
        this.temp = tempCelsius;
        this.tempUnit = '°C';
        this.power = powerWatt;
        this.powerUnit = 'W';
    }

}
```
value.ts ist unsere Datenerhaltungsklasse. 

## database.ts
```typescript
import { Value } from './value';

export class Database {

    public static getInstance (): Database {
        if (!this.instance) {
            this.instance = new Database();
        }
        return this.instance;
    }

    // Feld (in JS) ist Array-List (in Java)
    // Objekt (in JS) ist HashMap (in Java)

    private static instance: Database;

    private data: Value[] = [];

    private constructor () {
        this.add(new Value(23.4, 100));
        this.add(new Value(23.5, 120));
        this.add(new Value(23.6, 150));
        this.add(new Value(23.7, 200));
    }

    public size (): number {
        return this.data.length;
    }

    public get (index: number): Value {
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
```

### Singleton

  > Das Singleton (selten auch Einzelstück genannt) ist ein in der Softwareentwicklung eingesetztes Entwurfsmuster und gehört zur Kategorie der Erzeugungsmuster (engl. creational patterns). Es stellt sicher, dass von einer Klasse genau ein Objekt existiert.[1] Dieses Singleton ist darüber hinaus üblicherweise global verfügbar. Das Muster ist eines der von der sogenannten Viererbande (GoF) publizierten Muster. 


