# 1.Protokoll
**Name:** Jakob Boecksteiner   
**Datum:** 19.11.2018  
**Gruppe:** 1  
**Anwesend:** Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Knappitsch Robert, Kobor Markus, Köhler Marcel  
**Abwesend:** -  

## REST-Server
**R**epresentational **S**tate **T**ransfer Server abgekürzt auch *REST-Server* wird für die Maschine-zu-Maschine-Kommunikation in Werbsevices verwendet wird. *HTTP* ist das verwendete Übertragungsprotkoll.  
Wichtigtste prinzipien des REST-Servers: 
* Zustandslos  
* Client/Server  
* Einheitliche Schnittstelle 
* Mehrschichtige Systeme

Weitere Infos zum REST-Server: [Link](https://de.wikipedia.org/wiki/Representational_State_Transfer)

## HTTP Server/Client
*HTTP* steht für **H**yper**T**ext **T**ransfer **P**rotokoll. Unter Server/Client versteht man die Aufteilung von Aufgaben auch einem Server-Programm und einem Client-Programm, diese Tauschen Daten über das Netzwerk aus. Der Client sendet einen **Request** an den Server und der Server antwortet mit einem **Respond**. Wichtig Server und CLient sind nicht zwingend zwei verschiedene Rechner!

Schlüsselwörter für den Request:
* **GET**     -> Inhalte vom Server fordern
* **POST**    -> Übermitteln von Inhalten
* **PUT**     -> Erstellen von neuen Inhalten auf dem Server
* **DELETE**  -> Löschen von Inhalten

Mit dem **nc** Tool kann man eine GET-Anfrage an einen Server senden. Es folgt ein Beispiel in der der Client( in dem Fall wir) eine Anfrage macht und der Server antwortet.

```   
boecki@boecki-T470s:~$ nc htl-mechatronik.at 80 -C
GET /infotext.html HTTP/1.1
Host: www.htl-mechatronik.at
```  
Der Server hat die anfrage erhalten so sieht zum Beispiel eine Antwort eines Servers aus.

```
HTTP/1.1 200 OK
Date: Mon, 15 Oct 2018 08:48:04 GMT
Server: Apache/2.4.7 (Ubuntu)
Last-Modified: Tue, 06 Jan 2015 08:13:36 GMT
ETag: "1e9-50bf76235166b"
Accept-Ranges: bytes
Content-Length: 489
Vary: Accept-Encoding
Keep-Alive: timeout=10, max=100
Connection: Keep-Alive
Content-Type: text/html

<html>
<head>
<META HTTP-EQUIV="CONTENT-TYPE" CONTENT="text/html; charset=utf->
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

### Statuscodes
Ein Server Response enthält immer einen Statuscode. 

Statuscode | Bedeutung
---------- | ---------
1xx | Bearbeitung der Anfrage in Arbeit
2xx | Erfolgreiche
3xx | Weitere Schritte des Clients nötig
4xx | Fehler des Clients
5xx | Fehler des Servers    


Weitere Infos zu HTTP: [Link](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)

## Typescript

Typescript ist eine von Microsoft entwickelte Programmiersprache und basiert auf Javascript. Der Typescript-Code wird vor dem Ausführen in einen JavaScript-Code **transpiliert**. Der Hauptgrund für die verwendung von Typescript ist, dass es in Javascript ansich keine Datentypen gibt, dadurch wird die Fehlersuche in Typescript erleichtert.

Weitere Infos zu Typescript: [Link](https://de.wikipedia.org/wiki/TypeScript)
