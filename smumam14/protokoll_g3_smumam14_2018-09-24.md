# Laborprotokoll  
Erste Einheit am 24. Sept. 2018  
Martin Schmuck  
5AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: niemand  

## Thema der Einheit: (REST-)Server + HTTP + TypeScript
________

#### (Fern-)Kommunikation in der Automatisierungstechnik:  
Man nehme an, man möchte mit einem PC auf eine SPS zugreifen, Zustände abfragen und diese steuern. Dabei wurde lange Zeit eine Methode angewandt, welche durch die nachstehende Grafik veranschaulicht werden soll:  
![mit Feldbus](/smumam14/resources/fb.png)    
> &copy; 2018, Martin Schmuck  

Hier benötigt man Zusatzbibliotheken, die Programmierung wird ebenfalls verkompliziert.   
  
________________________________

In letzter Zeit wird versucht, sich mehr in Richtung des folgenden Konzepts zu bewegen: 
![HTTP](/smumam14/resources/http.png)    
> &copy; 2018, Martin Schmuck  

Diese Lösung verspricht eine einfachrer Realisierung, dafür kann die Sicherheit hier leiden.  
  
#### Grundbegriffe 
Abkürzung | Begriff | Aufgabe
----------|---------|----------
`HTTP` | `Hypertext Transfer Protocol` | Protokoll zur Übertragung von Webseiten  
`HTML` | `Hypertext Markup Language` | Seitenbeschreibungssprache, wobei das Wort Sprache hier eher fehl am Platz ist. Eigentlich eine Codierungsform, mit der die Struktur einer Webseite festgelegt wird. Bis in die späten 1980er-Jahre wurde hier auch das Aussehen geregelt.  
`CSS` | `Cascading Style Sheet` | legt das Erscheinungsbild der Seite fest  
`JavaScript` | | Programmiersprache für die clientseitige Programmierung  



#### Was ist ein REST-Server?
REST (=Representational State Transfer) - Server sind Programme, welche für eine webbasierte Kommunikation nach dem Server-Client-Prinzip bestimmt sind. Sie werden häufig zur Abfrage von Zuständen, z.B an einem entfernten System, eingesetzt. Diese Abfragen erfolgen in der Regel via HTTP. Gleich wie bei HTTP sind alle Anfragen zustandslos, das heißt, dass jede Anfrage für sich abgearbeitet wird und nicht durch vorhergehende Abfrage beeinträchtigt wird. Ein typische Anwendung wäre zum Beispiel das Programmieren einer Steuerungsapp für einen Wechselrichter, welcher elektrische Energie von den Photovoltaikzellen in die für die Netzeinspeisung benötigte Form umwandelt. Gerade bei solchen Use-Cases ist eine deartige Lösung oft schneller und leichter umzusetzen als zum Beispiel die Kommunikation über Modbus.

#### HTTP
![Server-Client-Prinzip](/smumam14/resources/sc.png)    
> &copy; 2018, Martin Schmuck  
  
Bei HTTP handelt es sich um ein textbasiertes, zustandsloses (siehe oben) Übertragungsprotokoll, welches für die Übertragung von Webseiten zwischen Server und Client zuständig ist. 

##### Aufbau eines HTTP-Pakets
Die HTTP-Pakete werden in Header und Body (Kopf und Rumpf) eingeteilt. Im Header verbergen sich Informationen über die verwendete HTTP-Version, die verwendete Codierung, die Größe des Bodys, etc., während im Body die eigentlichen Nutzdaten untergebracht werden. 

##### Ablauf einer Anfrage  
Der Server wartet im Ausgangszustand auf Anfragen vom Client. Der Client sendet an den Server ein sogenanntes `SYN`-Paket. Wird dieses Paket vom Server registriert, antwortet dieser mit einem `ACK`-Paket. Sobald der Client dies der Client erhält, sendet er ebenfalls ein `ACK`-Paket. Dann steht die Verbindung zwischen Server und Client.  Möchte einer der beiden Teilnehmer die Verbindung beenden sendet er ein `FIN`-Paket, der andere antwortet mit einem `FIN-ACK`-Paket.

###### Keep-alive-Pakete  
Logischerweise werden nicht ununterbrochen zwischen Server und Client Pakete hin- und herübertragen. Es kann z.B. im Falle eines Stromausfalls dazu kommen, dass ein Client nicht mehr sendet, die Verbindug bleibt dennoch vorerst offen (vom Server aus gesehen). Um "tote" Verbindugen nicht unnötig lange offen lassen zu müssen, wartet der Server meist ein Timeout im Bereich von bis zu zwei Minuten ab und schließt dann die Verbindung von selbst. Wenn der Client dies verhindern will, muss er in regelmäßigen Abständen `Keep-alive`-Pakete an den Server senden.  
  
##### HTTP-Befehle
Das HTTP-Protocol sieht eine Vielzahl an verschiedenen Befehlen vor. Die wichtigsten vier sind:
Befehl (Methode) | Zweck  
-----------------|------  
`GET` | Daten vom Server abrufen.  
`POST` | Daten an den Server senden, die es dort schon gibt, also Daten ändern.  
`PUT` | Daten an den Server senden, die es dort noch nicht gibt (neue Inhalte erstellen).  
`DELETE` | Daten vom Server löschen.  
  
##### Statuscodes
HTTP sieht dreistellige Nummern zur Statusmeldung vor.
Nummernbereich | Bedeutung
---------------|----------
`1xx` | Die Abarbeitung der Anfrage dauert noch an.  
`2xx` | Erfolgreich
`3xx` | Weitere Schritte des Clients notwendig
`4xx` | Clientseitiger Fehler, z. B. `403` für unberechtigter Zugriff oder `404` für ein Dokument das nicht existiert
`5xx` | Serverseitiger Fehler  

  
#### JavaScript  
JavaScript ist, anders als man vermuten möchte, in der Bedienung nicht mit Java zu vergleichen. Bei JavaScript handelt es sich um ein Programmiersprache, welche man primär für die clientseitige Programmierung verwendet. Seit einiger Zeit kann man diese jedoch auch für Server verwenden. JavaScript verfügt über eine schwache, dynamische Typisierung, was bedeutet, dass der Typ einer Variable erst durch den Inhalt festgelegt wird. Dies ist für manche Programmierer ein rotes Tuch, da dies zwar praktisch aber auch sehr fehleranfällig ist. Wir verwenden den Microsoft-Abkömmling dieser Sprache, der TypeScript genannt wird, dort werden viele Dinge (unter anderem die Typisierung) besser umgesetzt. 
