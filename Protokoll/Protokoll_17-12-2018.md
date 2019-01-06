# Protokoll der 1. Einheit

## 1. Einheit

* Name: Mario Nabernik  
* Klasse: 5AHME  
* Datum 17.12.2018  
* Gruppe: 2  
* Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Mario Nabernik, Muri Lorenz, Platzer Andreas  
* Abwesend: Martinak Moritz
* Thema: 


# REST-Server

**Re**presentational **S**tate **T**ransfer bezeichnet ein Programmierparadigma für 
verteilte Systeme (häufig Webservices).
REST hat das Ziel, einen Architekturstil zu schaffen, der die Anforderungen des modernen Web besser darstellt. 

>Ein Programmierparadigma ist ein fundamentaler Programmierstil.[1] „Der Programmierung liegen je nach Design der einzelnen Programmiersprache verschiedene Prinzipien zugrunde. Diese sollen den Entwickler bei der Erstellung von ‚gutem Code‘ unterstützen, in manchen Fällen sogar zu einer bestimmten Herangehensweise bei der Lösung von Problemen zwingen“
 
 [Quelle: Wikipedia, Programmierparadigma](https://de.wikipedia.org/wiki/Programmierparadigma)
  
Ein REST-Server wird dazu eingesetzt, um eine Maschine-zu-Maschine Kommunikation in Webservices umzusetzen. Das dabei verwendetet Übertragungsprotokoll ist HTTP.

# HTTP
Das Hypertext Transfer Protocol regelt die Kommunikation von Server und Clients (Web-Browser). Dies geschieht noch oberhalb des TCP/IP Protokolls.
Es ist außerdem ein zustandsloses Protokoll.

> Zustandslosigkeit ist die Eigenschaft eines Protokolls oder Systems, mehrere Anfragen – auch desselben Auftraggebers – 
grundsätzlich als voneinander unabhängige Transaktionen zu behandeln. Insbesondere werden Anfragen ohne Bezug zu 
früheren Anfragen behandelt und keine Sitzungsinformationen ausgetauscht und/oder verwaltet. Das Gegenteil ist 
Zustandsbehaftung oder auch Zustandshaltend. 

[Quelle: Wikipedia, Zustandslosigkeit](https://de.wikipedia.org/wiki/Zustandslosigkeit)

## Funktionsweise von HTTP
HTTP basiert auf dem *Request-Response*-System. Das bedeutet, dass der Client einen *Request* sendet und der Server anschließend mit einem *Response* antwortet.

### Verbindungs- und Paketaufbau
Client und Server bauen zum Austausch der Nachrichten im Standardfall eine TCP-Verbindung auf Port 80 auf.
Die "Request und Response" gennanten Nachrichten bestehen aus einem Header und den wesentlichen Daten. Der Header enthält Steuerinformationen und im Datenabschnitt befindet sich meist ein HTML-Dokument oder Formulardaten, die der Client an den Server sendet
![HTTP-Handshake](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/5AHME/HTTP_Handshake.png)

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

# Typescript
>TypeScript ist eine Sprache für JavaScript im Anwendungsmaßstab. TypeScript fügt JavaScript optionale Typen hinzu, die Tools für umfangreiche JavaScript-Anwendungen für jeden Browser, jeden Host und jedes Betriebssystem unterstützen. TypeScript kompiliert zu lesbarem, standardbasiertem JavaScript.

*[Typescript, npm](https://www.npmjs.com/package/typescript)*

## Visual Studio Code
Visual Studio Code ist eine IDE uir Programmierung von Typescript. Die IDE muss vor Benutzung eingerichtet werden. Dabei sind folgende Dateien wichtig:

### tsconfig.json
Diese Datei ist für die Konfiguration des Typescript-Compilers zuständig.

### gulpfile.json
Diese Datei ist für den Übersetzungsvorgang verantwortlich.

### tslint.json
> TSLint ist ein erweiterbares statisches Analysewerkzeug, das TypeScript- Code auf Lesbarkeit, Wartbarkeit und Funktionsfehler überprüft . Es wird weitgehend von modernen Editoren und Build-Systemen unterstützt und kann mit Ihren eigenen Fusselregeln, Konfigurationen und Formaten angepasst werden.  
*[Quelle: TSLint](https://palantir.github.io/tslint/)*
