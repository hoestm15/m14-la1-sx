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
![](https://github.com/suspam14/la1/blob/master/modbus_transaction_error_free_png.png)
### Die 3 Varianten der Übertragung:
Variante | Beschreibung  
--- | ---  
ASCII | Rein textuelee Übertragung von Daten  
RTU (Remote Terminal Unit)  | binäre byteweise Übertragung von Daten  
TCP |  Übertragung der Daten in TCP Paketen  

Die *RTU* Variante hat den Nachteil, dass Paketende und Paketanfang durch Pausen detektiert werden, was zu Problemen mit diversen Betriebssystemen führen kann. Hierfür gibt es keine Lösung, mit der man nicht vom Protokoll abweichen würde.

### ASCII Transmission Mode
Im ASCII Transmission Mode werden die Daten als ASCII-Zeichen versendet. Als Übertragungskonfiguration für die serielle wird hier 7E1 oder 7N2 empfohlen. Es werden nur 7 Datenbits benötigt da ein ASCII-Zeichen nur 7 Bits braucht. Bei Bedarf ist es auch möglich von der empfohlenen Konfiguration abzuweichen.
#### Datenpaket im ASCII Transmission Mode
![](https://github.com/suspam14/la1/blob/master/modbus_ascii.png)
Die Übertragung wird mit einem `:` eingeleitet.

### Aufbau eines Pakets in Modbus
![](https://github.com/suspam14/la1/blob/master/modbus_units.png)
Ein Paket in Modbus beginnt mit der Adresse des Gerätes welches das paket empfangen soll. Die Adressen werden beim Konfigurieren des Bussystems festgelegt. Danach folgt der Kernbestandteil des Datenpakets, der Funktionscode und die Daten. Diesen Kernbestandteil nennt man **PTU** (Protocoll Data Unit). Das ganze Paket nennt man **ADU** (Application Data Unit). Im ASCII oder RTU Mode ist am Ende des Pakets noch eine Prüfsumme dabei. Im TCP Mode wird diese nicht benötigt, da das TCP Protokoll eine eigene Prüfsumme besitzt.

### Daten-Modell
Das Daten-Modell von Modbus unterscheidet sich in 4 Bereiche:
Name | Verwendung 
--- | ---  
Discrete Inputs | einzelnes bit, nur lesbar  
Coils | einzelnes bit, les- und beschreibbar  
Input Registers | 16-bit Register, nur lesbar   
Hold Registers | 16-bit Register, les- und beschreibbar  

### Funktionscodes
In jeder Anfrage über Modbus befindet sich ein Funktionscode, der die Art der Anfrage wiederspiegelt. Es sind Werte zwischen 1 und 127 zulässig. Ein Teil der Funktionscodes sind eindeutig definiert, andere kann der Benutzer selbst vergeben.
Beispiele für definierte Functionscodes:  

Code | Zweck | Typ  
--- | --- | ---  
1 | Coil auslesen | 1 Bit  
2 | Discrete Inputs lesen | 1 Bit  
3 | Hold Register lesen | 16 Bit  
4 | Input Register lesen | 16 Bit 
5 | einzelnes Coil beschreiben | 1 Bit  
6 | einzelnes Hold Register beschreiben | 16 Bit  
15 | mehrere Coils beschreiben | min. 1 Bit
16 | mehrere Hold Register beschreiben | min. 16 Bit  

### Fehlerbehandlung
Wenn es bei einer Request zu einem Fehler kommt wird im Function Code das 7te Bit gesetzt. Um dem anderen Gerät mitzuteilen welcher Fehler aufgetreten ist, wird im Daten-Bereich ein Exception Code mitgesendet.
Der Exception Code wird nach folgendem Schema ermittelt:  
![Exception](https://github.com/suspam14/la1/blob/master/modbus_exception.png)

### Dokumente zu Modbus 
Um genauere Infos zu erlangen gibt es mehrere offizielle Dokumente die das Modbus Protokoll näher beschreiben: 
* [Application Protocol](http://www.modbus.org/docs/Modbus_Application_Protocol_V1_1b3.pdf)
* [over serial line](http://www.modbus.org/docs/Modbus_over_serial_line_V1_02.pdf)  
* [Messanging Implementation Guide](http://www.modbus.org/docs/Modbus_Messaging_Implementation_Guide_V1_0b.pdf)

## Erstellen der Programme
Für unser Projekt werden zwei Programme benötigt, eines für den µC und eines für den PC. 
#### µC
Aufgrund von Zeitmangel in den Laboreinheiten wurde das µC-Programm vom SVN Server der HTL Arnfels bezogen. Die fertige Hex-Datei musste nur noch via Programmer auf das SURE Board übertragen werden. 
#### PC
Das PC-Programm soll mit JAVA realisiert werden. Um keine Zeit beim bauen der GUI zu verschwenden haben wir die fertige GUI vom SVN Server der HTL Arnfels bezogen. Die Kommunikation mit dem µC via der seriellen Schnittstelle muss nun noch in das Java Programm implementiert werden. Beim implementieren einer Seriellen Schnittstelle muss einiges beachtet werden.

### Serielle Schnittstellen in Java
Die Grundidee hinter Java ist eine Plattform-unabhängige Objekt-orientierte Programmiersprache zu sein. Das wird über die Java VM ermöglicht, auf dieser läuft der vom Benutzer programmierte Java Native Code. Der Java Native Code kann nicht direkt auf das Betriebssystem oder Hardware Ressourcen zugreifen, um dieses Problem zu umgehen gibt es das Java Native Interface. 
#### Java Native Interface (JNI)
Das Java Native Interface ermöglicht es Plattform unabhängig auf das Betriebssystem oder Hardware Ressourcen zuzugreifen. 
Ermöglicht wird dies durch den Aufbau des Java Native Interface, es besteht aus zwei Komponenten, der Betriebssystemseite und der Java-Seite. Die Betriebssystem-Seite wird meist in C oder C++ programmiert.  
Funktionsweise von Java und der JNI:  
![JNI](https://github.com/suspam14/la1/blob/master/JNI.svg)
Das JNI wird für viele hardwarenahe Anwendungszwecke benötigt. Für Serielle Schnittstellen gibt es mehrere Libaries, aber keine offizielle, was dazu führt das viele Libaries verbuggt sind oder nicht auf jeder Plattform funktionieren. Wir verwenden die JSSC Libary (Java Simple Serial Connector).

 
