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

