# 1.Protokoll  
  
  **Name**:  *Bernhard Reinbacher*  
  **Datum:** *24.09.2018*  
  **Uhrzeit:** *8:00 - 10:30*  
  **Gruppe:** *3*  
  
   
    
 **Abwesend:** niemand  
 **Anwesend:** Bernhard Reinbacher, Ruffenacht Florian, Sackl Martin, Sackl Roland, Sammer Daniel, Schmuck Martin, Schuster Patrick  
  
*********************************************************************************************************************************  
## Rest Server  
Dieser Server ist dazu da, um HTTP-Statusabfragen durchführen lässt. Weiter Infos: [Representational State Transfer](https://de.wikipedia.org/wiki/Representational_State_Transfer)
*********************************************************************************************************************************  
## Systemsteuerung aus der Ferne  
Um Systeme aus der Ferne zu steuern, gibt es einige Möglichkeiten.  
### über Feldbus/Gateway/Netzwerk  
![Netzwerk1](/reibem14/Netzwerk1.PNG)    
* * hier müssen eigene Bibliotheken instaliert werden und zusätzlich ist die Programmierung komplizierter  

### über Netzwerk mit HTTP-Technik   
![Netzwerk2](/reibem14/Netzwerk2.PNG)   
* *  einfach, da nur mit HTTP gearbeitet wird und diese Bibliotheken bereitsvorhanden sind  
     die Sicherheit leidet etwas darunter    
     *********************************************************************************************************************************   
## HTTP  
HTTP(Hypertext Transfer Protocol) ist ein Übertragungsprotokoll, das textbasiert funktioniert und für die Übertragung von Daten zwischen Server und Client dient. 
### Aufbau  
Im **Header** befinden sich Informationen über den Server, dem Body und der Codierung. Es werden Informationen ausgetauscht über:   
* die Verbindungsqualität  
* ob der Server HTTP spricht  
* die Länge der folgenden Nachricht  
* die Codierung des Body  
* Body Beginn und Ende    
  
Im **Body** sind die restlichen Daten vorhanden.    
  
Wichtig: zwischen **Header** und **Body** muss es eine Leerzeile geben. Damit kann der Serven den Unterschied zwischen den beiden erkennen.
  
### Funktionsweise  
Der Client schickt eine Anfrage(SYN Paket) an den Server, der währenddessen auf Anfragen wartet. Wenn die Anfrage korrekt war, antwortet der Server mit einem ACK-Paket, welches wiederum auch der Client zurückschickt. Danach sind zwei Datenröhren für den Datentranfer bereitgestellt.  

* Anfrage | Bedeutung  
  ------- | ---------  
  GET | Cliet fordert Ressource von Server an  
  POST | Client schickt Daten an Server, jedoch muss die URL bereits am Server existieren  
  PUT | Client schickt Daten an Server, jedoch kann die URL bereits am Server erstellt werden  
  DELETE | Client löscht Daten am Server  
********************************************************************************************************************************  
## nc Tool  
nc heißt Networt Client und ist ein Programm, zum Aufbauen von Verbindungen zu einem Server. Man arbeitet hierbei aus dem Terminal heraus und alles was darin geschrieben wird, wird sofort an den Server geschickt. Alle Daten die vom Server empfangen werden, werden im Terminal ausgegeben.       
  
      
Nach dem Aufruf von `nc www.htl-mechatronik.at 80*` bekommt man eine Antwort vom Server mitInformationen über die zuvor beschriebene HTTP-Verbindung. Wichtig hierbei ist, das man die URL korrekt eingibt und die dazugehörige Portnummer.  
```
 bernhard@bernhard-vm:~$ nc www.htl-mechatronik.at 80

HTTP/1.1 400 Bad Request
Date: Sat, 29 Sep 2018 12:17:46 GMT
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
  
Wenn man den lokalen Host kontakiert bekommt man folgende Informationen:  
```bernhard@bernhard-vm:~$ nc -l 4711

GET / HTTP/1.1

Host: localhost:4711		                                                                    
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:62.0) Gecko/20100101 Firefox/62.0	  	
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8		                  
Accept-Language: de,en-US;q=0.7,en;q=0.3	                                                  
Accept-Encoding: gzip, deflate	                                                                                                                                                                          
Connection: keep-alive		         
Upgrade-Insecure-Requests: 1  
```  
Information | Bedeutung  
----------- | ---------  
1.Zeile | mein lokaler Host = 4711  
2.Zeile | welcher Browser steckt dahinter?  
3.Zeile | was akzepiert der Browser?  
4.Zeile | welche Sprachen werden akzeptiert?  
5.Zeile | Client kann binäre Daten schicken, aber dann müssen diese richtig gezipt sein  
6.Zeile | Wenn die Anfrage kommt, soll Verbindung offen bleiben   
********************************************************************************************************************************

## HTTPs Verbindung    
HTTPs ist eine Erweiterung des HTTP Protokolls. HTTPs ist mit einer Transportverschlüsselung versehen um die Daten sicher übertragen zu können. Deshalb müssen Server und Client jeweils eine Encode und Decode Stelle besitzen.
![HTTPS](/reibem14/HTTPS.PNG)  
********************************************************************************************************************************  
## JavaScript  
JavaScript ist eine Sprache mit der man die Möglichkeit hat, HTML und Webbasiert zu programmieren. Obwohl man glauben könnte Java und JavaScript sind sich sehr änhlich, sind sie grundverschieden. Weitere Informationen: [JavaScriptTutorial](https://www.w3schools.com/js/default.asp)  
  
#### Rest-Server anlegen  
Um in JavaScript ein Programm schreiben zu können, muss man es sich im Projektordner installieren. Dies muss man machen, da es fast täglich neue Versionen gibt. Erstens wird ein package.json erstellt, das wichtige Informationen enthält.(json ist hier der Datentyp, welcher dank seiner Formatierung leicht zu lesen ist)  
```` 

  "name": "rest-server1",
  "version": "0.0.1",
  "description": "5 AHME LA GR3 Rest Server 1",
  "main": "main.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "Bernhard Reinbacher",
  "license": "MIT",
  "devDependencies": {
    "typescript": "^3.0.3"
  },
  "dependencies": {
    "express": "^4.16.3",
    "save": "^2.3.2"
  }
}  


    

