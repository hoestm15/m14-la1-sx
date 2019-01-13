# Protokoll
Michael Mörth  
5AHME, Gruppe 2 
07.01.19  
Anwesend: Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: -

# Visual Studio Code
Visual Studio Code ist eine **plattformunabhängige** Programmierumgebung von Microsoft. Diese wird zur Programmierung von Typescript entwickelt. Typescript ist quasi ein "JavaScript Dialekt", wobei der Hauptunterschied darin liegt, dass Typescript jeder Variable einen Datentyp zuweist.  
Typescript Quellcodes müssen vor der Ausführung in einen JavaScript Code **transpiliert** werden.

## Transpilieren vs. Kompilieren
**Kompilieren**  
Ist der generelle Term um Quellcodes von einer Sprache in eine andere Sprache umzuwandeln  
**Transpilieren**  
Ist ein spezieller Term um Quellcode von einer Sprache in eine andere Sprache mit ähnlichen Abstraktionsgrad umzuwandeln  

Das Umwandeln eines C#-Codes in einen IL(Intermidate Language)-Code wird als Kompilierung bezeichnet, da IL ein komplett anderes Level der Abstraktivität hat als C#.  
Das Umwandeln eines TypeScript-Codes in einen JavaScript-Code wird hingegen als Transpilierung bezeichnet, da beide Sprachen ein ähnliches Level der Abstraktivität haben.
[Quelle](https://www.stevefenton.co.uk/2012/11/compiling-vs-transpiling/)

## Einrichten von Visual Studio Code
### settings.json
Im Ordner .vscode kann man in der Datei settings.json eintragen, welche Dateien man in Visual Studio nicht angezeigt bekommen möchte.
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
### Lint
### tslint.json
> TSLint ist ein erweiterbares statisches Analysewerkzeug, das TypeScript- Code auf Lesbarkeit, Wartbarkeit und Funktionsfehler überprüft . Es wird weitgehend von modernen Editoren und Build-Systemen unterstützt und kann mit Ihren eigenen Fusselregeln, Konfigurationen und Formaten angepasst werden.  
*[Quelle: TSLint](https://palantir.github.io/tslint/)*

### Tasks
Mit Hilfe von Tasks wird der Transpiliervorgang für die IDE automatisiert. Um diesen Vorgang zu realisieren gibt es Tasks. In diesen Tasks ist definiert was beim Builden, Cleanen etc. zu tun ist. Wir verwenden **gulp**.
```js
gulp.task('build', function (done) {
    console.log("Task build gestartet");
    sequence('transpile', 'copyFiles', () => {
        console.log(finalMessage);
    });
});
```

### Dokumentation mit VisualStudio Code
VisualStudio Code ermöglicht es, Markdown-Dateien im Projekt anzulegen. Dies ermöglicht es, einfach und schnell Dokumentationen für das Programm zu erstellen.

# Übung mit der Konsole - Transpilieren
Wir haben ein Projekt mit dem **Node Package Manager** erstellt. Der Befehl für die Konsole lautet: `npm init`. Mit diesem Befehl werden Packete loakl installiert. Dafür wird die Datei `package.json` verwendet, welche mit `npm init` erzeugt wurde.


Danach haben wir in unserem erstellten Projektordner das Programm `main.ts` erstellt:  
```js
console.log('Hallo');
```  

Danach haben wir versucht, dass Programm über die Konsole mit `node main.ts`auszuführen. Der Versuch war erfolgreich, da keine TypeScript spezifischen Ausdrücke verwendet wurden. Also haben wir unseren Code erweitert:

```js
const x = 27;
let y: number;

y=10*x;

console.log('Hallo', y);
```  

Wenn wir nun versucht haben das Programm mit `node main.ts` auszuführen, haben wir eine Fehlermeldung erhalten:
```
/home/michael/Schreibtisch/Labor/Voruebung/main.ts:2
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

Um diesen Fehler zu beheben haben wir mit dem Node Package Manager das **TypeScript** Paket installiert.  
Dazu muss in der Konsole folgender Befehl eingegeben werden: `npm install typescript`.  
Das Programm `main.ts` kann nun mit dem Befehl `./node_modules/typescript/bin/tsc main.ts` zur Datei `main.js` transpiliert werden.  
Das Ausführen der Datei `main.js` ergibt folgende Ausgabe in der Konsole:
```
Hallo 270
```
Die Transpilierung war erfolgreich.

## package.json
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
Wir haben festgestellt, dass das ausführbare Programm ein Abhängigkeit von TypeScript hat. Allerdings ist das nicht ganz richtig, da nur der Entwickler Typescript benötigt um das Programm ändern zu können. Der Endverbraucher der das asuführbare Programm benutzt wird TypeScript nicht benötigen. Damit der Endverbraucher also keine unnötigen Pakete downloaden muss,haben wir folgende Maßnahmen getroffen:  
* Entfernen des TypeScript-Pakets mit `npm rm typescript`
* Neu installieren von TypeScript mit Zusatz `npm install --save-dev typescript`

Ein erneuter Blick in die Datei `package.json` ergibt:
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
Es wurde ein neuer Eintrag "devDependencies" erstellt. Dieser Eintrag ermöglicht es, dass das TypeScript-Paket nur mehr dann installiert wird, wenn der Benutzer Änderungen an der Datei vornehmen möchte.

Um nun eine Abhängigkeit für nen Endverbraucher einzubauen haben wir das Paket `sprintf` installiert. Das haben wir folgenden Befehl verwendet: `npm install sprintf-js`.  
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
