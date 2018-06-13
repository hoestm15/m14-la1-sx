# _Protokoll Siebente Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 15.05.2018**  
**Uhrzeit: 9:40-12:25**  
  
**Anwesenheit: _Es waren alle Schüler anwesend_**  
  
-----------------------------------------------------------  
#### Wiederholung Einheit 5 & 6  
Jene Schüler, die in der Einheit 6 nicht anwesend waren, wurden am Beginn der LAB-Einheit über den Stoff der 5ten und 6ten LAB-Einheit geprüft. Somit wurden unsere Gedächtnisse wieder auf den aktuellen Stand gebracht, da die letzte Einheit sehr lange her war.  
Es wurden die Themen *Serielle Schnittstellen in Java*, *UART*, *MODBUS* und *Feldbus* wiederholt.  
siehe: [Protokoll Einheit 6, Patrick Schuster](https://github.com/HTLMechatronics/m14-la1-sx/blob/suspam14/suspam14/Protokoll6.md) & [Protokoll Einheit 5, Daniel Sammer](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/Protokoll5.md)  
  
-----------------------------------------------------------  
#### Fortsetzung Projekt: Temperatur-Messung  
##### Swingworker  
Eine SwingWorker-Klasse ist eine abstrakte Klasse, mit der man länger andauernde GUI-Interaktionen in einem Background-Thread ablaufen lassen kann. Es können mehrere Background-Threads zum Ausführen solcher Aufgaben verwendet werden, da heutzutage Computer mehrere Prozessor-Kerne besitzt (siehe: [SwingWorker](https://docs.oracle.com/javase/8/docs/api/javax/swing/SwingWorker.html). Somit wird Multi-Tasking möglich und Multi-Threading ab hier zu einem sehr wichtigen Thema.  
  
###### Multi-Threading  
Mutli-Threading kann auch als Mehrsträngigkeit bezeichnet werden. Damit ist in der Informatik gemeint, dass das Abarbeiten mehrerer Threads quasi gleichzeitig stattfinden kann. Da hier die einzelnen Threads nicht voneinander abgeschottet sind (im Gegensatz zum Multi-Tasking), können diese sogenannten *Race-Conditiones* verursachen. Diese sollen durch Synchronisation vermieden werden.  
[Wiki/Mulithreading](https://de.wikipedia.org/wiki/Multithreading)  
[Wiki/Race-Conditions](https://de.wikipedia.org/wiki/Race_Condition)  
  
##### SingleMeasurementWorker  
Die Klasse *SingleMeasurementWorker* ist dafür da, damit in einem Background-Thread die Temperatur über die seriellen Schnittstelle abgefragt werden soll. Dafür soll die Klasse an das SureBoard (Slave -> Modbus) eine Anfrage senden.  

Der SingleMeasurementWorker soll an den Modbus-Slave (Sureboard) eine Anfrage senden, dass dieser den ausgelesenen Wert des Temperatursensors and die JAVA-Gui übermittelt. Dazu senden wir eine Anfrage mit 8 Bytes und warten 100ms auf eine Antwort. Falls kein Paket angekommen ist oder das Paket ungültig ist wird durch die Fehlerbehandlung eine Exception geworfen. Der empfangene Temperaturwert besteht aus zwei Bytes, einem High-Byte und einem Low-Byte. Das muss beim auslesen beachtet werden. Der aus den zwei Bytes zusammengerechnte Wert (zwischen 0 und 256) wird danach in Grad Celsius umgewandelt und zurückgegeben.

Der SingleMeasurementWorker ist eine JAVAl-Klasse, die in einem eigenen Thread die Temperatur über die serielle Schnitstelle einmalig abfragen soll. Ihm wird im Konstruktor die serielle Schnitstelle (serialPort) übergeben. Die Modbus-Anfrage besteht aus folgenden 8 Bytes: 2,4,0,0x30,0,1,0x31,0xf6.

Nach einer Wartezeit von 100ms wird die Antwort abgefragt und auf Herz und Nieren geprüft. Gegebenenfalls wird eine Exception geworfen. Sie soll aus 9 Bytes bestehen und die Werte der Temperaturmessung befinden sich an der 3. und der 4. Stelle. Löst die Antwort keine Exception aus, wird die Temperatur in Grad ausgerechet und zurückgegeben.
