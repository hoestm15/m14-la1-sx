# Protokoll 19.11.2018

## 1. Einheit
## Thema: REST-Server
 
 Name: Markus Kobor  
 Klasse: 5AHME  
 Datum: 19.11.2018  
 Anwesend: Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Knappitsch Robert, Kobor Markus <br>
 Abwesend: Niemand <br> <br> <br>
 
## Was ist ein REST-Server?

>Representational State Transfer (abgekürzt REST) bezeichnet ein Programmierparadigma für verteilte Systeme, insbesondere für Webservices. REST ist eine Abstraktion der Struktur und des Verhaltens des World Wide Web. REST hat das Ziel, einen Architekturstil zu schaffen, der die Anforderungen des modernen Web besser darstellt. Dabei unterscheidet sich REST vor allem in der Forderung nach einer einheitlichen Schnittstelle von anderen Architekturstilen.

>Der Zweck von REST liegt schwerpunktmäßig auf der Maschine-zu-Maschine-Kommunikation.

REST-Server finden oft Gebrauch in der Web-Technologie, wo über HTTP kommuniziert wird.

## HTTP

>Das Hypertext Transfer Protocol (HTTP) ist ein zustandsloses Protokoll zur Übertragung von Daten auf der Anwendungsschicht über ein Rechnernetz. Es wird hauptsächlich eingesetzt, um Webseiten (Hypertext-Dokumente) aus dem World Wide Web (WWW) in einen Webbrowser zu laden.

In HTTP kommuniziert ein Client mit einem Server über Nachrichten, von denen es zwei unterschiedliche Arten gibt:
Die Anfrage (Request) vom Client und die Antwort (Response) als Reaktion darauf vom Server.

Eine Nachricht besteht bdabei aus zwei Teilen:
Dem Nachrichtenkopf (Header) und dem Nachrichtenrumpf (Body).
Im Header sind Informationen über den Body, wie zum Beispiel verwendete Kodierungen enthalten, während sich im Body der eigentliche Inhalt befindet.

Für den Aufbau einer Verbindung sendet der Client, der eine Verbindung aufbauen will,dem Server ein SYN-Paket (von englisch synchronize).
Der Server empfängt das Paket, bestätitgt den Erhalt des ersten SYN-Pakets und stimmt dem Verbindungsaufbau zu, indem er ein SYN/ACK-Paket zurückschickt (ACK von engl. acknowledgement ‚Bestätigung‘).
Der Client bestätigt zuletzt den Erhalt des SYN/ACK-Pakets durch das Senden eines eigenen ACK-Pakets.
Die Verbindung ist damit aufgebaut.

Einmal aufgebaut, ist die Verbindung für beide Kommunikationspartner gleichberechtigt, das heißt man kann der Verbindung nicht ansehen, wer der Server und wer der Client ist. Daher hat eine Unterscheidung dieser beiden Rollen in der weiteren Betrachtung keine Bedeutung mehr.

