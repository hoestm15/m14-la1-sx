# Protokoll 2: Java Server
Name: Patrick Schuster  
Klasse: 5AHME  
Gruppe: 3    
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: -

# Visual Studio Code
## Informationen zu Code
Visual Studio Code ist eine Programmierumgebung der Firma Microsoft und ist plattformübergreifend verfügbar. 
Es ist Open-Source, basiert auf dem Framework ELectron und hat Funktionen wie z.B. Syntaxvorhebung, Debugging, Autovervollständigung und Versionsverwaltung. 
Es werden Sprachen wie C++, CSS, HTML, Java, PHP, SQL, Typescript, etc. unterstützt und durch Plug-ins kann die Programmierumgebung beliebig erweitert werden.
Trotz des Namens hat Visual Studio Code nicht viel mit Visual Studio zu tun. Beide sind von der Firma Microsoft, 
werden aber von unterschiedlichen Teams entwickelt und folgen einer anderen Philosophie. Ein großer Unterschied in der Handhabung der Projekte
zwischen den VS und VS Code besteht darin, dass VS Code nicht mit Projektdateien sondern mit Quelltextdateien und Ordnern arbeitet.  
[Website von VS Code](https://code.visualstudio.com/)
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
### tsconfig.json
In dieser Datei werden die Optionen für den Compiler/Transpiler (TSC) angegeben.
```json 
{
    "compilerOptions": {
        "module": "commonjs",
        "noImplicitAny": true,
        "removeComments": true,
        "preserveConstEnums": true,
        "sourceMap": true,
        "target": "es2017",
        //"typeRoots": [
        //    "node_modules/@types"
        //]
           

    },
        "include": [
            "**/*.ts"
        ],
}  
```
**Bemerkung:** Die auskommentierten Zeilen werden vom Syntax Highlighting rot markiert, 
da *.json* Dateien eigentlich keine Kommentare vorsehen. Man kann diese aber trotzdem verwenden.

Option | Bedeutung  
---- | ---------  
module | spezifiziert die Code  Generation der Module  
noImplicitAny | gibt an ob eine Deklaration mit any einen Error erzeugen soll  
removeComments | gibt an ob Kommentare gelöscht werden sollen  
preserveConstEnums | gibt an das ConstEnums nicht gelöscht werden sollen 
sourceMap |   gibt an ob Map-Dateien generiert werden sollen
target | gibt an welche Version verwendet wird

# programm
