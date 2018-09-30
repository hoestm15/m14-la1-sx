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

#### Kommunikation in der Automatisierungstechnik:  
Man nehme an, man möchte mit einem PC auf eine SPS zugreifen, Zustände abfragen und diese steuern. Dabei wurde lange Zeit eine Methode angewandt, welche durch die nachstehende Grafik veranschaulicht werden soll: 

#### Was ist ein REST-Server?
REST (=Representational State Transfer) - Server sind Programme, welche für eine webbasierte Kommunikation nach dem Server-Client-Prinzip bestimmt sind. Sie werden häufig zur Abfrage von Zuständen, z.B an einem entfernten System, eingesetzt. Diese Abfragen erfolgen in der Regel via HTTP. Gleich wie bei HTTP sind alle Anfragen zustandslos, das heißt, dass jede Anfrage für sich abgearbeitet wird und nicht durch vorhergehende Abfrage beeinträchtigt wird. Ein typische Anwendung wäre zum Beispiel das Programmieren einer Steuerungsapp für einen Wechselrichter, welcher elektrische Energie von den Photovoltaikzellen in die für die Netzeinspeisung benötigte Form umwandelt. Gerade bei solchen Use-Cases ist eine deartige Lösung oft schneller und leichter umzusetzen als zum Beispiel die Kommunikation über Modbus.


#### JavaScript
