# Protokoll
Florian Nebel  
5AHME, Gruppe 2  
17.12.2018  
Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Mario Nabernik, Muri Lorenz, Platzer Andreas  
Abwesend: Moritz Martinak  

# REST Server  
Der Representational State Transfer ist ein Architekturstilhinter welchem der Anspruch steht, 
selbst unabhängig von jeglichen konkreten Protokollen funktionieren soll, auch wenn zur Implementation REST-geeigneter
Architekturen in der Regel ebenfalls HTTP verwendet wird. Die Kernidee bei REST ist das Konzept der Ressource. 
Alles was in REST adressierbar ist, ist eine Ressource. Es gelten folgende Grundprinzipien: **Adressierbarkeit**, **Zustandslosigkeit**, 
**Entkopplung von Resource und Repräsentation** und **Vereinheitlichung von Schnittstellen**.  
[siehe auch: Thomas Drilling, REST](https://www.dev-insider.de/konzept-aufbau-und-funktionsweise-von-rest-a-603152/)  

# HTTP
[siehe auch: HTTP, Wikipedia](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)  
Mit dem Hypertext Transfer Protocol werden Daten in der Anwendungsschicht über ein Netzwerk übertragen. Es ist ein zustandsloses 
Protokoll, was bedeutet, dass alle Informationen, bei jeder Anfrage mitgesendet werden müssen, da keinerlei Daten wie z.B. Cookies 
gespeichert werden. Die Daten werden textuell und im Gegensatz zu HTTPS ohne jede Verschlüsselung übertragen.  
[siehe auch: Security, HTTP/HTTPS](https://lms.at/dotlrn/classes/digi/610437.5AHME_AIIT.18_19/xolrn/519DFD18ACBBB.symlink?resource_id=0-305198065&m=view#106003071)    

## Funktionsweise
HTTP liegt das Request-Response-System zu Grunde, welches daraus besteht, dass ein Client eine Anfrage (Request) an einen Server sende,
welcher mit einer Antwort (Response) antwortet. Die folgende Grafik stellt den Verbindungsaufbau, den **HTTP-Handshake** dar. 
Als erstes, wenn der Client eine Verbindung aufbauen möchte, schickt er das **SYN-Package** über das Netzwerk an den Server. Sobald 
dieses angekommen ist, antwortet dieser mit dem **ACK-Package** (acknowledge). Mit einem weiteren "acknowledge" vom Client ist die 
Verbindung erfolgreich hergestellt.  
![Handshake](https://github.com/HTLMechatronics/m14-la1-sx/blob/nebflm14/nebflm14/Handshake.png)  

### Paketaufbau
Jedes HTTP-Paket besteht aus einem **Header** in welchem sich Informationen befinden, wie die folgenden Daten zu interpretieren sind 
und dem **Body** in welchem der eigentliche Inhalt übertragen wird.

### Request
Mit vier der von HTTP zur Verfügung gestellten Anfragemethoden lassen sich bereits die wichtigsten Funktionen abdecken:  
* GET: Daten vom Server holen  
* POST: Daten an den Server senden
* PUT: Daten auf den Server hochladen  
* DELETE: Daten vom Server löschen  

### Statuscode
Auf jede Anfrage antwortet ein HTTP-Server mit einem Statuscode, welcher Informationen darüber gibt, ob die Anfrage verarbeitet werden 
kann, oder ob und welcher Fehler vorliegt.  
Statuscode | Beschreibung  
--- | ---  
1XX | Informationen (z.B. Bearbeitung dauert noch an; wird verwendet um Client-Timeout zu verhindern)  
2XX | erfolgreiche Operation  
3XX | Umleitung (weitere Schritte durch Client notwendig, um die Anfrage bearbeiten zu können)  
4XX | Client-Fehler  
5XX | Server-Fehler  

### Keep-Alive
In der ersten Version von HTTP konnte keine Verbindung dauerhaft am Leben erhalten bleiben. Dies wurde jedoch bereits in HTTP1.1 
durch das Header-Attribut Connection: **Keep-Alive** behoben. Wird dieses eingetragen wird die Verbindung nicht nach einem Datenaustasch 
geschlossen, sondern bleibt bestehen bis einer der Kommunikationspartner die Verbindung schließen will.

### Verbindung abbrechen
Da Verbindungen nun dauerhaft am Leben erhalten werden können, ist es notwendig, dass man diese auch schließen kann. Mit dem übertragen des **FIN-Package** 
bittet der Host um die Schließung der Verbindung. Darauf wird mit einem **FIN-ACK-Package**, einer Bestätigung der Beendigung geantwortet.  

## Übungen
Aufbauen einer Verbindung zum Server der HTL Mechatronik mit dem **nc-Tool**, welches über die Kommandline mit dem Befehl: `nc www.htl-mechatronik.at 80` aufgerufen wird.  
Mit der ersten Anfrage `GET / HTTP/1.1` konnten wir überprüfen, ob es möglich ist den Server zu erreichen.
Als Antwort wurde folgender Text gesendet:
```
HTTP/1.1 200 OK
Date: Mon, 19 Nov 2018 07:58:52 GMT
Server: Apache/2.4.7 (Ubuntu)
Last-Modified: Tue, 06 Jan 2015 08:13:36 GMT
ETag: "2a6-45ef12543982c"
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

# Typescript
>TypeScript ist eine Sprache für JavaScript im Anwendungsmaßstab. TypeScript fügt JavaScript optionale Typen hinzu, 
die Tools für umfangreiche JavaScript-Anwendungen für jeden Browser, jeden Host und jedes Betriebssystem unterstützen. 
TypeScript kompiliert zu lesbarem, standardbasiertem JavaScript.  
[Quelle: npmjs, Typescript](https://www.npmjs.com/package/typescript)

## Visual Studio Code
Um in der nächsten Einheit praktische Übungen in der Entwicklungsumgebung vornehmen zu können, haben wir einige Änderungen 
in vorgenommen.

### tsconfig.json
Diese Datei ist zuständig für die korrekte Konfiguration des Compilers.

### gulpfile.json
gulpfile ist für den Übersetzungsvorgang des Quellcodes verantwortlich.

### tslint.json
**TSLint** ist ein Analysewerkzeug, mit dessen hilfe der TypeScript-Code auf Lesbarkeit, Wartbarkeit und Funktionsfehler überprüft werden kann.


