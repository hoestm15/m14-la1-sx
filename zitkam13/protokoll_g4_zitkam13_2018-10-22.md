# 1.Protokoll
**Name:** Zitz Karlheinz   
**Datum:** 13.10.2018  
**Uhrzeit:** 8:00-10:30  
**Gruppe:** 4  
**Anwesend**: Strauß Lukas,Strutz Sebastian, Tuttner Raphael, Uhl Christan, Wieser Markus, Zitz Karlheinz  
**Abwesend**: Waltl Kilian  

# Dateien im Projektordner  
Am Beginn der Einheit besprachen wir alle einzelnen Dateien in unserem Projektordner.
Im Projektordner befinden sich weitere 4 Ordner. Die Ordner lauten:  
  
* dist   
Hier befinden sich alle die transpilierten Programmen. Das heißt die von TypeScript umgewandet wurden in           JavaScript. 

* node_Modules   
Hier befinden sich alle Packete, welche das Programm für die Ausführung benötigt. 

* src   
Hier befinden sich alle TypeScript Dateien. 

* .vscode  
In diesem Ordner findet man alle Dateien die nicht angezeigt werden. Deswegen beginnt der Dateiname mit                  einem Punkt.  

### .vscode
Im Ordner **.vscode** gibt es noch 4 Dateien die sogenannten **Steuerdateien** für Visual Studio Code.
* keybindings.json:  
In dieser Datei können Tastenkombinationen für Aktivitäten (z:B. Build) im Programm erstellt werden.  
* launch.json:  
Die Datei **launch.json** legt fest wie ein Program gestartet werden soll.  
* settings.json  
In dieser Datei stehen alle Dateien die Bei VSCode nicht im Dateiexplorer angezeigt werden sollen. Bei unserem Program ist es zum Beispiel:  
```
{
	"files.exclude": {
		"**/node_modules": true,
		"**/.vscode/": true,
		"**/package-lock.json": true
		"**/dist/": true 
	}
}
```  
* tasks.json  

### package.json
Eine weitere wichtige Datei ist die **package.json** Datei. In dieser Dtei stehen alle Projektinformationen und deren Abhängigkeiten. Wie zum Beispiel:  
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
  "author": "Karlheinz Zitz",
  "private": true,
  "license": "MIT",
  "dependencies": {
    "body-parser": "^1.18.3",
    "express": "^4.16.3"
  },
  "devDependencies": {
    "@types/body-parser": "^1.17.0",
    "@types/express": "^4.16.0",
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
Mit dem Shel-Kommando **npm install** schaut der Node Package Manager in diese **package.json** und installiert danach alle Pakete die er für die Ausführung des Programs benötigt. Die benötigten Pakete stehen bei **devDependencies**.  

### gulpfile.js  
Die Datei **gulpfile.js** steuert die Übersetzung mit dem Übersetzungstool **gulp**  
Dabei gibt es 2 Möglichkeiten um **gulp** zu installieren.  
* Lokale Installation: node_modules/gulp/bin/gulp.js  
* Globale Installation: sudo npm install -g gulp  
Das **-g** nach npm install steht für eine **globale INstallation**.  
Damit man **gulp** updaten kann benötigt man statt dem Schlüsselwort **install** das SChlüsselwort **update**. Der Berfehl lautet daher danach **sudo npm update -g gulp**.  

### tsconfig.json  
In der Datei **tsconfig.json** befindet sich die Konfiguration für den Transpieler. Der Transpieler transpeliert eine TypeScript Datei in eine JavaScript Datei.  
In unseren Beispiel sieht diese Datei folgendermaßen aus:  
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

### tslint  
Tslint is ein Tool, welches während des codieren auf die Schönheit des programmierten Codes achtet. Damit Tslint funktioniert benötigt es die Datei **tslint.json**.  

