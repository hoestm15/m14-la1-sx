# 3.Laborprotokoll 

*von Florian Ruffenacht*

Datum: 01.10.2018 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

Abwesend: -

## Warum ist HTTP noch relevant?
Der HTTP-Standard gilt allgemein als unsicher und wird überwiegend durch die verschlüsselte Weiterentwicklung HTTPs ersetzt. Doch in manchen Fällen wird HTTP durchaus verwendet. Das soll das folgende Beispiel zeigen:

![HTTP in der Firewall](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/HttpInFirewall.svg)

Hier werden über das Internet Daten an einen Webserver übertragen. Die Datenübertragung läuft aber nur bis zum Proxy-Server verschlüsselt über HTTPs. In der Umgebung der Firewall, in der der Proxy-Server die Daten an den eigentlichen Server  vermittelt, läuft die Kommunikation nur über HTTP.


## Visual Studio Code
### Allgemeines
Der Quelltexteditor Visual Studio Code von Microsoft ist **plattformunabhängig** auf Windows, Linux und MacOS erhältlich. Es werden viele
Programmiersprachen wie C#, C++, CoffeeScript, F#, HTML, Ini, Java, JavaScript, Makefile, Markdown, Objective-C, Python, R, Ruby, SQL, 
Swift, TypeScript, Visual Basic und XML unterstützt. Visual Studio Code kann mit dem Konsolenbefehl ```code``` gestartet werden. Optional
kann das Programm mit ```code . ``` im Projektordner geöffnet werden, wobei man sich dann gleich im jeweiligen Projekt befindet. 

### Schnellstartleiste
Auf der unten ersichtlichen Abbildung ist die Schnellstartleiste von Code abgebildet. An oberster Stelle findet man den **Dateiexplorer**. Es folgen die **Suchfunktion**, die **Versionsverwaltung**, der Menüpunkt für **Debugging** und der Menüpunkt für **externe Plug-ins**. Die stehen für Visual Studio Code zahlreich zur Verfügung, können den Quelltexteditor im schlimmsten Fall aber auch lahmlegen. Deswegen gibt es auch die Möglichkeit, Code ohne Plug-ins zu starten. Werden Datein nur mit einem einfachen Klick geöffnet, verschwinden sie beim Öffnen der nächsten Datei wieder. Das kann beim Suchen nach Codestellen hilfreich sein. Um Datein dauerhauft zu öffnen, ist ein Doppelklick notwendig.

![Code Schnellstartleiste](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/Bildschirmfoto%20vom%202018-10-02%2020-47-41.png)

### Verbergen von Datein
Beim Programmieren möchte man manchmal nicht alle Datein im Projektordner auch im Quelltexteditor sehen. Um Datein auszublenden, legt man im Projektverzeichnis mit ```mkdir .vscode``` ein neues Verzeichnis an und erstellt mit ```nano settings.json``` eine neue Datei. In dieser können folgendermaßen gewisse Datein für Code "unsichtbar" gemacht werden:

```
"files.exclude": {
		"**/node_modules/": true,
		"**/.vscode/": true,
		"**/package-lock.json": true
	}
```

[Weitere Informationen zu Visual Studio Code](https://flaviocopes.com/vscode/)

## Programmieren des Rest-Servers

### Express-Modul
Mit Node.js werden die Module "http" und "https" zur Erstellung von Web-Servern mitgeliefert. Diese sind eher mühsam zu bedienen und bedürfen Einarbeitungszeit. Deswegen verwenden wir das externe Modul "Express", welches auf "http" und "https" von Node.js aufbauen. Express ermöglicht ein sehr komfortables Arbeiten. 

### Grundaufbau
Um vom Server überhaupt einmal eine Verbindung herstellen zu können, schrieben wir folgendes TypeScript-Datei:

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
Die Datei start mit dem "import"-Aufruf, bei dem Express importiert wird.Dem Konstruktor der Main-Klasse wird nur die Port-Nummer übergeben. Diese Variable wird vor dem Konstruktor als Nummer deklariert. Die Variable express.Express wird mit dem Datentyp "server" deklariert. Damit hier keine Fehler entsteht, müssen zuerst die Datentypen von Express mit folgendem Befehl nachinstalliert werden:

```npm install --save-dev @types/express```

Mit dem Aufruf ```this.server.listen(this.port);``` wird der Server gestartet.  Wenn man jetzt in einem Explorer die Adresse 127.0.0.1 und den Port 80 eingiebt erkennt man, dass eine Verbindung aufgebaut werden kann. Es kommt aber noch keine sinnvolle Antwort vom Server zurück.

### Response auf GET-Anfrage
Um bei einer GET-Anfrage passend zu antworten, wird der Konstruktor um den unten dargestellten Befehl erweitert. Im ersten Parameter wird angegeben, auf welcher URL dieser Befehl antwortet. Hier wurde ein Stern gesetzt, weil auf alle URLs gleich geantwortet werden soll. Im zweiten Pararmeter wird die funktionale Programmierung angewendet. Mit den Pararmetern "req" und "res" soll die Handlermethode **handleGet** aufgerufen werden.
``` typescript
this.server.get('*', (req,resp) => this.handleGet(req,resp))
```
Die Methode "handleGet" sieht wie folgend dargestellt aus. Mit **resp.send();** wird die Antwort auf die GET-Anfrage festgelegt. Der Aufruf von **resp.end()** signalisiert das Ende der Antwort und ohne diesen Aufruf würde keine Antwort gesendet werden. Die auskommentierte Zeile zeigt, wie ein Fehlercode zurückgegeben werden kann. 

```typescript
 private handleGet (req: express.Request, resp: express.Response) {
        //resp.status(400);
        resp.send('Hallo');
        resp.end();
    }
```
### Konfigurieren des tsc
Um den TypeScript-Compiler zu konfigurieren, wird die Datei **tsconfig.json** erstellt:
```json
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
Hier können Einstellungen am Compiler, wie zum Beispiel die JavaScript Version, in die transpeliert werden soll, verändert werden. Um die Einstellungen aktiv werden zu lassen, ist der Befehl ```node node_modules/typescript/bin/tsc/ -p tsconfig.json``` im Projektverzeichnis auszuführen.  
