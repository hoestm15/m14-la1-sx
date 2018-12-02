# Protokoll 26.11.2018

## 2. Einheit
## Thema: Erstellen eines REST-Servers
 
 Name: Markus Kobor  
 Klasse: 5AHME  
 Datum: 26.11.2018  
 Anwesend: Berger Emil, Böcksteiner Jakob, Ehmann Julian, Knappitsch Robert, Kobor Markus, Köhler Marcel <br>
 Abwesend: Bullner Jeremy <br> <br> <br>
 
 
# Visual Studio Code

![Icons](https://github.com/HTLMechatronics/m14-la1-sx/blob/kobmam14/kobmam14/vscode.png)

## Informationen zu Code
Visual Studio Code ist eine Programmierumgebung der Firma Microsoft und ist plattformübergreifend verfügbar. 
Es ist Open-Source, basiert auf dem Framework ELectron und hat Funktionen wie z.B. Syntaxvorhebung, Debugging, Autovervollständigung und Versionsverwaltung. 
Es werden Sprachen wie C++, CSS, HTML, Java, PHP, SQL, Typescript, etc. unterstützt und durch Plug-ins kann die Programmierumgebung beliebig erweitert werden.
Trotz des Namens hat Visual Studio Code nicht viel mit Visual Studio zu tun. Beide sind von der Firma Microsoft, 
werden aber von unterschiedlichen Teams entwickelt und folgen einer anderen Philosophie. Ein großer Unterschied in der Handhabung der Projekte
zwischen den VS und VS Code besteht darin, dass VS Code nicht mit Projektdateien sondern mit Quelltextdateien und Ordnern arbeitet.  
[Website von VS Code](https://code.visualstudio.com/) <br> <br>

## Express 
Express ist eine Framework für das Arbeiten mit HTTP und HTTPS und bietet eine vielzahl von nützlichen Funktionen für das Gestalten von Webanwendungen. <br> <br>

## Singelton
> Das Singleton (selten auch Einzelstück genannt) ist ein in der Softwareentwicklung eingesetztes Entwurfsmuster und gehört zur Kategorie der Erzeugungsmuster (engl. creational patterns). Es stellt sicher, dass von einer Klasse genau ein Objekt existiert. Dieses Singleton ist darüber hinaus üblicherweise global verfügbar.  <br>

Quelle: [Wikipedia/Singelton](https://de.wikipedia.org/wiki/Singleton_(Entwurfsmuster))

Das Singleton findet Verwendung, wenn: <br>
* nur ein Objekt zu einer Klasse existieren darf und ein einfacher Zugriff auf dieses Objekt benötigt wird oder
* das einzige Objekt durch Unterklassenbildung spezialisiert werden soll.

Anwendungsbeispiele sind: <br>
* ein zentrales Protokoll-Objekt, das Ausgaben in eine Datei schreibt.
* Druckaufträge, die zu einem Drucker gesendet werden, sollen nur in einen einzigen Puffer geschrieben werden.

Das Sinigelton: <br>
* erzeugt und verwaltet das einzige Objekt der Klasse
* bietet globalen Zugriff auf dieses Objekt über eine Instanzoperation (getInstance()). <br> <br>


## Arbeiten mit Code
Wenn man Code über das Desktop-Icon startet, muss im File Explorer erst das gewählte Projektverzeichnis ausgewählt werden um damit arbeiten zu können. Eine andere Möglichkeit ist es Code über das Terminal zu starten, dort kann man direkt den gewünschten Pfad dazuschreiben, so das Code diesen gleich als Projektverzeichnis nimmt.  <br> <br>

## Visual Studio Code Icons

![Icons](https://github.com/HTLMechatronics/m14-la1-sx/blob/kobmam14/kobmam14/vs.png)

1. File explorer

2. Suchleiste

3. Versionsverwaltung

4. Debugger

5. Extensions (Erweiterungen)  <br> <br>

## Anpassen der Programmierumgebung
Code ist eine sehr leichtgewichtige Programmierumgebung und benötigt einige Modifikationen um damit effizient arbeiten zu können.  <br> <br>

### .vscode
Im Ordner *.vscode* welcher sich im Projektverzeichnis befindet, gibt es eine Datei namens *setting.json*.
In dieser können diverse Einstellungen getätigt werden, z.B. das Ausblenden von Dateien und Ordnern in der IDE.
```json
{
  "files.exclude":{
        "**/code_modules/": true,
        "**/.vscode/": true,
        "**/package-lock.json/": true
        }
}
``` 
<br>

### Weitere Ordner in unserem Projektverzeichnis

**dist**: 
Im Ordner dist befinden sich alle transpilierten Programme.

**node_Modules**: 
Hier liegen alle für die Ausführung des Programms notwendigen Pakete.

**src**: 
Hier befinden sich alle programmierten Klassen. <br>

#### package.json
Die package.json-Datei ist eine Art Manifest für ein Projekt. Es kann eine Menge Dinge tun, die völlig unabhängig voneinander sind. Es ist zum Beispiel ein zentrales Konfigurationsrepository für Tools. Dort werden auch die Namen und Versionen des installierten Pakets gespeichert.

```
{
  "name": "restserver1",
  "version": "0.0.1",
  "description": "Restserver",
  "main": "main.js",
  "scripts": {
    "start": "node dist/main.js",
    "build": "./node_modules/gulp/bin/gulp.js build",
    "clean": "./node_modules/gulp/bin/gulp.js clean",
    "cleanAndBuild": "./node_modules/gulp/bin/gulp.js cleanAndBuild",
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "Markus Kobor",
  "private": true,
  "license": "MIT",
  "dependencies": {},
  "devDependencies": {
    "del": "^3.0.0",
    "gulp": "^3.9.1",
    "gulp-changed": "^3.2.0",
    "gulp-sourcemaps": "^2.6.4",
    "gulp-typescript": "^5.0.0-alpha.3",
    "gulp-using": "^0.1.1",
    "merge-stream": "^1.0.1",
    "run-sequence": "^2.2.1",
    "tslint": "^5.11.0",
    "typescript": "^3.1.1"
  }
}
```

#### tsconfig.json
Die Datei tsconfig.json ist für die Konfiguration des TypeScript-Compilers zuständig.

```
{
    "compilerOptions": {
        "module": "commonjs",
        "noImplicitAny": true,
        "removeComments": true,
        "preserveConstEnums": true,
        "sourceMap": true,
        "target": "ES2016",
        "experimentalDecorators": true,
        "noEmitOnError": true,
        "mapRoot": "./",
        "outDir": "./dist",
        "typeRoots": [ "node_modules/@types" ]
    },
    "include": [ "src/**/*.ts" ]
}
```

#### gulpfile.json
Das gulpfile ist für die Übersetzung zuständig.

```
// Node.js modules
const path = require('path');

// External modules,
// npm install --save-dev gulp gulp-changed gulp-typescript gulp-sourcemapsgulp-using 
// npm install --save-dev typescript del run-sequence merge-stream
const gulp       = require('gulp'),
      changed    = require('gulp-changed'),
      ts         = require('gulp-typescript'),
      sourcemaps = require('gulp-sourcemaps'),
      using      = require('gulp-using'),
      typescript = require('typescript'),
      del        = require('del'),
      sequence   = require('run-sequence'),
      merge      = require('merge-stream');
      ...
```

#### tslint.json
TSLint ist ein erweiterbares statisches Analysewerkzeug, das TypeScript-Code auf Lesbarkeit, Wartbarkeit und Funktionsfehler überprüft. Es wird weitgehend von modernen Editoren und Build-Systemen unterstützt und kann mit Ihren eigenen Fusselregeln, Konfigurationen und Formatierungselementen angepasst werden.

```
{
    "rulesDirectory": [],
    "rules": {
        "callable-types": true,
        "class-name": true,
        "comment-format": [
            true,
            "check-space"
        ],
        "curly": true,
        "eofline": true,
        "forin": true,
        "import-blacklist": [
            true,
            "rxjs"
        ],
        ...

```
 <br> <br>
## Programmieren des Servers

### main.ts

```
import { Server } from './server';

class Main {
    public static main () {
        new Server(4711).start();
    }
}

Main.main();

```

In der Klasse main.ts wird zuerst die Klasse server importiert. <br>
In der public static void main wird ein Server am Port 4711 gestartet nachdem sie über Main.main() aufgerufen wurde.

### server.ts

```
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
            (req, res, next) => this.handleGetData(req, res, next)
        );
        this._server.get('/dataset',
            (req, res, next) => this.handleGetDataSet(req, res, next)
        );
    }

    start () {
        this._server.listen(this._port);
        console.log('Server auf Port ' + this._port + ' gestartet.');
    }

    private handleGetData (req: express.Request,
                           res: express.Response,
                           next: express.NextFunction
    ) {
        console.log('this = ' + this);
        console.log('Server ' + this._port);
        res.json({ temp: 23.4, power: 120, unit: 'W' });
    }

    private handleGetDataSet ( req: express.Request,
                               res: express.Response,
                               next: express.NextFunction) {
        res.json(Database.getInstance().getAll());
    }
}
```

In server.ts wird das oben erwähnte Framework **express** verwendet indem es importiert wurde. <br>
Außerdem importieren wir die Klasse **database**.<br>
Hier sehen wir das erste Mal das Schlüsselwort **export**, welches immer dann verwendet werden muss, wenn eine Klasse in eine andere importiert wird.<br>
In der Klasse werden zuerst die beiden privaten Variablen *number* und *port* erstellt.<br>
Im Konstruktor der Klasse wird die Portnummer sowie die beiden Methoden **handleGetData** und **handleGetDataSet** übergeben.<br>
Diese Methoden regeln das Vorgehen des Servers bei einer Anfrage.<br>
Die Methode **start** startet den Server.

### value.ts

```
export class Value {
    time: Date;
    temp: number;
    power: number;
    powerUnit: string;
    tempUnit: string;

    constructor (tempCelsius: number, powerWatt: number) {
        this.time ;= new Date();
        this.temp = tempCelsius;
        this.tempUnit = '°C';
        this.power = powerWatt;
        this.powerUnit = 'W';
    }
}
```

In value.ts finden wir unsere Datenerhaltungsklasse.<br>
Hier werden für einen Messwert der Zeitpunkt, die Temperatur und die Leistung erhoben.

### database.ts

```
import { Value } from './value';

export class Database {

    public static getInstance(): Database {
        if (!this.Instance) {
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
}
```
