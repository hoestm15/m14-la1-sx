# Protokoll
  Böcksteiner Jakob  
  5AHME, Gruppe 1  
  26.11.18  
  Anwesend: Berger, Böcksteiner, Ehmann, Enzi, Kobor, Köhler, Knappitsch  
  Abwesend: Bullner  
  
## Visual Studio Code
### Allgemeines  
Visual Studio Code ist ein plattformunabhängiger Quelltext-Editor von Microsoft, der viele verschiedene Programmiersprachen unterstützt (C, C++, HTML, Java, Javascript, TypeScript, ...). Es lässt sich zwar wie jede andere Applikation öffnen, aber man kann auch komfortabel über den Konsolenbefehl `code` einsteigen. Mit `code .` gelangt man direkt in das aktuelle Projektverzeichnis.  
  
### Schnellstartleiste  
Die Schnellstartleiste in VS Code beinhaltet einen Dateiexplorer, eine Suchfunktion, eine Versionsverwaltung, einen Punkt, um in den Debug-Mode zu gelangen und die Möglichkeit, externe Plug-ins einzufügen. 
Wenn man im Dateiexplorer eine Datei mit einem einfachen Mausklick öffnet, dann wird der Dateiname kursiv dargestellt. Klickt man nun auf eine andere Datei, verschwindet der Tab der ersteren. Mit einem Doppelklick öffnet man Dateien dauerhaft.  
  
### Dateiexplorer übersichtlicher gestalten  
Um den Dateiexplorer übersichtlicher zu gestalten, legt man im Projektverzeichnis einen neuen Ordner `.vscode` an. In diesem Ordner erstellt man die Datei `settings.json`. Dort kann man alle für die Programmierung irrelevanten Dateien ausblenden lassen.

```
"files.exclude": {
		"**/node_modules/": true,
		"**/.vscode/": true,
		"**/package-lock.json": true
	}
```
  
### TSC konfigurieren  
Die Konfiguration des TypeScript-Compilers findet in der Datei `tsconfig.json` statt:  
```TypeScript
{
    "compilerOptions": {
        "module": "commonjs",
        "noImplicitAny": true,
        "removeComments": true,
        "preserveConstEnums": true,
        "sourceMap": true,
        "target": "es2017"
    },
    
    "include": [
        "**/*.ts"
    ]
}
```
In dieser Datei können Einstellungen für den Compiler getroffen werden. Beispielsweise kann man die Sprache, in die der Compiler transpilieren soll, einstellen. Der Compiler lässt sich in der Konsole mit `node node_modules/typescript/bin/tsc/ -p tsconfig.json` starten.  
