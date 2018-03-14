# Laborprotokoll  
Dritte Einheit am 13. März 2018 
Martin Schmuck  
4AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: niemand 

## Thema der Einheit: Visualisirung eines Temperatursensors
#### Wiederholung der 4. Einheit  
Zunächst wiederholten wir den Stoff der lezten Einheit.   
C-Code ausführbar machen:
  1. Präprozessieren
  1. Kompilieren
  1. Assemblieren
  1. Linken
  1. (eventuell) in Hex-Datei umwandeln
  
Übersetzung mit make:
 * Das make-Tool steuert den Übersetzungsvorgang
 * make-Tool ruft makefiles auf, Übersetzung wird dadurch gesteuert
 * make-Tool überprüft Zeitstempel und sorgt so dafür, das nicht immer alles neu übersetzt werden muss, sondern gleichbleibende Teile übersprungen werden
 
## eigentliches Thema: Temperatursensor

Hier eine grobe Übersicht unseres Vorhabens: 
![bsb](https://github.com/HTLMechatronics/m14-la1-sx/blob/smumam14/smumam14/resources/shure_uebersicht.svg)
>(c) Martin Schmuck

Der Temperatursensor LM75A sitzt auf unserem SHURE-Board und ist mit dem µC mit I²C verbunden. Der PC, auf dem die Java Swing GUI läuft, greift über die interne Serielle Schnittstelle, den Seriell-USB-Wandler auf die USB-UART-Konvertierung auf dem SHURE-Board zu. Diese ist mit dem µC verbunden, welcher die Daten über I²C vom intelligenten Sensor ausliest. Die Daten sollen zwischen SHURE-Board und PC über einen Feldbus übertragen werden. 

:point_right: __Java Swing:__  
Java Swing ist eine einfache Möglichkeit, um in Java graphische Benutzerschnittstellen zu realisieren (= GUI). Der Vorteil liegt darin, dass es sehr einfach und schnell geht, sich in die Swing-Programmierung einzuarbeiten. Leider wird Java Swing aber seit ca. einem Jahrzehnt nicht mehr wirklich gepflegt. Der Nachfolger und eine alternative Lösung für noch komplexere GUI's wäre Java FX, welches wesentlich komplexer aufgebaut ist und bereits mehrere Wochen bis Monate Einarbeitung benötigt, um benutzt werden zu können. Generell besteht leider im Moment die Situation, dass Java seit der Übernahme vom eigentlichen Entwickler Sun Microsystems durch Oracle nur mehr halbherzig supported wird. 

:point_right: __Intelligenter Sensor:__  
Intelligent ist der Sensor deswegen, weil er schon einen fertigen Temperaturwert zurückliefert, das heißt, er muss irgendwie einen eingebauten Prozessor haben, welcher die Werte umrechenen kann. Im Gegensatz dazu würde ein unintelligenter Sensor (zB Pt100) einfach zB eine Spannung zwischen 0 und 10 Volt zurückliefern und mann müsste sich selbst um die Auswertung kümmern.
  
:point_right: __Feldbus:__  
folgende Felbusse sind unter anderem zur Zeit üblich:
* Automatisierungstechnik / Industrie:  
       * Powerlink (offen, Basis: Ethernet, echtzeitfähig) [B&R; 2001]  
       * Profibus [1989]  
       * Modbus [1979]
* Automobilbereich:  
       * CAN-Bus (Controller Area Network): anspruchsvolle Systeme, zB Motor-/Getriebesteuerung [Bosch, Intel; 1983]  
       * LIN (Local Interconnect Network): weniger anspruchsvolle Systeme, zB Fensterheber [Daimler, VW, BMW; 1999]  
       * FlexRay: möglicher Nachfolger von CAN [Daimler, BMW; 2000]
 * Haustechnik:    
       * KNX (sehr kostspielig) [2002]  

Unsere Wahl fiel auf den sogennanten Modbus, da er sowohl mit RS485 als auch mit TCP/IP betreibbar ist und offen ist, das heißt man kann alle in alle Normen und Protokolle Einsicht nehmen und muss sich nicht erst Regelwerke um mehrere hundert Euro zulegen, bevor man arbeiten kann. Da wir uns an bestimmte Protokolle hielten, war unsere Vorgehensweise __nicht proprietär__. 
  
:point_right: __proprietär:__  
  Eine proprietäre Vorgehensweise wäre, gängige Standards außer Acht zu lassen und sich alle Protokolle zur Datenübertragung selbst zu "basteln". Dadurch würde die Endlösung zwar unter Umständen günstiger oder schneller zustande kommen, jedoch ist ein solches System nicht mit anderen kompatibel, da man ja eigenen Standards verwendet. Außerdem konnte eine proprietäre Lösung vielleicht auch in Folge schwerer zu warten sein als ein System, welches auf genormten Standards beruht.   
  
:point_right: __asynchrone Datenübertragung:__   
  Asynchron heißt im Grunde nur, dass Daten jederzeit auf der daherkommen können. Dies ist zum Beispiel bei UART (Universal Asynchronous Reciever Transmitter) der Fall. Bei der synchronen Datenübertragung können nur zu gewissen Zeiten Daten gesendet werden. Denkbar wäre, dass das Senden zum Beispiel mit einem ganz bestimmten Takt synchron laufen muss. Ein Beispiel für synchrone Datenübertragung ist SPI.  
  
:point_right: __RS-485:__   
Auch EIA-485 genannt, ist eine klassiche Zwei-Leiter-Übertragungstechnik, siehe auch [Wikipedia](https://de.wikipedia.org/wiki/EIA-485) für weitere Informationen.
  
#### Der Modbus
siehe auch [Skript Modbus](https://lms.at/dotlrn/classes/htl_elektrotechnik/610437.4AHME_LA1.17_18/xolrn/E7BE8C85F66CA/2148F16AC6F2E.symlink?resource_id=0-236827434-257560369&m=view#167572556) von DI Manfred Steiner  
  
Beim Modbus handelt es sich um einen offenen Feldbus, welcher 1979 von Gould-Modicon zur Kommunikation mit deren hauseigenen SPSen vorgestellt wurde. Er verfügt über drei verschiedene Ebenen:
* Modbus ASCII: Hier kann immer ein ASCII-Zeichen nach dem anderen gesendet werden (rein textuell)  
* Modbus RTU: Hier werden die Daten Binär übertragen
* Modbus TCP: Hier werden TCP/IP-Pakete übertragen

Der Modbus arbeitet nach dem Server-Client-Prinzip, wobei in unserem Fall die Rolle des Servers das SHURE-Boards einnimmt (wartet auf Anfragen) und der PC bzw. unsere Applikation als Client (fragt den Server nach der Temperatur (vereinfacht ausgedrückt)) fungiert. Eventuell findet man analog dazu auch die Bezeichnung Master-Slave-System.  
Hier ist eine Grafik dazu: 
![modbusprinzip](https://github.com/HTLMechatronics/m14-la1-sx/blob/smumam14/smumam14/resources/modbus_server_client.png)
>aus dem oben genannten Modbus-Skript, abgerufen von lms.at am 14.03.2018
  
#### Modbus-Modi
* ASCII: hier werden die Daten als ASCII-Zeichen versendet. Die empfohlene Konfiguration der seriellen Schnittstelle ist 7E1 oder 7N2, also nur 7 Datenbits. Dies ist aber Absicht, das die ASCII-Codepage mit 7 Bit auskommt. Im Falle des Falles darf davon jedoch auch abgewichen werden. Eine Übertragung wird mit einem Doppelpunkt eingeleitet, nach Adresse und Function Code kommen bis zu 252 Zeichen, danach eine LRC-Prüfsumme und abgeschlossen wird die Transmission mit einem CR (Wagenrücklauf) und einem LF (Zeilenvorschub).  
Hier die grafische Darstellung:  
![ASCII](https://github.com/HTLMechatronics/m14-la1-sx/blob/smumam14/smumam14/resources/modbus_ascii.png)  
>aus dem oben genannten Modbus-Skript, abgerufen von lms.at am 14.03.2018  

* RTU:  
* TCP: 
  
Ein Modbus-Paket ist wie folgt aufgebaut:  
![modbusunit](https://github.com/HTLMechatronics/m14-la1-sx/blob/smumam14/smumam14/resources/modbus_units.png)  
>aus dem oben genannten Modbus-Skript, abgerufen von lms.at am 14.03.2018  
  
Wie hier ersichtlich ist, werden die Daten in einem Modbuspaket verschieden zusammengestellt. Dies hängt von dem Modus ab. Die PDU, Protocol Data Unit, ist immer gleich und besteht aus dem Function Code, welcher die Art der Anfrage angibt und den eigentlichen Daten. Bei den Modi ASCII und RTU kommen noch Bereiche für Adresse und Prüfsumme hinzu, dann ist von einer ADU (Application Data Unit) die Rede. Bei TCP sind diese zusätzlichen Daten nicht erforderlich, das hier TCP/IP-Pakte versendet werden, welche bereits in sich eine Prüfsumme und eine Adresse (in diesem Fall ein Socket) haben.  

##### Modbus-Daten-Modell  
Das Modbus-Daten-Modell unterscheidet vier verschiedene Bereiche:  

Name | Zweck | Beispiel
-----|-------|---------
Discrete Inputs | ein einzelnes Bit, welches nur lesbar ist | Taster am SHURE-Board
Coils | les- und beschreibbares Bit | LED oder Spule (daher der Name)
Input Registers | lesbares Register (16-Bit-Wert) | ADC, Temperatursensor
Hold-Registers | les- und beschreibbares Register (16-Bit) | DAC, Pulsweitenmodulatormodul  
  
##### Funktionscodes
Function Codes oder (dt. Funktionscodes) werden verwendet, um die Art der Anfrage anzugeben. Hier ein Auszug einiger genormter Codes:  

Code | Zweck
-----|------
`1` | Coils lesen
`2` | Discrete Inputs lesen
`3` | Hold-Register lesen
`4` | Input-Register lesen
`5` | ein Coil beschreiben
`6` | ein Register beschreiben
`15` | mehrere Coils beschreiben
`16` | mehrere Register beschreiben
  
  




       

