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

# Übungsbeispiel
Zuerst haben wir folgende Befehlszeile in unsere Konsole eingegeben.  
`nc -C -l www.htl-mechatronik.at 80`
Mit diesem Befehl wird eine Verbindung zum HTL-Server in Arnfels hergestellt.  

Nachdem die Verbindung aufgebaut wurde, haben wir folgende Anfrage an den Server geschickt:
```
GET /infotext.html HTTP/1.1
Host: www.htl-mechatronik.at
Connection: keep-alive
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:57.0) Gecko/20100101 Firefox/57.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de-at
DNT: 1
Accept-Encoding: deflate
```
Der Server beantwortete unsere Anfrage folgendermaßen:  
```
HTTP/1.1 200 OK
Date: Mon, 19 Nov 2018 07:59:45 GMT
Server: Apache/2.4.7 (Ubuntu)
Last-Modified: Tue, 06 Jan 2015 08:13:36 GMT
ETag: "1e9-50bf76235166b"
Accept-Ranges: bytes
Content-Length: 489
Vary: Accept-Encoding
Content-Type: text/html

<html>
<head>
<META HTTP-EQUIV="CONTENT-TYPE" CONTENT="text/html; charset=utf-8">
<title>HTBLA Kaindorf Abteilung Mechatronik - Server Arnfels</title>
<body LANG="de-DE" DIR="LTR">
</head>
<h1>HTBLA Kaindorf<h1>
<h2> Abteilung Mechatronik - Server Arnfels</h2>
<p>
<!--
<IMG SRC="gif/under_construction.gif" NAME="Grafik1" ALIGN=LEFT WIDTH=404 HEIGHT=312 BORDER=0><BR><BR>
-->
<a href="http://www.htl-kaindorf.at/mechatronik">http://www.htl-kaindorf.at/mechatronik</a>
</p>
</body></html>
```
Wenn der Server eine Anfrage bekommt welche er nicht bearbeiten kann, wird folgende Antwort geschickt:
```
HTTP/1.1 400 Bad Request
Date: Sun, 25 Nov 2018 18:29:08 GMT
Server: Apache/2.4.7 (Ubuntu)
Content-Length: 313
Connection: close
Content-Type: text/html; charset=iso-8859-1

<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
<html><head>
<title>400 Bad Request</title>
</head><body>
<h1>Bad Request</h1>
<p>Your browser sent a request that this server could not understand.<br />
</p>
<hr>
<address>Apache/2.4.7 (Ubuntu) Server at www.htl-mechatronik.at Port 80</address>
</body></html>
```
# Typescript

### tsconfig.json
In der tscongi.json File werden Optionen festgelegt, die der Compiler benötigt um ein Projekt zu tanspilieren.
Beispielsweise kann man mit "outDir": "./dist" festlegen, dass Output-Dateien wie bei Netbeans im dist-Ordner zu finden sind, oder dass Input-Files für den Kompiler im Ordner src liegen. Transpilieren der .ts-Dateien über die tsconfig.json wird mit dem Command tsc -p tsconfig.json
Vorischt: tsc funktioniert nur, wenn man es global installiert: sudo npm install -g typescript, ansonsten muss man vor dem tsc-Command noch den Verzeichnis-Pfad angeben.

### tslint.json
Lint wird verwendet, damit wir freundlich dazu genötigt werden "schönen Code" zu produzieren. Die Datei tslint.json liegt im Hauptverzeichnis und man kann in ihr festlegen, welche "Fehler" gemeldet werden. (Zum Beispiel unnötige Leerzeichen oder fehlende Semicolons). Ohne diese Datei wird uns derartiges nicht angezeigt. Zusätzlich benötigen wir noch ein Plug-In, dazu aber unten mehr.
[Link zu unserer tslint.json](https://www.htl-mechatronik.at/gitweb/m14/?p=sx-fiv.git;a=blob;f=5AHME/ue02_typescript/tslint.json;h=22e9ee67d5a3869242de981362826f640b24dfc4;hb=d4e3db4405c8923aa35ddfccb370e1b2a51b74bc)
Wenn man vor einer Code-Sequenz im Programm einen Kommentar schreibt wie `//tslint: disable`, wird Lint für die folgenden Zeilen deaktiviert. Es ist auch Möglich einzelne Fehler zu deaktivieren.
