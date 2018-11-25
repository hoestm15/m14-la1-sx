# Protokoll 3: REST-Server
Name: Patrick Schuster  
Klasse: 5AHME  
Gruppe: 3    
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schuster  
Abwesend: Schmuck

# Übersetzungstools
Jede Programmiersprache benötigt ein anderes Übersetzungstool, da verschiedene Anforderungen an den Compiler gestellt werden.
#### Liste mit Übersetzungstools
Sprache | Übersetzungstool  
---|---  
Java | [javac](https://en.wikipedia.org/wiki/Javac)  
Java (Android) | [gradle](https://de.wikipedia.org/wiki/Gradle)  
C | [make](https://de.wikipedia.org/wiki/Make)  
Typescript | [Gulp](https://de.wikipedia.org/wiki/Gulp.js)  

# Config Dateien

## gulpfile.js
Die gulpfile wird zum steuern des gulp-tools verwendet. In dieser Datei werden alle nötigen Informationen die für das Übersetzen notwendig sind angegeben. Das C-Äquivalent zur gulpfile wäre die makefile.
## tslint.json
Die tslint.json Datei dient zur Konfiguration des TSLint-Tools, dieses Tool hilft dem Programmierer dabei schön zu programmieren, indem es Unschönheiten und Fehler markiert. TSLint wird über den Plugin-Manager von VS Code installiert.
```json
"max-line-length": [
            true,
            140  
```
## tsconfig.json
Die tsconfig Datei dient dazu den tsc Compiler zu steuern. Dieser Compiler, auch Transpiler gennant, übersetzt den Typescript Code in Javascript. 
```json
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
## settings.json
Die settings dient dazu die Programmierumgebung VS Code zu konfigurieren. Es kann zum Beispiel eingestellt werden das bestimmte Dateien und Verzeichnisse nicht in Code angezeigt werden. Diese Datei befindet sich im .vscode Ordner.
```json
{
        "files.exclude": {
                "**/node_modules": true,
                "**/.vscode": true,
                "**/package-lock.json": true,
                "**/gulpfile.js" : true,
                "**tslint.json": true,
                "**/dist": true,
                "**/tsconfig.json": true
        }
}
```
## tasks.json
In dieser Datei wird die Programmierumgebung mit dem gulp-tool verknüpft.
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "command": "gulp",
            "type": "shell",
            "args": [
                "--gulpfile",
                "gulpfile.js",
                "build"
            ],
            "group": "build",
```
## launch.json
Diese Datei konfiguriert was bei der Anwendung des Debuggers passieren soll.
```json
{
    "version": "0.2.0",
    "configurations": [

        {
            "type": "node",
            "request": "launch",
            "name": "Launch Program",
            "program": "${workspaceRoot}/src/main.ts",
            "cwd": "${workspaceRoot}/dist",
            "console": "integratedTerminal",
            "outFiles": [ "${workspaceRoot}/dist/*.js" ],
            //"trace": "all",
            "sourceMaps": true,
            "preLaunchTask": "build",
            "smartStep": true
        }
    ]
}  
```
## keybindings.json
In dieser Datei können Tastenkützel zu bestimmten Vorgängen zugewiesen werden.
```json
 [
    {
        "key": "ctrl+alt+v",
        "command": "workbench.action.tasks.runTask",
        "args": "cleanAndBuild"
    },{
        "key": "ctrl+alt+b",
        "command": "workbench.action.tasks.runTask",
        "args": "build"
    },
    {
        "key": "ctrl+alt+c",
        "command": "workbench.action.tasks.runTask",
        "args": "clean"
    }
]
```
# REST-Server
In dieser Einheit wurde der Server soweit erweitert, dass der Server bereits auf verschiedene Anfragen reagieren kann und auf diese sinnvoll antwortet. In unserem Beispiel kann mit der HTL-ID der Name des Schülers angefragt werden.
## Anwendung
Um den REST-Server zu verwenden muss er zuerst gestartet werden. Danach kann mit der url http://localhost:8080/student?htlid=suspam14 die Handlermethode für die Ausgabe eines Schülers aufgerufen werden, welche eine Antwort mit den Daten des Schülers an den Browser schickt. Die Antort würde `{htlid: 'suspam14', surname: 'Schuster', firstname: 'Patrick'}` lauten.
## Funktionsweise
Nach dem starten des Servers warten dieser auf eine Anfrage. Sobald eine Anfrage kommt wird im Konstruktur die passende Handlermethode aufgerufen. Wenn z.B. eine Anfrage mit `/status` kommt wird mit dieser Zeile Quellcode die Handlermethode aufgerufen `this.server.get('/status', (req, resp) => this.handleGetStatus(req, resp));`. Die Parameter *req* und *resp* werden durch den Arrow Operator an die *handleGetStatus* Methode weitergegeben.
Wenn eine Anfrage mit `/student` kommt wird die *handleGetStudent* Methode aufgerufen. Wenn eine Anfrage, die keiner Handler Methode zugewiesen werden kann, kommt wird die Methode *HandleGet* aufgerufen die anschließend eine Fehlermeldung zurückgibt.
## Quelltext
```typescript
import * as express from 'express';
import * as bodyParser from 'body-parser';

class Main {

    private port: number;
    private server: express.Express;

    constructor(port: number) {
        this.port = port;
        this.server = express();
        this.server.use(bodyParser.urlencoded({extended: false}));
        this.server.get('/status', (req, resp) => this.handleGetStatus(req, resp));
        this.server.get('/student', (req, resp) => this.handleGetStudent(req, resp));
        this.server.get('*', (req, resp) => this.handleGet(req, resp));
        this.server.listen(this.port);
    }

    private handleGet(req: express.Request, resp: express.Response) {
        resp.status(400);
        resp.send('Error');
        resp.end();
    }

    private handleGetStatus(req: express.Request, resp: express.Response) {
        resp.send('Server is running');
        resp.end();
    }

    private handleGetStudent(req: express.Request, resp: express.Response) {
        switch (req.query.htlid) {
            case 'suspam14':
                resp.json({htlid: 'suspam14', surname: 'Schuster', firstname: 'Patrick'});
                break;
            case 'reibem14':
                resp.json({htlid: 'reibem14', surname: 'Reinbacher', firstname: 'Bernhard'});
                break;
            default:
                resp.status(400);
                resp.send(req.query.htlid + ' not found');
                break;

        }
        resp.end();
    }
}

const main = new Main(8080);  
```
