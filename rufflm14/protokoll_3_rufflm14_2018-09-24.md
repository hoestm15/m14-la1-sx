# 1.Laborprotokoll 

*von Florian Ruffenacht*

Datum: 24.09.2018 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

## HTTP-Kommunikation

### Ansatz von HTTP
In der klassischen Variante den Datenaustausch zwischen einem PC und einem anderen Gerät über größere Distanzen zu realisieren, erfolgt dieser über ein Netzwerk und einen Feldbus:

![Klassischer Datenaustausch](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/NetzwerkKlassisch.svg)

Heutzutage wird aber immer mehr ein anderer Ansatz verfolgt. Der PC (= HTTP(s)-Client) und der sogenannte HTTP(s)-Server sind nur über das Netzwerk verbunden.Weil dieses Prinzip dazu verwendet wird, Webseiten aus dem World Wide Web (WWW) in einen Webbrowser zu laden, ist es ein wichitger Bestandteil des modernen Lebens. Die Netzwerkverbindung muss aber nicht zwingend das Internet sein, da dies oft Sicherheitsrisiken mit sich bringt. 

![HTTP(s) Datenaustausch](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/NetzwerkHTTP.svg)

### HTTP-Protokoll
Das Hypertext Transfer Protokoll ist textuell aufgebaut und basiert auf dem Server-Client Prinzip. Der Client sendet eine Anfrage (=Request), auf die der Server antwortet (=Response).

![Server-Client Prinzip](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/ServerClientPrinzip.jpeg)

Für den Request stehen folgende Schlüsselwörter zur Verfügung:

* **GET**     -> Inhalte vom Server fordern
* **POST**    -> Übermitteln von Inhalten
* **PUT**     -> Erstellen von neuen Inhalten auf dem Server
* **DELETE**  -> Löschen von Inhalten

Das Protokoll ist so einfach gehalten, dass man es sogar eigenhändig in der Konsole probieren kann. Neben dem GET-Befehl sind noch weitere Informationen in der Anfrage nötig. Außerdem muss darauf geachtet werde, das richitge ENTER zu verwenden. An folgendem Beispiel kann man sehen, wie eine HTTP-Anfrage in der Konsole aussieht:
```
florian@florian:~$ nc -c www.htl-mechatronik.at 80
GET /infotext.html HTTP/1.1
Host: www.htl-mechatronik.atnde 
Connection: keep-alive
Pragma: no-cache
Cache-Control: no-cache
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:58.0) Gecko/20100101 Firefox/58.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: deflate
```
Wird die Anfrage vom Server akzeptiert, folgt die Antwort mit einigen Informationen zum Server selbst und einem HTML-Dokument:

```
HTTP/1.1 200 OK
Date: Mon, 24 Sep 2018 07:48:04 GMT
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
Die Verbindung wird duch ein "Final Flag" im TCP-Protokoll beendet.

### Statuscodes
Die Antwort des  Servers enthält immer einen der folgenden Statuscodes:

Statuscode | Bedeutung
---------- | ---------
1xx | Die Bearbeitung der Anfrage dauert noch an
2xx | Erfolgreiche Operation
3xx | Es sind noch weitere Schritte des Clients notwendig zur erfolgreichen Operation notwendig
4xx | Fehler des Clients
5xx | Fehler des Servers

[Mehr zum HTTP-Protokoll](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)

## Typescript
Die von Microsoft entwickelte Programmiersprache Typescript basiert auf JavaScript. Der TypeScript-Code wird vor dem Ausführen in einen JavaScript-Code "transpiliert". Der Hauptunterschied zwischen den beiden Sprachen liegt darin, dass in TypeScript jeder Variable ein eindeutiger Datentyp zugeweisen wird. Dadurch können Fehler leichter gleich beim Programmieren in der IDE gefunden werden.

[Mehr Informationen zu TypeScript](https://msdn.microsoft.com/de-de/magazine/dn890374.aspx)

Um eine TypeScript Programm zu schreiben, muss TypeScript im jeweiligen Projektordner installiert werden. Dazu wird zuerst mit ```npm init``` eine Datei mit dem Namen **package.json** ersteltt. Darin sind grundsätzliche Informationen zum Projekt enthalten:
```
npm init
package name: (rest-server) 
version: (1.0.0) 0.0.1
description: 5AHME LA1 G3 Rest Server
entry point: (index.js) main.js
test command: 
git repository: 
keywords: 
author: Florian Ruffenacht
license: (ISC) "MIT"
```
Mit dem Kommando ```npm install --save-dev typescript``` kann TypeScript installiert werden. Das sollte immer im Projekt und nicht global erfolgen, da sich der Standard schnell ändern kann und das Programm dann möglicherweise fehlerhaft ist. Beim Hochladen auf ein Repository sollte die Datei node.modules ausgeschlossen werden, um die Datenmenge zu reduzieren.
