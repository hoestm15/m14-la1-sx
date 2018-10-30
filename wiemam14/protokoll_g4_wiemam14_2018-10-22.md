# *2. Laborprotokoll*

  Name: Markus Wieser   
  Klasse: 5AHME   
  Datum: 22.10.2018   
  Anwesend: Strauß Lukas, Strutz Sebastian, Tuttner Raphael, Uhl Christian, Wieser Markus, Zitz Karlheinz    
  Abwesend: Waltl Kilian

# Typescript

## Statuscodes

Ganz zu Beginn der Einheit haben wir noch einmal über Statuscodes gesprochen. Statuscodes sind diejenigen Codes, welche man von einem Server erhält.

Beginnt der Code z.B. mit der Zahl 2**, kann man von einer erfolgreichen Operation ausgehen.
Beginnt der Code jedoch mit der Zahl 4**, geht man von einem Client Fehler aus.

400 -> Bad Request

403 -> Forbidden (Mangelnde Berechtigung)

## Typescript Dateien

In der letzten Einhalt haben wir verschiedene Dateien vom Mechatronik-Server heruntergeladen

Die verschiedenen Dateien und ihre Anwendungszwecke:

* src: Ordner für die Quelltextdateien.

* .vscode: Ordner für die Konfigurationsdateien:

    * keybindings.json: Hier befinden sich verschiedene Tastenkombinationen, welche das Programmieren in der Entwicklungsumgebung erleichtern.
    
    * launch.json: Hier wird eingestellt, wie ein Programm gestartet wird.
    
    * settings.json:  Hier kann man verschiedene Einstellungen treffen wie z. B. node js ausblenden.
    
    * tasks.json: Hier wid Gulp aufgerufen.
    
* package.json: Projektinfos und Abhängigkeiten

* gulpfile.js: Hier steht die Steuerung der Übersetzung. (make in C, gradle in Android Studio, ant in Netbeans)

* tslint.json: Hier wird die Überprüfung für das gewünschte Design des Quelltextes bestimmt. (Vor allem in Firmen sehr wichtig)

* tsconfig.json:  Hier wird mit Hilfe eines Transpilers aus einer Typescriptdatei eine Javascriptdatei gemacht.

# Visual Studio Code

Visual Studio Code ist ein freier Quelltext-Editor von Microsoft. Außerdem ist er Plattformübergreifend verfügbar.

![Umgebung vs](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/umgebung_vs.png)  

## Visual Studio Code Icons

![Icons](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/Icons.png)


