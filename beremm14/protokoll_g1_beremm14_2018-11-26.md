# Protokoll
  Berger Emil  
  5AHME, Gruppe 1  
  19.11.18  
  Anwesend: Berger, Böcksteiner, Ehmann, Enzi, Kobor, Köhler, Knappitsch  
  Abwesend: Bullner  

# Visual Studio Code
  Visual Studio Code ist eine **plattformunabhängige** (Linux, macOS, Windows) Programmierumgebung von Microsoft, die für die Programmierung von TypeScript entwickelt wurde. TypeScript ist eine "angenehmere" Form von JavaScript - der Hauptunterschied legt darin, dass TypeScript jeder Variable einen Datentyp zuweist.  
  Ein TypeScript Quelltext muss vor der Ausführung in einen JavaScript Code "transpiliert" werden. Dafür muss Visual Studio Code erst eingerichtet werden, genauere Informationen zu diesem Vorgang gibt es in diesem [FIVU Protokoll](https://github.com/HTLMechatronics/m14-5ahme-fivu/blob/beremm14/Protokoll_2018-10-05_beremm14.md).  
  
## Einrichten von Visual Studio Code
  Es folgt ein Auszug aus meinem [FIVU Protokoll](https://github.com/HTLMechatronics/m14-5ahme-fivu/blob/beremm14/Protokoll_2018-10-05_beremm14.md):  
  
### [tsconfig.json](https://www.typescriptlang.org/docs/handbook/tsconfig-json.html)
Zuerst ist im Hauptverzeichnis des Projektes eine tsconfig.json-File zu erstellen. Darin sind Optionen festgelegt, die der Compiler benötigt um ein projekt zu transpilieren.
Beispielsweise kann man mit `"outDir": "./dist"` festlegen, dass Output-Dateien wie bei Netbeans im dist-Ordner zu finden sind, oder dass Input-Files für den Kompiler im Ordner src liegen.
  Transpilieren der .ts-Dateien über die tsconfig.json wird mit dem Command `tsc -p tsconfig.json`  
  *Vorischt: `tsc` funktioniert nur, wenn man es global installiert: `sudo npm install -g typescript`, ansonsten muss man vor dem tsc-Command noch den Verzeichnis-Pfad angeben.*

### settings.json
Im Ordner .vscode erstellt man eine settings.json-Datei, inder man einträgt, welche Dateien man nicht in Visual Studio sehen möchte.
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
Lint wird verwendet, damit wir freundlich dazu genötigt werden "schönen Code" zu produzieren. Die Datei tslint.json liegt im Hauptverzeichnis und man kann in ihr festlegen, welche "Fehler" gemeldet werden. (Zum Beispiel unnötige Leerzeichen oder fehlende Semicolons). Ohne diese Datei wird uns derartiges nicht angezeigt. Zusätzlich benötigen wir noch ein Plug-In, dazu aber unten mehr. Dazu muss auch das PlugIn in Code installiert werden.

### [Tasks](https://code.visualstudio.com/docs/editor/tasks)
Mit Hilfe von Tasks werden die einzelnen Schritte des transpilierens für die IDE automatisiert. Um dies zu realisieren gibt es so genannte Tasks - JavaScript-Files, die ausgeführt werden und in denen definiert ist, was zu tun ist, wenn wir in Visual Studio Code ein Projekt builden, cleanen, etc.
Wir verwenden **gulp**:
```js
gulp.task('build', function (done) {
    console.log("Task build gestartet");
    sequence('transpile', 'copyFiles', () => {
        console.log(finalMessage);
    });
});
```
Oben ist zu sehen der Gulp-Task `build`, der über ⇧⌘B oder in dem man in der Commandozeile "build" schreibt, aufgerufen werden kann.
  
## Arbeiten mit Visual Studio Code
  Um ein Projekt zu öffnen, muss man im Terminal mit dem `cd`-Command in das Projektverzeichnis gehen und den Command `code` ausführen. Danach öffnet sich Visual Studio Code mit diesem Verzeichnis als Workspace. Alternativ kann man Visual Studio Code öffnen und mit *⌘O* das gewünschte Verzeichnis im Finder-Dialogfenster auswählen.  
  
  Auf der linken Seite befindet sich die Projektnavigation. Unsere `*.ts`-Quelldateien befinden sich im Ordner *src*, die transpilierten `*.js`-Dateien im Ordner *dist*.  
  
### Projektnavigation

Ordner | Inhalt
------ | ------
assets | HTML-Files, Bilder, Files, etc.
dist | Transpilierter Quelltext in JavaScript von unseren TypeScript-Dateien
node_modules | Pakete für die Ausführung der `*.js`-Dateien
src | TypeScript-Quelltext
views | zB pug-Dateien
.vscode | Steuerdateien für Visual Studio Code

### Navigation in Visual Studio Code
Auf der linken Seite der IDE befindet sich eine Symbolleiste. In der folgenden Tabelle werden die Funktionen aufgelistet (das meiste ist selbsterklärend):

Menüpunkt | Funktion | Tastaturkürzel
--------- | -------- | --------------
Explorer | File-Explorer für den Überblick im Projekt | ⇧⌘E
Search | Suchen innerhalb des Projektes | ⇧⌘F
Source Control | Versionsverwaltung | ⌃⇧G
Debug | Debugger | ⇧⌘D
Extension | Extensions-Store zum Installieren von PlugIns für Code | ⇧⌘X

### Features von Visual Studio Code
Visual Studio Code beinhaltet zahlreiche Funktionen, die dem Programmierer das Leben erleichtern sollen. Um nur ein Beispiel zu nennen, ensteht mit Hilfe der ⌥-Taste (alt) und durch erneutes Klicken in den Quelltext ein zweiter (zB vertikaler) Cursor.

# Projekt: Rest-Server

## main.ts
```typescript
import {Server} from './server';

class Main {

    public static main () {
        new Server(4711).start();
    }
}

Main.main();
```
In `main.ts` wird wird die Klasse `Server` importiert. In der main-Methode wird ein Server am Port 4711 gestartet. Da JavaScript von "oben nach unten" wie C durchläuft muss nur am Ende die Methode `Main.main();` aufgerufen werden.

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
  In `server.ts` wird das Modul `express` importiert, ein npm-Modul, das das Arbeiten mit http und https ermöglicht. Weiters wird die Klasse `Database` importiert.  
  Da die Klasse `Server` in `Main` importiert wird, muss vor der Klasse das Schlüsselwort `export` geschrieben werden.  
  Um den Server aufzubauen braucht man zwei Variablen: `_port: number` und `_server: express.Express` *(Vorsicht beim Datentyp: "Express" alleine reicht nicht!)*.  
  Im Konstruktor wird die Portnummer und die Handler-Methoden für `localhost:4711/data` und `localhost:4711/dataset` übergeben.  
  Mit der Methode `start();` wird der Server gestartet.  
  In den Handler-Methoden wird definiert, wie der Server darauf reagieren soll, wenn eine Anfrage eintrifft.  

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
value.ts ist unsere Datenerhaltungsklasse für einen Messwert. Auffällig ist, dass sie sich sehr unterscheidet von Datenerhaltungsklassen in Java (keine Getter, variablen public).

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
### [Singleton](https://de.wikipedia.org/wiki/Singleton_(Entwurfsmuster))
  > Das Singleton (selten auch Einzelstück genannt) ist ein in der Softwareentwicklung eingesetztes Entwurfsmuster und gehört zur Kategorie der Erzeugungsmuster (engl. creational patterns). Es stellt sicher, dass von einer Klasse genau ein Objekt existiert.[1] Dieses Singleton ist darüber hinaus üblicherweise global verfügbar. Das Muster ist eines der von der sogenannten Viererbande (GoF) publizierten Muster.  
  
  Da eine Datenbank genau einmal existiert und nur Werte hinzugefügt/gelöscht/geändert werden, ist es sinnvoll, das Entwurfsmuster *Singleton* zu verwenden. Dies wird erreicht in dem der **Konstruktor private** ist und eine statische Methode **getInstance();** aufgerufen wird, die beim ersten Aufruf das Objekt erzeugt und in der statischen Objektvariable `instance: Database;` ablegt. Wenn das Objekt einmal angelegt worden ist, wird nur mehr auf die Variable zugegriffen und es wird kein neues Objekt mehr erzeugt.
