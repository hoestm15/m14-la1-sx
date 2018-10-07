# Protokoll 2: Java Server
Name: Patrick Schuster  
Klasse: 5AHME  
Gruppe: 3    
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: -

# Visual Studio Code
## Informationen zu Code
Visual Studio Code ist eine Programmierumgebung der Firma Microsoft und ist plattformübergreifend verfügbar. 
Es ist Open-Source, basiert auf dem Framework ELectron und hat Funktionen wie z.B. Syntaxvorhebung, Debugging, Autovervollständigung und Versionsverwaltung. 
Es werden Sprachen wie C++, CSS, HTML, Java, PHP, SQL, Typescript, etc. unterstützt und durch Plug-ins kann die Programmierumgebung beliebig erweitert werden.
Trotz des Namens hat Visual Studio Code nicht viel mit Visual Studio zu tun. Beide sind von der Firma Microsoft, 
werden aber von unterschiedlichen Teams entwickelt und folgen einer anderen Philosophie. Ein großer Unterschied in der Handhabung der Projekte
zwischen den VS und VS Code besteht darin, dass VS Code nicht mit Projektdateien sondern mit Quelltextdateien und Ordnern arbeitet.  
[Website von VS Code](https://code.visualstudio.com/)

## Arbeiten mit Code
Wenn man Code über das Desktop-Icon startet muss man im File Explorer erst das gewählte Projektverzeichnis ausgewählt werden um damit arbeiten zu können. Eine andere Möglichkeit ist es Code über den Terminal zu starten, dort kann man direkt den gewünschten Pfad dazuschreiben, so das Code diesen gleich als Projektverzeichnis nimmt.
Um in Code die Menüleiste anzeigen zu können (falls sie ausgeblendet ist) muss man auf der ALT-Taste oben bleiben, dann erscheint die Menüleiste.
Um die Hauptfunktionen aufrufen zu können befindet sich links eine Leiste mit mehreren Icons, über den Debugger Icon kann man auch auf den Terminal zugreifen ohne die Programmierumgebung verlassen zu müssen.

## Anpassen der Programmierumgebung
Code ist eine sehr leichtgewichtige Programmierumgebung und benötigt einige Modifikationen um damit effizient arbeiten zu können. 

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
### tsconfig.json
In dieser Datei werden die Optionen für den Compiler/Transpiler (TSC) angegeben.
```json 
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
**Bemerkung:** Die auskommentierten Zeilen werden vom Syntax Highlighting rot markiert, 
da *.json* Dateien eigentlich keine Kommentare vorsehen. Man kann diese aber trotzdem verwenden.

Option | Bedeutung  
---- | ---------  
module | spezifiziert die Quellcode generierung der Module  
noImplicitAny | gibt an ob eine Deklaration mit any einen Error erzeugen soll  
removeComments | gibt an ob Kommentare gelöscht werden sollen  
preserveConstEnums | gibt an das ConstEnums nicht gelöscht werden sollen 
sourceMap |   gibt an ob Map-Dateien generiert werden sollen
target | gibt an welche Version verwendet wird

# Server
## Unterschied zwischen Server in Java und Javascript/Typescript
In Java gibt es für die Realisierung eines Servers fertige Klassen und Bibliotheken wie z.B. ServerSocket. Mit dieser Klasse kann man einfach zu arbeiten und erleichtert das erstellen eines Servers erheblich.
In Javascript/Typescript hingegen gibt es keine leicht anzuwendenten Klassen wie in Java. Es gibt zwar die Klassen*http* und *https*, aber der umgang mit diesen erweißt sich als recht unbequem.
Um die Programmierung eines Servers mit Typescript zu erleichtern greifen wir auf das Express Framework zurück. Dieses stellt eine komfortable Möglichkeit dar einen Server zu realisieren und bietet viele hilfreiche Funktionen im Webbereich.
## HTTP und HTTPS
Bei der Übertragung zwischen zwei Hosts wird nicht immer nur ein Protokoll verwendet. Es können auch verschiedene Verwendet werden. 
Dieses Beispiel zeigt wie man mit HTTPS auf einem Rechner im Intranet zugreift. Innerhalb des Intranets, hinter dem Proxy Server, ist keine Verschlüsselung mehr Notwendig und es kann zwischen dem Proxy Server und dem Rechner ohne Verschlüsselung übertragen werden. Diese Geräte sind meistens auch räumlich nicht weit voneinander entfernt und sind z.B. am selben Rack oder laufen beide auf VMs am selben Rechner.
![](https://github.com/suspam14/la1/blob/master/Intranet_https.svg)
## Programm
Es sollte ein Programm erstellt werden, welches einen einfachen Server realisiert. Der Server sollte auf eine Anfrage warten und mit Hallo antworten.
```typescript  
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
Das Server-Programm hört so lange zu bis eine Anfrage kommt. Dann schickt der Server eine Antwort mit "Hallo" zurück und schließt die Verbindung.
## Express 
Express ist eine Framework für das Arbeiten mit HTTP und HTTPS und bietet eine vielzahl von nützlichen Funktionen für das Gestalten von Webanwendungen.

