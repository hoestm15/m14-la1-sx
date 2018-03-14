# 4. Protokoll  
## Thema: Feldbus  
**Name:** Sackl Martin   
**Klasse** 4ahme    
**Gruppe:** 3

Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster   
Abwesend: -  
*******************************************************************************************************************************************  
## Aufgabenstellung  
Ziel der Übung ist es, eine Temperaturmessung mit hilfe eines Temperatursensors, welcher über ein Sure-Board betrieben wird durchzuführen. Dazu sollen ein Java-Programm entwickelt und die Ergebnisse über eine vorgefertigte GUI ausgegeben werden.
Um diese Übung jedoch realisieren zu können, muss zuerst eine Methode festgelegt werden, die bestimmt, wie Daten zwischen dem Board und dem PC ausgetauscht werden.  
Dies erfolgt über ein Feldbusprotokoll.  
Wir haben Modbus als Protokoll festgelegt, da es kostenlos, und relativ leicht Verständlich ist.  

## Temperatursensor  
Der Sensor LM75A ist ein Temperatursensor auf dem Sure-Board und ist mit dem µC mit I²C verbunden. Es ist ein "intelligenter" Sensor, dass bedeutet dass er einen Prozessor eingebaut hat und einen fertigen Temperaturwert zurückliefert. Bei "unintelligenten" Sensoren bekommt man eine Spanung zurückgeliefert und man muss sich seinen Wert selbst ausrechnen.   

## Felbus  
Es ist ein Bussystem, das in einer Anlage Feldgeräte und Stellglieder zwecks Kommunikation mit einem Automatisierungsgerät verbindet. Es gibt nomierte Protokolle um bei mehrere Kommunikationsteilnehmer ihre Nachrichten über dieselbe Leitung senden zu wissen, wer was wann sagt.  

Die erste Generation der Feldbustechnik wurde in den 1980er Jahren entwickelt, um die bis dahin übliche Parallelverdrahtung binärer Signale sowie die analoge Signalübertragung durch digitale Übertragungstechnik zu ersetzen. Heute sind viele unterschiedliche Feldbussysteme mit unterschiedlichen Eigenschaften am Markt etabliert. Seit 1999 werden Feldbusse in der Norm IEC 61158 weltweit standardisiert. Die zweite Generation der Feldbustechnik basiert auf Echtzeit-Ethernet.  

Folgende Felbusse sind zur Zeit üblich:  
* Modbus (Industrie)  
* Powerlink (Industrie)  
* Profibus (Industrie)  
* CAN (Automobilbereich)  
* LIN (Automobilbereich)  
* Flexray (Automobilbereich)  
* KNX (Haustechnik)  

## Modbus  
Anfänglich wurde Modbus für die Kommunikation zwischen SPS-Geräten entwickelt, etablierte sich aber in der Industrie als De-Facto-Standard, da es sich wie bereits erwähnt um ein offenes Protokoll handelt. Seit 2007 ist die Version Modbus TCP Teil der IEC 61158. Es lassen sich sowohl RS-232-Netzwerke, sowie TCP/IP-Netzwerke aufbauen. 
![](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacmam14/sacmam14/modbus_communication_stack.png)  

Mit Modbus kann ein Master mit mehreren Slaves verbunden werden. Jeder Teilnehmer des Netzwerkes ist berechtigt Daten zu übertragen, regeln tut dies der Master.  

Der Ablauf der Kommunikationen erfolgt über eine Client/Server-Architektur.  
![](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacmam14/sacmam14/clientserver.png)  

Die Datenübertragung wird in 3 Betriebsarten unterschieden:  
* Modbus RTU (bniäre Übertragung von Daten)  
* Modbus ASCII (textuelle, byteweise Übertragung von Daten)  
* Modbus TCP (Daten werden in TCP Paketen übertragen)  

### Protokollaufbau  
#### RTU  
m RTU-Modus wird der Sendebeginn durch eine Sendepause von mindestens der 3,5-fachen Zeichenlänge markiert. Die Länge der Sendepause hängt somit von der Übertragungsgeschwindigkeit ab. Das Adressfeld besteht aus acht Bit, die die Empfängeradresse darstellen. Der Slave sendet bei seiner Antwort an den Master ebendiese Adresse zurück, damit der Master die Antwort zuordnen kann. Das Funktionsfeld besteht aus 8 Bit. Hat der Slave die Anfrage des Masters korrekt empfangen, so antwortet er mit demselben Funktionscode. Ist ein Fehler aufgetreten, so verändert er den Funktionscode, indem er das höchstwertige Bit des Funktionsfeldes auf 1 setzt. Das Datenfeld enthält Hinweise, welche Register der Slave auslesen soll, und ab welcher Adresse diese beginnen. Der Slave setzt dort die ausgelesenen Daten (z. B. Messwerte) ein, um sie an den Master zu senden. Im Fehlerfall wird dort ein Fehlercode übertragen. Das Feld für die Prüfsumme, die mittels CRC ermittelt wird, beträgt 16 Bit. Das gesamte Telegramm muss in einem kontinuierlichen Datenstrom übertragen werden. Tritt zwischen zwei Zeichen eine Sendeunterbrechung auf, die länger als 1,5 Zeichen ist, so ist das Telegramm als unvollständig zu bewerten und sollte vom Empfänger verworfen werden.  
Quelle: [wikipedia.org](https://de.wikipedia.org/wiki/Modbus)  

#### ASCII  
Im ASCII-Modus beginnen Nachrichten mit einem vorangestellten Doppelpunkt, das Ende der Nachricht wird durch die Zeichenfolge Carriage return – Line feed (CRLF) markiert.  

Die ersten zwei Bytes enthalten zwei ASCII-Zeichen, die die Adresse des Empfängers darstellen. Der auszuführende Befehl ist auf den nächsten zwei Bytes codiert. Über ein Zeichen folgen die Daten. Über das gesamte Telegramm (ohne Start- und Ende-Markierung) wird zur Fehlerprüfung ein LRC ausgeführt, dessen Paritätsdatenwort in den abschließenden zwei Zeichen untergebracht wird. Tritt während der Übertragung eines Frames eine Pause von > 1s auf, wird der Frame als Fehlerfall bewertet. Der Benutzer kann ein längeres Timeout konfigurieren.  
Quelle: [wikipedia.org](https://de.wikipedia.org/wiki/Modbus)  

#### TCP  
Transaktionsnummer |	Protokollkennzeichen |	Zahl der noch folgenden Bytes | Adresse | Funktion | Daten  
-------------------|-----------------------|--------------------------------|---------|----------|-------  
2 Byte |	2 Byte (immer 0x0000) |	2 Byte (n+2) |	1 Byte |	1 Byte |	n Byte  

Quelle: [wikipedia.org](https://de.wikipedia.org/wiki/Modbus)  

### Objekttypen  
Lese- und Schreibzugriffe auf folgende Objekttypen ist möglich:  

Schnittstellentyp | Objekttyp | Zugriff | Größe  
------------------|-----------|---------|------  
Digitaler Eingang | "Discrete Input" | Lesen | 1 bit  
Analoger Eingang | "Input Register" | Lesen | 16 bit  
Digitaler Ein-/Ausgang | "Coil" | Lesen & Schreiben | 1 bit  
Analoger Ein-/Ausgang | "Holding Register" | Lesen & Schreiben | 16 bit  

### Function-Codes  
Über Function-Codes sind die Bedeutungen der Frames im Modbus-Frame definiert.  
Für Requests und Non-Error-Responses werden folgende Codes verwendet:  
* User defined Function Codes (65-72, 100-110, dürfen individuell verwendet werden)   
* Reserved Function Codes (8, 9, 10, 13, 14, 41, 42, 90, 91, 125, 126, 127, Werte, welche von Unternehmen werwendet wurden)  
* Public Function Codes (alle zwischen 1 und 127 übrigen Werte, eindeutig von der Modbus.org community festgelegt)  
  
An folgender Tabelle lassen sich die Bedeutungen einiger, wichtiger Public Function Codes ablesen:  
   
Function Code | Hex | Name | Typ  
--------------|-----| -----| ---  
1 | 01 | Read Coils | Bit  
2 | 02 | Read Discrete Inputs | Bit  
3 | 03 | Read Holding Registers | 16-Bit  
4 | 04 | Read Input Register | 16-Bit  
5 | 05 | Write Single Coil | Bit  
6 | 06 | Write Single Register | 16-Bit  
15| 0F | Write Multiple Coils |	Bit  
16| 10 | Write Multiple Registers | 16-Bit  

Für weitere, detailiertere Informationen siehe: [Modbus](http://www.modbus.org/docs/Modbus_Application_Protocol_V1_1b3.pdf)  
