# _Protokoll Zweite Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 10.01.2018**  
**Uhrzeit: 8:00-10:30**  
  
**Anwesenheit: _Es waren alle Schüler anwesend_**  
  
**Thema: Typescript / Visual Studio Code**  
  
-----------------------------------------------------------
  
### Server in Java und Node.js  
In Node.js gibt es die Klassen http und https, aber diese sind in der Anwendung eher unbequemm umständlich. Aufgrunddessen kommt bei uns das Tool *Express* zum Einsatz. Express ermöglicht eine im Vergleich leichte Anwendung beider Protokolle, http und https. Damit dieses Tool funktioniert, muss es am Entwicklungsrechner und am Zielsystem installiert sein. Express steht deswegen in der Datei package.json in den *Dependencies*.  
In Java ist die Realisierung eines Servers einfacher. Es gibt z.B. die ausprogrammierte Klasse ServerSocket, welche einfach als Bibliothek eingebunden werden können.  

### Gibt es noch Anwendungen, in denen man in einem Netzwerk auf Verschlüsselungen verzichtet?  
JA!  
![Use-Case http-Technologie]()  
Der Client schickt eine Anfrage an die Domain eines Unternehmen, verschlüsselt mittels https. Die Firewall erhält die Anfrage zuerst und leitet sie verschlüsselt an einen Web-Server. Dieser erkennt, dass er die Request wieder weiterleiten muss und sendet sie aber nun unverschlüsselt an den Ziel-Rechner. Das diese Übertragung unverschlüsselt stattfinden kann, kann unterschiedliche Gründe haben. Die Häufigste aber ist, dass sich die beiden Geräte örtlich nicht weit voneinander entfernt liegen.  

