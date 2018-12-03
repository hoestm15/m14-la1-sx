# Protokoll: Marcel Köhler
## 2.Einheit
## Thema: REST Server
Klasse: 5AHME  
Anwesend: Berger, Böcksteiner, Ehmann, Kobor, Knappitsch, Köhler  
Abwesend: Bullner


## Visual Studio Code
Visual Studio Code ist eine plattformunabhängige IDE welche von Microsoft entwickelt wird. Diese IDE unterstützt verschiedene Programmiersprachen. Man kann diese IDE mit dem Konsolenbefehl `code` starten aber auch mit dem Befehl `code .` wobei man hier die IDE im Verzeichniss öffnet in dem mann sich gerade befindet, so kann mann direkt im Projekt starten.


### Navigation in Visual Studio Code
Auf der Linken Seite des programms befindet sich die Schnellstartleiste. In dieser findet mann in folgender Reihenfolge aufgezählte Menüeinträge: **Dateiexplorer, Suchfunktion, Versionsverwaltung, Debugging und den Plugin-Manager** .  
Um unwichtige Dateien nicht anzeigen zu lassen kann man im Order .vscode in der Datei `settings.json` alle Dateien hinzufügen die in der IDE bei der Dateiauswahl nicht sichtbar sein sollen.

### Konfiguration Visual Studio Code

#### settings.json
Diese Datei befindet sich im `.vscode` Ordner. In dieser Datei kann mann Dateien hinzufügen welche nicht im Dateiexplorer angezeigt werden sollen.
```
{
	"files.exclude": {
	    "**/node_modules": true,
	    "**/dist": true,
	    "package-lock.json": true,
	    ".vscode": true
	}
}
```
### tsconfig.json
Diese Datei wird zum compilieren beötigt. In ihr stehen wichtige compilier Optionen. Mann kann unter anderem auch festlegen, dass das compilierte Projekt in den `/dist` ordner abgelegt wird oder das Input-Files für den Compiler im Ordner `/src` liegen.
Zum transpilieren der .ts mithilfe der tsconfig.json muss mann in der Konsole den folgenden Befehl eingeben:  
`tsc -p tsconfig.json`  *Dies funktionier nur dann wenn tsc global installier wurde. Um dies Global zu instalieren muss man den folgenden Befehl eingeben `sudo npm install -g typescript`.*

### Lint
Lint wird dazu verwendet um auf die Formatierung des Codes zu achten. Es weißt einen darauf hin das man zu viele Zeichen in einer Zeile benutzt hat oder anderes. Um dies zu verwenden muss man ein PlugIn installieren. Wir verwenden **gulb**

### Tasks
Tasks sind dazu da um die einzelnen Schritte des transpilierens zu automatisieren. In diesen ist definiert was zu tun ist, wenn wir in Visual Studio Code ein Projekt Compilieren oder nur einen build erstellen.

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
In `main.ts` wird wird die Klasse `Server` importiert. In der main-Methode wird ein Server am Port 4711 gestartet. Da bei JavaScript nicht automatisch die main Methode aufgerufen wird muss mann am Ende noch die Methode `Main.main();` aufrufen um den Server zu starten.


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
value.ts ist unsere Datenunterhaltungsklasse welche sich von Java unterscheidet, da sie keine getter oder setter bestitzt.

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

    // Neues Feld mit dem Inhalt des alten Feldes
    public getAll (): Value [] {
        return [].concat(this.data);
    }


}
```
Hier legen wir unsere Datenbank an in welcher alle Daten gespeichert werden sollen. In dieser finden sich Methoden die verschiedene Werte oder auch einen ganzen Datensatz als Rückgabewert haben.  
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
  In `server.ts` das Modul für vereinfachte HTTP server `express` und unsere Datenbank `database` importiert.
  Um einen Server aufzubauen benötigt mann zwei Variablen: `_port: number` und `_server: express.Express`.
  Im Konstruktor wird die Portnummer und die Handler-Methoden für `localhost:4711/data` und `localhost:4711/dataset` übergeben.  
  Mit der Methode `start();` wird der Server gestartet.   

### [Singleton](https://de.wikipedia.org/wiki/Singleton_(Entwurfsmuster))
  > Das Singleton (selten auch Einzelstück genannt) ist ein in der Softwareentwicklung eingesetztes Entwurfsmuster und gehört zur Kategorie der Erzeugungsmuster (engl. creational patterns). Es stellt sicher, dass von einer Klasse genau ein Objekt existiert.[1] Dieses Singleton ist darüber hinaus üblicherweise global verfügbar. Das Muster ist eines der von der sogenannten Viererbande (GoF) publizierten Muster.  
