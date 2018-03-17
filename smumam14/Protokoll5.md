# Laborprotokoll  
Fünfte Einheit am 13. März 2018  
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
  
### Der Modbus
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
Ein Modbus-Paket ist wie folgt aufgebaut:  
![modbusunit](https://github.com/HTLMechatronics/m14-la1-sx/blob/smumam14/smumam14/resources/modbus_units.png)  
>aus dem oben genannten Modbus-Skript, abgerufen von lms.at am 14.03.2018  
  
Wie hier ersichtlich ist, werden die Daten in einem Modbuspaket verschieden zusammengestellt. Dies hängt von dem Modus ab. Die PDU, Protocol Data Unit, ist immer gleich und besteht aus dem Function Code, welcher die Art der Anfrage angibt und den eigentlichen Daten. Bei den Modi ASCII und RTU kommen noch Bereiche für Adresse und Prüfsumme hinzu, dann ist von einer ADU (Application Data Unit) die Rede. Bei TCP sind diese zusätzlichen Daten nicht erforderlich, das hier TCP/IP-Pakte versendet werden, welche bereits in sich eine Prüfsumme und eine Adresse (in diesem Fall ein Socket) haben.  
 
:point_right: __ASCII:__  
hier werden die Daten als ASCII-Zeichen versendet. Die empfohlene Konfiguration der seriellen Schnittstelle ist 7E1 oder 7N2, also nur 7 Datenbits. Dies ist aber Absicht, das die ASCII-Codepage mit 7 Bit auskommt. Im Falle des Falles darf davon jedoch auch abgewichen werden. Eine Übertragung wird mit einem Doppelpunkt eingeleitet, nach Adresse und Function Code kommen bis zu 252 Zeichen, danach eine LRC-Prüfsumme und abgeschlossen wird die Transmission mit einem CR (Wagenrücklauf) und einem LF (Zeilenvorschub).  
Hier die grafische Darstellung:  
![ASCII](https://github.com/HTLMechatronics/m14-la1-sx/blob/smumam14/smumam14/resources/modbus_ascii.png)  
>aus dem oben genannten Modbus-Skript, abgerufen von lms.at am 14.03.2018  
Beispiel einer Übertragung: `:0401000A000868<CR><LF>`

:point_right: __Zwischenfrage: Wie weiß der Modbus-Empfänger, wann beim RTU-Modus die Übertragung beendet ist?__  
Da der RTU-Modus die Daten bitweise überträgt, kann man nicht so einfach feststellen, wann eine Übertragung beendet ist. Daher wurde festgelegt, dass, wenn auf der Leitung eine Pause von 3,5 Zeichen auftritt, der Empfänger die Übertragung des Pakets als abgeschlossen interpretieren soll. Dies kann jedoch zu einem Problem führen, da 3,5 Zeichen je nach Konfiguration zeitlich gesehen deutlich unter einer Millisekunde sein können und es durch das Betriebssystem des Rechners ohne weiters zu solchen Verzögerungen kommen kann. In diesem Moment würde der Empfänger (zB µC) zwei Pakete bekommen, aber anhand der Prüfsummen sehen, dass etwas nicht stimmt und beide Pakete als korrupt erkennen und verwerfen. An diesem Punkt ist die Abhilfe nur durch "pfuschen" möglich, nämlich in dem man zum Beispiel in der Konfiguration die Wartezeit von 3,5 Zeichen auf 35 oder 70 Zeichen erhöht. Außerdem darf in einer RTU-Übertragung keine Pause von mehr als 1,5 Zeichen sein, da der Empfänger das Paket dann auch verwerfen würde. Gegebenenfalls muss auch diese Zeit angepasst werden. Alternativ wäre nur der Umstieg auf eine anderes Verfahren zu nennen. Außerdem darf in einer RTU-Übertragung keine Pause von mehr als 1,5 Zeichen sein, da der Empfänger das Paket dann auch verwerfen würde. Gegebenenfalls muss auch diese Zeit angepasst werden. 

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
  
#### Beispielübertragung
entnommen aus dem oben genannten Modbus-Skript, abgerufen von lms.at am 14.03.2018:  
  
"Lese 8 Coils beginnend bei Coils-Adresse 11 (= 10 = 0x0a in der PDU):"
```
Request       | Function Code | Starting Address | Quantity of coils |
        ------+---------------+------------------+-------------------|
         Byte |       1       |    2   |    3    |    4    |    5    |
        ------+---------------+--------+---------+---------+---------|
         Wert |     0x01      |  0x00  |  0x0a   |  0x00   |  0x08   |
        --------------------------------------------------------------
```
```
Response      | Function Code | Byte count | coil values |
        ------+---------------+------------+--------------
         Byte |       1       |      2     |      3      |
        ------+---------------+------------+-------------|
         Wert |     0x01      |    0x01    |    0xc7     |
        --------------------------------------------------
```

```  
Error         | Function Code | Exception code |
        ------+---------------+----------------|
         Byte |       1       |        2       |
        ------+---------------+----------------|
         Wert |     0x81      |      0x03      |
        ----------------------------------------
```
Hier sind zwei weitere Eigenarten von Modbus ersichtlich:
1. Egal ob es sich um eine Anfrage (Request), Antwort (Response) oder eine Fehlermeldung (Error) handelt, es wird stets der Function Code mitgesendet, welcher aussagt, welche Art von Anfrage es ursprünglich war.
1. In der Definition wird mit 1 begonnen zu zählen (dort, wo die Adressen für die Coils usw. festgelegt werden). Diese Vorgehensweise ist eher unüblich, da man in der Informatik traditionell mit 0 zu zählen beginnt. Und hier hat man beide Systeme vermischt, da, wenn man die Adresse 11 ansprechen will, man erst wieder 10 über die Schnittstelle übertragen muss. Ein Beispiel: Das erste Coil am Zielsystem hat die Nummer 1 (NICHT 0), wenn man jedoch dieses Bit ansprechen will, ist die Adresse 0x00 (NICHT 0x01) zu übertragen. Dies muss man sich unbedingt merken und ständig im Auge behalten, da es sonst beim Entwickeln leicht zu Missverständnissen kommen kann, weil man permanent die falschen Adressen anspricht und so die falschen Daten überträgt. 

### Erstellung der Programme

Zuerst nahmen wir das fertige Programm für unseren µC vom [SVN-Server in Arnfels](https://www.htl-mechatronik.at/svn/modbus). Danach haben wir mithilfe des Bootloaders die fertigen IntelHex-Dateien auf unsere SHURE-Boards geladen. Bei manchen war jedoch kein Bootloader installiert und bei wiederum anderen konnte keine Schnittstelle geöffnet werden, was sich jedoch durch einen Neustart relativ unkompliziert reparieren ließ. Anschließen holten wir uns die Java-Swing-Vorlage vom LMS-Download-Bereich. Herr Prof. DI Steiner hatte die GUI bereits für uns fertiggestellt, damit wir unsere ohnehin schon knappe Zeit sparen konnten. Bevor wir mit dem Programmieren loslegen konnten, wendeten wir uns noch einem Problem in Java zu, nämlich der Kommunikation über die serielle Schnittstelle.

#### Serielle Schnittstelle in Java
Hier eine Abbildung, wie Java grundsätzlich funktioniert:
!(Java-Prinzip)[https://github.com/HTLMechatronics/m14-la1-sx/blob/smumam14/smumam14/resources/java_uebersicht.png]
> (c) Martin Schmuck

       

