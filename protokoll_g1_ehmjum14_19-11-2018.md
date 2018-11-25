# 1.Protokoll
**Name:** Julian Ehmann   
**Datum:** 19.11.2018  
**Gruppe:** 1  
**Anwesend:** Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Knappitsch Robert, Kobor Markus, Köhler Marcel  
**Abwesend:** -  

# REST-Server  
REST-Server ist die Abkürzung für **R**epresentational **S**tate **T**ransfer Server, der für die 
Maschine-zu-Maschine-Kommunikation in Werbsevices verwendet wird. HTTP (**H**yper**T**ext **T**ransfer **P**rotocol) ist das verwendete Übertragungsprotkoll. Ein REST-Server hat einige Prinzipien. 
REST-Server:    
* - sind Zustandslos  
* - basiert auf dem Client/Server Prinzip
* - sind eine einheitliche Schnittstelle  
* - sind mehrschichtig aufgebaut
* - Code on demand (Client kann Rechenoperationen für den Server ausführen)


# HTTP Server/Client  
Die Übertragung zwischen Server und Client findet textuell statt und das Protokoll ist zustandslos. Wird hauptsächlich dazu verwendet um Webseiten aus dem WWW in einen Webbrowser zu laden. HTTP versucht immer eine TLS-Verbindung zum Port 80 am Host aufzubauen. **Wichtig**: Client und Server sind **Keine** Rechner. Client und Server können sich auch auf dem selbem Rechner befinden. Weiters ist noch zu sagen, dass der Client eine Anfrage (**Request**) an den Server sendet und der Server nach Verarbeitung der Anfrage eine Antwort (**Respond**) zurück an den Client sendet.  


Für den Request vom Client gibt es einige Schlüsselwörter:  
* **GET** -> Fordert Inhalte vom Serveran  
* **POST** -> Mit diesem Schlüsselwort kann man Daten ändern  
* **PUT** -> Hiermit kann man neue Dateien erstellen   
* **DELETE** -> Löscht Inhalte  

## Keep-Alive Pakete
Wenn eine Verbinndung zwischen Server und Client besteht werden nicht dauerhaft Pakete übertragen. Um zu verhindern, dass der Server die Verbindung aufgrund einer Überschreitung der Zeit abbricht kann der Client sogennante *Keep-Alive-Pakete* schicken um dem Server damit mitzuteilen, dass er immernoch "lebt" und die Verbindung aufrecht erhalten will.  


Wir benutzen das **nc**-Tool um eine Anfrage mit GET zu senden. Im Folgenden Beispiel wird zuerst die Eingabe des Users (also uns) und dann die Antwort des Servers.
```   
aspirev17-julia:~$ nc htl-mechatronik.at 80 -C
GET /infotext.html HTTP/1.1
Host: www.htl-mechatronik.at
```  

Bekommt ein Server eine Anfrage von einem Client schickt der Server eine Antwort zum Client zurück.     

```
HTTP/1.1 200 OK
Date: Mon, 19 Nov 2018 08:48:24 GMT
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
Da einige von uns nicht bei Herr Prof. Steiner in Fivu sind mussten diese ca. 4-5 Personen noch Visual-Studio und sämtliche andere benötigten Datein und Programme herunterladen.
Um Typscript zu installieren führten wir den Befehl `npm install --save-dev typescript` aus. Durch diesen Befehl wird Typescript im Projektordner fürs entwickeln installiert und wird nicht für das fertige Programm verwendet (Typescript wird zu Javascript übersetzt. Javascript wird zu Ausführung benötigt).  
Weiters haben einige Schüler unserer Gruppe das Framework *Express* mit dem Befehl `npm install --save express` installiert. Dieses uns hilfreiche Werkzeuge für die Programmierung zu verfügung stellt. Es mussten deshalb nur einige Schüler installieren, da ein paar wenige diese Arbeiten bereits in Fivu gemacht haben.

