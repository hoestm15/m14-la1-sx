# Protokoll
Gerhard Mandl 
5AHME, Gruppe 2  
17.12.18  
Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Mario Nabernik, Muri Lorenz, Platzer Andreas  
Abwesend: Moritz Martinak  

# REST-Serverü
__REST__ steht für REpresentational State Transfer. Gemeint ist damit eine Programmierschnittstelle, die sich an den Paradigmen
und Verhalten des Word Wide Web (WWW) orientier und einen Ansatz für die Kommunikation zwischen Client und Server in Netzwerken
beschreibt.  
Das verwendete Übertragungsprotokoll ist HTTP.  

Für genaueres klicken Sie bitte hier.

# HTTP

Der Begriff __HTTP__ steht für Hypertext Transfer Protokoll, das HTTP ist eine Sprache, welche bei der Kommunikation zwischen
zb. einem Client und einem Webserver verwendet wird.
Meistens wird verwechselt, dass als Sprache HTML verwendet wird. Jedoch ist HTML keine Sprache sondern nur eine Codierungsform.
Zudem ist HTTP ein zustandsloses Protkoll, darunter versteht man, dass Informationen aus früheren Anwendungen verloren gehen.
Die Daten werden textuel übertragen und sind nicht verschlüsselt. Für das verschlüsselte Übertragen von Daten gibt es das HTTPS.

### __Funktionsprinzip__:  

![](https://github.com/HTLMechatronics/m14-5ahme-fivu/blob/mangem13/ServerClient.png)

__Kurz zusammenfgefasst__:Der Client schickt dem Server eine Anfrage (z.B. mit der Funktion GET), der Server bearbeitet diese und schickt eine Response zurück.
Dies tut er auch wenn er die Anfrage nicht verarbeiten kann.

__Genauere beschreibung__: Zuerst wird vom Client ein __SYN__-Paket an den Server geschickt, damit signalisiert er das er eine Verbindung aufbauen möchte. Der Server bestätigt das __SYN__-Paket mit einem __ACK__-Paket und schickt dieses an den Client. Der Client bestätigt das Empfangen des __ACK__-Paket mit einem weitern __ACK__-Paket, sobald dieses vom Server empfangen wird wurde eine Verbindung aufgebaut.

Normalerweise werden die Kommunikationen sobald nicht gesendet wird nach einer gewissen Dauer geschlossen um dies zu verhindern wird ein Attribut das __Keep-Alive__ im Header es HTTP-Pakets eingebunden.

__Wie wird die Verbindung geschlossen?__

Wenn einer der Verbindungsteilnehmer die Verbindung beenden möchte, schickt dieser ein __FIN__-Paket. Der andere Teilnehmer 
bestätigt diese Anfage mit einem __FIN-ACK__-Paket dadurch wird die Verbindung geschlossen.

### __Wichtige Funktionen:__  

| __Funktion__      | __Beschreibung__  |
| ------------- |-------------- |
| GET           | Listen/Daten anfragen |
| POST          | Daten verändern       |
| PUT           | Neue Daten anlegen    |
| DELETE        | Daten löschen         |

__Anmerkung:__ Es gibt noch weitere Funktionen jedoch sind die oben genannenten, jene die für uns relevant sind.

Für näheres zu HTTP klicke [hier](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)
