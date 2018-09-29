# _Protokoll Erste Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 24.09.2018**  
**Uhrzeit: 8:00-10:30**  
  
**Anwesenheit: _Es waren alle Schüler anwesend_**  
  
-----------------------------------------------------------
  
### REST-Server  
**RE**presentational **S**tate **T**ransfer Server  
Ein REST-Server ist ein HTTP-Dienst, der HTTP-Status-Abfragen zulässt. HTTP steht für *Hypertext Transfer Protocol*, das Übertragungsprotokoll.  

-------------------------------------------------------------  

#### HTTP  
Bei HTTP handelt es sich um ein *zustandsloses* Protokoll, d.h. das Anfragen ohne Bezug auf vorherige Antworten verarbeitet werden.  
Die Übertragung findet textuell statt.  
  
##### Aufbau  
Header (*Nachrichtenkopf*)  
Der Header beinhaltet Informationen zum Body, wie zum Beispiel die verwendete Kodierung oder den Inhaltstyp, damit dieser vom Empfänger korrekt interpretiert werden kann.  
  
Body (*Nachrichtenrumpf*)  
Der Body enthält die Nutzdaten.  
  
##### Funktionsweise  
Server befindet sich grundsätzlich in einem *LISTEN*-Zustand und wartet auf eine Anfrage mit einem SYN-Package von einem Client.  
Erhält er nun eine Anfrage vom Client, antwortet er mit einem ACK-Package.  
Antwortet der Client ebenfalls mit einer ACK-Package, steht die Verbindung. Grundsätzlich sind Server und Client in diesem Status gleichwertig und könnten die Rolle tauschen (ist normal nicht der Fall).  
Zum Beenden der Verbindung schickt zuerst einer der beiden ein FIN-Package, der andere antwortet mit einem FIN-ACK-Package.  
  
##### Anfragemethoden  
Der Client legt bei seiner Request (*Anfrage*) fest, was er vom Server möchte.  
  
Methode | Erklärung
------- | ---------
GET | Daten vom Server abrufen
POST | Daten zum Server zum Weiterverarbeiten schicken
PUT | Daten auf den Server hochladen
DELETE | Daten vom Server löschen
  
Natürlich gibt es noch weitere Methoden, diese sind jedoch auf Wikipedia selbst nachzulesen.  
  
##### Statuscodes  
Bei jeder HTTP-Anfrage antwortet der Server mit einem HTTP-Statuscode. Dieser gibt Auskunft, ob die Anfrage erfolgreich bearbeitet wurde oder ob es zu Umleitungen oder Störungen kam.  

Statuscode | Bedeutung
---------- | ---------
1xx | Informationen, dient zur Antwort, falls die Bearbeitung länger andauert
2xx | Erfolgreiche Operation
3xx | Es kam zu einer Umleitung, bzw. sind noch weitere Schritte des Clients notwendig
4xx | Client-Fehler
5xx | Server-Fehler
  
Weitere Informationen zu HTTP: [Wikipedia/HTTP](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)  
  
-----------------------------------------------------------------------  
  
##### Praktische Übungen mit nc  
Mittels *nc* konnten wir eine Verbindung zu einem Server herstellen. Diese Übung diente dazu, uns mit dem Inhalt von HTTP-Anfragen und Server-Responses vertraut zu machen.  
  
###### NC-Verbindungsaufbau zu Server  
``
daniel@daniel-VirtualBox:~$ nc www.htl-mechatronik.at 80
``
###### HTTP-Anfrage  
``
GET / HTTP/1.1
``
###### Server-Antwort  
```
HTTP/1.1 400 Bad Request              //Statuscode
Date: Mon, 24 Sep 2018 06:54:24 GMT
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
  
###### NC-Verbindungsaufbau zu Localhost  
``
daniel@daniel-VirtualBox:~$ nc -l 4711
``
###### HTTP-Anfrage  
``
GET / HTTP/1.1
``
###### Response  
```
Host: localhost:4711
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:58.0) Gecko/20100101 Firefox/58.0	welcher Browser steckt dahinter?
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8				was akzeptiert der Browser?
Accept-Language: de,en-US;q=0.7,en;q=0.3							akzeptierte Sprachen
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1

```
  
##### Anlegen eines Projektes mittels node.js  

