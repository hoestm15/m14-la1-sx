# Protokoll 13.02.2018  

## 5. Einheit  

## Thema: Modbus

Name: Moritz Martinak  
Lehrer: sx  
Gruppe: 2  
Übungsdatum: 13.02.2018  
Abwesend: Michael Mörth, Mario Nabernik, Marcel Köhler  

# Modbus  

## Grundlagen

Das Modbus-Protokoll wurde für die Kommunikatrion zwischen SPS Geräten entwickelt. Da es sich um ein kostenfreies System handelt und sich sowohl RS-232 Verbindungen, RS-385 Busse und TCP/IP Netzwerke umsetzen lassen können, wird es gerne in der Hausautomatisierung und Industreie verwendet.  
Über Modbus wird ein **Master** mit mehreren **Slaves** verbunden, dabei muss jeder Teilnehmer eine eindeutige Adresse besitzen. Die Adresse 0 ist für den Broadcast reserviert. Jeder Teilnehmer hat die Berechtigung Daten zu senden, jedoch regelt dies meist der Master.  
Es gibt drei Arten der Übertragung:  
- Modbus ASCII (byteweise Übertragung von Daten die im ASCII-Code codeirt sind)  
- Modbus RTU (byteweise Übertragung von Daten im Binärsystem)  
- Modbus TCP (Übertragung von Daten in TCP Paketen)  

## Kommunikation  

Die Kommunikation basiert auf einem Server/Vlient Prinzip. Dabei wird vom Client ein Request an den Server geschickt, dieser entfängt ihn und schickt die angefragten Daten zurück. ![Bild](https://github.com/HTLMechatronics/m14-la1-sx/blob/marmom13/marmom13/modbus_transaction_error_free_png.png)  
Genauer nachzulesen im [Skript](https://lms.at/dotlrn/classes/htl_elektrotechnik/610437.4AHME_LA1.17_18/xolrn/E7BE8C85F66CA/2148F16AC6F2E.symlink?resource_id=0-236827434-257560369&m=view#167572556).  

## Daten-Modell  
Das _Modbus-Daten-Modell_ wird in drei Tabellen unterschieden:  

| Art | Definition | Beispiel |
|:---:| ---------- | -------- |
| Discrete Inputs | Ein einzelnes Bit das nur gelesen werden kann | Taster, Endschalter... |
