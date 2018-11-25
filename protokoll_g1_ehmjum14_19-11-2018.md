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
Wir benutzen das **nc**-Tool um eine Anfrage mit GET zu senden.

# Typescript
Typeskript ist eine von Microsoft entwickelte Programmiersprache und basiert auf JavaScript. Der TypeScript-Code wird daher vor dem Ausführen in einem JavaScript-Code transpiliert.   
Unter Transpelieren, das Ähnlichkeit mit dem Wort Compelieren hat, versteht man die umwandlung einer **T**ype**S**cript Datei (***.ts**) in eine **J**ava**S**cript Datei (***.js**).  
Da einige von uns nicht bei Herr Prof. Steiner in Fivu sind mussten diese ca. 4-5 Personen noch Visual-Studio und sämtliche andere benötigten Datein und Programme herunterladen.
Um Typscript zu installieren führten wir den Befehl `npm install --save-dev typescript` aus. Durch diesen Befehl wird Typescript im Projektordner fürs entwickeln installiert und wird nicht für das fertige Programm verwendet (Typescript wird zu Javascript übersetzt. Javascript wird zu Ausführung benötigt).  
Weiters haben einige Schüler unserer Gruppe das Framework *Express* mit dem Befehl `npm install --save express` installiert. Dieses uns hilfreiche Werkzeuge für die Programmierung zu verfügung stellt. Es mussten deshalb nur einige Schüler installieren, da ein paar wenige diese Arbeiten bereits in Fivu gemacht haben.

