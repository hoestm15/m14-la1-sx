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

Die Kommunikation basiert auf einem Server/Vlient Prinzip. Dabei wird vom Client ein Request an den Server geschickt, dieser entfängt ihn und schickt die angefragten Daten zurück.  
![Bild](https://github.com/HTLMechatronics/m14-la1-sx/blob/marmom13/marmom13/modbus_transaction_error_free_png.png)  
Genauer nachzulesen im [Skript](https://lms.at/dotlrn/classes/htl_elektrotechnik/610437.4AHME_LA1.17_18/xolrn/E7BE8C85F66CA/2148F16AC6F2E.symlink?resource_id=0-236827434-257560369&m=view#167572556).  

## Daten-Modell  
Das _Modbus-Daten-Modell_ wird in drei Tabellen unterschieden:  

| Art | Definition | Beispiel |
|:---:| ---------- | -------- |
| Discrete Inputs | Ein einzelnes Bit das nur gelesen werden kann | Taster, Endschalter... |
| Coils | Einzelnes Bit das gelesen und beschrieben werden kann | Relais, LED... |
| Input Register | Ein 16-Bit Wert der nur gelesen kann | Sensoren, ADC... |
| Hold-Registers | Ein 16-Bit Wert der gelesen und beschrieben werden kann | PWM-Einheit, DAC... |  

16 Bit-Werte werden dabei in der Big-Endian Variante versendet, das heißt das im Daten-Frame das höherwertige Byte als erstes versendet wird.  
![Bild](https://github.com/HTLMechatronics/m14-la1-sx/blob/marmom13/marmom13/modbus_addressing_model_png.png)  

Wie im Bild zu erkennen ist werden In einer Protocol Data Unit Werte von 0 bis 65535, im Modbus data model jedoch Adressen von 1 bis 65536 verwendet werden. Daher ist ein Adress-Mapping erforderlich.  
Genauer nachzulesen im [Skript](https://lms.at/dotlrn/classes/htl_elektrotechnik/610437.4AHME_LA1.17_18/xolrn/E7BE8C85F66CA/2148F16AC6F2E.symlink?resource_id=0-236827434-257560369&m=view#167572805).  

## Function-Codes  

In einem Modbusframe gibt es immer einen Function-Code der die Bedeutung des Frames definiert. Dabei sind Werte zwischen 1 und 127 für Non-Error-Responses zulässig. Diese werden in drei Bereiche unterteilt:  
- User defined Function Codes (65-72, 100-110)  
Dürfen Individuell verwendet werden.  
- Reserved Function Codes (8 (19,21-65535), 9, 10, 13, 14, 41, 42, 90, 91, 125, 126, 127)  
Werte die von Unternehmen für Produkte verwendtet wurden.  
- Public Function Codes (Alle übrigen Werte)  
Werte die von der Modbus-Community eindeutig festgelegt sind.  


