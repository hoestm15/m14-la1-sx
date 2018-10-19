# Laborprotokoll  
Name: Sebastian Strutz  
Gruppe: 4  
Klasse: 5AHME  
Datum: Mo, 15. Oktober 2018  
Ort: Automatisierungslabor, Htbla Kaindorf  
  
Anwesend: Strauß, Strutz, Tuttner, Uhl, Waltl, Wieser, Zitz  
Abwesend: -  
## Thema: REST-Server  
Der Name **REST**-Server steht für **RE**presentational **S**tate **T**ransfer Server und wird meist für die Maschine-zu-Maschine-Kommunikation in Websevices verwendet. Das HTTP Protokoll wird als Sprache zwischen Server und Client verwendet. Rest Server werden häufig zur Abfrage von Zuständen, z.B. an einem entferntem System eingesetzt.
Der Architekturstil eines REST - Servers weist 6 Eigenschaften auf:  
1. **Zustandslosigkeit:** Die REST-nachricht enthält alle Informationen, dei für den Server/Client notwendig sind, um die Nachricht zu verstehen. Weder Server noch Client speichert Zustandsinformationen.  
2. **Client/Server Prinzip:** Client-Server-Architektur  
3. Catching: Ist eine Technik um Ressourcen anhand bestimmter Kriterien in einem Chache zwischenzuspeichern, um unötige Datenübetragungen oder Serveranfragen zu vermeiden.
4. **Einheitliche Schnittstellen:** Hauptunterscheidungsmerkmal von anderen Architekturstilen.   
Besteht aus weitern 3 Eigenschaften:  
              * Adressierbarkeit von Ressourcen: Jeder REST-konforme Dienst hat eine eindeutige Adresse.  
              * Repräsentaition zur Veränderung von Ressourcen: Ein REST-Server kann in verschiedenen Sprachen oder Formaten(HTML, JSON oder XML)   einer Ressource ausliefern.  
              * Selbstbeschreibende Nachrichten: REST-Nachrichten sind selbstbeschreiben.  
5. Mehrschichtige Systeme: Durch Mehrschichtige Systeme, wird die Architektur vereinfacht.  
6. Code on Demand: Unter Code on Demand ist zu verstehen, dass erst im Bedarfsfall an den Client, Code zur lokalen Ausführung übertragen werden kann.  

## Kommunikation in der Automatisierungstechnik  
Der klassische Ansatz Daten voon einem System(z.B. SPS) über eine kürzer Distanz zu einem PC zu übetragen, war über einen Feldbus. Dieser Ansatz bringt einige Probleme mitsich, z.B. zusätzliche Hardware. 
  
![Feldbus](https://github.com/HTLMechatronics/m14-la1-sx/blob/strsem13/strsem13/Feldbus.png)
  
Stattdessen wird heutzutage direkt über das Netzwerk gearbeitet. Das geschieht über HTTP-Server und HTTP-Clients. Das Problem an dieser Variante ist das Sicherheitsriskio.  
  
![Netzwerk über HTTP](https://github.com/HTLMechatronics/m14-la1-sx/blob/strsem13/strsem13/Netzwerk%20%C3%BCber%20HTTP.png)  

## TCP/IP

Transmission Control Protocol/ Internet Protocol ist eine Familie von Netzwerkprotokollen, die im OSI Schichten Modell auf Layer 4 (Transport Layer) arbeitet. Die Identifizierung erfolgt über IP-Adressen. Die Aufgabe des TCP/IP Protokolles ist die Datenübertragung innerhalb eines dezentralen Netzwerks. 

#### Verbindungsaufbau
Der Client sendet dem Server ein SYN-Paket, der Server empfägt das Paket. Falls der Port geschlossen ist, antwortet er mit einem TCP_RST Paket um zu signalisieren das keine Verbindung aufgebaut werden kann. Falls der Port geöffnet ist, sendet der Server ein SYN/ACK Paket zurück. Der Client sendet, nach Erhalt des SYN/ACK-Paketes, ein ACk-Packet an dem Server, um zu signalisieren, dass die Verbindung aufgebaut ist. Will einer der Teilnehmer die Verbindung trennen, so sendet er ein FIN-paket, der andere host antwortet dann mit einem FIN-ACk-Paket. 

![TCP/IP](https://github.com/HTLMechatronics/m14-la1-sx/blob/strsem13/strsem13/Verbindungsaufbau%20TCPIP.png)
  
## HTTP  
**HTTP** (**H**ypter**T**ext **T**ransfer **P**rotocol) ist ein Protokoll zur Übertragung von Daten auf der der Anwendungsschicht(OSI Schicht 7). Das Protkoll ist zustandslos, dass bedeutet das Informationen aus früheren Anforderungen verloren gehen, deshalb ist ein mitführen von Sitzungsdaten erforderlich. Um Daten verschlüsselt zu Übertragen gibt es das HTTPS Protokoll. Weiteres erfolgt die Übetragung textuell. 

### Verbindugsaufbau 
Die Kommunikation zwischen Slient und Server erfolgt durch Austausch von HTTP-Nachrichten. Dadurch das HTTP nicht auf Hyptertext beschrnkt ist, sondern auch zum Austausch von Daten verwendet wird, ist es auf ein weiteres Protokoll angewiesen. Für dieses Protokoll wird üblicherweise TCP eingesetzt.  
  
![HTTP](https://github.com/HTLMechatronics/m14-la1-sx/blob/strsem13/strsem13/Verbindungsaufbau%20HTTP.png)
  
### Keep-Alive Paket
Wenn eine Verbinndung zwischen Server und Client besteht werden nicht dauerhaft Pakete übertragen. Um zu verhindern, dass der Server die Verbindung aufgrund einer Überschreitung der Zeit abbricht kann der Client sogennante Keep-Alive-Pakete schicken um dem Server mitzuteilen, dass er immernoch "lebt" und die Verbindung aufrecht erhalten will. 
  
### Paketaufbau
HTTP Pakete werden in Header und Body (Kopf und Rumpf) eingeteilt. . Im Header verbergen sich Informationen über die verwendete HTTP-Version, die verwendete Codierung, die Größe des Bodys, etc., während im Body die eigentlichen Nutzdaten untergebracht werden. Die beiden werden durch eine Leerzeile getrennt.
  
### HTTP-Befehle  
Das HTTP-Protokoll sieht eine Vielzahl an verschiedenen Befehlen vor. Die wichtigsten vier sind:
* GET:     Daten vom Server abrufen    
* POST:    Daten zum Server schicken   
* PUT:     Daten auf den Server laden  
* DELETE:  Datem vom Server löschen    

## Praktische Übung
Zuerst wollten wir Daten vom Server abrufen, dies geschiet mit dem GET-Befehl. Zuerst musss aber eine Verbindung zu dem Server aufgebaut werden, dies funktioniert mit dem Befehl:  
```nc www.htl-mechatronik.at 80```  
Danach haben wir eine HTTP Anfrage gesendet:    
```GET / HTTP/1.1```  
Der Server hat mit einem Bad Request geantwortet:  
```
HTTP/1.1 400 Bad Request
Date: Fri, 19 Oct 2018 07:26:28 GMT
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
```` 
Um herauszufinden wieso der Server eine Fehlermeldung ausgegeben hat, haben wir einen Verbindung mit dem Local Host aufgebaut, und haben dann wieder eine HTTP-Anfrage gesendet. Um das auszuprobieren muss auf einem Browser ein Server erstellt werden, dazu muss man einen Browse starten, un den Folgenden URL eingeben:  
```http://localhost:4711/```  
Danach kann man das folgende in die Linux Konsole eingeben:  
```
nc -l 4711
GET / HTTP/1.1
```` 
Anschließend hat der Server wie folgt geantwortet: 
```
Host: localhost:4711
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:58.0) Gecko/20100101 Firefox/58.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Cache-Control: max-age=0
```
Der Fehler in der Anfrage war, dass unsere Anfrage einen normalen line feed verwendete. Der Server hingegen erwartete eine Kombination aus line feed und carriage return. Diesen Fehler konnten wir beheben indem wir beim nc-Tool eine Option (-C) auswählten, die den line feed umwandelte, so dass der Server die Zeilenumbrüche erkannte.  
Danach haben wir den nc-Befehl mit dem -C probiert:  
```
nc -C www.htl-mechatronik-at 80 
GET / HTTP/1.1
```  
Danach kam die gewünschte Antwort vom Server:  
``` 
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
### Rest-Client
Wir haben uns auch verschiedene Rest-Clients angeschaut und, über welche Funktionen diese Verfügen.

#### Installation Datein 
Zum Schluss der Einheit haben wir den Code von Linux geupdatet.   
[Link Code Update](https://code.visualstudio.com/docs/?dv=linux64_deb)  

Danach haben wir noch einen Ordner, vom Mechatronik Server heruntergeladen:    
[Link Mechatronik Server](https://www.htl-mechatronik.at/gitweb/m14/?p=sx-la1.git;a=tree;f=5AHME/g3/rest-server1/src;h=7db76bd7654e762a352c2182386aa541feca6f97;hb=a4385316c2cee94cc5348ec8be6a3fb0022d5d41)
