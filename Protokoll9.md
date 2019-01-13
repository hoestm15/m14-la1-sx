# Protokoll
Florian Nebel
5AHME, Gruppe 2  
07.Jänner.2019  
Anwesend: Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: ---

## Json
JSON (JavaScript Object Notation) ist ein Dateiformat, welches als Ersatz von XML gesehen werden kann. Es wurde entwickelt um 
leicht für den Menschen lesbar zu sein und wird daher im Bereich des Datenaustasches zwischen Programmen (z.B. Server-Client) 
verwendet.
  
### Textuelle Formatierung
Neben der verschachtelung von Daten ist es auch möglch Felder eines Datentyps zu erstellen.
Folgende Datentypen sind verfügbar:  
Datentyp | Beispiel  
--- | ---  
boolean | `true`  
number | `-7398.34`  
String | `Hallo!`  

* Datensätze werden durch Kommas voneinander getrennt.
* Ein Objekt wird durch geschwungene Klammern eingeschlossen.
* Die Daten die ein Array beinhaltet werden durch eckige Klammern eingeschlossen

#### Beispiel
```json
{"menu": {
  "id": "file",
  "value": "File",
  "popup": {
    "menuitem": [
      {"value": "New", "onclick": "CreateNewDoc()"},
      {"value": "Open", "onclick": "OpenDoc()"},
      {"value": "Close", "onclick": "CloseDoc()"}
    ]
  }
}}
```
siehe auch: [json.org](www.json.org)  


## VisualStudio Code
Visual Studio Code ist eine Entwicklungsumgebung, welche sich im Besitz von Microsoft befindet. Dieses plattformunabhängige 
Programm wird zum entwickeln von **Typescript**-Programmen verwendet. Typescript ist ein JavaScript-Dialekt der sich dadurch 
auszeichnet, dass jeder Variable selbst ein Datentyp zugewießen wird, ohne dass er vom Programmierer festgelegt wird. Um den
Quellcode ausführen zu können muss dieser in ausführbaren JavaScript-Code transpiliert werden.

### Transpilieren
Transpilieren bedeutet, dass der Quellcode in einen ausführbaren Code umgewandelt wird. Beim Compilieren hingegen wird der 
Quellcode in ein anderes Abstraktionslevel umgewandelt, wie z.B. bei C, wo der Quellcode in Maschinenbefehle umgewandelt wird.  
siehe auch: [Steve Fenton](https://www.stevefenton.co.uk/2012/11/compiling-vs-transpiling/)

### Setup
Um mit VisualStudio Code einfach Arbeiten zu können, wurden einige Anpassungen vorgenommen.  

#### settings.json
Im Verzeichnis `.vscode` wurde die Datei settings.json abgelegt, in welcher alle Dateien und Verzeichnisse vermerkt wurden, welche
nicht im Verzeichnisbaum der Programmieroberfläche aufscheinen sollen.
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

### Task
In einem Task wird wird festgelegt was beim Aufruf der Funktionen Clean, Build usw. passieren soll. Dadurch kann der 
Transpiliervorgang automatisiert werden. In unserem Fall findet gulp.js Verwendung.

### Markdown in VisualStudio Code
In dieser Entwicklungsumgebung ist es möglich zur Dokumentation Markdown-Dateien zu erstellen, welche interpretiert und dargestellt 
werden.

## Übungen
### TypeScript
Nachdem wir mit Node Package Manager ein Projekt erstellt hatten, (`npm init`) legten wir die Datei `main.ts`an.  
```js
console.log('Hallo');
```  
Mittels `node main.ts` konnten wir die Datei ausführen. Wären im Quellcode Elemente aus TypeScript verwendet worden wäre das 
Ausführen nicht möglich gewesen.  
  
Um den folgenden Quellcode transpilieren zu können mussten wird das Paket **TypeScript** installieren.
```js
const x = 45;
let y: number;

y=10*x;

console.log('Hallo', y);
```  
### package.json
```json
{
  "name": "voruebung",
  "version": "1.0.0",
  "description": "voruebung",
  "main": "main.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "Florian Nebel",
  "license": "MIT",
  "dependencies": {
    "typescript": "^3.0.5"
  }
}
```
Durch das Entfernen der Abhängigkeit zu TypeScript durch löschen vom System ist das Programm auch für den Benutzer ausführbar. 
Dieser benötigt Typescript nicht und muss keine Pakete herunterladen, welche nur zur Entwicklung notwendig sind.
  
Im nächsten Schritt wurde das Paket `sprintf` installiert, welches es ermöglicht formatierte Bildschirmausgaben darzustellen.
```js
import { sprintf } from 'sprintf-js';

const x = 45;
let y: number;

y=10*x;

console.log('Hallo', sprintf('%.02f', y));
```
  
Resultat:
```
Hallo 450.00
```
