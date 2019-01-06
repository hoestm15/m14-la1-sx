# Protokoll 17.12.2018

## 1. Einheit
Name: Muri Lorenz <br>
Klasse: 5AHME <br>
Gruppe: 2 <br>
Datum der Einheit: 17.12.2018 <br> 
Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Mario Nabernik, Muri Lorenz, Platzer Andreas <br>
Abwesend: Moritz Martinak <br>

## Thema: REST - Representational State Transfer

### REST
REST wird hauptsächlich wird bei Maschine-zu-Maschine-Kommunikation eingesetzt, dieses System ist auf einheitliche Schnittstllen aufgebaut dadurch ist REST eine einfacherer Programmierparadigma als zum Beispiel: SOAP [(Link zu Wikipedia)](https://de.wikipedia.org/wiki/SOAP) oder WSDL [(Link zu Wikipedia)](https://de.wikipedia.org/wiki/Web_Services_Description_Language). Zur Üertragung wird bei REST-Servern hauptsächlich mittels HTTP übertragen.
[Quelle Wikipedia](https://de.wikipedia.org/wiki/Representational_State_Transfer) <br>
<br>

### HTTP
[HTTP](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol) steht für Hypertext Transfer Protocol, dieses Protokoll wird zur Übertragung von Daten in einem Netzwerk verwendet. Um Daten verschlüsslet zu Übertragen verwendet man [HTTPS](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol_Secure).
<br>

### Funktionsweise/Prinzip
HTTP funktioniert nach dem klassichen Request-Response-Prinzip. Der Client schickt eine Anfrage(Request) an den Server, der mit einer Response antwortet.

![HTTP-Prinzip](https://github.com/HTLMechatronics/m14-la1-sx/blob/murlom14/murlom14-la1-2018_19/HTTP-Prinzip.jpg)
1. Zum Verindungsaufbau sendet der Client an den Server ein SYN-Package
2. Beim erfolgreichem Erhalten sendet der Server ein ARC-Package zurück und stimmt somit den Verbindungsaufbau zu.
3. Schlussendlich wird vom Client noch ein ACK-Package an den Server gesendet, dies bedeutet die Verbindung steht und Daten können ausgetauscht werden.
