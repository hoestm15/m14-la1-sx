# Protokoll 23.01.2018

## 5. Einheit
## Thema: Modbus

Name: Markus Kobor  <br>
Klasse: 4AHME  <br>
Datum 23.01.2017  <br>
Gruppe: 1  <br>
Anwesend: Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Enzi Gert, Knappitsch Robert, Kobor Markus  <br>
Abwesend: -  <br>

### Aufgabe: Temperaturmessung

Ziel der Übung ist es, eine Temperaturmessung mit hilfe eines Temperatursensors, welcher über ein Sure-Board betrieben wird durchzuführen. Dazu sollen ein Java-Programm entwickelt und die Ergebnisse über eine vorgefertigte GUI ausgegeben werden.
Um diese Übung jedoch realisieren zu können, muss zuerst eine Methode festgelegt werden, die bestimmt, wie Daten zwischen dem Board und dem PC ausgetauscht werden.
Dies erfolgt über ein Feldbusprotokoll.
Wir haben **Modbus** als Protokoll festgelegt, da es kostenlos, und relativ leicht Verständlich ist.

### Modbus

Das **Kommunikationsprotokoll** Modbus, wurde für die Kommunikation zwischen speicherprogrammierbaren Steuerungen ins Leben gerufen.
Es findet häufig in der Industrie und Hausautomatisierung Verwendung, da es sich beim Modbus-Protokoll um einen offen Standard handelt. Außerdem lassen sich damit RS-232-Verbindungen, RS-485-Busse und TCP/IP-Netzwerke umsetzen.


Mittels Modbus können **ein Master**(fragt an) und **mehrere Slaves**(liefern Antwort) verbunden werden.

 Die Datenübertragung wird in drei verschieden Betriebsarten unterschieden:

    * Modbus RTU (bniäre Übertragung von Daten)
    
    * Modbus ASCII (textuelle, byteweise Übertragung von Daten)
   
    * Modbus TCP (Daten werden in TCP Paketen übertragen)
    
Der Ablauf der Kommuniktion wird über ein Server/Client Prinzip geregelt. Das bedeutet, dass ein Client (z.B. ein PC) ein **Request** an den Server stellt, (z.B. ein Sensor) welcher darauf mit einer **Response** antwortet.
Dabei muss jeder Busteilnehmer eine eindeutige Adresse besitzen. Die Adresse "0" ist dabei für einen Broadcast reserviert.
Alle Teilnehmer dürfen Nachrichten über den Bus senden, normalerweise wird dies aber vom Master geregelt.
