# 3.Protokoll  
  
  **Name**:  *Sackl Roland*  
  **Datum:** *01.10.2018*  
  **Uhrzeit:** *8:00-10:30*  
  **Gruppe:** *3*  
  
  **Abwesend:** Schmuck Martin  
  **Anwesend:**   Sackl Martin, Sackl Roland, Reinbacher Bernhard,Sammer Daniel,Ruffennacht Florian,Schuster Patrick
   

## Übersetzungstools  
Es gibt je nach Programmiersprache andere Anforderungen an den Compiler:

Typescript | Java | Java(unter Android) | C  
---------- | ---- | ------------------- | -  
Gulp | javac | gradle | make   
gulp | javac | gradle | make  

## Konfigurartionsdateien  

### tslint.json   
Durch diesen Plug-in wird der Programmierer bei der optisch anprechenden Gestaltung seines Codes unterstüzt.   In der Datei können verschidene Einstellungen am tool vorgenommemn werden.  
Ein Beispiel: Die maximale Anzahl an Zeichen in einer Zeile.

```javascript  
"max-line-length": [
            true,
            140  
```  


### tsconfig.json
Hier werden die Einstellungen beim Übersetzungsvorgang mit dem **tsc** gesteuert und gespeichert. 
Die Datei sieht folgendermaßen aus:
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
 In der Datei im **.vscode**-Ordner wird zum Ausblenden von unerwünschten Dateien in der Programmierumgebung verwendet. Außerdem kann es auch während des Programmierens gesehen.

```json
{
        "files.exclude": {
                "**/node_modules": true,
                "**/.vscode": true,
                "**/package-lock.json": true,
                "**/gulpfile.js" : true,
                "**tslint.json": true,
                "**/dist": true,
                "**/tsconfig.json": true
        }
}
```





### task.json
Die Taks im Quelltextmanager, die sich ebenfalls im **.vscode**-Ordner befinden, werden mit denen des gulp-tools verknüpft.  

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "command": "gulp",
            "type": "shell",
            "args": [
                "--gulpfile",
                "gulpfile.js",
                "build"
            ],
            "group": "build",
```



### launch.json
In der Datei launch.json im **.vscode**-Ordner definiert die Einstellungen beim Debuggen.

```
{
    "version": "0.2.0",
    "configurations": [

        {
            "type": "node",
            "request": "launch",
            "name": "Launch Program",
            "program": "${workspaceRoot}/src/main.ts",
            "cwd": "${workspaceRoot}/dist",
            "console": "integratedTerminal",
            "outFiles": [ "${workspaceRoot}/dist/*.js" ],
            //"trace": "all",
            "sourceMaps": true,
            "preLaunchTask": "build",
            "smartStep": true
        }
    ]
}  
```
