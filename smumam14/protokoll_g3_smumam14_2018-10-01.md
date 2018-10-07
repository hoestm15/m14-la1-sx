# Laborprotokoll  
Erste Einheit am 24. Sept. 2018  
Martin Schmuck  
5AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: niemand  

## Thema der Einheit: TypeScript mit Visual Studio Code
________

#### Unterschiede in der Realisierung eines Servers zwischen Java und Node.js
In Java gibt es beispielsweise Klassen wie ServerSocket, welche fertig ausprogrammiert sind und als Bibliotheken eingebunden und verwendet werden können. Dies erleichtert die Arbeit beim Erstellen eines Servers in dieser Sprache erheblich. Bei Node.js als Plattform bzw. TypeScript als Sprache gibt es zwar die Klassen http und https, diese sind jedoch unbequem in der Handhabung. Deshalb verwenden wir das Tool __Express__. Dieses Tool bietet eine komfortabele Möglichkeit, die beiden Protokolle zu verwenden. Dabei muss es jedoch sowohl am Entwicklungsrechner als auch am Zielsystem installiert sein, weshalb bei der Installation von diesem Tool die Option `save`und nicht `save-dev` angegeben werden muss, was eine entsprechende Eintragung in die Datei `package.json` im Abschnitt Dependencies bewirkt.  
Siehe dazu das [Protokoll der letzten Einheit](/smumam14/protokoll_g3_smumam14_2018-09-24.md#anlegen-eines-typescript-projektes).  

#### Einsatzgebiet http  
Gibt es überhaupt noch Use-Cases, bei denen man über das Netzwerk unter Verzicht auf Verschlüsselung übertragen möchte? Ja, man betrachte dazu folgende Skizze:  
![without-ssl](/smumam14/resources/http-use-case.png)  
Als erstes wird eine verschlüsselte Anfrage über https z. B. an die Domain eines Unternehmens gesendet. Die Firewall bekommt diese Anfrage und leitet sie wiederum verschlüsselt an einen Webserver, hier als Apache bezeichnet, weiter. Dieser Server erkennt, dass er die Anfrage abermals weiterleiten muss und sendet sie __unverschlüsselt__ an den eigentlichen Zielrechner. Warum ist ab hier unter Umständen keine weitere Verschlüsselung mehr notwendig? Weil diese beiden Geräte meist räumlich nicht weit voneinander entfernt sind (zum Beispiel im selben Rack, eventuell laufen beide auch als VM's auf der selben physikalischen Maschine). Solche Voraussetzungen könnten eine Verschlüsselung redundant machen. 

#### Visual Studio Code (kurz VS Code) 
Dabei handelt es sich um eine freie IDE, welche von Microsoft angeboten wird ([MIT-Lizenz](https://de.wikipedia.org/wiki/MIT-Lizenz)). Diese wird in der Schweiz entwickelt und hat, anders als wir zuerst vermuteten, mit ihrer Namensschwester "Visual Studio"  nicht wirklich viel gemeinsam. Dies fällt allein schon beim ersten Anblick auf, der sich wie folgt darbietet:   
![Programmstart](/smumam14/resources/scrsht1.png)  

##### Programmstart
Gestartet wird das Studio so, dass man sich den Projektordner mit dem Terminal hineinnavigiert und dann den Befehl `code .` eingibt. Das hat den Vorteil, dass man sofort im Projektordner arbeitet und diesen nicht erst umständlich einstellen muss. Sobald die IDE gestartet ist, sieht man das oben eingefügte Startbild. 

##### Aufbau  
Die Menüleiste im klassischen Sinne wird standardmäßig ausgeblendet. Um sie anzuzeigen, genügt ein Druck auf die `ALT`-Taste. Ganz links sieht man 6 Icons in einer Leiste. Das erste ist der normale File-Explorer, mit dem man durch das Projekt navigieren kann. Das zweite Symbol bietet die Möglichkeit, nach bestimmten Begriffen zu suchen. Der dritte Menüpunkt offeriert die Möglichkeit der Integration einer Versionsverwaltung, zum Beispiel [Git](smumam14/Protokoll1.md). Der vierte Punkt ist für den Debugger vorgesehen, der fünfte zur Verwaltung der Erweiterungen gedacht. Als sechstes Menü im linken unteren Eck findet man die Einstellungen. Eine sehr praktisches Feature von VS Code ist, dass man in der IDE eine vollwertige Bash zur Verfügung hat (im Bild oben ersichtlich). Dank dieser großartigen Funktion wird das nervenraubende Hin- und Herspringen zwischen zwei Fenstern obsolet. Eine weitere Besonderheit ist der File-Explorer. Durch einmaliges Anklicken einer Datei wird diese als neue Lasche (Tab) geöffnet. Klickt man dann eine andere Datei an, wird in diese geöffnet und die vorher angeklicke automatisch geschlossen. Dies ermöglicht ein flinkes Durchsichten, auch wenn dabei dutzende Dateien geöffnet werden müssen. Wenn man eine Datei dauerhaft offen haben möchte, muss man sie mit einem Doppelklick öffnen.  

##### Konfiguration  
Die Konfiguration der IDE erfolgt nicht über eine GUI, sondern im Wesentlichen über zwei `.json`-Dateien. Anpassungen sind notwendig, da man mit der IDE im Auslieferungszustand noch nicht effizient arbeiten kann.  
```
martin@schmuck:~/rest-server1$ cat .vscode/settings.json 
{
  "files.exclude":{                // sorgt dafür, dass im File-Explore in VS Code Übersicht herrscht, indem alle für die 
     "**/node_modules/": true,     // Entwicklung irrelevanten Dateien und Verzeichnisse ausgeblendet werden.
     "**/.vscode/": true,
     "**/package-lock.json" :true 
  }
}
martin@schmuck:~/rest-server1$ cat tsconfig.json 
{
    "compilerOptions":
   {
        "module": "commonjs",		// Stellt die Module zur Quellcode-Generierung ein
        "noImplicitAny": true, 		// Soll bei einer Deklaraion mit Any ein Fehler geworfen werden?
        "removeComments": true,		// Werden Kommentare entfernd
        "preserveConstEnums": true,	// Konstante Enum-Deklaration im generierten Code werden nicht gelöscht
        "sourceMap": true,		// Soll eine .map-Datei erstellt werden?
        "target": "es6"			// Spezifiziert die Zielversion nach dem Transpilieren (hier ECMAS Version 6)
	},
    "include": [			// Bindet alle .ts-Dateien ein
        "**/*.ts"
    ]
   
}
 ```  
 Kommentare sind normalerweise in `.json`-Dateien nicht vorgesehen, an dieser Stelle jedoch ausnahmsweise erlaubt.  
 
 #### Programm  
 ```typescript  
import * as express from 'express';

class Main 
{
    private port: number;
    private server: express.Express;

    constructor(port: number)
    {
        this.port = port;
        this.server = express();
        this.server.get('*', (req, resp) => this.handleGet(req, resp)); // Weitergabe der Aufgaben einer Methode an eine andere
        this.server.listen(this.port);
    }

    private handleGet(req: express.RequestHandler, resp:express.Response) 
    {
        resp.send('Hallo');
        resp.end;
    }
}

let main = new Main(8080); 
```  
Zur Erklärung: das Schlüsselwort `var` bewirkt, dass, egal wo im Quelltext die Variable deklariert / definiert wird, sie vom Compiler so behandelt wird, wie wenn am Beginn des Blocks die Deklaration durchgeführt wird. Will man das nicht, verwendet man `let`. Was noch auffält ist, dass hier der Konstruktor nicht gleich heißt wie die dazugehörige Klasse, sondern mit dem Schlüsselwort `constructor` eingeleitet wird. Die Erklärung für den Operator `=>` ist im Kommentar oben untergebracht. Gebaut (bzw. transpiliert) wird übrigens mit folgendem Befehl im Terminal: `node node_modules/typescript/bin/tsc -p tsconfig.json`  
  
  
Der transpilierte Text sieht je nach in der `tsconfig.json` (siehe oben) eingestellten JavaScript anders aus. Hier für Version 6:  
```javascript
"use strict";
exports.__esModule = true;
var express = require("express");
var Main = (function () {
    function Main(port) {
        var _this = this;
        this.port = port;
        this.server = express();
        this.server.get("*");
        this.server.listen('*', function (req, resp) { return _this.handleGet(req, resp); });
    }
    Main.prototype.handleGet = function (req, resp) {
        resp.send("Hallo");
        resp.end();
    };
   return Main;
}());
var main = new Main(8080);
//# sourceMappingURL=main.js.map 
```  

