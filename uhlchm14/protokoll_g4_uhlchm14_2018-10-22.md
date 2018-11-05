# 2.Protokoll
**Name:** Uhl Christian

**Datum:** 13.10.2018

**Gruppe:** 4

**Anwesend**: Strauß Lukas, Strutz Sebastian, Tuttner Raphael, Uhl Christan, Wieser Markus, Zitz Karlheinz

**Abwesend**: Waltl Kilian  

## Visual Studio Code

### Allgemeines  
Der Quelltexteditor Visual Studio Code von Microsoft ist **plattformunabhängig** auf Windows, Linux und MacOS erhältlich. Es werden viele Programmiersprachen wie C#, C++, CoffeeScript, F#, HTML, Ini, Java, JavaScript, Makefile, Markdown, Objective-C, Python, R, Ruby, SQL, Swift, TypeScript, Visual Basic und XML unterstützt. Visual Studio Code kann mit dem Konsolenbefehl code gestartet werden. Optional kann das Programm mit code . im Projektordner geöffnet werden, wobei man sich dann gleich im jeweiligen Projekt befindet.  

### Schnellstartleiste  
Auf der Abbildung, die unten links ersichtlich ist, ist die **Schnellstartleiste** von Visual Studio Code abgebildet. Das erste Icon ist der **Dateiexplorer**. Es folgen die Icons für die **Suchfunktion**, die **Versionsverwaltung** ,der **Menüpunkt für Debugging** und der **Menüpunkt für externe Plug-ins**. Werden Datein nur mit einem einfachen Klick geöffnet, verschwinden sie beim Öffnen der nächsten Datei wieder. Das kann beim Suchen nach Codestellen hilfreich sein. Um Datein dauerhauft zu öffnen, ist ein Doppelklick notwendig.  

![Schnellestartleiste](https://github.com/HTLMechatronics/m14-la1-sx/blob/uhlchm14/uhlchm14/schnellstartleiste1.jpg)  

Damit man im **Dateiexplorer** nur die wichtigsten Dateien sieht, kann man wie schon weiter oben aufgelistet im Ordner **.vscode** eine Datei mit dem Namen **settings.json** erstellen und alle Dateien oder Order die man ausblenden will hinein schreiben. Die werden dann für den Benutzer "unsichtbar" gemacht.  

## Dateien im Projektordner  
Es gibt viele Dateien in unserem Projektordner und jede ist für einen Zweck bestimmt und in diesem Kapitel versuche ich die wichtigsten aufzuschlüsseln.
Im Projektordner befinden sich weitere 4 Ordner.  
  
* dist   
Hier befinden sich alle die transpilierten Programmen. Das heißt die von TypeScript in JavaScript umgewandelt wurden. 

* node_Modules   
Hier befinden sich alle Packete, welche das Programm für die Ausführung benötigt. 

* src   
Hier befinden sich unsere Quelltextdateien d.h. alle TypeScript Dateien. 

* .vscode  
In diesem Ordner findet man alle Dateien die nicht angezeigt werden. Deswegen beginnt der Dateiname mit einem Punkt.  

### .vscode
Im Ordner **.vscode** gibt es noch 4 Dateien die sogenannten **Steuerdateien** für Visual Studio Code.
* keybindings.json:  
In dieser Datei können Tastenkombinationen für Aktivitäten (z:B. Build) im Programm erstellt werden.  
* launch.json:  
Die Datei **launch.json** legt fest wie ein Program gestartet werden soll.  
* settings.json  
In dieser Datei stehen alle Dateien die Bei VSCode nicht im Dateiexplorer angezeigt werden sollen. Bei unserem Programm haben wir .vscode, node_modules und den dist Ordner ausgeblendet.
* tasks.json

### package.json
Eine weitere wichtige Datei ist die **package.json** Datei. In dieser Dtei stehen alle Projektinformationen und deren Abhängigkeiten. Wie zum Beispiel:  
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
  "author": "Karlheinz Zitz",
  "private": true,
  "license": "MIT",
  "dependencies": {
    "body-parser": "^1.18.3",
    "express": "^4.16.3"
  },
  "devDependencies": {
    "@types/body-parser": "^1.17.0",
    "@types/express": "^4.16.0",
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
Mit dem Shell-Kommando **npm install** schaut der Node Package Manager in diese **package.json** und installiert danach alle Pakete die er für die Ausführung des Programs benötigt. Die benötigten Pakete stehen bei **devDependencies**.  

### gulpfile.js  
Die Datei **gulpfile.js** steuert die Übersetzung mit dem Übersetzungstool **gulp**  
Dabei gibt es 2 Möglichkeiten um **gulp** zu installieren.  
* Lokale Installation: node_modules/gulp/bin/gulp.js  
* Globale Installation: sudo npm install -g gulp  
Das **-g** nach npm install steht für eine **globale Installation**.  
Damit man **gulp** updaten kann benötigt man statt dem Schlüsselwort **install** das Schlüsselwort **update**. Der Berfehl lautet daher danach **sudo npm update -g gulp**.  

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


## Programmieren des Rest-Servers  
Für die Programmierung unseres Rest-Servers erstellten wir 2 Klassen. **main.ts** und **server.ts**.  
Für einen Web-Server bekommt man von Node.js. Mit dem HTT - Protokoll ist es schwierig zu arbeiten, deswegen verwenden wir im Unterricht ein externes Modul mit dem Namen **Express**. Dieses Modul baut auf das "http" und "https" Modul auf und ermöglicht komfortables Arbeiten.  

### Server Klasse  
```  
import * as express from 'express';
import * as bodyParser from 'body-parser';
export class  Server {
   private _server: express.Express;
    constructor ( port: number) {
        this._server = express();
        this._server.use(bodyParser.urlencoded({extended: false}));
        this._server.get('/student', (req, resp, next) 
        this._server.listen(port);
        console.log('HTTP server gestartet auf Port ' + port);
    }
    private handleGetStudent (req: express.Request,
                              resp: express.Response,
                              next: express.NextFunction) {
        console.log('Abfrage');
        console.log(req.query.htlid);
        switch (req.query.htlid) {
            case 'tutram12':
            resp.json({surname: 'Tuttner', firstname: 'Raphael'}); break;
            case 'zitkam13':
            resp.json({surname: 'Zitz', firstname: 'Karlheinz'}); break;
            case 'strlum14':
            resp.json({surname: 'Strauß', firstname: 'Lukas'}); break;

            default:
                resp.status(404);
                resp.end();

        }
        resp.send('Antwort' + req.query.htlid);
    }
}
```  
Im ersten Schritt werden 2 Pakete eingebunden. Das Paket **Express** und das Paket **Body-Parser**.  
Wir erstellten auch eine Methode für einen GET request von einem Client. Diese Methode heißt **handleGetStudent**.  
