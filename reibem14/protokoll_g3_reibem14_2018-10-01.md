# 2.Protokoll  
  
  **Name**:  *Bernhard Reinbacher*  
  **Datum:** *01.10.2018*  
  **Uhrzeit:** *8:00 - 10:30*  
  **Gruppe:** *3*  
  
   
    
 **Abwesend:** niemand  
 **Anwesend:** Bernhard Reinbacher, Ruffenacht Florian, Sackl Martin, Sackl Roland, Sammer Daniel, Schmuck Martin, Schuster Patrick  
  
*********************************************************************************************************************************    
## Visual Studio Code   
![vscode](/reibem14/vscode2.png)     
Visual Studio Code ist eine multiplattformfähige Programmierumgebung von Microsoft.Bis auf Namen und Logo hat Visual Studio Code jedoch nichts mit Visual Studio gemeinsam. Mithilfe dieses Programms kann man mit vielen Programmiersprachen arbeiten: Java, Javascript, C, C#, C++, Typescript, usw. Der Unterschied zwischen Visual Studio und Visual Studio Code liegt darin, dass Visual Studio Code mit Quelltextdateien und Ordnern arbeitet und Visual Studio mit Projektdateien. Erstmals veröffentlicht wurde Visual Studio Code im April 2016. Weiter Infos: [Visual Studio Code](https://code.visualstudio.com/)      

### Programmierumgebung einstellen  
Um mit der Entwicklungsumgebung gleich bequem arbeiten zu können wie mit Netbeans, muss man einige Einstellungen treffen. Diese Einstellungen werden im Ordner **.vscode** gespeichert und können jederzeit geändert werden. Falls Änderungen getroffen werden, werden diese sofort im Programm sichtbar. Unter **tsconfig.json** sind hingegen die Compileroptionen hinterlegt.    
  
#### .vscode  
In der Datei **settings.json** sind die Einstellungen, welche man zu ein- und ausblenden von Dateien im Explorer benötigt. Wie im Bild gezeigt, werden code_modules, .vscode und package-lock.json im Visual Studio Code ausgeblendet.  
![settings.json](/reibem14/settings.json.PNG)  
  
#### tsconfig.json  
In dieser Datei werden die Optionen für den Compiler gespeichert.   
```javascript  
{
    "compilerOptions": {
        "module": "commonjs",
        "noImplicitAny": true,
        "removeComments": true,
        "preserveConstEnums": true,
        "sourceMap": true,
        "target": "es2017",
        //"typeRoots": [
        //    "node_modules/@types"
        //]
           

    },
        "include": [
            "**/*.ts"
        ],
}  
```

Code | Bedeutung  
---- | ---------  
module | Code generation  
noImplicitAny | erzeut Error bei einer Deklaration mit any  
removeComments | löscht alle Kommentare die mit /* beginnen  
preserveConstEnums | löscht keine constEnums Deklarationen im Code  
sourceMap | generiert dazugehörige .map Files  
target | welche Version wird verwendet   
********************************************************************************************************************************  
## Programm  
```javascript  
import * as express from 'express';

class Main {

    private port: number;
    private server: express.Express;

    constructor(port: number) {
        this.port = port;
        this.server = express();

        this.server.get('*', (req, resp) => this.handleGet(req, resp));


        this.server.listen(this.port);
    }

    private handleGet(req: express.RequestHandler, resp:express.Response) {
        resp.send('Hallo');
        resp.end;
     
    }
}

let main = new Main(8080);  
```

  
  

