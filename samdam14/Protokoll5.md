# _Protokoll Fünfte Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 13.03.2018**  
**Uhrzeit: 9:40-12:25**  
  
**Anwesenheit: _Es waren alle Schüler anwesend_**  
  
-----------------------------------------------------------  
#### Wiederholung UART  
> Universal Asynchronous Receiver Transmitter ist eine elektronische Schaltung, die zur Realisierung digitaler serieller Schnittstellen dient. Dabei kann es sich sowohl um ein eigenständiges elektronisches Bauelement (ein UART-Chip bzw. -Baustein) oder um einen Funktionsblock eines höherintegrierten Bauteils (z. B. eines Mikrocontrollers) handeln.  

Eine UART-Schnittstelle dient zum Senden umd zum Empfangen von Daten über Datenleitungen. Die Übertragung erfolgt Byteweise (Bitweise seriell). Asynchron bedeutet, dass zu jedem beliebigen Zeitpunkt Daten übertragen werden können. Die Datenübertragung beginnt mit einem Start-Bit, gefolgt von den Daten und endet mit einem eventuellen Parity-Bit und 1, 1.5 oder 2 Stopp-Bits.  
![UART-Datenübertragung](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/uart.png)  
  
----------------------------------------------------------  
#### Projekt: Temperaturmessung  
![UART/Feldbus](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/feldbus.png)  
Gemessene Werte des Temperatursensors LM75 am *SURE-Board* sollen mittels Feldbusprotokoll auf den Computer übertragen werden. Dort sollen die Daten von einer *Java Swing Appliktion* bearbeitet und visualisiert werden. Benötigtes Wissen wird folgt im Protokoll!  
  
##### Feldbusprotokoll  
Damit man Daten vom SURE-Board auf den Computer übertragen kann, wird ein Feldbusprotokoll benötigt.  
Beispiele für Feldbusprotokolle:  
* Powerlink (B&R): echtzeitfähiges Ethernet, zur Übertragung von Prozessdaten in der Automatiserungstechnik (z.B. SPS)  
* ControllerAreaNetwork CAN (Intel): wurde zur Reduzierung der Kabelbäume in Fahrzeugen (damals bis zu 2km) entwickelt, für Automobilunternehmen  
* FlexRay: höhere Datenrate war durch kontinuierlichen Anstieg der Fahrerassistenz-Systeme notwendig (Antrieb und Fahrwerk), für Automobilunternehmen  
* LocalInterconnectNetwork: wird dann angewendet, wenn die Vielseitigkeit von CAN nicht benötigt wird, z.B. innerhalb der Tür eines Fahrzeugs, für Automobilunternehmen  
* Profinet (PROFIBUS): Process Field Network, nutzt TCP/IP und IT-Standards, ist Echzeit-Ethernet-fähig und ermöglicht die Integration in Feldbussystemen z.B. RS-485  

[Wiki/Feldbus](https://de.wikipedia.org/wiki/Feldbus)  
[Wiki/EthernetPowerlink](https://de.wikipedia.org/wiki/Ethernet_Powerlink)  
[Wiki/ControllerAreaNetwork](https://de.wikipedia.org/wiki/Controller_Area_Network)  
[Wiki/FlexRay](https://de.wikipedia.org/wiki/FlexRay)  
[Wiki/LocalInterconnectNetwork](https://de.wikipedia.org/wiki/Local_Interconnect_Network)  
[Wiki/Profinet](https://de.wikipedia.org/wiki/Profinet)  
  
Die oben genannten Feldbusprotokolle stehen alle in Verbindung mit Lizenzen und hohen Kosten. Damit sind sie für unser Protokoll nicht zu gebrauchen. Eine lizenz- und kostenfreie Alternative bietet das Feldbusprotokoll *Modbus*.  
  
-------------------------------------------------------------------  
  
##### Modbus  
![Modbus](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/modbus.JPG)  
Das Modbus-Protokoll wurde am Anfang zur Kommunikation zwischen zwei oder mehreren SPSen. In der Industrie hat sich *Modbus* als ein "De-Facto-Standard" hervorgehoben. De-Facto, da es sich um ein offenes Protokoll handelt. Die Version Modbus TCP ist aber dennoch seit 2007 Teil der Norm IEC 61158. Das Modbus-Protokoll findet sich heuzutage in der Hausautomatisierung/Haustechnik in Verbindung mit RS-485-Netzwerken.   
[Wiki/Modbus](https://de.wikipedia.org/wiki/Modbus)  
[Wiki/Feldbus/Normung(IEC61158](https://de.wikipedia.org/wiki/Feldbus#Normung)  
  
Der Kommunikationsablauf von Modbus ist ein einfaches Master-Slave- / Server-Client-Prinzip. Der Client stellt eine Anfrage (*request*) an den Server. Dieser agiert aufgrund dieser Anfrage und sendet dem Client eine Antwort (*response*).  
![FunktionsweiseModbus](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/clientserver.png)  
Jeder Bus-Teilnehmer braucht eine eindeutige Adresse. (Adresse 0 ist für den Broadcast reserviert1). Theoretisch kann jeder Server und Client sein. Praktisch ist es aber, wenn ein *Master*/Server Anfragen stellt (z.B. an Aktoren oder Sensoren) und der jeweils adressierte *Slave*/Client mit einer Antwort antwortet.  
  
Bi Modbus unterscheidet man zwischen 3 Betriebsarten:  
Betriebsart | Übertragungsweise
----------- | -----------------
Modbus ASCII | byteweise Übertragung, textuell
Modbus RTU | byteweise Übertragung, binär
Modbus TCP | Übertragung in TCP-Paketen



Mit Modbus kann ein Master mit mehreren Slaves verbunden werden. Jeder Teilnehmer des Netzwerkes ist berechtigt Daten zu übertragen, regeln tut dies der Master.

Man unterscheidet zwischen 3 Betriebsarten:

Modbus ASCII (byteweise Übertragung, textuell)
Modbus RTU (byteweise Übertragung, binär)
Modbus TCP (Übertragung in TCP-Paketen)

