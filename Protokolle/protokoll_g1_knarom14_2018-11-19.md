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
* **1.1:** Der zusätzlichen Headereintrag(Keepalive) ermöglicht das Wiederverwenden der Verbindung.

## Übung
Mit dem Tool **nc**(netcat) haben wir einen Server über localhost gestartet und mit einem Web-Browser darauf zugegriffen.
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



