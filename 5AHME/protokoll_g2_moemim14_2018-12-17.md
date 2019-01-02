# Protokoll
Michael Mörth  
5AHME, Gruppe 2  
17.12.18  
Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Mario Nabernik, Muri Lorenz, Platzer Andreas  
Abwesend: Moritz Martinak  

# REST-Server
> Representational State Transfer (abgekürzt REST, seltener auch ReST) bezeichnet ein Programmierparadigma für verteilte Systeme, insbesondere für Webservices. REST ist eine Abstraktion der Struktur und des Verhaltens des World Wide Web. REST hat das Ziel, einen Architekturstil zu schaffen, der die Anforderungen des modernen Web besser darstellt. Dabei unterscheidet sich REST vor allem in der Forderung nach einer einheitlichen Schnittstelle (siehe Abschnitt Prinzipien) von anderen Architekturstilen.
  
  *[Quelle: Wikipedia, REST-Server](https://de.wikipedia.org/wiki/Representational_State_Transfer)*  
  
Ein REST-Server wird dazu eingesetzt, um eine Maschine-zu-Maschine Kommunikation in Webservices umzusetzen. Das dabei verwendetet Übertragungsprotokoll ist HTTP.

# HTTP
> Das Hypertext Transfer Protocol (HTTP, englisch für Hypertext-Übertragungsprotokoll) ist ein zustandsloses Protokoll zur Übertragung von Daten auf der Anwendungsschicht über ein Rechnernetz.
  
  *[Quelle: Wikipedia, HTTP](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)*  

Unter einem zustandslosen Protokoll versteht man, dass Informationen aus früheren Anwendungen verloren gehen. Die Daten werden textuell übertragen und sind nicht verschlüsselt. Für das verschlüsselte Übertragen von Daten gibt es [HTTPS](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol_Secure).

## Funktionsweise von HTTP
HTTP basiert auf dem *Request-Response*-System. Das bedeutet, dass der Client einen *Request* sendet und der Server anschließend mit einem *Response* antwortet.

### Verbindungsaufbau
![HTTP-Handshake]()
