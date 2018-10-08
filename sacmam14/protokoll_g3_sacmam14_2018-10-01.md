# 2. Protokoll  
**Name:** Sackl Martin  
**Klasse** 5ahme  
**Gruppe:** 3  

Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster   
Abwesend: -  
*******************************************************************************************************************************************  
# Visual Studio Code  
Visual Studio Code ist ein freier Quelltext-Editor von Microsoft. Visual Studio Code ist plattformübergreifend für die Betriebssysteme Windows, macOS und Linux verfügbar. Visual Studio Code basiert auf dem Framework Electron und ermöglicht u. a. Syntaxhervorhebung, Code-Faltung, Debugging, Autovervollständigung und Versionsverwaltung.  

## Einstellung der Programmierumgebung  
Um bequem Arbeiten zu können sollte man einige Einstellungen ändern. In dem Ordner **.vscode** sind die Einstellung gespeichert und diese können jederzeit geändert werden. Sobald man Änderungen vornimmt, werden diese sofort im Programm sichtbar. Im Ordner **tsconfig.json** sind Compileroptionen hinterlegt.  

####  tsconfig.json  
Compileroptionen sind hier hinterlegt  
```javascript  
{  
    "compilerOptions": {    
        "module": "commonjs",         //Code generation  
        "noImplicitAny": true,        //Bei einer Deklaration mit any, erzeugt es einen Error  
        "removeComments": true,       //Kommentare werden gelöscht  
        "preserveConstEnums": true,   //ConstEnums Deklarationen werden nicht gelöscht  
        "sourceMap": true,            //dazugehörigen .map Files werden generiert  
        "target": "es2017",           //beschreibt welche Version verwendet wird  
        //"typeRoots": [  
        // "node_modules/@types"  
        //]  
    },  
        "include": [  
          "**/*.ts"  
        ],  
}   
```  

#### .vscode  
Hier kann man Einstellen welche Dateien man ein- bzw. ausblenden möchte. Mit **true** werden die Dateien ausgeblendet und mit **false** werden sie eingeblendet.  
******************************************************************************************  
# Programm  
Hier wird dem Server gesagt, dass er solange zuhören (listen) soll, bis eine Anfrage kommt. Als Antwort wird dann "Hallo" zurückgeschickt, anschließend wird die Antwort geschlossen.  
Mit **express** kann man auf **HTTP** und **HTTPS** zugreifen, da es ein externes Modul ist. Mit diesem Modul ist ein komfortables Arbeiten möglich. Da man sich eben nicht immer auf ein Übertragungsprotokoll fixieren möchte, kann man eben **HTTP** und **HTTPS** verwenden.  
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

let main = new Main(8080);   //mit let, wird die Variable erst definiert, wenn man diese Zeile abarbeitet  
```  

