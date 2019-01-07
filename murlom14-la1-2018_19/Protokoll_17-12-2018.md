# Protokoll 17.12.2018

## 1. Einheit
Name: Muri Lorenz <br>
Klasse: 5AHME <br>
Gruppe: 2 <br>
Datum der Einheit: 17.12.2018 <br> 
Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Mario Nabernik, Muri Lorenz, Platzer Andreas <br>
Abwesend: Moritz Martinak <br>

## Thema: REST - Representational State Transfer

### REST
REST wird hauptsächlich wird bei Maschine-zu-Maschine-Kommunikation eingesetzt, dieses System ist auf einheitliche Schnittstllen aufgebaut dadurch ist REST eine einfacherer Programmierparadigma als zum Beispiel: SOAP [(Link zu Wikipedia)](https://de.wikipedia.org/wiki/SOAP) oder WSDL [(Link zu Wikipedia)](https://de.wikipedia.org/wiki/Web_Services_Description_Language). Zur Üertragung wird bei REST-Servern hauptsächlich mittels HTTP übertragen.
[Quelle Wikipedia](https://de.wikipedia.org/wiki/Representational_State_Transfer) <br>
<br>

### HTTP
[HTTP](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol) steht für Hypertext Transfer Protocol, dieses Protokoll wird zur Übertragung von Daten in einem Netzwerk verwendet. Um Daten verschlüsslet zu Übertragen verwendet man [HTTPS](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol_Secure).
<br>

### Funktionsweise/Prinzip
HTTP funktioniert nach dem klassichen Request-Response-Prinzip. Der Client schickt eine Anfrage(Request) an den Server, der mit einer Response antwortet.

![HTTP-Prinzip](https://github.com/HTLMechatronics/m14-la1-sx/blob/murlom14/murlom14-la1-2018_19/HTTP-Prinzip.jpg)
1. Zum Verindungsaufbau sendet der Client an den Server ein SYN-Package
2. Beim erfolgreichem Erhalten sendet der Server ein ARC-Package zurück und stimmt somit den Verbindungsaufbau zu.
3. Schlussendlich wird vom Client noch ein ACK-Package an den Server gesendet, dies bedeutet die Verbindung steht und Daten können ausgetauscht werden. <br>

Bei HTTP gibt es standartisierte Requests:
Request | Beschreibung  
------- | ---------  
GET | Daten abrufen  
POST | Daten senden 
PUT | Daten hochladen  
DELETE | Daten löschen

Zum Schließen der Verbindung sendet der Client ein FIN-Package welches mit einem FIN-ACK-Package beschlossen wird.

### Praktische Übung
Die Übung bestand daraus mittels Terminal eine Verbindung zu der Website www.htl-mechatronik.at zu erstellen
`Lorenz-MBP:~ muri$ nc www.htl-mechatronik.at 80`
Dieses Kommando stellt eine Verbindung her und wartet dann auf eine Anfrage:
`GET / HTTP/1.1`

Antwort:
```
HTTP/1.1 400 Bad Request
Date: Sun, 07 Jan 2019 18:29:08 GMT
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
Diese einfache Anfrage hat der HTL-Server nicht verstanden und gab nur eine bad Request zurück.




