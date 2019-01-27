# 3. Protokoll  
**Name:** Sackl Martin  
**Klasse** 5ahme  
**Gruppe:** 3  

Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schuster   
Abwesend: Schmuck  
*******************************************************************************************************************************************  
# Übersetzungstools  
Um den Rest-Server programmieren zu können benötigt man ein Übersetzungstool. Es gibt verschiedene Tools da jede Programmiersprache andere Anforderungen an den Compiler sendet.  

Übersetzungstool | Sprache  
-----------------|-----------  
[javac](https://en.wikipedia.org/wiki/Javac) | Java  
[gradle](https://en.wikipedia.org/wiki/Gradle) | Java (Android)  
[gulp](https://de.wikipedia.org/wiki/Gulp.js) | Typescript  
[make](https://de.wikipedia.org/wiki/Make) | C  

# Dateien zum Konfigurieren  
### settings.json  
Mit dieser Datei kann die Prgrammierumgebung VS Code konfiguriert werden. Man kann bestimmte Verzeichnisse und Dateien ausblenden.  
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
### tslint.json  
Mit dieser Datei kann man das TSLint-Tool konfigurieren. Dieses Tool hilft dabei Fehler  und "Unschönheiten" zu markieren. Man kann z.B. auch die maximale Zeilenlänge festlegen.  
```json
"max-line-length": [
            true,
            140  
```  
