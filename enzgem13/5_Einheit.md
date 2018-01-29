# 5.Einheit: 23.01.2018

Gegenstand: LA1  
Name: Gert Enzi  
KN: 5  
Klasse: 4AHME  
Gruppe: 1  

## Vorstellung des Projekts: Temperaturmessung  
Die Aufgabe ist, mithilfe des Sure-Boards (ATMEGA16) eine Temperaturmessung durchzuführen. Das Ergebnis soll in einem Java Programm 
mit GUI angezeigt werden. Dich bevor wir mit dem Programm beginnen können muss zunächst die Datenübertragung geklärt bzw. festgelegt 
werden. Dafür wird ein entsprechendes Feldbusprotokoll benötigt. Dieses Feldbusprotokoll legt fest, wie Daten wohin übertragen werden.
Wir werden für unsere Zwecke *Modbus* verwenden, da man es kostenfrei beziehen kann und relativ leicht zu verstehen ist.

## Einführung: Modbus
Ursprünglich wurde das Modbus-Protokoll für die Kommunikation zwischen SPS Geräten entwickelt, Nun wird es in der Hausautomatisierung
und Industrie gerne verwendet, da es wie schon erwähnt kostenfrei ist und sich damit sowohl RS-232 Verbindungen, RS-485 Busse und 
TCP/IP Netzwerke umsetzen lassen. 
Mit Modbus kann ein **Master** mit mehreren **Slaves** verbunden werden.  
Jeder Busteilnehmer **muss** eine eindeutige Adresse besitzen. Die Adresse 0 ist hierbei für einen Broadcast (Datenpakete werden von
einem Punkt aus an alle Teilnehmer des Nachrichtennetzes gesendet) reserviert. Jeder Teilnehmer ist berechtigt, Nachrichten über den Bus 
zu senden, jedoch regelt dies meist der Master.  
**Master**......sendet eine Anfrage
**Slave**.......(adressiert) antwortet
Modbus ist also ein einfaches Protokoll, das auf dem Request/Response Prinzip aufgebaut ist.  
Man unterscheidet bei der Datenübertragung zwischen drei Betriebsarten:  
* Modbus ACSII (byteweise Übertragung von Daten - rein textuell)
* Modbus RTU   (byteweise Übertragung von Daten - binär)
* Modbus TCP   (Übertragung von Daten in TCP Paketen)
    
Die Kommunikation zwischen verschiedenen Teilnehmern innerhalb eines Systems beruht auf dem **Server/Client** Prinzip. Der Client (z.B. PC)
sendet eine Anfrage (Request) an den Server (Aktor, Sensor oder anderer PC) und als Antwort erhält der Client eine Antwort (Response) vom
Server. Kurz gesagt:  
```Client -> Request(Daten oder Codes) -> Server(führt Anweisung aus) -> Response -> Client(erhält die Antwort, meist Daten oder Codes)```
  
### Modbus Gateway  
Ein Gateway wird benötigt, wenn man verschiedene Varianten eines Feldbusprotokolls miteinander verbinden möchte (z.B.: TCP/IP mit 
RS232 verbinden). 
  
  
Genauere Infos zu Modbus: http://www.modbus.org/docs/Modbus_Application_Protocol_V1_1b3.pdf  
  
## Modbus Daten-Model  
Das Daten-Model unterscheidet zwischen vier Adressräumen(Register, Ausgänge...):  
* Discrete Inputs (ein Bit das nur gelesen werden kann)
* Coils (1 Coil entspricht 1 Bit das beschrieben und gelesen werden kann)
* Input Register (16 Bit Wert der nur gelesen werden kann)
* Hold Register (16 Bit Wert der gelesen und beschrieben werden kann)  
      
Die obigen Adressräume können für verschiedene Aufgaben verwendet werden. So wird ein *Discrete Input* in der Regel ein Taster oder Sensor sein und eine *Coil* für eine LED oder ein Relais verwendet werden.  

## Function Codes  
Function Codes werden dazu verwendet bestimmte Teile des Datenmodells zu erreichen und ebenso um andere Informationen im Frame 
bekanntzugeben.  
Für Requests verwendet man die folgenden Codes:
* User defined Function Codes (können vom Benutzer individuell verwendet werden)
* Reserved Funtion Codes (Werte, die von Unternehmen verwendet und reserviert wurden)
* Public Function Codes (Werte die von der Modbus.org community festgelegt wurden)  
  
Um besser zu verstehen, wofür Function Codes verwendet werden, sieht man sich am besten die Tabelle der Public Function Codes an.  
(Nur ein Auszug der Tabelle):  
| Function Code | Hex | Name | Typ |
|:-------------:| --- | ---- | --- |

  
