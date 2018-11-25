# Protokoll
  Berger Emil  
  5AHME, Gruppe 1  
  19.11.18  
  Anwesend: Berger, Böcksteiner, Bullner, Ehmann, Enzi, Kobor, Knappitsch  
  Abwesend: niemand  
    
# REST Server
> Representational State Transfer (abgekürzt REST, seltener auch ReST) bezeichnet ein Programmierparadigma für verteilte Systeme, insbesondere für Webservices. REST ist eine Abstraktion der Struktur und des Verhaltens des World Wide Web. REST hat das Ziel, einen Architekturstil zu schaffen, der die Anforderungen des modernen Web besser darstellt. Dabei unterscheidet sich REST vor allem in der Forderung nach einer einheitlichen Schnittstelle (siehe Abschnitt Prinzipien) von anderen Architekturstilen.
  
  *[Quelle: Wikipedia, REST-Server](https://de.wikipedia.org/wiki/Representational_State_Transfer)*
  Kurz gesagt wird der REST-Server für Maschine-zu-Maschine Kommunikation in Webservices verwendet, als Übertragungsprotokoll wird HTTP verwendet.  

# HTTP
> Das Hypertext Transfer Protocol (HTTP, englisch für Hypertext-Übertragungsprotokoll) ist ein zustandsloses Protokoll zur Übertragung von Daten auf der Anwendungsschicht über ein Rechnernetz.
  
  *[Quelle: Wikipedia, HTTP](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)*. 
  Zustandslos bedeutet, dass Informationen aus früheren Anwendungen verloren gehen, die Übertragung der Daten ist textuell.  
  Um Daten verschlüsselt zu verschicken gibt es [HTTPS](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol_Secure).  
  **[Dokumentation HTTP 1.1, Internet Engineering Task Force IETF](https://tools.ietf.org/html/rfc7230)**  

## Funktionsweise
HTTP funktioniert nach dem klassichen *Request-Response*-System.
Der Client schickt eine Request, auf die der Server mit einer Response antwortet.
(Server/Client, Req/Res, Master/Slave)

### Verbindungsaufbau
Der Server wartet auf ein **SYN**-Package, dass der Client schickt, wenn er eine Verbindung aufbauen möchte.
Wenn das **SYN**-Package angekommen ist, sendet der Server ein **ACK**-Package zurück.
Wenn das **ACK**-Package beim Client ist, sendet dieser auch ein **ACK** an den Server und dann ist die Verbindung aufgebaut.

### Paketaufbau
  HTTP-Pakete bestehen aus einem **Header** und einem **Body**.  
  Im Header befinden sich Informationen, die benötigt werden, um die Daten richtig zu interpretieren. (zB Codierung)  
  Im Body befinden sich die eigentlichen Daten, die angefordert wurden, oder gesendet werden sollen.  

### Requests

Request | Beschreibung  
------- | ---------  
GET | Daten vom Server abrufen  
POST | Daten an Server senden (für Weiterverarbeitung)  
PUT | Daten auf den Server hochladen  
DELETE | Daten vom Server löschen  

### Statuscodes

Statuscode | Beschreibung  
--- | ---  
1xx | Information (Status, falls die Bearbeitung der Anfrage länger dauert)  
2xx | erfolgreiche Operation  
3xx | Umleitung (Der Client muss weitere Informationen geben, um die Anfrage bearbeiten zu können)
4xx | Client-Fehler  
5xx | Server-Fehler  

### 
