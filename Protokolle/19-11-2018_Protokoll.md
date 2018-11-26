# Protokoll: Marcel Köhler
## 3.Einheit
## Thema: REST Server
Klasse: 4AHME  
Anwesend: Berger, Böcksteiner, Bullner, Ehmann, Enzi, Kobor, Knappitsch, Köhler
Abwesend: niemand

## Rest Server
Ein REST-Server ist ein Server der für die Maschine-zu-Maschine Kommunikation verwendet wird. Der Architekturstile verweist auf 6 Einstellungen/Prinzipien die ein Dienst haben muss wobei nicht festgelegt ist wie diese Implementiert werden.

### Die 6 Prinzipien
#### * Client-Server
Es sollen alle Eigenschaften des Server-Client Models verwendet werden.

#### * Zustandslosigkeit
Jede Anfrage und Antwort ist so in sich geschlossen, dass weder der Server noch Client Zustandsinformationen zwischen zwei Nachrichten speichern muss.

#### * Caching
> HTTP Caching soll genutzt werden, wobei aber gilt: Eine Anfrage, die nicht gestellt werden muss, ist die schnellste Anfrage.
*[Quelle: REST-Server Wikipedia](https://de.wikipedia.org/wiki/Representational_State_Transfer#Prinzipien)
