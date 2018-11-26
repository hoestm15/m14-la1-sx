# Protokoll: Marcel Köhler
## 1.Einheit
## Thema: REST Server
Klasse: 4AHME  
Anwesend: Berger, Böcksteiner, Bullner, Ehmann, Enzi, Kobor, Knappitsch, Köhler
Abwesend: niemand

## Rest Server
Ein REST-Server ist ein Server der für die Maschine-zu-Maschine Kommunikation verwendet wird. Der Architekturstiel verweist auf 6 Einstellungen/Prinzipien die ein Dienst haben muss wobei nicht festgelegt ist wie diese Implementiert werden.

### Die 6 Prinzipien
#### Client-Server
Es sollen alle Eigenschaften des Server-Client Models verwendet werden.

#### Zustandslosigkeit
Jede Anfrage und Antwort ist so in sich geschlossen, dass weder der Server noch Client Zustandsinformationen zwischen zwei Nachrichten speichern muss.

#### Caching
> HTTP Caching soll genutzt werden, wobei aber gilt: Eine Anfrage, die nicht gestellt werden muss, ist die schnellste Anfrage.
*[Quelle: REST-Server Wikipedia](https://de.wikipedia.org/wiki/Representational_State_Transfer#Prinzipien)

#### Einheitliche Schnittstelle
Ziel ist es eine Einheitliche Schnittstelle zu haben die leicht zu implementieren ist. Diese Schnittstelle hat 4 Eigenschaften.

#### Mehrschichtige Systeme
> Die Systeme sollen mehrschichtig aufgebaut sein. Dadurch reicht es, dem Anwender lediglich eine Schnittstelle anzubieten. Dahinterliegende Ebenen können verborgen bleiben und somit die Architektur insgesamt vereinfacht werden.
*[Quelle: REST-Server Wikipedia](https://de.wikipedia.org/wiki/Representational_State_Transfer#Prinzipien)

#### Code on Demand (optional)
Unter Code on Demand ist zu verstehen, dass erst im Bedarfsfall an den Client Code zur lokalen Ausführung übertragen werden kann. Ein Beispiel hierfür wäre die Übertragung von JavaScript-Code bei einer HTML-Repräsentation.


## HTTP
> Das Hypertext Transfer Protocol (HTTP, englisch für Hypertext-Übertragungsprotokoll) ist ein zustandsloses Protokoll zur Übertragung von Daten auf der Anwendungsschicht über ein Rechnernetz. Es wird hauptsächlich eingesetzt, um Webseiten (Hypertext-Dokumente) aus dem World Wide Web (WWW) in einen Webbrowser zu laden. Es ist jedoch nicht prinzipiell darauf beschränkt und auch als allgemeines Dateiübertragungsprotokoll sehr verbreitet.
*[Quelle: Wikipedia HTTP](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)

### Funktionsweise
HTTP funktioniert nach dem Request-Response-System. Hierbei sendet der Client eine Anfrage zum Server der diese wiederum benatwortet. HTTPS funktioniert auf der selben weiße nur das vor dem senden der Anfrage zuerst mit dem öffintlichen Schlüssel des Server verschlüsselt wird.

### Anfragenaufbau
HTTP Pakete bestehen aus 2 Teilen, dem **Body**  und dem **Header**.
Im Header befinden sich Informationen um die Daten richtig zu interpretieren wie z.b. welche Version von HTML man benutzt, Statuscodes, Die länge der Daten, Datentyp (text o. anderes).
Im Body befinden sich die Daten die gesendet werden sollen.

![HTTP-Anfrage](https://github.com/HTLMechatronics/m14-la1-sx/blob/koemam13/Protokolle/Bilder/HTTP-Anfrage.svg)


### Anfragen
Anfrage | Beschreibung
------- | ------------
GET | Daten vom Server abrufen
POST | Daten an den Server senden 
HEAD | zur überprüfung der Gültigkeit von Datem im Cache
PUT | Daten auf den Server hochladen
PATCH |  Daten am server verändern ohne sie ganz zu ersetzen
DELETE | Daten vom Server löschen
TRACE | liefert Anfragen so zurück wie der Server sie erhalten hat. Sinnvoll für debugging
OPTIONS | liefert eine Liste der vom Server unterstützten Methoden und Merkmale.
CONNECT | wird von Proxyservern implementiert, die in der Lage sind, SSL-Tunnel zur Verfügung zu stellen.

### Statuscodes
Statuscode | Beschreibung
---------- | ------------
1xx | Informationen
2xx | erfolgreiche Anfrage/Operation
3xx | Umleitung and eine andere Adresse
4xx | Client-Fehler
5xx | Server-Fehler


## Übungen mithilfe des Terminals
Es soll eine Verbindung mit dem Server in Arnfels hergestellt werden. Dazu haben wir das *nc*-Tool verwendet.

Wir erstellten eine Verbindung im Terminal die wie folgt aussieht:
`nc www.htl-mechatronik.at 80`

Anschließend machten wir eine GET-Anfrage welche so aussieht:
`GET / HTTP/1.1`

Als antwort haben wir folgendes bekommen:
```
HTTP/1.1 400 Bad Request
Date: Mon, 26 Nov 2018 05:13:53 GMT
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

Unsere Anfrage war fehlerhaft weswegen wir daraufhin eine Verbindung mit dem localhost hergestellt haben, um zu sehen wie eine korrekte Antwort aussieht.
`nc -l 4711`



```
Host: localhost:4711
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
User-Agent: Mozilla/5.0
Accept-Language: de-at
DNT: 1
Accept-Encoding: gzip, deflate
```
Nun haben wir unsere Anfrage zum HTL Server so verändert das auch dieser sie versteht.
`nc -C www.htl-mechatronik.at 80`

```
Host: www.htl-mechatronik.at
Connection: keep-alive
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de-at
DNT: 1
Accept-Encoding: deflate
```

Als Antwort haben wir folgendes bekommen:
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
   
   ## Visual Studio Code
   Visual Studio Code ist eine IDE welche von Microsoft entwickelt wird. In dieser kann man je nach installierten PlugIns viele verschiedene programmiersprachen verwenden. 
   
  ## Typescript
  Typescript ist eine Skript-Sprache die zur verwendunt von Webanwendungen verwendet wird. Sie stammt von JavaScript.
  Der unterschied zwischen den beiden sprachen ist das bei Typescript Datentypen verwendet werden und bei Javascript nicht welches dort zu vielen problemen führen kann. Typescript muss in JavaScript Transpiliert werden.
   
   ### Tasks
   Tasks sind dazu da um die einzelnen Schritte des transpilierens zu automatisieren. In diesen ist definiert was zu tun ist, wenn wir in Visual Studio Code ein Projekt Compilieren oder nur einen build erstellen.
   
  ### Lint
  Lint wird dazu verwendet um auf die Formatierung des Codes zu achten. Es weißt einen darauf hin das man zu viele Zeichen in einer Zeile benutzt hat oder anderes. Um dies zu verwenden muss man ein PlugIn installieren.
  wir verwenden **gulb**
  
  ### settings.json
  die Datei settings.json findet man in dem .vscode Verzeichnis. In dieser Datei kann mann Dateien hinzufügen die man nicht in Visual Studio sehen möchte.
  
  ### tsconfig.json
  In der tsconfig.json werden optionen für den Compiler festgelegt.
  Zum transpilieren der .ts-Dateien mithilfe der tsconfig.json muss man folgenden Befehl benutzen:
  `tsc -p tsconfig.json`
  * tsc funktioniert nur dann wenn man das tool global installiert hat. wenn dem nicht der fall ist muss man auch den Verzeichnis-Pfad angeben.
  
  
