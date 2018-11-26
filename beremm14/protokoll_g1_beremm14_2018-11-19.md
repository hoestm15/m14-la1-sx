# Protokoll
  Berger Emil  
  5AHME, Gruppe 1  
  19.11.18  
  Anwesend: Berger, Böcksteiner, Bullner, Ehmann, Enzi, Kobor, Köhler, Knappitsch  
  Abwesend: niemand  
    
# REST Server
> Representational State Transfer (abgekürzt REST, seltener auch ReST) bezeichnet ein Programmierparadigma für verteilte Systeme, insbesondere für Webservices. REST ist eine Abstraktion der Struktur und des Verhaltens des World Wide Web. REST hat das Ziel, einen Architekturstil zu schaffen, der die Anforderungen des modernen Web besser darstellt. Dabei unterscheidet sich REST vor allem in der Forderung nach einer einheitlichen Schnittstelle (siehe Abschnitt Prinzipien) von anderen Architekturstilen.
  
  *[Quelle: Wikipedia, REST-Server](https://de.wikipedia.org/wiki/Representational_State_Transfer)*
  Kurz gesagt wird der REST-Server für Maschine-zu-Maschine Kommunikation in Webservices verwendet, als Übertragungsprotokoll wird HTTP verwendet.  

# HTTP
> Das Hypertext Transfer Protocol (HTTP, englisch für Hypertext-Übertragungsprotokoll) ist ein zustandsloses Protokoll zur Übertragung von Daten auf der Anwendungsschicht über ein Rechnernetz.
  
  *[Quelle: Wikipedia, HTTP](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)*. 
  Zustandslos bedeutet, dass Informationen aus früheren Anwendungen verloren gehen, die Übertragung der Daten ist textuell.  
  Um Daten verschlüsselt zu verschicken gibt es [HTTPS](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol_Secure).  
  **[Dokumentation HTTP 1.1, Internet Engineering Task Force IETF](https://tools.ietf.org/html/rfc7230)**  

## Funktionsweise
HTTP funktioniert nach dem klassichen *Request-Response*-System.
Der Client schickt eine Request, auf die der Server mit einer Response antwortet.
(Server/Client, Req/Res, Master/Slave)

### Verbindungsaufbau
Der Server wartet auf ein **SYN**-Package, dass der Client schickt, wenn er eine Verbindung aufbauen möchte.
Wenn das **SYN**-Package angekommen ist, sendet der Server ein **ACK**-Package zurück.
Wenn das **ACK**-Package beim Client ist, sendet dieser auch ein **ACK** an den Server und dann ist die Verbindung aufgebaut.

### Paketaufbau
  HTTP-Pakete bestehen aus einem **Header** und einem **Body**.  
  Im Header befinden sich Informationen, die benötigt werden, um die Daten richtig zu interpretieren. (zB Codierung)  
  Im Body befinden sich die eigentlichen Daten, die angefordert wurden, oder gesendet werden sollen.  

### Requests

Request | Beschreibung  
------- | ---------  
GET | Daten vom Server abrufen  
POST | Daten an Server senden (für Weiterverarbeitung)  
PUT | Daten auf den Server hochladen  
DELETE | Daten vom Server löschen  

### Statuscodes

Statuscode | Beschreibung  
--- | ---  
1xx | Information (Status, falls die Bearbeitung der Anfrage länger dauert)  
2xx | erfolgreiche Operation  
3xx | Umleitung (Der Client muss weitere Informationen geben, um die Anfrage bearbeiten zu können)
4xx | Client-Fehler  
5xx | Server-Fehler  

### Keep Alive
Wenn über HTTP kommuniziert wird, ist es meistens gewünscht, dass die "Konversation" länger geführt wird und die Verbindung nicht nach einem Mal geschlossen wird. In diesem Fall wird im Header `Connection: Keep-Alive` eingetragen.

### Verbindung schließen
Wenn einer der Hosts die Verbindung schließen will, sendet er ein **FIN**-Package. Der andere antwortet mit einem **FIN-ACK**-Package und die Verbindung ist geschlossen.

## Übung im Terminal
  Es soll eine Verbindung zu einem Server hergestellt werden.  
  
  Mit dem *nc*-Tool in der Shell haben wir eine Verbindung zum Server der HTL Mechatronik hergestellt.  
  `Emils-MacBook-Pro:~ emil$ nc www.htl-mechatronik.at 80`  
  
  Danach haben wir die Anfrage `GET / HTTP/1.1` gesendet.  
  Folgende Antwort haben wir erhalten:  
  
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

  Unsere Anfrage war fehlerhaft, daher haben wir eine Verbindung mit dem localhost aufgenommen, um zu sehen, wie eine korrekte Antwort aussieht.  
  `Emils-MacBook-Pro:~ emil$ nc -l 4711`  
  
  ```
Host: localhost:4711
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/12.0 Safari/605.1.15
Accept-Language: de-at
DNT: 1
Accept-Encoding: gzip, deflate
  ```
  
  Wir haben unsere Anfrage so modifiziert, dass es der HTL-Server versteht.  
  
  Damit der Server den normalen *LineFeed* als *carriage Return* versteht, müssen wir zusätzlich *-C* angeben:  
  `Emils-MacBook-Pro:~ emil$ nc -C www.htl-mechatronik.at 80`  
  
  Unsere Anfrage an den Server sieht nun so aus:  
  ```
  GET /infotext.html HTTP/1.1
Host: www.htl-mechatronik.at
Connection: keep-alive
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/12.0 Safari/605.1.15
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de-at
DNT: 1
Accept-Encoding: deflate
  ```
  
  Die erhaltene Antwort ergiebt dies:  
  ```
Date: Sun, 25 Nov 2018 18:41:23 GMT
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
  
# Typescript
Typescript ist eine Skript-Sprache die zur Webentwicklung verwendet wird. Sie wird von Microsoft entwickelt und kommt von JavaScript. Der wesentliche Unterschied zwischen den beiden Sprachen ist der, dass Typescript für jede Variable einen Datentyp festlegt - da es JavaScript nicht macht, kommt es öfters zu Problemen. Typescript-Code muss erst in JavaScript-Code "transpiliert" werden, der dann ausgeführt werden kann.

## Visual Studio Code
Visual Studio Code ist eine IDE zur Programmierung von Typescript. Diese muss vor Benutzung umfassend eingerichtet werden. Dazu gibt es Informationen in meinem **[FIVU-Protokoll](https://github.com/HTLMechatronics/m14-5ahme-fivu/blob/beremm14/Protokoll_2018-10-05_beremm14.md)**, weiters folgen Auszüge daraus:

### [tsconfig.json](https://www.typescriptlang.org/docs/handbook/tsconfig-json.html)
Zuerst ist im Hauptverzeichnis des Projektes eine tsconfig.json-File zu erstellen. Darin sind Optionen festgelegt, die der Compiler benötigt um ein projekt zu transpilieren.
Beispielsweise kann man mit `"outDir": "./dist"` festlegen, dass Output-Dateien wie bei Netbeans im dist-Ordner zu finden sind, oder dass Input-Files für den Kompiler im Ordner src liegen.
  Transpilieren der .ts-Dateien über die tsconfig.json wird mit dem Command `tsc -p tsconfig.json`  
  *Vorischt: `tsc` funktioniert nur, wenn man es global installiert: `sudo npm install -g typescript`, ansonsten muss man vor dem tsc-Command noch den Verzeichnis-Pfad angeben.*

### settings.json
Im Ordner .vscode erstellt man eine settings.json-Datei, inder man einträgt, welche Dateien man nicht in Visual Studio sehen möchte.
```json
{
	"files.exclude": {
	    "**/node_modules": true,
	    "**/dist": true,
	    "package-lock.json": true,
	    ".vscode": true
	}
}
```

### Lint
Lint wird verwendet, damit wir freundlich dazu genötigt werden "schönen Code" zu produzieren. Die Datei tslint.json liegt im Hauptverzeichnis und man kann in ihr festlegen, welche "Fehler" gemeldet werden. (Zum Beispiel unnötige Leerzeichen oder fehlende Semicolons). Ohne diese Datei wird uns derartiges nicht angezeigt. Zusätzlich benötigen wir noch ein Plug-In, dazu aber unten mehr. Dazu muss auch das PlugIn in Code installiert werden.

### [Tasks](https://code.visualstudio.com/docs/editor/tasks)
Mit Hilfe von Tasks werden die einzelnen Schritte des transpilierens für die IDE automatisiert. Um dies zu realisieren gibt es so genannte Tasks - JavaScript-Files, die ausgeführt werden und in denen definiert ist, was zu tun ist, wenn wir in Visual Studio Code ein Projekt builden, cleanen, etc.
Wir verwenden **gulp**:
```js
gulp.task('build', function (done) {
    console.log("Task build gestartet");
    sequence('transpile', 'copyFiles', () => {
        console.log(finalMessage);
    });
});
```
Oben ist zu sehen der Gulp-Task `build`, der über ⇧⌘B oder in dem man in der Commandozeile "build" schreibt, aufgerufen werden kann.

## Projekt
  Gegen Ende der Einheit haben wir uns ein Projekt vom GIT-Server Arnfels geholt und in VSCode geöffnet.  
  [Link zum Repository](https://www.htl-mechatronik.at/gitweb/m14/?p=sx-la1.git;a=commit;h=a8dbc871d4fee14c3a3551867c334645403a8d5a)
