# Laborprotokoll  
Erste Einheit am 24. Sept. 2018  
Martin Schmuck  
5AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: niemand  

## Thema der Einheit: (REST-)Server + HTTP + TypeScript
________

#### (Fern-)Kommunikation in der Automatisierungstechnik:  
Man nehme an, man möchte mit einem PC auf eine SPS zugreifen, Zustände abfragen und diese steuern. Dabei wurde lange Zeit eine Methode angewandt, welche durch die nachstehende Grafik veranschaulicht werden soll:  
![mit Feldbus](/smumam14/resources/fb.png)    
> &copy; 2018, Martin Schmuck  

Hier benötigt man Zusatzbibliotheken, die Programmierung wird ebenfalls verkompliziert.   
  
________________________________

In letzter Zeit wird versucht, sich mehr in Richtung des folgenden Konzepts zu bewegen: 
![HTTP](/smumam14/resources/http.png)    
> &copy; 2018, Martin Schmuck  

Diese Lösung verspricht eine einfachrer Realisierung, dafür kann die Sicherheit hier leiden.  
  
#### Grundbegriffe 
Abkürzung | Begriff | Aufgabe
----------|---------|----------
`HTTP` | `Hypertext Transfer Protocol` | Protokoll zur Übertragung von Webseiten  
`HTML` | `Hypertext Markup Language` | Seitenbeschreibungssprache, wobei das Wort Sprache hier eher fehl am Platz ist. Eigentlich eine Codierungsform, mit der die Struktur einer Webseite festgelegt wird. Bis in die späten 1980er-Jahre wurde hier auch das Aussehen geregelt.  
`CSS` | `Cascading Style Sheet` | legt das Erscheinungsbild der Seite fest  
`JavaScript` | | Programmiersprache für die clientseitige Programmierung  



#### Was ist ein REST-Server?
REST (=Representational State Transfer) - Server sind Programme, welche für eine webbasierte Kommunikation nach dem Server-Client-Prinzip bestimmt sind. Sie werden häufig zur Abfrage von Zuständen, z.B an einem entfernten System, eingesetzt. Diese Abfragen erfolgen in der Regel via HTTP. Gleich wie bei HTTP sind alle Anfragen zustandslos, das heißt, dass jede Anfrage für sich abgearbeitet wird und nicht durch vorhergehende Abfrage beeinträchtigt wird. Ein typische Anwendung wäre zum Beispiel das Programmieren einer Steuerungsapp für einen Wechselrichter, welcher elektrische Energie von den Photovoltaikzellen in die für die Netzeinspeisung benötigte Form umwandelt. Gerade bei solchen Use-Cases ist eine deartige Lösung oft schneller und leichter umzusetzen als zum Beispiel die Kommunikation über Modbus.

#### HTTP
![Server-Client-Prinzip](/smumam14/resources/sc.png)    
> &copy; 2018, Martin Schmuck  
  
Bei HTTP handelt es sich um ein textbasiertes, zustandsloses (siehe oben) Übertragungsprotokoll, welches für die Übertragung von Webseiten zwischen Server und Client zuständig ist. 

##### Aufbau eines HTTP-Pakets
Die HTTP-Pakete werden in Header und Body (Kopf und Rumpf) eingeteilt. Im Header verbergen sich Informationen über die verwendete HTTP-Version, die verwendete Codierung, die Größe des Bodys, etc., während im Body die eigentlichen Nutzdaten untergebracht werden. 

##### Ablauf einer Anfrage  
Der Server wartet im Ausgangszustand auf Anfragen vom Client. Der Client sendet an den Server ein sogenanntes `SYN`-Paket. Wird dieses Paket vom Server registriert, antwortet dieser mit einem `ACK`-Paket. Sobald der Client dies der Client erhält, sendet er ebenfalls ein `ACK`-Paket. Dann steht die Verbindung zwischen Server und Client.  Möchte einer der beiden Teilnehmer die Verbindung beenden sendet er ein `FIN`-Paket, der andere antwortet mit einem `FIN-ACK`-Paket.

###### Keep-alive-Pakete  
Logischerweise werden nicht ununterbrochen zwischen Server und Client Pakete hin- und herübertragen. Es kann z.B. im Falle eines Stromausfalls dazu kommen, dass ein Client nicht mehr sendet, die Verbindug bleibt dennoch vorerst offen (vom Server aus gesehen). Um "tote" Verbindugen nicht unnötig lange offen lassen zu müssen, wartet der Server meist ein Timeout im Bereich von bis zu zwei Minuten ab und schließt dann die Verbindung von selbst. Wenn der Client dies verhindern will, muss er in regelmäßigen Abständen `Keep-alive`-Pakete an den Server senden.  
  
##### HTTP-Befehle  
Das HTTP-Protokoll sieht eine Vielzahl an verschiedenen Befehlen vor. Die wichtigsten vier sind:   
  
  
Befehl (Methode) | Zweck  
-----------------|------  
`GET` | Daten vom Server abrufen.  
`POST` | Daten an den Server senden, die es dort schon gibt, also Daten ändern.  
`PUT` | Daten an den Server senden, die es dort noch nicht gibt (neue Inhalte erstellen).  
`DELETE` | Daten vom Server löschen.  
  
##### Statuscodes  
HTTP sieht dreistellige Nummern zur Statusmeldung vor.  
  
  
Nummernbereich | Bedeutung  
---------------|----------  
`1xx` | Die Abarbeitung der Anfrage dauert noch an.  
`2xx` | Erfolgreich
`3xx` | Weitere Schritte des Clients notwendig
`4xx` | Clientseitiger Fehler, z. B. `403` für unberechtigter Zugriff oder `404` für ein Dokument das nicht existiert
`5xx` | Serverseitiger Fehler  
  
#### HTTPS-Verbindung  
HTTPS ist die Erweiterung des HTTP-Protokolls um eine Möglichkeit der Verschlüsselung. Dabei werden zwei verschlüsselte Datenröhren aufgebaut, Server und Client müssen je über eine Encrypt- als auch eine Decryptfunktion und -stelle verfügen. Dabei werden die Daten sowohl gegen unbefugte Lese- als auch Schreibzugriffe geschützt.  
  
#### JavaScript  
JavaScript ist, anders als man vermuten möchte, in der Bedienung nicht mit Java zu vergleichen. Bei JavaScript handelt es sich um ein Programmiersprache, welche man primär für die clientseitige Programmierung verwendet. Seit einiger Zeit kann man diese jedoch auch für Server verwenden. JavaScript verfügt über eine schwache, dynamische Typisierung, was bedeutet, dass der Typ einer Variable erst durch den Inhalt festgelegt wird. Dies ist für manche Programmierer ein rotes Tuch, da dies zwar praktisch aber auch sehr fehleranfällig ist. Wir verwenden den Microsoft-Abkömmling dieser Sprache, der TypeScript genannt wird, dort werden viele Dinge (unter anderem die Typisierung) besser umgesetzt. 
___________________________
  
  
### Praktische Übungen  
Wir öffneten eine Konsole unter Ubuntu und versuchten, zu einem Server eine Verbindung aufzubauen. Die Syntax lautet:  
  
  `nc <Server-URL> <Portnummer>`  
    
 Dank der Einfachheit des HTTP-Protokolls kann man nun mit dem Terminal einen HTTP-Client interpretieren. So könnte eine einfache Anfrage aussehen:  
   
   ```
martin@schmuck:~$ nc www.htl-mechatronik.at 80

GET HTTP/1.1

HTTP/1.1 400 Bad Request
Date: Sun, 30 Sep 2018 18:07:58 GMT
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
  
Wie man sieht, hat das noch nicht funktioniert. Also sehen wir uns an, wie es der Broser macht:
``` 
GET / HTTP/1.1
Host: www.htl-mechatronik.at
Connection: keep-alive
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Ubuntu Chromium/69.0.3497.81 Chrome/69.0.3497.81 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
Accept-Encoding: gzip, deflate
Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7
If-None-Match: "1e9-50bf76235166b-gzip"
If-Modified-Since: Tue, 06 Jan 2015 08:13:36 GMT
  
HTTP/1.1 200 OK
Date: Sun, 30 Sep 2018 18:13:42 GMT
Server: Apache/2.4.7 (Ubuntu)
Last-Modified: Tue, 06 Jan 2015 08:13:36 GMT
ETag: "1e9-50bf76235166b-gzip"
Accept-Ranges: bytes
Vary: Accept-Encoding
Content-Encoding: gzip
Content-Length: 328
Keep-Alive: timeout=10, max=100
Connection: Keep-Alive
Content-Type: text/html
```  
  
Man sieht, dass hier noch einige andere Information mitgesendet werden, wie zum Beispiel in Zeile 6-8 der verwendete Browrser, die Sprache oder welche Art von Inhalten der Client unterstützt bzw. erwartert. Wenn wir jetzt diese Anfrage genau so ins Terminal kopieren, müssen wir beim Aufruf von `nc` noch die Option `-C` hinzufügen, da sonst die falschen Art von Zeilenvorschub mitgesendet werden (zum Beispiel `LF` statt `CR LF`).  Dann kommt auch ein brauchbare Antwort zurück. Wenn man jetzt noch die Zeile 7 mit Accept-Encoding weglässt, bekommt man wirklich in Plain Text im Terminal die Antwort des Servers, ansonsten würde diese mit gzip komprimiert werden und man sähe nur kryptische Zeichen am Schrim.  
  
#### Anlegen eines TypeScript-Projektes  
Da beim Kompilieren eines TypeScript-Projekts der Code zunächst in einen JavaScript-Code übersetzt wird, braucht man am Client TypeScript nicht zu installieren. Auf dem Entwicklungsrechner muss man es installieren, jedoch sollte dies immer im Projektverzeichnis erfolgen und niemals global. Das hat den Grund, dass es oft Updates gibt und sich Standards sehr schnell ändern. Dann hätte man mit verschiedenen Projekten, welche auf unterschiedlichen Versionen der Plattform basieren, schnell Probleme. Also erstellen wir uns ein leere Projektverzeichnis, in welches wir uns mit dem Terminal hineinnavigieren. Der Befehl `npm init` erstellt nach der Abfrage von einigen grundlegenden Infos zum Projekt eine Dateistruktur im Projektordner. 
  
  
```  
martin@schmuck:~$   node --version              // Die installierte node.js-Version prüfen (sollte min. V7 sein)
v7.10.1

martin@schmuck:~$   npm init                    // Package (Projekt) anlegen

This utility will walk you through creating a package.json file.
It only covers the most common items, and tries to guess sensible defaults.

See `npm help json` for definitive documentation on these fields
and exactly what they do.

Use `npm install <pkg> --save` afterwards to install a package and
save it as a dependency in the package.json file.

Press ^C at any time to quit.

name: (rest-server1) 
version: (1.0.0) 0.0.1
description: 5m la1 rest server 1
entry point: (index.js) main.js
test command: 
git repository: 
keywords: 
author: Martin Schmuck
license: (ISC) GPL-3.0
About to write to /home/cpt-kirk/rest-server1/package.json:

{
  "name": "rest-server1",
  "version": "0.0.1",
  "description": "5m la1 rest server 1",
  "main": "main.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "Martin Schmuck",
  "license": "GPL-3.0"
}


Is this ok? (yes) 
  ```  
Anschließend werden TypeScript und Express (= Paket mit nützlichen Tools) mit `npm install --save-dev typescript` und  `npm install --save express` installiert. Die Option `--save-dev` bzw. `--save` gibt an, dass diese beiden Pakete in der Konfigurationsdatei des Projekts vermerkt werden (siehe weiter unten). Daher muss man sich, falls man das Projekt zum Beispiel von einem Kollegen übernimmt, nicht alle Abhängigkeiten wie zB TypeScript mühsam nachinstallieren. Dies geschieht einfach mit `npm install`.  
  
Werfen wir abschließend noch einen Blick in die Datei `package.json`, wo sämtliche das Projekt betreffenden Informationen gespeichert werden.

```
cpt-kirk@xubuntu-n:~/rest-server1$ cat package.json 
{
  "name": "rest-server1",
  "version": "0.0.1",
  "description": "5m la1 rest server 1",
  "main": "main.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "Martin Schmuck",
  "license": "GPL-3.0",
  "devDependencies": {
    "typescript": "^3.0.3"  // ^ bedeutet, dass man eine Version verwenden kann, welche ungefähr der genannten entspricht.
  },
  "dependencies": {
    "express": "^4.16.3" 
  }
}
```
  
