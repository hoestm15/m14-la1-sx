# Protokoll: Knappitsch Robert
## 1. Einheit: REST-Server

* 5AHME (Gruppe 1)
* 19.11.2018
* Anwesend: Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Knappitsch Robert, Kobor Markus, Köhler Marcel
* Abwesend: -

## REST-Server (Representational State Transfer)

> Representational State Transfer (abgekürzt REST, seltener auch ReST) bezeichnet ein Programmierparadigma für verteilte Systeme, insbesondere für Webservices. REST ist eine Abstraktion der Struktur und des Verhaltens des World Wide Web. REST hat das Ziel, einen Architekturstil zu schaffen, der die Anforderungen des modernen Web besser darstellt. Dabei unterscheidet sich REST vor allem in der Forderung nach einer einheitlichen Schnittstelle (siehe Abschnitt Prinzipien) von anderen Architekturstilen. Der Zweck von REST liegt schwerpunktmäßig auf der Maschine-zu-Maschine-Kommunikation.

* Hauptanwendung: Maschine-zu-Maschine-Kommunikation
* Kommunikation über HTTP


[Quelle: Wikipedia - Representational State Transfer](https://de.wikipedia.org/wiki/Representational_State_Transfer)

## HTTP (Hypertext Transfer Protocol)
> Das Hypertext Transfer Protocol (HTTP, englisch für Hypertext-Übertragungsprotokoll) ist ein zustandsloses Protokoll zur Übertragung von Daten auf der Anwendungsschicht über ein Rechnernetz. Es wird hauptsächlich eingesetzt, um Webseiten (Hypertext-Dokumente) aus dem World Wide Web (WWW) in einen Webbrowser zu laden.

[Quelle: Wikipedia - Hypertext Transfer Protocol](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)

### Funktionsweise: 
* Request-Response System (Server <-> Client)
### Verbindungsaufbau: 
* Client: SYN-Paket (Anfrage an den Server zum Verbindungsaufbau)
* Server: SYN/ACK-Paket (Antwort des Servers an Client nach Erhalt des SYN-Pakets)
* Client: ACK-Paket (Antwort des Clients an den Server, danach ist die Verbindung aufgebaut)
### Paketaufbau:
* Header (Nachrichtenkopf): Informationen über Body z.B.: verwendete Kodierung, Inhaltstyp, ...
* Body (Nachrichtenrumpf): eigentliche Nutzdaten
#### HTTP - Requests:
**Anfrage** | **Beschreibung**
---|---
GET | Ressource(z.B. Datei) vom Server anfordern
POST | schickt Daten zur weiteren Verarbeitung an den Server
PUT | hochladen einer Ressource auf einen Webserver
DELETE | löscht die angegebene Resource auf dem Server

#### HTTP - Statuscodes:
**Code** | **Bedeutung**
---|---
1xx | Information: Bearbeitung der Anfrage dauert noch an. Dies wird bei manchen Clients benötigt, da es sonst zu einer Zeitüberschreitung kommt.
2xx | Erfolgreiche Operation: Anfrage wurde bearbeitet und die Antwort wird an den Anfragesteller zurückgesendet
3xx | Umleitung: Die gewünschte Datei befindet sich an einem anderen Platz.
4xx | Client-Fehler: z.B.: eine Datei wurde angefragt, die auf dem Server nicht existiert
5xx | Server-Fehler: z.B.: Server verfügt nicht über die notwendigen Funktionen um die Anfrage richtig zu bearbeiten

Zusätzlich zum Statuscode enthält der Header der Server-Antwort noch eine Beschreibung des Fehlers.
z.B.: 
```
HTTP/1.1 404 Not Found
…
```

### Unterschied zwischen HTTP/1.0 und HTTP/1.1
* **1.0:** Vor jeder Anfrage wird eine neue Verbindung aufgebaut und danach wieder vom Server geschlossen.
* **1.1:** Der zusätzlichen Headereintrag(Keepalive) ermöglicht das Wiederverwenden der Verbindung.N

## NC(netcat)
> Netcat, auch nc genannt, ist ein einfaches Werkzeug, um Daten von der Standardein- oder -ausgabe über Netzwerkverbindungen zu transportieren. Es arbeitet als Server oder Client mit den Protokollen TCP und UDP. Die Manpage bezeichnet es als TCP/IP swiss army knife (Schweizer Taschenmesser für TCP/IP).
[Quelle: Wikipedia - Netcat](https://de.wikipedia.org/wiki/Netcat)

## Übung
Mit dem Tool **nc** haben wir einen Server über localhost gestartet und mit einem Web-Browser darauf zugegriffen. 
* -l: legt fest, dass nc die Rolle des Servers übernehmen soll
* -C: ermöglicht das Lesen regulären Zeilenvorschub als Carriage Return (ansonsten wird die Antwort nach der ersten Zeile abgebrochen)
* 4711: Port
```
robert@robert-Aspire-E5-771G:~$ nc -l -C 4711
GET / HTTP/1.1
Host: localhost:4711
Connection: keep-alive
Purpose: prefetch
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
Accept-Encoding: gzip, deflate, br
Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7
```
Daraufhin haben wir vom Server eine Antwort gesendet, welche im Browser angezeigt wurde.
```
HTTP/1.1 200 OK
Server: Apache/1.3.29
Content length: 5
Content-Language: de 
Connection: close               
Content-Type: text/html

Hallo
```
Als nächstes bauten wir eine Verbindung zu [http://www.htl-mechatronik.at](http://www.htl-mechatronik.at/) aufgebaut.
```
robert@robert-Aspire-E5-771G:~$ nc -C www.htl-mechtronik.at 80
GET / HTTP/1.1
Host: www.htl-mechatronik.at:80
User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36
Accept: text/html
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: deflate
```
Vom Server haben wir folgende Antwort erhalten:
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


