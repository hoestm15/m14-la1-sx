# 1.Laborprotokoll 

*von Florian Ruffenacht*

Datum: 24.09.2018 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

Abwesend: -

## Warum ist HTTP noch relevant?
Der HTTP-Standard gilt allgemein als unsicher und wird überwiegend durch die verschlüsselte Weiternentwicklung HTTPs ersetzt. Doch in manchen Fällen wird ist HTTP durchaus präsent. Das soll das folgende Beispiel zeigen:

![HTTP in der Firewall](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/HttpInFirewall.svg)

Hier werden über das Internet Daten an einen Webserver übertragen. Die Datenübertragung läuft aber nur bis zum Proxy-Server verschlüsselt über HTTPs. In der Umgebung der Firewall, in der der Proxy-Server die Daten an den eigentlichen Server  vermittelt, läuft die Kommunikation nur über HTTP.


## Visual Studio Code
### Allgemeines
Der Quelltexteditor Visual Studio Code von Microsoft ist **plattformunabhängig** auf Windows, Linux und MacOS erhältlich. Es werden viele
Programmiersprachen wie C#, C++, CoffeeScript, F#, HTML, Ini, Java, JavaScript, Makefile, Markdown, Objective-C, Python, R, Ruby, SQL, 
Swift, TypeScript, Visual Basic und XML unterstützt. Visual Studio Code kann mit dem Konsolenbefehl ```code``` gestartet werden. Optional
kann das Programm mit ```code . ``` im Projektordner geöffnet werden, wobei man sich dann gleich im jeweiligen Projekt befindet. 

### Schnellstartleiste
Auf der unten ersichtlichen Abbildung ist die Schnellstartleiste von Code abgebildet. An oberster Stelle findet man den **Dateiexplorer**.
Es folgen die **Suchfunktion**, die **Versionsverwaltung**, der Menüpunkt für **Debugging** und der Menüpunkt für **externe Plug-ins**. 
Die stehen für Visual Studio Code zahlreich zur Verfügung, können den Quelltexteditor im schlimmsten Fall aber auch lahmlegen. Deswegen 
gibt es auch die Möglichkeit, Code ohne Plug-ins zu starten.

[Weitere Informationen zu Visual Studio Code](https://flaviocopes.com/vscode/)
