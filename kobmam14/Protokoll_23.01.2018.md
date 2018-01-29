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

Ziel der Übung ist es, eine Temperaturmessung mit hilfe eines Temperatursensors, welcher über ein Sure-Board betrieben wird durchzuführen. Dazu sollen ein Java-Programm entwickelt und die Ergebnisse über eine vorgefertigte GUI ausgegeben werden. <br>
Um diese Übung jedoch realisieren zu können, muss zuerst eine Methode festgelegt werden, die bestimmt, wie Daten zwischen dem Board und dem PC ausgetauscht werden. <br>
Dies erfolgt über ein Feldbusprotokoll. <br>
Wir haben **Modbus** als Protokoll festgelegt, da es kostenlos, und relativ leicht Verständlich ist.

### Modbus

Das **Kommunikationsprotokoll** Modbus, wurde für die Kommunikation zwischen speicherprogrammierbaren Steuerungen ins Leben gerufen. <br>
Es findet häufig in der Industrie und Hausautomatisierung Verwendung, da es sich beim Modbus-Protokoll um einen offen Standard handelt. Außerdem lassen sich damit RS-232-Verbindungen, RS-485-Busse und TCP/IP-Netzwerke umsetzen.


Mittels Modbus können **ein Master**(fragt an) und **mehrere Slaves**(liefern Antwort) verbunden werden.

 Die Datenübertragung wird in drei verschieden Betriebsarten unterschieden:

   * Modbus RTU (bniäre Übertragung von Daten)
    
   * Modbus ASCII (textuelle, byteweise Übertragung von Daten)
   
   * Modbus TCP (Daten werden in TCP Paketen übertragen)
      Der **TCP-Port 502** ist für Modbus/TCP reserviert.
    
Der Ablauf der Kommuniktion wird über ein Server/Client Prinzip geregelt. Das bedeutet, dass ein Client (z.B. ein PC) ein **Request** an den Server stellt, (z.B. ein Sensor) welcher darauf mit einer **Response** antwortet. <br>
Dabei muss jeder Busteilnehmer eine eindeutige Adresse besitzen. Die Adresse "0" ist dabei für einen Broadcast reserviert. <br>
Alle Teilnehmer dürfen Nachrichten über den Bus senden, normalerweise wird dies aber vom Master geregelt.

#### Modbus-Gateway

Unter Gateway versteht man einen Protokollumsetzter. Dies bedeutet, dass verschiedene Modbus-Varianten miteinander verbunden werden können. (zum Beispiel TCP/IP und RS-232)

### Daten-Modell

 Beim Modbus Daten-Modell wird in vier verschiedene Adressräume unterschieden:

   * Discrete Inputs (ein einzelnes Bit, welches nur gelesen werden kann)
      zum Beispiel: ein Taster
      
   * Coils (ein Bit, welches gelesen und beschrieben werden kann)
      zum Beispiel: eine LED
      
   * Input Registers (ein 16-Bit Wert der nur gelesen werden kann)
      zum Beispiel: ein Temperatursensor
    
   * Hold-Registers (ein 16-Bit Wert der gelesen und beschrieben werden kann)
      zum Beispiel: die Anzeige am Sure-Board
      

### Function-Codes

Über Function-Codes sind die Bedeutungen der Frames im Modbus-Frame defineiert. <br>
Für Requests und Non-Error-Responses werden folgende Codes verwendet:


   * User defined Function Codes (65-72, 100-110, dürfen individuell verwendet werden)
    
   * Reserved Function Codes (8, 9, 10, 13, 14, 41, 42, 90, 91, 125, 126, 127, Werte, welche von Unternehmen werwendet wurden)
   
   * Public Function Codes (alle zwischen 1 und 127 übrigen Werte, eindeutig von der Modbus.org community festgelegt)
   
An folgender Tabelle lassen sich die Bedeutungen einiger, wichtiger Public Function Codes ablesen:
   
   Function Code | Hex | Name | Typ
--------------- | --------- | --------- | ---
1 | 01 | Read Coils | Bit
2 | 02 | Read Discrete Inputs | Bit
3 | 03 | Read Holding Registers | 16-Bit
4 | 04 | Read Input Register | 16-Bit
5 | 05 | Write Single Coil | Bit
6 | 06 | Write Single Register | 16-Bit 
15| 0F | Write Multiple Coils |	Bit
16| 10 | Write Multiple Registers | 16-Bit


### Java Native Interface (JNI)

Da unser Projekt mit Hilfe von Java entwickelt werden soll, dieses jedoch keine seriellen Schnittstellen unterstüzt, benötigen wir JNI. Durch JNI ist es möglich, dass die Java VM und das Operating System miteinander kommunizieren können.

> JNI ermöglicht es, native Methoden zu schreiben für Situationen, in denen es nicht möglich ist, ausschließlich Java als Programmiersprache einzusetzen. Dies ist der Fall, wenn beispielsweise die Standard-Java-Klassenbibliothek bestimmte Plattform-abhängige Features oder andere Programmbibliotheken nicht unterstützt. Weiterhin ist es per JNI möglich, eine weitere in einer anderen Programmiersprache programmierte Anwendung für Java zugreifbar zu machen. Viele Klassen der Java-Standardbibliothek basieren auf JNI, um beispielsweise die Datei-Ein- und Ausgabe oder Soundwiedergabe zu ermöglichen. Indem Java Leistungs- und Plattform-abhängige Implementierungen in die Standardbibliothek integriert, kann der Java-Programmierer und -Nutzer diese Features in sicherer und Plattform-unabhängiger Weise nutzen.  
  *Quelle: [Wikipedia, JNI](https://de.wikipedia.org/wiki/Java_Native_Interface)* 
