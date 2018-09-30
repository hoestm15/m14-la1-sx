# 1. Protokoll  
**Name:** Sackl Martin  
**Klasse** 5ahme  
**Gruppe:** 3  

Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster   
Abwesend: -  
*******************************************************************************************************************************************  
## REST-Server  
REST steht für die Abkürzung **R**epresentational **S**tate **T**ransfer.  
Diese Abkürzung bezeichnet ein Programmierparadigma für verteilte Systeme, insbesondere für Webservice. Der Zweck von REST liegt schwerpunktmäßig auf der Maschine-zu-Maschine-Kommunikation.  
Der REST-Server ist ein HTTP-Dienst, der HTTP-Statusabfragen zulässt.  

## Möglichkeiten für Systemsteuerung aus der Ferne  
1. Mit HTTP-Technik über das Netzwerk (Nicht so sicher wie die 2. Möglichkeit)  
![HTTP-Technik](https://github.com/HTLMechatronics/m14-la1-sx/blob/reibem14/reibem14/Netzwerk2.PNG)  
Image: Reinbacher Bernhard  

2. Mit Netzwerk/Feldbus/Gateway  
![HTTP-Technik](https://github.com/HTLMechatronics/m14-la1-sx/blob/reibem14/reibem14/Netzwerk1.PNG)  
Image: Reinbacher Bernhard  

## HTTP
HTTP steht für die Abkürzung **H**ypertext **T**ransfer **P**rotocol - Übertragungsprotokoll.  
Es ist ein zustandsloses Protokoll zur Übertragung von Daten. HTTP wird hauptsächlich eingesetzt, um Webseiten aus dem Worl Wide Web in einen Webbrowser zu laden. Diese Übertragung findet textuell statt.  

### Aufbau  
Die Kommunkationseinheiten zwischen Client und Server werden als Nachrichten bezeichnet. Es gibt zwei unterschiedliche Arten von Nachrichten: Request (Anfrage) vom Client an den Server und Response (Antwort) vom Server zum Client. 
Jede Nachricht besteht aus zwei Teilen dem Header und dem Body.  
Der **Header** enthält Informationen wie zum Beispiel Codierungen und den Inhaltstyp des Bodys.
Der **Body** enthält die Nutzdaten.  

### Funktion  
Das HTTP-Protokoll funktioniert nach dem Cient-Server-Prinzip. Der Client, meist ein Browser, sendet eine Request an den HTTP-Server, der daraufhin seine Response zurücksendet und die Verbindung schließt. 
Diese Kommunikation verläuft auf Basis von Meldungen im Text-Format.  

### Anfrage  
**Anfrage**|**Beschreibung**  
-----------|----------------  
GET|Ressourcen vom Server werden vom Client angefordert  
POST|Daten werden von Client an Server geschickt, URL muss am Server existieren  
PUT|Daten werden von Client an Server geschickt, URL kann am Server erstellt werden  
DELET|Daten werden vom Client am Server gelöscht  

### Statuscodes  
Ein HTTP-Statuscode wird von einem Server auf jede HTTP-Anfrage als Antwort geliefert.  

**Code**|**Beschreibung**  
--------|----------------  
1xx|Die Bearbeitung der Anfrage dauert noch an.  
2xx|Die Anfrage war erfolgreich, die Antwort kann verwertet werden.  
3xx|Um eine erfolgreiche Bearbeitung der Anfrage sicherzustellen, sind weitere Schritte seitens des Clients erforderlich.  
4xx|Die Ursache des Scheiterns der Anfrage liegt im Verantwortungsbereich des Clients.  
5xx|Die Ursache des Scheiterns der Anfrage liegt im Verantwortungsbereich des Servers.  

## NC-Tool
NC ist die Abkürzung für **N**et**C**at.  
NetCat ist ein universelles Kommandozeilenwerkzeug. Es wird im Terminal für die Kommunikation über Netzwerkverbindungen genutzt. Es wird also eine Verbindung zum Server hergestellt.  

#### Verbindungsaufbau Server  
```    
martin@martin-VirtualBox:~$ nc www.htl-mechatronik.at 80    //Verbindungsaufbau zum Server  
GET / HTTP/1.1                                              //Anfrage  
```     

###### Antwort  
```    
HTTP/1.1 400 Bad Request                                   //Statuscode  
Date: Mon, 24 Sep 2018 09:15:24 GMT  
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

#### Verbindungsaufbau LocalHost  
```    
martin@martin-VirtualBox:~$ nc -l 4711                        //Verbindungsaufbau zum LocalHost  
GET / HTTP/1.1                                                //Anfrage  
```  

###### Antwort  
```  
Host: localhost:4711  
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:58.0) Gecko/20100101 Firefox/58.0  //welcher Browser  
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8                   //was akzeptiert Browser  
Accept-Language: de,en-US;q=0.7,en;q=0.3                                                  //akzeptierte Sprachen  
Accept-Encoding: gzip, deflate                                                            //akzeptierte Codierung  
Connection: keep-alive                                                                    //Verbidnung offen halten  
Upgrade-Insecure-Requests: 1
```  
