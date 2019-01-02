# Protokoll
Michael Mörth  
5AHME, Gruppe 2  
17.12.18  
Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Mario Nabernik, Muri Lorenz, Platzer Andreas  
Abwesend: Moritz Martinak  

# REST-Server
> Representational State Transfer (abgekürzt REST, seltener auch ReST) bezeichnet ein Programmierparadigma für verteilte Systeme, insbesondere für Webservices. REST ist eine Abstraktion der Struktur und des Verhaltens des World Wide Web. REST hat das Ziel, einen Architekturstil zu schaffen, der die Anforderungen des modernen Web besser darstellt. Dabei unterscheidet sich REST vor allem in der Forderung nach einer einheitlichen Schnittstelle (siehe Abschnitt Prinzipien) von anderen Architekturstilen.
  
  *[Quelle: Wikipedia, REST-Server](https://de.wikipedia.org/wiki/Representational_State_Transfer)*  
  
Ein REST-Server wird dazu eingesetzt, um eine Maschine-zu-Maschine Kommunikation in Webservices umzusetzen. Das dabei verwendetet Übertragungsprotokoll ist HTTP.

# HTTP
> Das Hypertext Transfer Protocol (HTTP, englisch für Hypertext-Übertragungsprotokoll) ist ein zustandsloses Protokoll zur Übertragung von Daten auf der Anwendungsschicht über ein Rechnernetz.
  
  *[Quelle: Wikipedia, HTTP](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)*  

Unter einem zustandslosen Protokoll versteht man, dass Informationen aus früheren Anwendungen verloren gehen. Die Daten werden textuell übertragen und sind nicht verschlüsselt. Für das verschlüsselte Übertragen von Daten gibt es [HTTPS](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol_Secure).

## Funktionsweise von HTTP
HTTP basiert auf dem *Request-Response*-System. Das bedeutet, dass der Client einen *Request* sendet und der Server anschließend mit einem *Response* antwortet.

### Verbindungsaufbau
![HTTP-Handshake](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/5AHME/HTTP_Handshake.png)

Das obrige Bild beschreibt den sogenannten **HTTP-Handshake**. Wenn der Client die Verbindung aufbauen möchte, sendet dieser als erstes ein **SYN**-Package an den Server. Wenn das **SYN**-Package beim Server angekommen ist, antwortet der Server mit einem **ACK**-Package. Wenn der Client das **ACK**-Package vom Server erhalten hat, sendet dieser ein weiteres **ACK**-Package an den Server. Damit wurde erflogreich eine Verbindung aufgebaut.

### Paketaufbau
Ein HTTP-Paket besteht immer aus einem **Header** und einem **Body**.  
Im Header befinden sich alle Informationen, um Daten richtig zu interpretieren (Codierung etc.).  
Im Body befinden sich die zu übertragenden Daten.

### Requests
Request | Beschreibung  
--- | ---  
GET | Daten vom Server abrufen  
POST | Daten an Server senden 
PUT | Daten auf den Server hochladen  
DELETE | Daten vom Server löschen 

*[Quelle: Wikipedia, HTTP](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)*

### Stauscodes
Statuscode | Beschreibung  
--- | ---  
1xx | Information (Status, falls die Bearbeitung der Anfrage länger dauert)  
2xx | erfolgreiche Operation  
3xx | Umleitung (Der Client muss weitere Informationen geben, um die Anfrage bearbeiten zu können)
4xx | Client-Fehler  
5xx | Server-Fehler

*[Quelle: Wikipedia, HTTP](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)*

### Keep-Alive
Keep-Alive ist ein Attribut das im Header eines HTTP-Pakets eingetragen wird, damit die Kommunikation nicht sofort beendet wird.

### Verbindung schließen
Wenn einer der Hosts die Verbindung schließen möchte, sendet dieser ein **FIN**-Package. Der andere Host antwortet darauf mit einem **FIN-ACK**-Package und die Verbindung wird anschließend geschlossen.

## Übung mit HTTP im Terminal
Unsere Aufgabe war es, eine Verbindung zu einem Server herzustellen.  
Mit dem Tool *nc* der Shell haben wir eine Verbindung zum HTL-Server in Arnfels hergestellt.
`nc -C -l www.htl-mechatronik.at 80` 

Danach haben wir eine Anfrage an der Server geschickt. Diese sah wie folgt aus:
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

Der Server hat darauf mit folgendem geantwortet:
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

Sollte eine falsche Anfrage an den Server gesendet werden, so würde die Antwort wie folgt aussehen:
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

