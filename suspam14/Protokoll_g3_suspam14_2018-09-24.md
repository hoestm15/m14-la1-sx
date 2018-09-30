# Protokoll 1: REST-Server
Name: Patrick Schuster  
Klasse: 5AHME  
Gruppe: 3    
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: -

# Kommunikation in der Automatisierungstechnik
Der klassische Ansatz Daten von einem Gerät (z.B. SPS oder Feldgerät) über eine weitere Distanz zu einem PC zu übertragen war über einen Feldbus und einem Netzwerk. Dieser Ansatz bringt einige Probleme mit sich, wie z.B. die Notwendigkeit von zusätzlicher Hardware und wird heutzutage zunehmend weniger verwendet. 
![klassischer Ansatz](https://github.com/suspam14/la1/blob/master/%C3%9Cbertragung_klassisch.svg)  
Stattdessen wird heutzutage der Ansatz verfolgt direkt über das Netzwerk zu arbeiten. Das geschieht über HTTP-Server und HTTP-Clients. Das HTTP-Protkoll wird auch im WWW verwendet, was aber nicht zwingend heißt es nur dort funktioniert. HTTP kann auch abgeschottet vom WWW verwendet werden, da es nur ein Übertragungsprotkoll ist. SPSen oder Feldgeräte im "freien" Internet zu verwendet stellt nämlich einige Sicherheitsrisiken dar.
![HTTP Ansatz](https://github.com/suspam14/la1/blob/master/%C3%9Cbertragung_http.svg)

# REST-Server  
Der Name REST-Server steht für **RE**presentational **S**tate **T**ransfer Server und wird meist für die 
Maschine-zu-Maschine-Kommunikation in Werbsevices verwendet. Das dabei verwendete Übertragungsprotkoll ist HTTP.  
# HTTP
Der Name HTTP steht für **H**yper**T**ext **T**ransfer **P**rotokoll. HTTP ist ein Protkoll zur Übertragung
von Daten auf der Anwendungsschicht ([Application Layer](https://de.wikipedia.org/wiki/OSI-Modell#Schicht_7_%E2%80%93_Anwendungsschicht_(Application_Layer))). 
Das Protkoll ist zustandslos, dass bedeutet das Informationen aus früheren Anforderungen verloren gehen, 
deshalb ist ein zuverlässiges mitführen von Sitzungsdaten erforderlich. Weiters erfolgt die Übertragung textuell. 
Um Daten verschlüsselt zu Übertragen gibt es das Protokoll HTTPS.  
## Funktionsweise 
### Verbindungsaufbau
Im Grundzustand des Servers ist der *Listen-Zustand*, in diesem wartet er auf eine Anfrage von einem CLient durch durch ein *SYN-Package*. Erhält der Server eine Anfrage so sendet er ein *ACK-Package*, damit der Client weiß das die Anfrage angekommen ist. Sobald der Client diese *ACK-Package* empfangen hat sendet er auch ein *ACK-Package* zurück. Wenn der Server diese empfängt steht die Verbindung.
![REST-Server](https://github.com/suspam14/la1/blob/master/REST-Server.svg)
### Beenden der Verbindung
Will einer der beiden Hosts die Verbindung beenden, so sendet er ein *FIN-Package*, der andere Host antwortet mit einem *FIN-ACK-Package*.
### Keep-Alive Pakete
Wenn eine Verbinndung zwischen Server und Client besteht werden nicht dauerhaft Pakete übertragen. Um zu verhindern, dass der Server die Verbindung aufgrund einer Überschreitung der Zwit abbricht kann der Client sogennante *Keep-Alive-Pakete* schicken um dem Server damit mitzuteilen, dass er immernoch "lebt" und die Verbindung aufrecht erhalten will. Typische Zeiten für eine Überschreitung sind, je nach Server, zwischen 30 und 120 Sekunden. Nach dieser Zeit ohne empfangene/gesendete Pakete bricht der Server die Verbindung ab.
## Paketaufbau
Ein HTTP-Paket besteht aus einem *Header* und einem *Body*.
### Header (Nachrichtenkopf)  
Im Header befinden sichalle wichtigen Informationen vom Body, die der Empfänger benötigt um die Daten richtig interpretieren zu können. Zu diesen Informationen gehört z.B. die Kodierung.  
### Body (Nachrichtenrumpf)  
Im Body befinden sich die eigentlichen Daten, die Übertragen werden sollen. Diese Daten nennt man Nutzdaten.  
## "Befehle"
Im HTTP-Protokoll gibt es mehrere Methoden mit denen der Cliente festlegt was er vom Server möchte.
Die wichtigsten befinden sich in dieser Tabelle.  
#### Anfragemethoden  
Methode | Beschreibung  
------- | ---------  
GET | Daten vom Server abrufen  
POST | Daten zum Server schicken (für Weiterverarbeitung)  
PUT | Daten auf den Server hochladen  
DELETE | Daten vom Server löschen  
#### Statuscodes
Wenn vom Client eine Anfrage kommt muss der Server diese interpretieren und bearbeiten. Sowohl bei der Interpretation, als auch bei der Bearbeitung können Fehler auftreten. Um dem Client mitzuteilen, was vorgefallen ist bzw. was gerade passiert sieht HTTP verschiedene Statuscodes vor.  

Statuscode | Beschreibung  
--- | ---  
1xx | Information (Zwischenantwort falls die Bearbeitung länger dauert)  
2xx | erfolgreiche Operation  (Anfrage wurde beantwortet und Antwort wird gesendet)  
3xx | Umleitung (Der Client muss weitere Informationen geben, um die Anfrage bearbeiten zu können)
4xx | Client-Fehler (Es ist ein Fehler aufgetreten der im Verantwortungsbereich de Clients liegt  
5xx | Server-Fehler (Es ist ein Fehler aufgetreten, dessen Ursache beim Server liegt)  

## Praktische Übung
### Aufgabenstellung
Es soll eine Verbindung zu einem Server hergestellt werden.
### Ablauf der Übung
Mit dem *nc*-Tool in der Linux-Shell haben wir versucht eine Verbindung zum HTL-Mechatronik Server aufzubauen.
```patrick@Patrick-XMG-A705:~$ nc www.htl-mechatronik.at 80```  
Dannach haben wir eine HTTP-Anfrage versendet.  
```GET / HTTP/1.1```  
Der Server hat wie folgt geantwortet.  
```
HTTP/1.1 400 Bad Request
Date: Mon, 24 Sep 2018 06:54:01 GMT
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
</body></html
```
Die von uns versendete Anfrag war fehlerhaft, deshalb haben wir eine Fehlermeldung als Antwort bekommen.
Um herauszufinden wie eine korrekte Anfrage aussieht haben wir eine Verbindung mit dem localhost aufgebaut.
```patrick@Patrick-XMG-A705:~$ nc -l 4711```  
Anschließend haben wir eine Anfrage versendet.  
```GET / HTTP/1.1```  
Der Server hat wie folgt geantwortet.
```Host: localhost:4711
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:62.0) Gecko/20100101 Firefox/62.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1
```
Wir haben das empfangene Paket modifiziert, so dass wir es an den HTl-Server schicken können  
```patrick@Patrick-XMG-A705:~$ nc www.htl-mechatronik.at 80```
```GET / HTTP/1.1
Host: www.htlmechatronik.at
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:62.0) Gecko/20100101 Firefox/62.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1
```
Vom Server kam aber wieder die gleiche Fehlermeldung.
Der Server "behauptete" wieder die Anfrage nicht verstehen zu können. 
Der Fehler in der Anfrage war, dass unsere Anfrage einen normalen *line feed* verwendete. Der Server hingegen erwartete eine combination aus *line feed* und *carriage return*. 
Diesen Fehler konnten wir beheben indem wir beim *nc*-Tool eine Option (-C) auswälhten, die den *line feed* umwandelte, so dass der Server die zeilenumbrüche erkannte.  
```patrick@Patrick-XMG-A705:~$ nc -C www.htl-mechatronik.at 80```  
Wir schickten die gleiche Anfrage und bekamen eine merkwürdige Antwort, in welcher die Nutzdaten nicht lesbar waren.  
Das lag daran, dass in der Anfrage die falsche Codierung angaben und der Server uns somit eine gezipte Datei schickte.
Um dieses Problem zu beheben schickten wir eine Anfrage ohne *gzip* als Codierung.
Der Server gab uns die erwünschte Antwort.
```HTTP/1.1 200 OK
Date: Mon, 24 Sep 2018 07:43:03 GMT
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
# Anlegen eines Javascript/Typescript-Projektes
Das zweite Thema der Einheit war, wie man ein Projekt anlegt und die benötigten Komponenten dafür installiert.
Dafür legten wir einen Ordner an und gingen mit `cd` in diesen.  
Dort führten wir den Befehl `npm init` aus. Nach der Ausführung dieses Befehls kann man alle wichtigen Daten für das Projekt eingeben, diese werden in die Datei *package.json* geschrieben.  Die Datei *package.json* hat folgenden Inhalt:  
```
npm init
package name: (rest-server) 
version: (1.0.0) 0.0.1
description: 5AHME LA1 G3 Rest Server
entry point: (index.js) main.js
test command: 
git repository: 
keywords: 
author: Schuster
license: (ISC) "MIT"
```
Um Typscript zu installieren führten wir den Befehl `npm install --save-dev typescript` aus. Durch diesen Befehl wird Typescript im Projektordner fürs entwickeln installiert und wird nicht für das fertige Programm verwendet (Typescript wird zu Javascript übersetzt. Javascript wird zu Ausführung benötigt). 
> Von einer globalen Installation ist abzuraten, da man in verschiedenen Projekten durchaus verschiedene Javascript und Typescript Versionen verwendet was zu Problemen führen kann.  

Weiters haben wir das Framework *Express* mit dem Befehl `npm install --save express` welches uns hilfreiche Werkzeuge für die Programmierung zu verfügung stellt.










