# 3.Protokoll  
  
  **Name**:  *Sackl Roland*  
  **Datum:** *01.10.2018*  
  **Uhrzeit:** *8:00-10:30*  
  **Gruppe:** *3*  
  
  **Abwesend:** Schmuck Martin  
  **Anwesend:**   Sackl Martin, Sackl Roland, Reinbacher Bernhard,Sammer Daniel,Ruffennacht Florian,Schuster Patrick
   

## Übersetzungstools  
Es gibt je nach Programmiersprache andere Anforderungen an den Compiler:

Typescript | Java | Java(unter Android) | C  
---------- | ---- | ------------------- | -  
Gulp | javac | gradle | make   
gulp | javac | gradle | make  

## Konfigurartionsdateien  

### tslint.json   
Durch diesen Plug-in wird der Programmierer bei der optisch anprechenden Gestaltung seines Codes unterstüzt.   In der Datei können verschidene Einstellungen am tool vorgenommemn werden.  
Ein Beispiel: Die maximale Anzahl an Zeichen in einer Zeile.

```javascript  
"max-line-length": [
            true,
            140  
```  


### tsconfig.json
Hier werden die Einstellungen beim Übersetzungsvorgang mit dem **tsc** gesteuert und gespeichert. 
Die Datei sieht folgendermaßen aus:
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
 In der Datei im **.vscode**-Ordner wird zum Ausblenden von unerwünschten Dateien in der Programmierumgebung verwendet. Außerdem kann es auch während des Programmierens gesehen.

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
Die Taks im Quelltextmanager, die sich ebenfalls im **.vscode**-Ordner befinden, werden mit denen des gulp-tools verknüpft.  

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
In der Datei launch.json im **.vscode**-Ordner definiert die Einstellungen beim Debuggen.

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
In dieser Datei lassen sich Tastenkürzel für gewissen Vorgänge speichern.
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
## Rest-Server anlegen

In der letzten Einheit wurde der Server so verändert, dass eine sinnvolle Antwort auf unterschiedliche Anfragen gesendet wird. In unserer Übung soll durch aufrufen einer URL eine Meldung bzw. Informationen über Schüler zurückgegeben werden.  

```  typescript  
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
                resp.json({htlid: 'suspam14', sirname: 'Schuster', firstname: 'Patrick'});
                break;
            case 'reibem14':
                resp.json({htlid: 'reibem14', sirname: 'Reinbacher', firstname: 'Bernhard'});
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

### Konstruktor und Handlermethode  

Auf *listen(zuhören)* wird der Server geschalten und wartet bis ein *Request* eintrifft. Dass man */status* in der URL eingeben kann, bewirkt die Zeile ```typescript this.server.get('/status', (req, resp) => this.handleGetStatus(req, resp)); ```.Die Handlermethode  wird mittels *HandleGetStatus* aufgerufen und bewirkt das *Response* "Server is running" zurückgegeben wird. Auch die restlichen Handlermethoden arbeiten mit den gleichen Prinzip.   

### Anwenden des Rest-Servers  
Wenn man Durch aufrufen von *http://localhost:8080/student?htlid=sacrom14* aufruft, wird der Student *sacrom14* mit den dazugehörigen Informationen durch der Handlermethode ausgegeben.  
![8080](/sacrom14/8080.PNG)  
  
Die einzelelnen Teile der URL lauten:  
![URL](/sacrom14/URL.PNG)    
