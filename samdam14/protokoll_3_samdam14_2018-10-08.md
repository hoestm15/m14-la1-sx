# _Protokoll Dritte Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 10.08.2018**  
**Uhrzeit: 8:00-10:30**  
  
**Anwesenheit: _Es waren alle Schüler anwesend_**  
  
**Thema: Tools zur Programmierung in Typescript**  
  
-----------------------------------------------------------
  
### Tools in Typescript  
Um das Programmieren in Typescript angenehmer zu machen, bzw. schöner zu gestalten, kann man ganz einfach Tools nachinstallieren und somit in ein Projekt einbinden. Diese Tools können dann dazu verhelfen, schöneren Code zu erzeugen oder z.B. den Code zu kompilieren.  
[Diverse Tools für Typescript](http://definitelytyped.org/directory/tools.html)  
  
#### TSLint  
TSLint hilft, den Typescript-Code "schöner" zu gestalten. Dabei ist nicht nur die Optik gemeint, sondern der Code wird generell übersichtlicher und somit leserlicher. TSLint ist mit 1,8 Millionen wöchentlichen Downloads auch ein viel verwendetes Tool. Mit *npm install tslint typescript --save-dev* kann man das Tool im Arbeitsverzeichnis installieren.  
[npmjs/tslint](https://palantir.github.io/tslint/)  
  
In der tslint.json Datei können Einstellungen am Tool getroffen werden, also auf was es achten soll. Z.B. kann man TSLint sagen, wie lange eine Zeile maximal sein darf und / oder wie Leerzeichen und -zeilen gehandhabt werden sollen.  
```typescript
// Beispiel maximale Zeilenlänge
"rules": {
        "max-line-length": {
            "options": [120]
        }
 }
```
  
#### gulp  
Gulp ist ein Übersetzungs-Tool, welches sehr einfach zu erlernen und zu bedienen ist. Mit *npm install gulp* kann man das Tool einbinden. Gulp ist mit in etwa einer Millionen Downloads pro Woche ein weit verbreitetes Tool. Ein weiteres Beispiel für ein Übersetzungs-Tool in Typescript wäre *grunt*.  
[gulp](https://gulpjs.com/)  
[grunt](https://gruntjs.com/)  
  
-----------------------------------------------------------------------------  
  
### Erstellte Dateien  
In der Einheit wurden folgende Dateien erstellt bzw. bearbeitet:  
  
#### settings.json  
Das File **settings.json** haben wir dafür verwendet, um Dateien, die für das Programmieren nicht von Bedeutung sind bzw. zur Verwirrung führen können, aus dem von VS Code zu Verfügung gestellten File-Manager auszublenden. Die Datei ist im **.vscode** Ordner anzulegen.  
```typescript
// settings.json
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
  
#### tsconfig.json  
In dieser Konfigurations-Datei kann man Einstellungen für den Typescript Compiler treffen und verändern. Die Veränderungen haben auch Einfluss auf das Verhalten von *gulp*, da dieses Tool auf den *tsc* aufbaut.  
```typescript
// Beispiel für eine tsconfig.json Datei
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
  
#### launch.json  
In diesem File werden Einstellungen, die für das Debuggen / für das Launchen des Programmes notwendig sind, getroffen.  
```typescript
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
  
#### keybindings.json  
Wie der Dateiname schon sagt kann man hier Tastenkombinationen deklarieren. Das ist natürlich bei häufig verwendeten Tasks nützlich wie z.B. *build*, *clean* und *cleanAndBuild*.  
```typescript
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
  
-------------------------------------------------------------------------  
  
### Änderungen am Rest-Server  
In der letzten Einheit wurde darauf der Wert gelegt, dass unser Server überhaupt auf Anfragen reagiert und antwortet. Die Antwort ist natürlich nicht sinnvoll, das soll sich diese Einheit ändern, denn der Server soll in Abhängigkeit von der URL der Anfrage Informationen über den gewünschten Schüler liefern.  
Ziel: 
Anfrage: `http://localhost:8080/student?htlid=samdam14`  
Antwort: `{htlid: 'samdam14', surname: 'Sammer', firstname: 'Daniel'}`  
  
Nach dem Start des Servers und der Anwendung des bodyParsers werden die Anfragefälle `/status` und `/student` definiert. Sie sollen jeweils das Aufrufen der jeweiligen Handlermethode `handleGetStatus` und `handleGetStudent` bewirken. Außerdem wird der Fall behandelt, wenn keine bestimmte Anfrage vorhanden ist. In dem Fall bewirkt das Aufrufen der Handlermethode `handleGet` eine ERROR-Rückmeldung des Servers.  
Die verschiedenen Schüler werden in `handleGetStudent` durch ein switch-case gehandelt, im default case wird eine Antwort erzeugt, wenn der oder die Schüler(in) nicht gefunden wurde.  
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
