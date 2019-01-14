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
