# Protokoll 5: Visualisierung eines Temperatursensors
Name: Patrick Schuster  
Klasse: 4AHME  
Gruppe: 3    
Anwesend: Reinbacher, Ruffenacht, Sackl, Sackl, Sammer, Schmuck, Schuster  
Abwesend: keiner

# Aufgabenstellung
Es soll eine Temperaturmessung mit dem integrierten Temperatursensor am Sure Board erfolgen. Das Messergebnis soll über eine Java Visualisierung am PC ausgegeben werden.
![dere](https://github.com/suspam14/la1/blob/master/SureBoard_PC.svg)

Der **LM75** ist ein Temperatursensor, welcher direkt am SURE Board verbaut ist und über I²C mit dem µC verbunden ist. Der µC liest die Messdaten aus und überträgt sie via UART an den PC übertragen. Die Messdaten werden danach in einer GUI, die mit Java Swing realisiert wird, ausgegeben. Um die Messdaten über PC zu übertragen wird ein **Feldbus** benötigt.

### Feldbus
Ein Feldbus ist ein Bussystem, dass Daten der Feldebene überträgt. In der Feldebene befinden sich Sensoren und Aktoren, diese werden über das Bussystem mit dem Steuergerät (z.B. SPS oder µC) verbunden.  
#### Es gibt viele verschiedene Feldbusse, die am häufigsten verwendeten Feldbusse sind:  
Feldbus | Verwendung  
--- | ---  
Powerlink | Maschinen- und Anlagenbau, basiert auf Ethernet  
Profibus | Maschinen- und Anlagenbau   
Modbus | offener Standard, universell einsetzbar  
LIN | Automobilindustrie, einfache Systeme  
CAN | Automobilindustrie, mittel komplexe Systeme  
Flexray | Automobilindustrie, sehr komplexe Systeme  

### Java Swing
Java Swing ist ein GUI-Toolkit für die Programmiersprache Java und ist eine unkomplizierte Lösung für das erstellen von GUIs. Java Swing benötigt keine große Einarbeitungszeit und besitzt im normalfall alle benötigten Controls. Für komplexere GUIs gibt es das GUI-Toolkit Java FX, dieses ist der desiginierte Nachfolger von Java Swing. Es benötigt, aber ermöglicht auch komplexere GUIs.  
[weitere Infos zu Java Swing](https://www.java-tutorial.org/swing.html)

### UART
UART steht für *Universal Asynchronous Reciever Transmitter* und ist eine **serielle Schnittstelle**. Sie wird häufig bei µCs verwendet.   
[weitere Infos zu UART](https://www.mikrocontroller.net/articles/UART)
### Asynchrone Datenübertragung
Wenn Daten asynchron übertragen werden, bedeutet das, dass die Daten jederzeit übertragen werden können. Hingegen zur synchronen Übertragung, bei dieser können Daten nur zu gewissen Zeiten übertragen werden.

### intelligenter/nicht-intelligenter Sensor
Ein intelligenter Sensor ist ein Sensor der das erfassen der Messgrößen und das verarbeiten des gemessenen Signals in einem kombiniert. Solche Sensoren haben meistens einen integrierten µC oder FPGA.
Ein nicht-intelligenter Sensor hingegen erfasst nur die Messgrößen und liefert ein Signal das erst durch z.B. die kombination aus ADC und eine Recheneinheit ausgewertet werden muss.  
#### Beispiele: 
* intelligneter Sensor:  
  * LM75 mit SURE Board  
* nicht-intelligneter Sensor:  
  * LM75 ohne SURE Board
  * PT100  
  
[weitere Infos zu intelligenten Sensoren](https://de.wikipedia.org/wiki/Smart-Sensor)

## Modbus
Bei der Auswahl eines Feldbusses viel unsere Wahl auf Modbus, da Modbus ein einfacher offener Standard ist. Offen bedeutet das man diesen Standard nicht kaufen muss um Einsicht in die Protokolle zu bekommen. 
Das Modbus Protokoll wurde 1979 für die Kommunikation zwischen zwei Speicherprogrammierbaren Steuerungen entwickelt. Heutzutage wird es meist für die Automatisierung in der Industrie und für Privatanwendungen verwenden. 
Modbus arbeitet nach dem **Server/Client-Prinzip**

