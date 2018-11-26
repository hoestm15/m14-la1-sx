# Protokoll: Marcel Köhler
## 3.Einheit
## Thema: REST Server
Klasse: 4AHME  
Anwesend: Berger, Böcksteiner, Bullner, Ehmann, Enzi, Kobor, Knappitsch, Köhler
Abwesend: niemand

## Rest Server
Ein REST-Server ist ein Server der für die Maschine-zu-Maschine Kommunikation verwendet wird. Der Architekturstile verweist auf 6 Einstellungen/Prinzipien die ein Dienst haben muss wobei nicht festgelegt ist wie diese Implementiert werden.

### Die 6 Prinzipien
#### Client-Server
Es sollen alle Eigenschaften des Server-Client Models verwendet werden.

#### Zustandslosigkeit
Jede Anfrage und Antwort ist so in sich geschlossen, dass weder der Server noch Client Zustandsinformationen zwischen zwei Nachrichten speichern muss.

#### Caching
> HTTP Caching soll genutzt werden, wobei aber gilt: Eine Anfrage, die nicht gestellt werden muss, ist die schnellste Anfrage.
*[Quelle: REST-Server Wikipedia](https://de.wikipedia.org/wiki/Representational_State_Transfer#Prinzipien)

#### Einheitliche Schnittstelle
Ziel ist es eine Einheitliche Schnittstelle zu haben die leicht zu implementieren ist. Diese Schnittstelle hat 4 Eigenschaften.

#### Mehrschichtige Systeme
> Die Systeme sollen mehrschichtig aufgebaut sein. Dadurch reicht es, dem Anwender lediglich eine Schnittstelle anzubieten. Dahinterliegende Ebenen können verborgen bleiben und somit die Architektur insgesamt vereinfacht werden.
*[Quelle: REST-Server Wikipedia](https://de.wikipedia.org/wiki/Representational_State_Transfer#Prinzipien)

#### Code on Demand (optional)
Unter Code on Demand ist zu verstehen, dass erst im Bedarfsfall an den Client Code zur lokalen Ausführung übertragen werden kann. Ein Beispiel hierfür wäre die Übertragung von JavaScript-Code bei einer HTML-Repräsentation.


## HTTP
> Das Hypertext Transfer Protocol (HTTP, englisch für Hypertext-Übertragungsprotokoll) ist ein zustandsloses Protokoll zur Übertragung von Daten auf der Anwendungsschicht über ein Rechnernetz. Es wird hauptsächlich eingesetzt, um Webseiten (Hypertext-Dokumente) aus dem World Wide Web (WWW) in einen Webbrowser zu laden. Es ist jedoch nicht prinzipiell darauf beschränkt und auch als allgemeines Dateiübertragungsprotokoll sehr verbreitet.
*[Quelle: Wikipedia HTTP](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)

### Funktionsweise
HTTP funktioniert nach dem Request-Response-System. Hierbei sendet der Client eine Anfrage zum Server der diese wiederum benatwortet. HTTPS funktioniert auf der selben weiße nur das vor dem senden der Anfrage zuerst mit dem öffintlichen Schlüssel des Server verschlüsselt wird.

### Anfragenaufbau
HTTP Pakete bestehen aus 2 Teilen, dem **Body**  und dem **Header**.
Im Header befinden sich Informationen um die Daten richtig zu interpretieren wie z.b. welche Version von HTML man benutzt, Statuscodes, Die länge der Daten, Datentyp (text o. anderes).
Im Body befinden sich die Daten die gesendet werden sollen.

![HTTP-Anfrage](https://github.com/HTLMechatronics/m14-la1-sx/blob/koemam13/Protokolle/Bilder/HTTP-Anfrage.svg)
<img src="https://github.com/HTLMechatronics/m14-la1-sx/blob/koemam13/Protokolle/Bilder/HTTP-Anfrage.svg">
