# 1.Protokoll  
  
  **Name**:  *Sackl Roland*  
  **Datum:** *24.09.2018*  
  **Uhrzeit:** *8:00-10:30*  
  **Gruppe:** *3*  
  
  **Abwesend:**-   
  **Anwesend:**   Sackl Martin, Sackl Roland, Reinbacher Bernhard,Sammer Daniel,Ruffennacht Florian,Schuster Patrick,Schmuck Martin
   

----------------------------

# REST-Server  
REST-Server steht für **R**epresentational **S**tate **T**ransfer Server, der für die 
Maschine-zu-Maschine-Kommunikation in Werbsevices verwendet wird.HTTP ist das verwendete Übertragungsprotkoll.

# HTTP
HTTP steht für **H**yper**T**ext **T**ransfer **P**rotokoll. Das Protkoll ist zustandslos und die Übertragung findet textuell statt.Das Protokoll überträgt Daten auf der Anwendungsschicht.  

  
## Aufbau  
**Header**   
Der Header beinhaltet Informationen über den Server, dem Body und der Codierung.
Informtionen werden ausgetauscht über:
* die Codierung des Body 
* die Verbindungsqualität  
* spricht  der Server HTTP 
* Body Beginn und Ende
* die Länge der folgenden Nachricht  
 
**Body**
Der Body enthält die Nutzdaten.  
  

## Funktionsweise  

Eine  Anfrage(SYN Paket) wird von Client an den Server geschickt,währenddessen der Server auf die Anfragen wartet.War die Anfrage korrekt antwortet der Server mit einem ACK-Paket,welches wiederum auch der Client zurückschickt.Danach sind zwei Datenröhren für den Datentranfer bereitgestellt. Zum Beenden der Verbindung schickt zuerst einer der beiden ein FIN-Package darauf der andere mit einem FIN-ACK-Package antwortet.


  Anfrage | Bedeutung 
  ------- | ---------  
  GET | Cliet fordert Ressource von Server an  
  DELETE | Client löscht Daten am Server  
  POST | Client schickt Daten an Server, jedoch muss die URL bereits am Server existieren.  
  PUT | Client schickt Daten an Server, jedoch kann die URL bereits am Server erstellt werden.
 
## Statuscodes
Wenn vom Client eine Anfrage kommt muss der Server diese bearbeiten.Wobei leicht Fehler auftreten können.Um dem Client mitzuteilen, was vorgefallen ist sieht HTTP verschiedene Statuscodes vor.  

Statuscode | Beschreibung  
--- | ---  
1xx | Information (Zwischenantwort falls die Bearbeitung länger dauert)  
2xx | erfolgreiche Operation  (Anfrage wurde beantwortet und wird gesendet)  
3xx | Umleitung ( Client muss mehrere Informationen geben, um die Anfrage bearbeiten zu können)
4xx | Client-Fehler (Es ist ein Fehler aufgetreten der beim Client liegt
5xx | Server-Fehler (Es ist ein Fehler aufgetreten, der beim Server liegt)  
  
   
   
   
   ## Praktische Übungen mit nc  
 nc heißt Networt Client. Mit diesen Programm können wir eine Verbindungenzu einem Server aufbauen.
   
  
## NC-Verbindungsaufbau zu Server  
``
roland@roland-VirtualBox:~$ nc -l 4711 nc www.htl-mechatronik.at 80
``
## HTTP-Anfrage  
``
GET / HTTP/1.1
``
## Server-Antwort  
```
HTTP/1.1 400 Bad Request
Date: Mon, 24 Sep 2018 06:54:08 GMT
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
  
## NC-Verbindungsaufbau zu Localhost  
``
roland@roland-VirtualBox:~$ nc -l 4711
``
## Response  
``
Host: localhost:4711
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:58.0) Gecko/20100101 Firefox/58.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1
``
