# 1.Protokoll
**Name:** Uhl Christian   
**Datum:** 15.10.2018  
**Gruppe:** 4  
**Anwesend:** Strauß Lukas, Strutz Sebastian, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz  
**Abwesend:** -  

# REST-Server  
REST-Server steht für **R**epresentational **S**tate **T**ransfer Server, der für die 
Maschine-zu-Maschine-Kommunikation in Werbsevices verwendet wird. HTTP (**H**yper**T**ext **T**ransfer **P**rotocol) ist das verwendete Übertragungsprotkoll. Ein REST-Server hat einige Prinzipien. 
REST-Server ..  
* .. sind Zustandslos  
* .. basiert auf dem Client/Server Prinzip
* .. sind eine einheitliche Schnittstelle  
* .. benutzen HTTP-Chaching
* .. sind mehrschichtig aufgebaut
* .. Code on demand (Client kann Rechenoperationen für den Server ausführen)


# HTTP Server/Client  
Die Übertragung zwischen Server und Client findet textuell statt und das Protokoll ist zustandslos. Das Protokoll überträgt Daten auf der Anwendungsschicht. Die Übertragung wird im Folgenden Bild dargestellt.  
![HTTP](link)

## Protokoll  
Das Übertragungsprotokoll ist textuell aufgebaut und basiert auf einem Server-Client Prinzip. Der Client sendet daher eine Anfrage, den sogenannten Request, und der Server sendet danach eine Antwort, den sogenannten Rsponse. Für den Request vom Client gibt es einige Schlüsselwörter:  
* **GET** -> Fordert Inhalte vom Server  
* **POST** -> Mit diesem SChlüsselwort kann man Daten ändern  
* **PUT** -> Neue Dateien können erstellt werden  
* **DELETE** -> Löscht Inhalte
Wir benutzen das **nc**-Tool um eine Anfrage mit GET zu senden. Im Folgenden Beispiel wird zuerst die Eingabe des Users (also uns) und dann die Antwort des Servers.
```   
uhlga@PCvonChris:~$ nc htl-mechatronik.at 80 -C
GET /infotext.html HTTP/1.1
Host: www.htl-mechatronik.at
```  
Bekommt ein Server eine Anfrage von einem Client schickt der Server eine Antwort zum Client zurück.     

```
HTTP/1.1 200 OK
Date: Mon, 15 Oct 2018 08:48:24 GMT
Server: Apache/2.4.7 (Ubuntu)
Last-Modified: Tue, 06 Jan 2015 08:13:56 GMT
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

# Typescript
Typeskript ist eine von Microsoft entwickelte Programmiersprache und basiert auf JavaScript. Der TypeScript-Code wird daher vor dem Ausführen in einem JavaScript-Code transpiliert.   
Unter Transpelieren, das Ähnlichkeit mit dem Wort Compelieren hat, versteht man die umwandlung einer **T**ype**S**cript Datei (***.ts**) in eine **J**ava**S**cript Datei (***.js**).
Um Typscript zu installieren führten wir den Befehl `npm install --save-dev typescript` aus. Durch diesen Befehl wird Typescript im Projektordner fürs entwickeln installiert und wird nicht für das fertige Programm verwendet (Typescript wird zu Javascript übersetzt. Javascript wird zu Ausführung benötigt). 
Wir richteten uns zusätzlich die IDE *Visual Studio Code* ein, um benutzerfreundlicher damit arbeiten zu können. Dazu ladeten wir unter anderem die "nackte" .ts-Datei der Gruppe 3 herunter.
