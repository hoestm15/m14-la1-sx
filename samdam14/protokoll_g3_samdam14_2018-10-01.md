# _Protokoll Zweite Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 10.01.2018**  
**Uhrzeit: 8:00-10:30**  
  
**Anwesenheit: _Es waren alle Schüler anwesend_**  
  
**Thema: Typescript / Visual Studio Code**  
  
-----------------------------------------------------------
  
### Server in Java und Node.js  
In Node.js gibt es die Klassen HTTP und HTTPS, aber diese sind in der Anwendung eher unbequem umständlich. Aufgrunddessen kommt bei uns das Tool *Express* zum Einsatz. Express ermöglicht eine im Vergleich leichte Anwendung beider Protokolle, HTTP und HTTPS. Damit dieses Tool funktioniert, muss es am Entwicklungsrechner und am Zielsystem installiert sein. Express steht deswegen in der Datei package.json in den *Dependencies*.  
In Java ist die Realisierung eines Servers einfacher. Es gibt ausprogrammierte Klassen, wie z.B. ServerSocket, welche einfach als Bibliothek eingebunden werden können.  

### Gibt es noch Anwendungen, in denen man in einem Netzwerk auf Verschlüsselungen verzichtet?  
Ja!  
![](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/http%20Anwendung.PNG)  
Der Client schickt eine Anfrage an die Domain eines Unternehmen, verschlüsselt mittels https. Die Firewall erhält die Anfrage zuerst und leitet sie verschlüsselt an einen Web-Server. Dieser erkennt, dass er die Request wieder weiterleiten muss und sendet sie aber nun unverschlüsselt an den Ziel-Rechner. Das diese Übertragung unverschlüsselt stattfinden kann, kann unterschiedliche Gründe haben. Die Häufigste aber ist, dass sich die beiden Geräte örtlich nicht weit voneinander entfernt liegen.  

## Visual Studio Code  
![VS Code](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/VS%20Code.png)  
#### Allgemeines  
Visual Studio Code ist ein plattformunabhängiger Quelltext-Editor von Microsoft, der viele verschiedene Programmiersprachen unterstützt (C, C++, HTML, Java, Javascript, TypeScript, ...). Es lässt sich zwar wie jede andere Applikation öffnen, aber man kann auch komfortabel über den Konsolenbefehl `code` einsteigen. Mit `code .` gelangt man direkt in das aktuelle Projektverzeichnis.  
  
#### Schnellstartleiste  
Die Schnellstartleiste in VS Code beinhaltet einen Dateiexplorer, eine Suchfunktion, eine Versionsverwaltung, einen Punkt, um in den Debug-Mode zu gelangen und die Möglichkeit, externe Plug-ins einzufügen. Externe Plug-ins können dazu führen, dass das komplette System lahm gelegt wird. Um diese Problemzone zu umgehen, kann man den geschriebenen Code auch ohne Verwendung der Plug-ins starten.  
Wenn man im Dateiexplorer eine Datei mit einem einfachen Mausklick öffnet, dann wird der Dateiname kursiv dargestellt. Klickt man nun auf eine andere Datei, verschwindet der Tab der ersteren. Mit einem Doppelklick öffnet man Dateien dauerhaft.  
![Schnellstartleiste](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/startleiste.jpg)  
