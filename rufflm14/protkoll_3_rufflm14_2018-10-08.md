# 3. Laborprotokoll 

*von Florian Ruffenacht*

Datum: 08.10.2018 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

## Verwendete Tools zur Programmierung in TypeScript
Um den Rest-Server in Typescript angenehm progrmmieren zu können, wurden die folgenden Tools verwendet bzw. Dateien erstellt:

### TSLint-tool
Dieses Plug-in unterstützt den Programmierer bei der übersichtlichen und optisch anprechenden Gestaltung seines Codes. In der Datei 
**tslint.json** können Einstellungen am tool, wie zum Beispiel die maximal an Zeichen in einer Zeile, vorganommen werden:
```json
"max-line-length": [
            true,
            140  
```
[TSLint-Tool](https://www.npmjs.com/package/tslint)
### gulp-tool
Während es in den Programmieresprachen C, Java und Java mit für Android mit [make](https://de.wikipedia.org/wiki/Make), [javac](https://docs.oracle.com/javase/7/docs/technotes/tools/windows/javac.html) und [gradel](https://gradle.org/) sehr weit verbreitete Übersetzungstools gibt, stehen einem Javascript-Programmierer mehrere tools wie zum Beispiel [grunt](https://gruntjs.com/) oder eben [gulp](https://gulpjs.com/) zur Verfügung. Wir verwenden gulp, welches sich über die Datei **gulpfile.js** steuern lässt.

### tsconfig.json
Hier lassen sich Einstellungen beim Übersetzungsvorgang mit dem **tsc**, auf dem auch das gulp-tool aufbaut, verändern. Die Datei sieht folgendermaßen aus:
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

### settings.json
Diese Datei im **.vscode**-Ordner kann dazu verwendet werden, gewisse Dateien in Visual Studio Code auszublenden:

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
### task.json
Hier werden die Taks im Quelltextmanager mit denen des gulp-tools verknüpft. Diese Datei befindet sich ebenfalls im **.vscode**-Ordner.

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
### launch.json
Die Datei launch.json definiert die Einstellungen beim Debuggen und ist ebenfalls im **.vscode**-Ordner zu finden.

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
            //"trace": "all",
            "sourceMaps": true,
            "preLaunchTask": "build",
            "smartStep": true
        }
    ]
}  
```
### keybindings.json
In dieser Datei lassen sich Tastenkombinationen für das schnelle Aufrufen von Tasks in Code definieren:
 ```
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
## Rest-Server
Gegenüber der letzten Einheit wurde der Server so verändert, dass bereits eine sinnvolle Antwort auf unterschiedliche Anfragen gesendet wird. In unserem Fall werden, abhängig von der URL der Anfrage, Informationen zum jeweiligen Schüler zurückgesendet. 

Nach dem Starten des Servers wird der body parser angewendet. Die Zeile ```typescript this.server.get('/status', (req, resp) => this.handleGetStatus(req, resp));``` bewirkt das Aufrufen der Handlermethode **handleGetStatus**, die das Laufen des Servers bestätigt. Nach dem gleichen Prinzip wird die Handlermethode **handleGetStudent** aufgerufen, in welcher eine switch/case-Verzweigung zwischen den unterschiedlichen Anfragen unterscheidet. Wird weder ```/student``` noch ```/status``` in der URL angegeben, wird die Handlermethode **handleGet** aufgerufen, welche einen Fehlercode zurückgibt.

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
