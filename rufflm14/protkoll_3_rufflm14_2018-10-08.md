# 3. Laborprotokoll 

*von Florian Ruffenacht*

Datum: 08.10.2018 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

## Überblick über die verwendeten Tools zur Progrmmierung des Rest-Servers
Um den Rest-Server in Typescript angenehm progrmmieren zu können, wurden die folgenden Tools verwendet bzw. Dateien erstellt.

### TSLint-tool
Dieses Plug-in unterstützt den Programmierer bei der übersichtlichen und optisch anprechenden Gestaltung seines Codes. In der Datei 
**tslint.json** können Einstellungen am tool, wie zum Beispiel die maximal an Zeichen in einer Zeile, vorganommen werden:
```json
"max-line-length": [
            true,
            140  
```
[Weitere Informationenen zum TSLint-Tool](https://www.npmjs.com/package/tslint)
### gulp-tool
Während es in den Programmieresprachen C, Java und Java mit für Android mit [make](https://de.wikipedia.org/wiki/Make), [javac](https://docs.oracle.com/javase/7/docs/technotes/tools/windows/javac.html) und [gradel](https://gradle.org/) sehr weit verbreitete Übersetzungstools gibt, stehen einem Javascript-Programmierer mehrere tools wie zum Beispiel [grunt](https://gruntjs.com/) oder eben [gulp](https://gulpjs.com/) zur Verfügung. Wir verwenden gulp, welches sich über die Datei **gulpfile.js** steuern lässt.

### tsconfig.json
Hier lassen sich Einstellungen beim Übersetzungsvorgang mit dem **tsc**, auf dem auch das gulp-tool aufbaut, verändern. Die Datei sieht folgendermaßen aus:
```json
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

### settings.json
Diese Datei im **.vscode**-Ordner kann dazu verwendet werden, gewisse Dateien in Visual Studio Code auszublenden:

```json

