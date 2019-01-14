# Protokoll
Gerhard Mandl 
5AHME, Gruppe 2  
07.01.19  
Anwesend: Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: -

# Visual Studio Code 



# Node.js und Java

### Java
In java wird der Quelltext mit dem Tool __ant__ compiliert. Um genau zu sein wird die .java Datei zu einer .class Datei compiliert und aus mehrern class Dateien wird dann die eigentliche .jar Datei erzeugt.

### Node.js
Bei Javascript wird der Quelltext nicht compiliert sondern interpretiert, das verwendete Tool nennt sich __Gulp__.
Vorteile: 
+ gleiche Sprache zwischen Serve-Client  
+ im jeden Browser verfügbar

Da Javascript eine schlechte Programmiersprache ist weil sie keine Datentypen besitzt, wird der Quelltext oft mit Typescript geschrieben .ts und zu einer .js Datei transpiliert, dadurch wird js mit Datentypen erweitert. 

### .json
Der Begriff json steht für __JavaScript Object Notation__ und ist ein Datenformat mit einfacher lesbaren Textform, welches für Datenaustausch zwischen Anwendungen verwendet wird.

__JSON Datentypen__:
* Nullwert `null`
* Boolscher Wert `true` oder `false`
* Zahlenfolge von `0`-`9` welche mit `+` und `-` vorzeichenbehaftet betrachtet werden können und durch einen Dezimalpunkt `.` unterbrochen sein können
* Zeichenketten beginnen mit einem doppelten Anführungszeichen `"`
* Arrays beginnen mit `[` und enden mit `]`
* Objekte beginnen mit `{` und enden mit `}`
* Attribute von Objekten sehen folgendermaßen aus: `Schlüssel:Wert`
### Compiliert
Beim Compilieren wird ein Quellcode von einer Sprache in eine andere Sprache umgewandelt.

### Transpilieren
Beim Transpilieren wird ein Quellcode von einer Sprache in eine andere Sprache, welche einen ähnlichen Abstraktionsgrad aufweist, umgewandelt.



# Konfigurieren von Visual Stuido Code

### setting.json
In diesem Ordner wird eingestellt welche Dateien in Visual Studio Code nicht angezeigt werden sollen.
Dafür wird der Ordnername/Filename auf true gesetzt. 
```json
{
	"files.exclude": {
		"**/node_modules": true,
		"**/package-lock.json": true,
		"**/dist": true,
		"**/tsconfig.json": true,
		"**/gulpfile.js": true,
		"**/.vscode": true,
		"**tslint.json": true,
	}
}
```

### Tasks
Wir verwenden Taks um den Transpiliervorgang für die IDE zu automatisieren, da dies von vorhinein automatisiert ist. In den Taks wird definiert was beim Builden passiert.
```js
gulp.task('build', function (done) {
    console.log("Task build gestartet");
    sequence('transpile', 'copyFiles', () => {
        console.log(finalMessage);
    });
});
```

### tslin.json 
tslin ist ein Analysewerkzeug das Typescript auf sogenannte __SChonheitsfehler__ überprüft.
Zum Beispiel die Lesbarkeit des Codes. 

# Übung

Zuerst haben wir das __npm__ Tool installiert, mit diesem können wir Projekte erstellen.
Um ein Projekt anzulegen wird der Befehl __npm init__ verwendet.

Danach haben wir ein Programm in Typescript geschrieben und haben dieses ausgeführt, dabei wurde uns eine Fehlermeldung angezeigt.
```
/home/mangem/Schreibtisch/Labor/Voruebung/main.ts:2
let y: number;
     ^

SyntaxError: Unexpected token :
    at createScript (vm.js:80:10)
    at Object.runInThisContext (vm.js:139:10)
    at Module._compile (module.js:617:28)
    at Object.Module._extensions..js (module.js:664:10)
    at Module.load (module.js:566:32)
    at tryModuleLoad (module.js:506:12)
    at Function.Module._load (module.js:498:3)
    at Function.Module.runMain (module.js:694:10)
    at startup (bootstrap_node.js:204:16)
    at bootstrap_node.js:625:3
```

Um die Fehler zu beseitigen haben wir den Typescript Compiler mit dem Befehl __npm install typescript__ installiert.
Das Programm `main.ts` kann nun mit dem Befehl `./node_modules/typescript/bin/tsc main.ts` zur Datei `main.js` transpiliert werden.

Wenn wir nun die main.js ausführen, welche entsteht nachdem wird main.ts transpiliert haben, erhalten wir folgende Ausgabe in der Konsole: 
```
Hallo 270
```

### package.json
Da das ausführbare Programm eine Abhängigkeit von Typescript beinhaltet, haben wir diese Abhängigkeit gelöscht, da nur der Entwickler Typescript benötigt. Dafür gibt es eigene Abhängigkeiten welche sich __devDependencies__ nennt.

Nach dem erfolgreichen Transpilierung des Programmes haben wir uns die Datei `package.json` genauer angesehen:
```json
{
  "name": "voruebung",
  "version": "1.0.0",
  "description": "voruebung",
  "main": "main.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "Michael Moerth",
  "license": "MIT",
  "dependencies": {
    "typescript": "^3.2.2"
  },
}
```

Nun haben wir die __dependencies__ mit dem Befehl __npm rm typescript__ gelöscht und mit dem Befehl __npm install --save-dev typescript__ die Entwickler Abhängigkeiten erstellt.
```json
{
  "name": "voruebung",
  "version": "1.0.0",
  "description": "voruebung",
  "main": "main.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "Michael Moerth",
  "license": "MIT",
  "dependencies": { },
  "devDependencies": {
    "typescript": "^3.2.2"
  }
}
```

Anschließen haben wir eine Abhängigket für den Endverbraucher installiert. Wir haben das Paket __sprintf__ mit dem Befehl __npm install sprintf-js__ installiert.
Ein Blick in die Datei `package.json` ergibt nun:  
```json
{
  "name": "voruebung",
  "version": "1.0.0",
  "description": "voruebung",
  "main": "main.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "Michael Moerth",
  "license": "MIT",
  "dependencies": {
    "sprintf-js": "^1.1.2",
  },
  "devDependencies": {
    "typescript": "^3.2.2"
  }
}
```

Danach haben wir unser Programm __main.ts__ erweiter:
```js
import { sprintf } from 'sprintf-js';

const x = 27;
let y: number;

y=10*x;

console.log('Hallo', sprintf('%.02f', y));
```

Anschließend wurde das Programm wieder transpiliert und wir führten die dazugehörige main.js Datei aus.
```
Hallo 270.00
```
