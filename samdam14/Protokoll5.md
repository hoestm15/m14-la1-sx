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
Gemessene Werte des Temperatursensors LM75 am *SURE-Board* sollen mittels Feldbusprotokoll auf den Computer übertragen werden. Dort sollen die Daten von einer *Java Swing Appliktion* bearbeitet und visualisiert werden. Benötigtes Wissen zur Lösung der Aufgabenstellung wird im folgenden Protokoll erklärt!  
  
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
Das Modbus-Protokoll wurde am Anfang zur Kommunikation zwischen zwei oder mehreren SPSen. In der Industrie hat sich *Modbus* als ein "De-Facto-Standard" hervorgehoben. De-Facto, da es sich um ein offenes Protokoll handelt. Die Version Modbus TCP ist aber dennoch seit 2007 Teil der Norm IEC 61158. Das Modbus-Protokoll findet sich heuzutage in der Hausautomatisierung/Haustechnik in Verbindung mit RS-485-Netzwerken. Durch Modbus lassen sich Geräte mit unterschiedlichsten Verbindungstechnolgien miteinander verbinden.  
[Wiki/Modbus](https://de.wikipedia.org/wiki/Modbus)  
[Wiki/Feldbus/Normung(IEC61158](https://de.wikipedia.org/wiki/Feldbus#Normung)  
  
Der Kommunikationsablauf von Modbus ist ein einfaches Master-Slave- / Server-Client-Prinzip. Der Client stellt eine Anfrage (*request*) an den Server. Dieser agiert aufgrund dieser Anfrage und sendet dem Client eine Antwort (*response*).  
![FunktionsweiseModbus](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/clientserver.png)  
Jeder Bus-Teilnehmer braucht eine eindeutige Adresse. (Adresse 0 ist für den Broadcast reserviert1). Theoretisch kann jeder Server und Client sein. Praktisch ist es aber, wenn ein *Master*/Server Anfragen stellt (z.B. an Aktoren oder Sensoren) und der jeweils adressierte *Slave*/Client mit einer Antwort antwortet.  
  
Bi Modbus unterscheidet man zwischen 3 Betriebsarten:  
* Modbus ASCII: byteweise Übertragung, textuell  
* Modbus RTU: byteweise Übertragung, binär  
* Modbus TCP: Übertragung in TCP-Paketen  
  
---------------------------------------------  
  
##### Protokollaufbau RTU  
> Im RTU-Modus wird der Sendebeginn durch eine Sendepause von mindestens der 3,5-fachen Zeichenlänge markiert. Die Länge der Sendepause hängt somit von der Übertragungsgeschwindigkeit ab. Das Adressfeld besteht aus acht Bit, die die Empfängeradresse darstellen. Der Slave sendet bei seiner Antwort an den Master ebendiese Adresse zurück, damit der Master die Antwort zuordnen kann. Das Funktionsfeld besteht aus 8 Bit. Hat der Slave die Anfrage des Masters korrekt empfangen, so antwortet er mit demselben Funktionscode. Ist ein Fehler aufgetreten, so verändert er den Funktionscode, indem er das höchstwertige Bit des Funktionsfeldes auf 1 setzt. Das Datenfeld enthält Hinweise, welche Register der Slave auslesen soll, und ab welcher Adresse diese beginnen. Der Slave setzt dort die ausgelesenen Daten (z. B. Messwerte) ein, um sie an den Master zu senden. Im Fehlerfall wird dort ein Fehlercode übertragen. Das Feld für die Prüfsumme, die mittels CRC ermittelt wird, beträgt 16 Bit. Das gesamte Telegramm muss in einem kontinuierlichen Datenstrom übertragen werden. Tritt zwischen zwei Zeichen eine Sendeunterbrechung auf, die länger als 1,5 Zeichen ist, so ist das Telegramm als unvollständig zu bewerten und sollte vom Empfänger verworfen werden.  
Quelle:[Wiki/Modbus](https://de.wikipedia.org/wiki/Modbus)  
##### Protokollaufbau ASCII
> Im ASCII-Modus beginnen Nachrichten mit einem vorangestellten Doppelpunkt, das Ende der Nachricht wird durch die Zeichenfolge Carriage return – Line feed (CRLF) markiert.
Die ersten zwei Bytes enthalten zwei ASCII-Zeichen, die die Adresse des Empfängers darstellen. Der auszuführende Befehl ist auf den nächsten zwei Bytes codiert. Über ein Zeichen folgen die Daten. Über das gesamte Telegramm (ohne Start- und Ende-Markierung) wird zur Fehlerprüfung ein LRC ausgeführt, dessen Paritätsdatenwort in den abschließenden zwei Zeichen untergebracht wird. Tritt während der Übertragung eines Frames eine Pause von > 1s auf, wird der Frame als Fehlerfall bewertet. Der Benutzer kann ein längeres Timeout konfigurieren.  
[AufbauASCII](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/modbus_serial_ascii_frame.png)  
Quelle:[Wiki/Modbus](https://de.wikipedia.org/wiki/Modbus)  
##### Protokollaufbau TCP  
TCP ist RTU sehr ähnlich, allerdings werden TCP/IP-Pakete verwendet, um die Daten zu übermitteln. Der TCP-Port 502 ist für Modbus-Server standartisiert reserviert. Da die TCP/IP-Pakete verwendet werden, wird grundsätzlich keine zusätzliche Adesse benötigt, weil sie die IP-Adresse und die Portnummer beinhalten.  
  
---------------------------------------------------  
  
##### Daten-Modell  
Das Modbus Daten-Modell unterscheidet vier Tabellen (Adressräume) für:  
* *Discrete Inputs*  
  * Ein Discrete Input ist ein einzelnes Bit, das nur gelesen werden kann  
  * Beispiele: ein Taster, ein Endschalter, ...  
* *Coils*  
  * Eine Coil ist ein Bit das gelesen und beschrieben werden kann  
  * Namensherkunft: Spule eines Relais  
  * Beispiele: ein Relais, eine LED, ...  
* *Input Registers*  
  * Ein Input-Register ist ein 16-Bit Wert, kann nur gelesen werden  
  * Beispiele: ein Temperatursensor, ein ADC, die Geräte-ID, ...  
* *Hold-Registers*  
  * Ein Hold-Register ist ein 16-Bit Wert, kann gelesen und beschrieben werden  
  * Beispiele: PWM-Einheit, DAC, ...  
  
Die Adressen beginnen immer bei 1, anders als üblich mit 0 in der IT.  

###### Function-Code  
> Der Function-Code in einem Modbus-Frame definiert die Bedeutung des Frames. Für Requests und Non-Error-Responses sind Werte zwischen 1 und 127 zulässig. Dieser Bereich ist in drei Kategorien unterteilt:  
> User defined Function Codes (65-72, 100-110)  
> - Das sind Werte die individuell verwenden dürfen.  
> Reserved Function Codes  
> 8 (19,21-65535), 9, 10, 13, 14, 41, 42, 90, 91, 125, 126, 127  
> - Das sind Werte die von einigen Unternehmen für Produkte verwendete wurden.  
> Public Function Codes  
> - Alle übrigen Werte. Hier definierte Funktionen werden eindeutig von der Modbus.org community festgelegt.  
Quelle: [LA1-Skript Modbus](https://lms.at/dotlrn/classes/htl_elektrotechnik/610437.4AHME_LA1.17_18/xolrn/E7BE8C85F66CA/2148F16AC6F2E.symlink?resource_id=0-236827434-257560369&m=view#167572781)  
(NUR ZUGÄNGLICH FÜR KURSTEILNEHMER!)  
-------------------------------------------------  
###### Exceptions  
>Ist ein Request fehlerhaft, so wird in der Response das Bit-7 im Function-Code Feld gesetzt. Dadurch entsteht aus dem Function-Code 1 bis 127 ein Wert 129 bis 255. Weiters wird im Daten-Bereich ein Exception-Code gesendet. Dieser lässt Rückschlüsse auf die Art des Fehlers zu.  
Exceptions decken ein breites Feld von Fehlerursachen ab. Welche es genau sind, können im oben genannten Skript nachgelesen werden.  
  
------------------------------------------------------  
  
##### Java Native Interface JNI  
Java Native Interface wird dazu benötigt, um eine Verbindung zur Kommunikation zwischen der Java VM und der seriellen Schnittstelle, die in unserem Betriebssystem liegt, herzustellen. Im Gegensatz zu gewöhnlichen Java-Programmen ist ein Java-Programm, das JNI-Aufrufe verwendet, nur dann plattformunabhängig, wenn die native Programmbibliothek auf allen Plattformen verfügbar ist. Diese Programmbibliotheken müüsen dann am richtigen Ort gespeichert werden, damit das JNI sie erkennt. Abhilfe verschafft der Java Simple Serial Connector JSSC, da er plattformabhängige native Bibliotheken von alleine installiert.  
Auf der Seite der JVM des JNIs befinden sich Methoden mit dem Schlüsselwort **native**.  
Auf der Seite des Betriebssystem befinden sich die binären Bibliotheken (z.B. bei Windows: .dll).  
Im Paket javax.comm liegt die Java-Programmier-Schnittstelle *Java Communications API*. Sie dient dazu, im generellen plattformunabhängig auf serielle, parallele und USB-Schnittstellen zuzugreifen. Quelle:[Wiki/JavaCommunicationsAPI](https://de.wikipedia.org/wiki/Java_Communications_API)  
[Wiki/JavaNativeInterfaces](https://de.wikipedia.org/wiki/Java_Native_Interface)  
  

|Betriebssystem | Architektur | Wortbreite | Kürzel|
|-------------- | ----------- | ---------- | ------|
| Linux | x86 | 32 bit/64 bit | .so |
| Linux | ARM | 32 bit | .so |
| MacOS | x86 | 32 bit/64 bit | .jnilib |
| MacOS | PowerPC | 32 bit/64 bit | .jnilib |
| Solaris | x86 | 32 bit/64 bit | .so |
| Windows | x86 | 32 bit/64 bit | .dll |

###### Grafische Erklärung zur Problemzone zwischen JVM und Betriebssystem  
![FunktionsweiseJNI](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/JNI.png)  
  

