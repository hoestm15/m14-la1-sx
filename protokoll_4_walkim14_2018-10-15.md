# *1. Laborprotokoll*

  Name: Kilian Waltl  
  Klasse: 5AHME   
  Datum: 15.10.2018   
  Anwesend: Strauß Lukas, Strutz Sebastian, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz    
  Abwesend: -
  
  ## Grundsätzlicher Aufbau von HTTP
  
  Ganz grundsätzlich werden Daten zwischen einem System (z.B. SPS) und einem PC über einen Feldbus übertragen. Feldbusse sind zum Beispiel Modbus, Profibus oder Powerlink.
  
  ![Feldbus](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/netzwerkFeldbus.png)
  
  Heute wird aber der Client mit dem Server direkt über das Netzwerk verbunden. Dies bringt jedoch ein Sicherheitsrisiko mit sich.
  
  ![Netzwerk Direkt](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/netzwerkDirekt.png)
  
  
  ## HTTP (Hypertext Transfer Protocol)
  
  Das HTTP ist ein zustandsloses Protokoll zur Übertragung von Daten. Es ist textuell aufgebaut und basiert auf einem Server-Client Prinzip (Request/Response). Für eine verschlüsselte Übertragung gibt es das HTTPS Protokoll.
  
  ![HTTP(s) Datenaustausch](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/requestResponse.png)
  
  ### Schlüsselwörter für den Request
  
* **GET**     -> Inhalte vom Server ansehen
* **POST**    -> Inhalte ändern
* **DELETE**  -> Inhalte löschen
* **PUT**     -> Neue Inhalte anlegen

 ### Aufbau eines Pakets
  
  Hier sieht man, dass ein HTTP Paket immer in Header und Body aufgeteilt sind. Im Header sind Informationen über das Protokoll (die verwendete Version), über den Client und über den Server. Im Body sind die Daten enthalten.
  
  ![Paketaufbau](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/paketaufbau.jpg)
  
  ## TCP/IP
  
  Das Transmission Control Protocol/Internet Protocol ist eine Familie von Netzwerkprotokollen. Die Identifizierung der Rechner geschieht über die IP-Adresse. Für TCP/IP gibt es verschiedene Hilfs- und Anwendungsprotokolle, wie zum Beispiel DHCP.
  
  Beim Verbindungsaufbau sendet der Client dem Server ein SYN-Paket. Ist der Port geöffnet, wird ein SYN/ACK Paket zurückgesendet. Kommt auch dieses Paket vom Server beim Client an, sendet der Client ein ACK-Paket um einen erfolgreichen Verbindungsaufbau zu signalisieren. Um eine Verbindung zu trennen, muss ein FIN-Paket gesendet werden.
  
  ![Verbindungsaufbau](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/Verbindungsaufbau.png)
  
  ## REST-Server
  
  Der Begriff Rest-Server steht für Representational State Transfer. Ein Rest-Server wird häufig zur Abfrage von Zuständen verwendet. Diese Abfragen erfolgen meist über HTTP und sind zudem zustandslos. Ein REST-Server hat 6 bestimmte Eigenschaften:
  
  * Zustandslos:  Jede REST-Nachricht enthält alle Informationen, die für den Server bzw. Client notwendig sind, um die Nachricht zu verstehen. Weder der Server noch die Anwendung soll Zustandsinformationen zwischen zwei Nachrichten speichern. 
  * Client/Server Prinzip:  Grundsätzlich gilt die Client-Server-Architektur
  * Caching:  Hiermit werden bestimmte Ressourcen gespeichert und unnötige Datenübertragungen vermieden.
  * Einheitliche Schnittstelle: Dies ist ein Hautpunterscheidungsmerkmal. Sie besteht aus vier Eigenschaften:
  
  -> Adressierbarkeit von Ressourcen
  
  -> Repräsentationen zur Veränderung von Ressourcen
  
  -> Selbstbeschreibende Nachrichten
  
  -> Hypermedia as the Engine of Application State
  
  * Mehrschichtige Systeme: Durch diese System wird die Architektur vereinfacht.
  * Code on Demand: Diese Forderung von Fielding ist optional. Unter Code on Demand ist zu verstehen, dass erst im Bedarfsfall an den Client Code zur lokalen Ausführung übertragen werden kann.
  

  ## Übung
  
  Zu Beginn versuchten wir mit einem Server eine Verbindung aufzubauen. Dies kann einfach über die Konsole erfolgen.
  
  Für den Serveraufbau verwendeten wir diesen Befehl:
  
  ` nc www.htl-mechatronik.at 80 `
  
  Mithilfe von GET wird die Anfrage gesendet:
  
  ` GET / HTTP/1.1 `
  
  Darauf erfolgte ein Bad Request:
  
  ```
HTTP/1.1 400 Bad Request
Date: , 15 Oct 2018 09:32:47 GMIT
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
  
  Der Bad-Request entstand dadurch, dass wir einen falschen Zeilenumbruch (line feed) verwendet haben. Der Fehler wurde einfach behoben, indem wir dem nc-Tool -C hinzufügten. Hiermit kann der Server auch die Zeilenumbrüche richtig erkennen.
  
  `
  nc -C www.htl-mechatronik-at 80 
  GET / HTTP/1.1
  `
  
  Mit diesem Befehl kam dann die erwartete Antwort:
  
```
Date: Mon, 15 Sep 2018 09:38:12 GMT
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
````
  
  Am Ende der Einheit haben wir uns noch das Programm der letzten Gruppe heruntergeladen und alles aus der main.ts gelöscht.
