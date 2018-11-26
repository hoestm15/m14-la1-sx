# Protokoll 19.11.2018

## 1. Einheit
## Thema: REST-Server
 
 Name: Markus Kobor  
 Klasse: 5AHME  
 Datum: 19.11.2018  
 Anwesend: Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Knappitsch Robert, Kobor Markus, Köhler Marcel <br>
 Abwesend: Niemand <br> <br> <br>
 
 
## Was ist ein REST-Server?

>Representational State Transfer (abgekürzt REST) bezeichnet ein Programmierparadigma für verteilte Systeme, insbesondere für Webservices. REST ist eine Abstraktion der Struktur und des Verhaltens des World Wide Web. REST hat das Ziel, einen Architekturstil zu schaffen, der die Anforderungen des modernen Web besser darstellt. Dabei unterscheidet sich REST vor allem in der Forderung nach einer einheitlichen Schnittstelle von anderen Architekturstilen.

>Der Zweck von REST liegt schwerpunktmäßig auf der **Maschine-zu-Maschine-Kommunikation**.

*[REST-Server, Wikipedia](https://de.wikipedia.org/wiki/Representational_State_Transfer)*

REST-Server finden oft Gebrauch in der Web-Technologie, wo über HTTP kommuniziert wird.


## HTTP

>Das Hypertext Transfer Protocol (HTTP) ist ein zustandsloses Protokoll zur Übertragung von Daten auf der Anwendungsschicht über ein Rechnernetz. Es wird hauptsächlich eingesetzt, um Webseiten (Hypertext-Dokumente) aus dem World Wide Web (WWW) in einen Webbrowser zu laden.

*[HTTP, Wikipedia](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)*

#### Funktionsweise

In HTTP kommuniziert ein **Client** mit einem **Server** über Nachrichten, von denen es zwei unterschiedliche Arten gibt:
Die Anfrage (**Request**) vom Client und die Antwort (**Response**) als Reaktion darauf vom Server.

#### Paketaufbau

Eine Nachricht besteht bdabei aus zwei Teilen:
Dem Nachrichtenkopf (**Header**) und dem Nachrichtenrumpf (**Body**).
Im Header sind Informationen über den Body, wie zum Beispiel verwendete Kodierungen enthalten, während sich im Body der eigentliche Inhalt befindet.

#### Verbindungsaufabu

Für den Aufbau einer Verbindung sendet der Client, der eine Verbindung aufbauen will,dem Server ein SYN-Paket (von englisch synchronize).
Der Server empfängt das Paket, bestätitgt den Erhalt des ersten SYN-Pakets und stimmt dem Verbindungsaufbau zu, indem er ein SYN/ACK-Paket zurückschickt (ACK von engl. acknowledgement ‚Bestätigung‘).
Der Client bestätigt zuletzt den Erhalt des SYN/ACK-Pakets durch das Senden eines eigenen ACK-Pakets.
Die Verbindung ist damit aufgebaut.

![Aufbau einer Verbindung](https://github.com/HTLMechatronics/m14-la1-sx/blob/kobmam14/kobmam14/Tcp-handshake.png)

Einmal aufgebaut, ist die Verbindung für beide Kommunikationspartner gleichberechtigt, das heißt man kann der Verbindung nicht ansehen, wer der Server und wer der Client ist. Daher hat eine Unterscheidung dieser beiden Rollen in der weiteren Betrachtung keine Bedeutung mehr.

#### HTTP-Anfragemethoden

Anfragemethode | Erklärung  
-------------- | ------------ 
GET | Mit ihr wird eine Ressource vom Server angefordert
POST | Schickt Daten zur weiteren Verarbeitung zum Server  
HEAD | Weist den Server an, die gleichen HTTP-Header wie bei GET, nicht jedoch den Nachrichtenrumpf mit dem eigentlichen Dokumentinhalt zu senden
PUT | Dient dazu, eine Ressource auf einen Webserver hochzuladen. 
PATCH | Ändert ein bestehendes Dokument ohne dieses wie bei PUT vollständig zu ersetzen.
DELETE | Löscht die angegebene Ressource auf dem Server.

#### HTTP-Statuscodes

Statuscode | Erklärung  
---------- | ------------
1xx | Informationen (Die Bearbeitung der Anfrage dauert trotz der Rückmeldung noch an.)
2xx | Erfolgreiche Operation (Die Anfrage wurde bearbeitet und die Antwort wird an den Anfragesteller zurückgesendet.)
3xx | Umleitung (Um eine erfolgreiche Bearbeitung der Anfrage sicherzustellen, sind weitere Schritte seitens des Clients erforderlich.)
4xx | Client-Fehler (Bei der Bearbeitung der Anfrage ist ein Fehler aufgetreten, der im Verantwortungsbereich des Clients liegt.)
5xx | Server-Fehler (Es ist ein Fehler aufgetreten, dessen Ursache beim Server liegt.)

Hier noch eine vollständige Liste mit allen *[HTTP-Statuscodes](https://httpstatuses.com/)*.


## Ablauf der Übung

Unsere erste Aufgabe war es eine Verbindung zu einem Server aufzubauen. <br>
Dies haben wir zuerst über den Localhost realisiert:  

```
kobi@MarkusPC:~$ nc -l -C 4711
GET /favicon.ico HTTP/1.1
Host: localhost:4711
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:57.0) Gecko/20100101 Firefox/57.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive

HTTP/1.1 200 OK
Server: Apache/1.3.29
Content length: 5
Content-Language: de 
Connection: close               
Content-Type: text/html

Hallo
```

*Das Tool **nc** (oder netcat) kann TCP-Verbindungen öffnen, UDP-Pakete senden, beliebige TCP- und UDP-Ports abhören, Port-Scans durchführen und sowohl mit IPv4 als auch mit IPv6 umgehen.*

*Der Zusatz **-l** wird verwendet, um anzugeben, dass nc auf eine eingehende Verbindung achten soll, anstatt eine Verbindung zu einem Remote-Host herzustellen.*

**-C** *wird benötigt um den Server einen regulären Zeilenvorschub als Carriage Return sehen zu lassen.*

*Mit **keep-alive** kann der Client dem Server sagen, dass die Verbindung nach der Antwort nicht abgebaut werden soll und weitere Anfragen sequentiell folgen können. Die Verbindung bleibt solange bestehen, bis eine der beiden Seiten die TCP-Verbindung abbaut.* <br> <br>

Als nächstes haben wir eine Verbindung zum HTL-Mechatronik-Server hergestellt:

```
kobi@MarkusPC:~$ nc -C www.htl-mechatronik.at 80
GET / HTTP/1.1
Host: www.htl-mechatronik.at:80
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:57.0) Gecko/20100101 Firefox/57.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: deflate
Upgrade-Insecure-Requests: 1
Hallo
```

Die erhaltene Antwort sah wie folgt aus:

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

## Was ist Typescript?
>TypeScript ist eine Sprache für JavaScript im Anwendungsmaßstab. TypeScript fügt JavaScript optionale Typen hinzu, die Tools für umfangreiche JavaScript-Anwendungen für jeden Browser, jeden Host und jedes Betriebssystem unterstützen. TypeScript kompiliert zu lesbarem, standardbasiertem JavaScript.

*[Typescript, npm](https://www.npmjs.com/package/typescript)*

### Visual Studio Code
Microsoft Visual Studio Code ist ein kostenloser, quelloffener Code-Editor zum Entwickeln und Debuggen moderner Cloud- und Webanwendungen. Er läuft unter Windows, Linux sowie macOS und bringt alles mit, was man zur Softwareentwicklung braucht.

Für eine angenehmere Benützung können folgende Verzeichnisse angepasst werden:

#### package.json
Die package.json-Datei ist eine Art Manifest für ein Projekt. Es kann eine Menge Dinge tun, die völlig unabhängig voneinander sind. Es ist zum Beispiel ein zentrales Konfigurationsrepository für Tools. Dort werden auch die Namen und Versionen des installierten Pakets gespeichert.

```
{
  "name": "restserver1",
  "version": "0.0.1",
  "description": "Restserver",
  "main": "main.js",
  "scripts": {
    "start": "node dist/main.js",
    "build": "./node_modules/gulp/bin/gulp.js build",
    "clean": "./node_modules/gulp/bin/gulp.js clean",
    "cleanAndBuild": "./node_modules/gulp/bin/gulp.js cleanAndBuild",
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "Markus Kobor",
  "private": true,
  "license": "MIT",
  "dependencies": {},
  "devDependencies": {
    "del": "^3.0.0",
    "gulp": "^3.9.1",
    "gulp-changed": "^3.2.0",
    "gulp-sourcemaps": "^2.6.4",
    "gulp-typescript": "^5.0.0-alpha.3",
    "gulp-using": "^0.1.1",
    "merge-stream": "^1.0.1",
    "run-sequence": "^2.2.1",
    "tslint": "^5.11.0",
    "typescript": "^3.1.1"
  }
}
```

#### tsconfig.json
Die Datei tsconfig.json ist für die Konfiguration des TypeScript-Compilers zuständig.

```
{
    "compilerOptions": {
        "module": "commonjs",
        "noImplicitAny": true,
        "removeComments": true,
        "preserveConstEnums": true,
        "sourceMap": true,
        "target": "ES2016",
        "experimentalDecorators": true,
        "noEmitOnError": true,
        "mapRoot": "./",
        "outDir": "./dist",
        "typeRoots": [ "node_modules/@types" ]
    },
    "include": [ "src/**/*.ts" ]
}
```

#### gulpfile.json
Das gulpfile ist für die Übersetzung zuständig.

```
// Node.js modules
const path = require('path');

// External modules,
// npm install --save-dev gulp gulp-changed gulp-typescript gulp-sourcemapsgulp-using 
// npm install --save-dev typescript del run-sequence merge-stream
const gulp       = require('gulp'),
      changed    = require('gulp-changed'),
      ts         = require('gulp-typescript'),
      sourcemaps = require('gulp-sourcemaps'),
      using      = require('gulp-using'),
      typescript = require('typescript'),
      del        = require('del'),
      sequence   = require('run-sequence'),
      merge      = require('merge-stream');
      ...
```

#### tslint.json
TSLint ist ein erweiterbares statisches Analysewerkzeug, das TypeScript-Code auf Lesbarkeit, Wartbarkeit und Funktionsfehler überprüft. Es wird weitgehend von modernen Editoren und Build-Systemen unterstützt und kann mit Ihren eigenen Fusselregeln, Konfigurationen und Formatierungselementen angepasst werden.

```
{
    "rulesDirectory": [],
    "rules": {
        "callable-types": true,
        "class-name": true,
        "comment-format": [
            true,
            "check-space"
        ],
        "curly": true,
        "eofline": true,
        "forin": true,
        "import-blacklist": [
            true,
            "rxjs"
        ],
        ...

```
