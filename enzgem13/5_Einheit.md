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

[Grafik: Server-Client]

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
  

  
