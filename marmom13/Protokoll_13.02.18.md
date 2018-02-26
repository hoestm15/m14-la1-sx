# Protokoll 13.02.2018  

## 5. Einheit  

## Thema: Modbus

Name: Moritz Martinak  
Lehrer: sx  
Gruppe: 2  
Übungsdatum: 13.02.2018  
Abwesend: Michael Mörth  

# Grundlagen Modbus  

Das Modbus-Protokoll wurde für die Kommunikatrion zwischen SPS Geräten entwickelt. Da es sich um ein kostenfreies System handelt und sich sowohl RS-232 Verbindungen, RS-385 Busse und TCP/IP Netzwerke umsetzen lassen können, wird es gerne in der Hausautomatisierung und Industreie verwendet.  
Über Modbus wird ein **Master** mit mehreren **Slaves** verbunden, dabei muss jeder Teilnehmer eine eindeutige Adresse besitzen. Die Adresse 0 ist für den Broadcast reserviert. Jeder Teilnehmer hat die Berechtigung Daten zu senden, jedoch regelt dies meist der Master.  
Es gibt bei der Datenübertragung drei Betriebsarten:  

- Modbus ASCII (byteweise Übertragung von Daten die im ASCII-Code codeirt sind)  
- Modbus RTU (byteweise Übertragung von Daten im Binärsystem)  
- Modbus TCP (Übertragung von Daten in TCP Paketen)  




