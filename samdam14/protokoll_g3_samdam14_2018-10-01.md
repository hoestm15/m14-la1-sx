# _Protokoll Zweite Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 10.01.2018**  
**Uhrzeit: 8:00-10:30**  
  
**Anwesenheit: _Es waren alle Schüler anwesend_**  
  
**Thema: Typescript / Visual Studio Code**  
  
-----------------------------------------------------------
  
### Server in Java und Node.js  
In Node.js gibt es die Klassen HTTP und HTTPS, aber diese sind in der Anwendung eher unbequem umständlich. Aufgrunddessen kommt bei uns das Tool *Express* zum Einsatz. Express ermöglicht eine im Vergleich leichte Anwendung beider Protokolle, HTTP und HTTPS. Damit dieses Tool funktioniert, muss es am Entwicklungsrechner und am Zielsystem installiert sein. Express steht deswegen in der Datei package.json in den *Dependencies*.  
In Java ist die Realisierung eines Servers einfacher. Es gibt ausprogrammierte Klassen, wie z.B. ServerSocket, welche einfach als Bibliothek eingebunden werden können.  

### Gibt es noch Anwendungen, in denen man in einem Netzwerk auf Verschlüsselungen verzichtet?  
Ja!  
![](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/http%20Anwendung.PNG)  
Der Client schickt eine Anfrage an die Domain eines Unternehmen, verschlüsselt mittels https. Die Firewall erhält die Anfrage zuerst und leitet sie verschlüsselt an einen Web-Server. Dieser erkennt, dass er die Request wieder weiterleiten muss und sendet sie aber nun unverschlüsselt an den Ziel-Rechner. Das diese Übertragung unverschlüsselt stattfinden kann, kann unterschiedliche Gründe haben. Die Häufigste aber ist, dass sich die beiden Geräte örtlich nicht weit voneinander entfernt liegen.  

## Visual Studio Code  
![VS Code](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/VS%20Code.png)  
#### Allgemeines  
Visual Studio Code ist ein plattformunabhängiger Quelltext-Editor von Microsoft, der viele verschiedene Programmiersprachen unterstützt (C, C++, HTML, Java, Javascript, TypeScript, ...). Es lässt sich zwar wie jede andere Applikation öffnen, aber man kann auch komfortabel über den Konsolenbefehl `code` einsteigen. Mit `code .` gelangt man direkt in das aktuelle Projektverzeichnis.  
  
#### Schnellstartleiste  
Die Schnellstartleiste in VS Code beinhaltet einen Dateiexplorer, eine Suchfunktion, eine Versionsverwaltung, einen Punkt, um in den Debug-Mode zu gelangen und die Möglichkeit, externe Plug-ins einzufügen. Externe Plug-ins können dazu führen, dass das komplette System lahm gelegt wird. Um diese Problemzone zu umgehen, kann man den geschriebenen Code auch ohne Verwendung der Plug-ins starten.  
Wenn man im Dateiexplorer eine Datei mit einem einfachen Mausklick öffnet, dann wird der Dateiname kursiv dargestellt. Klickt man nun auf eine andere Datei, verschwindet der Tab der ersteren. Mit einem Doppelklick öffnet man Dateien dauerhaft.  
![Schnellstartleiste](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/startleiste.jpg)  
  
#### Dateiexplorer übersichtlicher gestalten  
Um den Dateiexplorer übersichtlicher zu gestalten, legt man im Projektverzeichnis einen neuen Ordner `.vscode` an. In diesem Ordner erstellt man die Datei `settings.json`. Dort kann man alle für die Programmierung irrelevanten Dateien ausblenden lassen (z.B. main.js, damit man nicht fälschlicherweise dort neuen Code erzeugt, welcher beim transpilieren verloren gehen würde).  
```
"files.exclude": {
		"**/node_modules/": true,
		"**/.vscode/": true,
		"**/package-lock.json": true
	}
```
  
#### TSC konfigurieren  
Die Konfiguration des TypeScript-Compilers findet in der Datei `tsconfig.json` statt:  
```TypeScript
{
    "compilerOptions": {
        "module": "commonjs",
        "noImplicitAny": true,
        "removeComments": true,
        "preserveConstEnums": true,
        "sourceMap": true,
        "target": "es2017"
    },
    
    "include": [
        "**/*.ts"
    ]
}
```
In dieser Datei können Einstellungen für den Compiler getroffen werden. Beispielsweise kann man die Sprache, in die der Compiler transpilieren soll, einstellen. Der Compiler lässt sich in der Konsole mit `node node_modules/typescript/bin/tsc/ -p tsconfig.json` starten.  
  
#### Programm  
Es soll ein Programm in TypeScript in VS Code erstellt werden. Das Programm soll einen Server realisieren, der auf Requests wartet und dann mit *Hallo* antwortet.  
  
##### Verbindung herstellen  
Um wie im nacholgendem Listing das Express-Tool zu verwenden, muss man zuerst die Datentypen von Express nachinstallieren:  
`npm install --save-dev @types/Express` (*--saved-dev*, da es nur für den Entwickler benötigt wird)  

```TypeScript
import * as express from 'express';

class Main{

    private port : number;
    private server : express.Express;

    constructor (port : number) {
        this.port=port;
        this.server= express();
        this.server.listen(this.port);
    }
}
let main = new Main(8080);
```
Beginnend mit dem Schlüsselwort *import* wird das Express-Tool implementiert. Der Konstruktor erhält als Parameter die Port-Nummer übergeben. Auffallend ist, dass der Konstruktor nicht wie die Klasse selbst heißt, sonder mit dem Schlüsselwort `constructor` beginnt. 
Mit `this.server.listen(this.port);` wird der Server gestartet. Würde man nun mit ihm Kontakt aufnehmen, wäre es zwar möglich, aber er würde noch keine vernünftige Antwort liefern.  
Das Schlüsselwort `var` wird so behandelt, als hätte die Deklaration bereits ganz am Anfang stattgefunden. Will man dies nicht, verwendet man `let`.  
  
##### Antworten auf GET-Anfragen  
Damit man GET-Requests beantworten kann, muss zunächst die Handler-Methode *handleGet* erstellt werden. *HandleGet* legt fest, wie der Server auf GET-Anfragen reagieren soll. Mit `resp.send` kann mit einer Textnachricht auf eine Anfrage reagiert werden, Mit `resp.status()` kann man einen Statuscode ausgeben. Mit `resp.end` wird das Ende der Server-Response signalisiert.  
 ```TypeScript
 private handleGet (req: express.Request, resp: express.Response) {
        //resp.status(400);
        resp.send('Hallo');
        resp.end();
    }
```
  
Damit eine GET-Anfrage tatsächlich vom Server beantwortet wird, muss der Konstruktor der Main Klasse um eine Zeile Code erweitert werden:
```TypeScript
this.server.get('*', (req,resp) => this.handleGet(req,resp))
```
Der erste Parameter sagt aus, auf welche Art von GET-Anfragen geantwortet werden soll. `*` bedeutet, dass auf alle reagiert werden soll.  Der zweite Parameter beinhaltet funktionalem Code. Dieser sagt aus, dass die Methoden *handleGet* aufgerufen werden soll.
