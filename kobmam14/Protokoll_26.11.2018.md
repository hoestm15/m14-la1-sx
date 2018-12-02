# Protokoll 26.11.2018

## 2. Einheit
## Thema: Erstellen eines REST-Servers
 
 Name: Markus Kobor  
 Klasse: 5AHME  
 Datum: 26.11.2018  
 Anwesend: Berger Emil, Böcksteiner Jakob, Ehmann Julian, Knappitsch Robert, Kobor Markus, Köhler Marcel <br>
 Abwesend: Bullner Jeremy <br> <br> <br>
 
 
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
#### package.json
Die package.json-Datei ist eine Art Manifest für ein Projekt. Es kann eine Menge Dinge tun, die völlig unabhängig voneinander sind. Es ist zum Beispiel ein zentrales Konfigurationsrepository für Tools. Dort werden auch die Namen und Versionen des installierten Pakets gespeichert.

```
{
  "name": "restserver1",
  "version": "0.0.1",
  "description": "Restserver",
  "main": "main.js",
  "scripts": {
    "start": "node dist/main.js",
    "build": "./node_modules/gulp/bin/gulp.js build",
    "clean": "./node_modules/gulp/bin/gulp.js clean",
    "cleanAndBuild": "./node_modules/gulp/bin/gulp.js cleanAndBuild",
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "Markus Kobor",
  "private": true,
  "license": "MIT",
  "dependencies": {},
  "devDependencies": {
    "del": "^3.0.0",
    "gulp": "^3.9.1",
    "gulp-changed": "^3.2.0",
    "gulp-sourcemaps": "^2.6.4",
    "gulp-typescript": "^5.0.0-alpha.3",
    "gulp-using": "^0.1.1",
    "merge-stream": "^1.0.1",
    "run-sequence": "^2.2.1",
    "tslint": "^5.11.0",
    "typescript": "^3.1.1"
  }
}
```

#### tsconfig.json
Die Datei tsconfig.json ist für die Konfiguration des TypeScript-Compilers zuständig.

```
{
    "compilerOptions": {
        "module": "commonjs",
        "noImplicitAny": true,
        "removeComments": true,
        "preserveConstEnums": true,
        "sourceMap": true,
        "target": "ES2016",
        "experimentalDecorators": true,
        "noEmitOnError": true,
        "mapRoot": "./",
        "outDir": "./dist",
        "typeRoots": [ "node_modules/@types" ]
    },
    "include": [ "src/**/*.ts" ]
}
```

#### gulpfile.json
Das gulpfile ist für die Übersetzung zuständig.

```
// Node.js modules
const path = require('path');

// External modules,
// npm install --save-dev gulp gulp-changed gulp-typescript gulp-sourcemapsgulp-using 
// npm install --save-dev typescript del run-sequence merge-stream
const gulp       = require('gulp'),
      changed    = require('gulp-changed'),
      ts         = require('gulp-typescript'),
      sourcemaps = require('gulp-sourcemaps'),
      using      = require('gulp-using'),
      typescript = require('typescript'),
      del        = require('del'),
      sequence   = require('run-sequence'),
      merge      = require('merge-stream');
      ...
```

#### tslint.json
TSLint ist ein erweiterbares statisches Analysewerkzeug, das TypeScript-Code auf Lesbarkeit, Wartbarkeit und Funktionsfehler überprüft. Es wird weitgehend von modernen Editoren und Build-Systemen unterstützt und kann mit Ihren eigenen Fusselregeln, Konfigurationen und Formatierungselementen angepasst werden.

```
{
    "rulesDirectory": [],
    "rules": {
        "callable-types": true,
        "class-name": true,
        "comment-format": [
            true,
            "check-space"
        ],
        "curly": true,
        "eofline": true,
        "forin": true,
        "import-blacklist": [
            true,
            "rxjs"
        ],
        ...

```


## Express 
Express ist eine Framework für das Arbeiten mit HTTP und HTTPS und bietet eine vielzahl von nützlichen Funktionen für das Gestalten von Webanwendungen.
