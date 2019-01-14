# Protokoll der 1. Einheit

## 1. Einheit

* Name: Mario Nabernik  
* Klasse: 5AHME  
* Datum 07.01.2019 
* Gruppe: 2  
* Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Mario Nabernik, Muri Lorenz, Platzer Andreas, Martinak Moritz
* Abwesend: -
* Thema: Transpilieren/Kompilieren

# Kompilieren  
Kompilieren heißt einen Quellcode in eine anwendbare Programmiersprache zu übersetzen, sodass etwa ein Computer den Code ausführen kann. Ein Programm wird mithilfe eines Compilers übersetzt. Es gibt Bau-Pakete, die sowohl den Quellcode eines Programms als auch den notwendigen Compiler beinhalten, um Nutzern das Kompilieren des Codes in eine ausführbare Datei zu erleichtern.

# Transpilieren  
Beim Vorgang des Transpilierens wird ein Code einer Sprache in eine andere Sprache Übersetzt. Ein Beispiel hierführ ist die Übersetzung von Typescript zu Javascript.

# Wiederholung JSON
JSON ist die Abkürzung für **JavaScript Object Notation** und ist ein kompaktes Datenformat in einer einfach lesbaren Textform zum Zweck des Datenaustauschs zwischen Anwendungen
 [Quelle: Wikipedia, JSON](https://de.wikipedia.org/wiki/JavaScript_Object_Notation)

## Datentypen

* Nullwert `null`
* Boolscher Wert `true` oder `false`
* Zahlenfolge von `0`-`9` welche mit `+` und `-` vorzeichenbehaftet betrachtet werden können und durch einen Dezimalpunkt `.` unterbrochen sein können
* Zeichenketten beginnen mit einem doppelten Anführungszeichen `"`
* Arrays beginnen mit `[` und enden mit `]`
* Objekte beginnen mit `{` und enden mit `}`
* Eigenschaften von Objekten sind folgendermaßen aufgebaut: `Schlüssel:Wert`

# Einrichten von Visual Studio Code

## settings.json
Die Datei settings.json befindet sich im .vscode Ordner. Diese Datei verwenden wir dazu, gezielt Dateien in unsere Programmierumgebung Ein- oder Auszublenden.

*Inhalt:*
```
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

## tslint.json
TSlint hilft dem Programmierer einen Programmierstil einzuhalten und selbst zu beeinflussen, da man damit eine Art Formatvorlage erstellen kann. TSlint weist den Programmierer mit Hilfe von Warnungen auf dieses Warnsignal hin und hilft einen durchgängigen Programmierstil einzuhalten.

## Tasks
Um externe Programme zum Kompilieren oder für andere Aufgaben verwenden zu können, stellt VS Code das Konzept von Tasks zur Verfügung. Dabei kann ein Programm konfiguriert werden, welches sich dann mit verschiedenen Aufgaben (Tasks) beauftragen lässt.
Mit Hilfe von Tasks wird der Transpiliervorgang für die IDE automatisiert. Um diesen Vorgang zu realisieren gibt es Tasks. In diesen Tasks ist definiert was beim Builden, Cleanen etc. zu tun ist. Wir verwenden [gulp](https://de.wikipedia.org/wiki/Gulp.js).

```js
gulp.task('build', function (done) {
    console.log("Task build gestartet");
    sequence('transpile', 'copyFiles', () => {
        console.log(finalMessage);
    });
});
```

## Markdown in VS
Es ist möglich in Visual Studio mit Markdown Dateien zu arbeiten. Dies ermöglicht eine einfache Art und Weise der Dokumentation.
Siehe auch:  [Protokoll 31-10-17](https://github.com/HTLMechatronics/m14-la1-sx/blob/nabmam14/Protokoll/Protokoll_31-10-17.md)

# Übungen in der 2.Einheit
Wir haben ein Projekt mit dem **Node Package Manager** - Projekt erstellen. `npm init` Pakete werden installiert. Dafür wird die Datei `package.json` verwendet, welche mit `npm init` erzeugt wurde.


Erstellen von `main.ts`
```js
console.log('Hallo');
```  
 Mit dem Konsolenbefehl `node main.ts` führten wir unser Programm aus. Dies war möglich, da wir noch keine TypeScript spezifischen Ausdrücke verwendeten.
 
 Wir erweitern unser Programm mit Typescript spezifischen Ausdrücken:
```js
const x = 27;
let y: number;

y=10*x;

console.log('Hallo', y);
```  

Mit dem Befehl `node main.ts` erhalten wir eine Fehlermeldung, da das Programm noch nicht **transpiliert** wurde.

```
/home/mario/Schreibtisch/lab/g2/main.ts:2
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

Richtige Ausgabe:
```
Hallo 270
```

## package.json

Um die Handhabung mit unserem Programm einfacher zu gestalten und um das Downloaden unnötiger Pakete auszuschließen treffen wir in `package.json` einige Maßnahmen.

* Entfernen des TypeScript-Pakets mit `npm rm typescript`
* Neu installieren von TypeScript mit Zusatz `npm install --save-dev typescript`
* Installieren von sprintf

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

Entstandene Änderungen:

`devDependencie` - Dieser Eintrag ermöglicht es, dass das TypeScript-Paket nur mehr dann installiert wird, wenn der Benutzer Änderungen an der Datei vornehmen möcht
`sprintf-js": "^1.1.` unter dependencies - Abhängigkeit für den Endverbraucher


Erneutes testen von `main.ts`
```js
import { sprintf } from 'sprintf-js';

const x = 27;
let y: number;

y=10*x;

console.log('Hallo', sprintf('%.02f', y));
```

Die Datei `main.ts` wurde nun in die Datei `main.js` transpiliert.

Ausführen von `main.js`:
```
Hallo 270.00
```
