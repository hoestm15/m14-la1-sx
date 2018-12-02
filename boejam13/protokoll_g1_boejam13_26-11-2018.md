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
{
	"files.exclude": {
	    "**/node_modules": true,
	    "**/dist": true,
	    "package-lock.json": true,
	    ".vscode": true
	}
}
```
  
### Lint
Lint ist dazu da, dass man eine Schönere formatierung hat, es zeigt Fehler an wie zb das man ein Leerzeichen zu viel hat. Die Datei tslint.json beschreibt welche Fehler gemeldet werden und welche nicht.

## Projekt Rest-Server


