# 2.Protokoll  
**Name:** Ehmann Julian   
**Datum:** 26.11.2018  
**Uhrzeit:** 8:00-10:30  
**Gruppe:** 1  
**Anwesend**: Berger Emil, Böcksteiner Jakob, Ehmann Julian, Knappitsch Robert, Kobor Markus, Köhler Marcel  
**Abwesend**: Bullner Jeremy  


# Dateien im Projektordner  
Am Beginn der Einheit besprachen wir alle einzelnen Dateien in unserem Projektordner.
Im Projektordner befinden sich weitere 4 Ordner. Die Ordner lauten:  

  
* dist   
Hier befinden sich alle die transpilierten Programmen. Das heißt die von TypeScript umgewandet wurden in           JavaScript. 

* node_Modules   
Hier befinden sich alle Packete, welche das Programm für die Ausführung benötigt. 

* src   
Hier befinden sich alle TypeScript Dateien. 

* .vscode  
In diesem Ordner findet man alle Dateien die nicht angezeigt werden. Deswegen beginnt der Dateiname mit                  einem Punkt.  


### .vscode
Im Ordner **.vscode** gibt es noch 4 Dateien die sogenannten **Steuerdateien** für Visual Studio Code.
* keybindings.json:  
In dieser Datei können Tastenkombinationen für Aktivitäten (z:B. Build) im Programm erstellt werden.  
* launch.json:  
Die Datei **launch.json** legt fest wie ein Program gestartet werden soll.  
* settings.json  
In dieser Datei stehen alle Dateien die Bei VSCode nicht im Dateiexplorer angezeigt werden sollen. Bei unserem Program ist es zum Beispiel:  
```
{
	"files.exclude": {
		"**/node_modules": true,
		"**/.vscode/": true,
		"**/package-lock.json": true
		"**/dist/": true 
	}
}
```  
* tasks.json  


### package.json
Eine weitere wichtige Datei ist die **package.json** Datei. In dieser Dtei stehen alle Projektinformationen und deren Abhängigkeiten.  


Mit dem Shel-Kommando **npm install** schaut der Node Package Manager in diese **package.json** und installiert danach alle Pakete die er für die Ausführung des Programs benötigt. Die benötigten Pakete stehen bei **devDependencies**.  

### gulpfile.js  
Die Datei **gulpfile.js** steuert die Übersetzung mit dem Übersetzungstool **gulp**  
Dabei gibt es 2 Möglichkeiten um **gulp** zu installieren.  
* Lokale Installation: node_modules/gulp/bin/gulp.js  
* Globale Installation: sudo npm install -g gulp  
Das **-g** nach npm install steht für eine **globale INstallation**.  
Damit man **gulp** updaten kann benötigt man statt dem Schlüsselwort **install** das SChlüsselwort **update**. Der Berfehl lautet daher danach **sudo npm update -g gulp**.  

### tsconfig.json  
In der Datei **tsconfig.json** befindet sich die Konfiguration für den Transpieler. Der Transpieler transpeliert eine TypeScript Datei in eine JavaScript Datei.  
In unseren Beispiel sieht diese Datei folgendermaßen aus:  
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

### tslint  
Tslint is ein Tool, welches während des codieren auf die Schönheit des programmierten Codes achtet. Damit Tslint funktioniert benötigt es die Datei **tslint.json**.  


# Visual Studio Code   
### Allgemeines  
Der Quelltexteditor Visual Studio Code von Microsoft ist **plattformunabhängig** auf Windows, Linux und MacOS erhältlich. Es werden viele Programmiersprachen wie C#, C++, CoffeeScript, F#, HTML, Ini, Java, JavaScript, Makefile, Markdown, Objective-C, Python, R, Ruby, SQL, Swift, TypeScript, Visual Basic und XML unterstützt. Visual Studio Code kann mit dem Konsolenbefehl code gestartet werden. Optional kann das Programm mit code . im Projektordner geöffnet werden, wobei man sich dann gleich im jeweiligen Projekt befindet.  


### Schnellstartleiste  
Auf der unten ersichtlichen Abbildung ist die **Schnellstartleiste** von Visual Studio Code abgebildet. An oberster Stelle findet man den **Dateiexplorer**. Es folgen die **Suchfunktion**, die **Versionsverwaltung** ,der **Menüpunkt für Debugging** und der **Menüpunkt für externe Plug-ins**. Werden Datein nur mit einem einfachen Klick geöffnet, verschwinden sie beim Öffnen der nächsten Datei wieder. Das kann beim Suchen nach Codestellen hilfreich sein. Um Datein dauerhauft zu öffnen, ist ein Doppelklick notwendig.  


Damit man im **Dateiexplorer** die unwichtigen Dateien nicht sieht kann wie schon weiter oben aufgelistet im Ordner **.vscode** eine Datei mit dem Namen **settings.json** erstellen und alle Dateien oder Order die man nicht sehen will hinein schreiben. Die werden dann für den Benutzer "unsichtbar" gemacht.  


# Programmieren des Rest-Servers  
Für die Programmierung unseres Rest-Servers erstellten wir 4 Klassen. Die erste war **main.ts** und die zweiter war **server.ts** und die beiden letzten Datenhaltungsklassen hießen **value.ts** und **database.ts**.  
Für einen Web-Server bekommt man von Node.js 2 Module mitgeliefert. Das **http** und das **https** Modul. Diese beiden Module sind nicht einfach zu bedienen und benötigen Einarbeitungszeit. Deswegen verwenden wir im Unterricht ein externes Modul mit dem Namen **Express**. Dieses Modul baut auf das "http" udn "https" Modul auf und ermöglicht komfortables Arbeiten.  

### Server Klasse  
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
        this._server.get('/data', (req, res, next) => this.handleGetData(req, res, next));
        this._server.get('/dataset', (req, res, next) => this.handleGetDataSet(req, res, next));
    }

public start () {
        this._server.listen(this._port);
        console.log('Server auf Port ' + this._port + ' gestartet.');
    }

    private handleGetData (req: express.Request, res: express.Response, next: express.NextFunction) {
        console.log('Server ' + this._port);
        res.json({ temp: 23.4, power: 120, unit: 'W'});
        next();
    }

    private handleGetDataSet (req: express.Request, res: express.Response, next: express.NextFunction) {
        res.json(Database.getInstance().getAll());
    }
}
```  
Im ersten Schritt wird 1 Paket und 1 Klasse eingebunden. Das Paket **Express** und die Klasse **Database**.  
Wir erstellten auch eine Methode für einen GET request von einem Client. Diese Methode heißt **handleGetData**. Diese erste Methode haben wir nur für Testzwecke geschrieben, da wir hier dierekt fixe Parameter beim Aufruf übergeben.  
Die bessere Variante kam etwas später, als wir festlegten, dass wir ein Programm schreiben welches Messwerte für uns speichert. Dafür erstellten wir 2 Datenerhaltungsklassen welche wie folgt heißen: **value.ts** und **database.ts**.  

**value.ts** speichter einen einzelnen Messwert wie folgt ab:  
```

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
Diese Klasse gibt vor, wie die Messwerte abgespeichert werden und was darin alles enthalten ist.  




**database.ts** speichert die gesamten Messwerte, mit allen Parametern, die wir in value festgelegt haben ab.
```

import { Value } from './value';

export class Database {


    public static getInstance(): Database {
        if (!this.instance) {
            this.instance = new Database();
        }
        return this.instance;
    }
        private static instance: Database;

        private data: Value [] = [];

        private constructor () {
            this.add(new Value(23.9, 200));
            this.add(new Value(23.5, 100));
            this.add(new Value(23.0, 120));
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
Diese Klasse binden wir wie oben zu sehen ist in unsere Server Klasse ein und können somit immer wieder neue Messwerte hinzufügen.
