# 1.Protokoll
**Name:** Zitz Karlheinz   
**Datum:** 13.10.2018  
**Uhrzeit:** 8:00-10:30  
**Gruppe:** 4  
**Anwesend:** Strauß Lukas, Strutz Sebastian, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz  
**Abwesend:** -  

# REST-Server  
REST-Server steht für **R**epresentational **S**tate **T**ransfer Server, der für die 
Maschine-zu-Maschine-Kommunikation in Werbsevices verwendet wird.HTTP ist das verwendete Übertragungsprotkoll.  
Ein REST-Server hat einige Prinzipien. Die wichtigsten sind :  
* Zustandslos  
* Client/Server  
* Einheitliche Schnittstelle  

# HTTP Server/Client  
HTTP steht für **H**yper**T**ext **T**ransfer **P**rotokoll. Die Übertragung zwischen Server und Client findet textuell statt und das Protokoll ist zustandslos. Das Protokoll überträgt Daten auf der Anwendungsschicht. Die Übertragung kan  man im folgenden Bild sehen.  
![HTTP](https://github.com/HTLMechatronics/m14-la1-sx/blob/zitkam13/zitkam13/http.png)  7

## Protokoll  
Das Übertragungsprotokoll ist textuell aufgebaut und basiert auf einem Server-Client Prinzip. Der Client sendet daher eine Anfrage, den sogenannten Request, und der Server sendet danach eine Antwort, den sogenannten Rsponse. Für den Request vom Client gibt es einige Schlüsselwörter:  
* **GET** -> Fordert Inhalte vom Server  
* **POST** -> Mit diesem SChlüsselwort kann man Daten ändern  
* **PUT** -> Neue Dateien können erstellt werden  
* **DELETE** -> Löscht Inhalte  
Mit einer Kosole kann man dieses Protokoll ausprobieren. Dafür benötigt man daś **nc** Tool. Wie eine solche Anfrage aussieht sieht man im follgenden Beispiel:  
```   
karlheinz@karlheinz-Aspire-E5-571G:~$ nc htl-mechatronik.at 80 -C
GET /infotext.html HTTP/1.1
Host: www.htl-mechatronik.at
```  
Bekommt ein Server eine Anfrage von einem Client schickt der Server eine Antwort zum Client zurück.   
Ein Beispiel einer Antwort ist zum Beispiel:  

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
### Statuscode  
Der Response vom Server enthält immer einen der folgenden Statuscodes:  

Statuscode | Bedeutung
---------- | ---------
1xx | Die Bearbeitung der Anfrage dauert noch an
2xx | Erfolgreiche Operation
3xx | Es sind noch weitere Schritte des Clients notwendig zur erfolgreichen Operation notwendig
4xx | Fehler des Clients
5xx | Fehler des Servers    


Weitere Informationen kan man unter dem folgenden [Link](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol) nachlesen. 
# Typescript
Typeskript ist eine von Microsoft entwickelte Programmiersprache und basiert auf JavaScript. Der TypeScript-Code wird daher vor dem Ausführen in einem JavaScript-Code **transpiliert**.   
Weitere Informationen kann man unter folgendem [Link](https://msdn.microsoft.com/de-de/magazine/dn890374.aspx) nachlesen.  
# Program  
Am Ende der Einheit,bevor wir mit den Wahlen de Schulsprechers begannen, ladeten wir uns das Programm der Gruppe 3 vom Gitweb-Repository herunter und löschten alle Inhalte in der **main.ts** Datei.  
[Link zum Gitweb- Repository](https://www.htl-mechatronik.at/gitweb/m14/?p=sx-la1.git;a=summary)
