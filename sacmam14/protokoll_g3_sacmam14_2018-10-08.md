# 3. Protokoll  
**Name:** Sackl Martin  
**Klasse** 5ahme  
**Gruppe:** 3  

Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schuster   
Abwesend: Schmuck  
*******************************************************************************************************************************************  
# Übersetzungstools  
Um den Rest-Server programmieren zu können benötigt man ein Übersetzungstool. Es gibt verschiedene Tools da jede Programmiersprache andere Anforderungen an den Compiler sendet.  

Übersetzungstool | Sprache  
-----------------|-----------  
[javac](https://en.wikipedia.org/wiki/Javac) | Java  
[gradle](https://en.wikipedia.org/wiki/Gradle) | Java (Android)  
[gulp](https://de.wikipedia.org/wiki/Gulp.js) | Typescript  
[make](https://de.wikipedia.org/wiki/Make) | C  

# Dateien zum Konfigurieren  
### settings.json  
Mit dieser Datei kann die Prgrammierumgebung VS Code konfiguriert werden. Man kann bestimmte Verzeichnisse und Dateien ausblenden.  
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
### tslint.json  
Mit dieser Datei kann man das TSLint-Tool konfigurieren. Dieses Tool hilft dabei Fehler  und "Unschönheiten" zu markieren. Man kann z.B. auch die maximale Zeilenlänge festlegen.  
```json
"max-line-length": [
            true,
            140  
```  
### tsconfig.json  
Hier man kann man Einstellungen bezüglich des Übersetzungsvorgang des tsc-Compilers verändern. Der Compiler übersetzt Typescript in Javasript.  
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
### gulpfile.js
Mit dieser Datei kann man das gulp-Tool steuern. In dieser sind alle Informationen über den Übersetzungsvorgang gespeichert.  

### launch.json  
Mit dieser Datei kann man den Debugger konfigurieren.  
```
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
            // "trace": "all",
            "sourceMaps": true,
            "preLaunchTask": "build",
            "smartStep": true
        }
    ]
}  
```  
### tasks.json  
Hier wird das gulp-Tool mit der Programmierumgebung verknüpft.  
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
### keybindings.json  
In dieser Datei kann man Tastenkürzel für bestimmte Vorgänge definieren.  
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
Der Server wurde soweit fertiggestellt, dass auf Anfragen reagieren kann, hier kann der Schüler mit der HTL-ID angefragt werden.  
### Anwendung  
Wenn der Server gestartet wird kann mit der URL http://localhost:8080/student?htlid=sacmam14 die Handlermethode aufgerufen werden. Die Methode schickt eine Antwort und lautet `{htlid: 'sacmam14', surname: 'Sackl', firstname: 'Martin'}`  
### Funktionsweise  
Sobald der Server gestartet wird, wartet er auf eine Anfrage. Wenn eine Anfrage gesendet wird, wird im Konstroktor die richtige Handlermethode aufgerufen. Zum Beispiel es wird eine Anfrage mit `/status` gesendet, dann wir die Handlermethode `this.server.get('/status', (req, resp) => this.handleGetStatus(req, resp));` aufgerufen.  Durch den Arrow Operator werden die Parameter **req** und **rep** an die `handleGetStatus` Methode weitergeben. Wenn eine Anfrage mit `/student` kommt wird die `handleGetStudent` Methode aufgerufen. `HandleGet` wird dann aufgerufen wenn eine Anfrage kommt, die keiner Handler-Methode zugewiesen werden kann, und gibt eine Fehlermeldung zurück.  
### Quelltext  
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
                resp.json({htlid: 'sacmam14', surname: 'Sackl', firstname: 'Martin'});
                break;
            case 'reibem14':
                resp.json({htlid: 'sacrom14', surname: 'Sackl', firstname: 'Roland'});
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
