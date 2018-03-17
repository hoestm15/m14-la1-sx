# **5. Laborprotokoll** 

*von Florian Ruffenacht*

Datum: 13.03.2017 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

Abwesend: keiner

## **Beschreibung der Aufgabenstellung**

Es soll eine Temperaturmessung über den am SURE-Board integrierten Temperatursensor erfolgen. Die Messdaten sollen am PC über ein **JAVA-Programm** ausgegeben werden. Dafür steht bereits eine vorgefertigte GUI (JAVASwing) zur Verfügung. Auch für den µC ist das Programm bereits vorgegeben.

## **Realisierung**

Die grundsätzliche Struktur sieht folgendermaßen aus:

![Grundstruktur als SVG](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/BildGrundstruktur.svg)

Der  **Temperaturensor LM75** gibt die Messdaten an das Rechenzentrum des Mikrocontrollers über I²C weiter. Während der LM75 hier als _unintelligenter_ Sensor agiert, kann das **SURE-Board** als Ganzes durchaus als _intelligenter_ Sensor bezeichnet werden. Der Mikorcontroller gibt die Messdaten über UART weiter. Die Verbindung zwischen dem SURE-Board und dem PC (MiniUSB/USB) ist in diesem Fall ein **Feldbus**.

[Weitere Informationen zum LM75](http://www.franksteinberg.de/lm75.htm)


### UART

Der UART ist eine einfache **serielle Schnittstelle**, die in Bezug auf Datenübertragungsrate, Anzahl der Stop-Bits und Even Parity/Uneven Parity konfiguriert werden kann. UART steht für **U**niversial **A**synchronous **R**eceiver **T**ransmitter. 

[Weitere Informationen zum UART](https://www.mikrocontroller.net/articles/AVR-Tutorial:_UART)

### JAVA Swing 

Die grafische Benutzeroberfläche (**GUI**) wurde mittels JAVA Swing programmiert. JAVA Swing ist unter Java die standardmäßige Lösung für GUIs. Die Einarbeitungszeit hält sich in Grenzen und im Normalfall reicht die zu Verfügung stehenden  Controls zur Darstellung aus. 

JAVA Swing ist seit 1998 Bestandteil der JAVARuntime und weit verbreitet. Als designierter Nachfolger kam 2014 JavaFX heraus, der Lücken im Bereich Medien und Animation schließen sollte. JavaFX wurde bisher aber nicht so stark angenommen wie erhofft.

[Weitere Informationen zu JAVA Swing](https://de.wikipedia.org/wiki/JavaFX)

[Weitere Informationen zu JAVA FX](https://de.wikipedia.org/wiki/Swing_(Java))

### Feldbusse


Ein Feldbus ist ein Bussystem, das in einer Anlage Sensoren und Aktoren mit einem Automatisierungsgerät verbindet. Welches Bussystem sivoll ist  hängt stark von der Anwendung ab. Folgende Feldbusse sind stark verbreitet:

* **[POWERLINK](https://de.wikipedia.org/wiki/Ethernet_Powerlink)** - basiert auf Ethernet, das für Echtzeitanwendungen erweitert wurde. Hauptsächlich für Maschinen- und Anlagenbau. 
* **[LIN](https://de.wikipedia.org/wiki/Local_Interconnect_Network)** - für wenig komplexe Anwendungen in der Automobilindustrie
* **[CAN](https://de.wikipedia.org/wiki/Controller_Area_Network)** - für mittel-komplexe Anwendungen in der Automibilindustrie
* **[Flexray](https://de.wikipedia.org/wiki/FlexRay)** - für komplexe Anwendungen in der Automobilindustrie
* **[Profibus](https://de.wikipedia.org/wiki/Profibus)**- für z.B. Roboter, Maschinenbau, Anlagenbau
* **[KNX](https://de.wikipedia.org/wiki/KNX-Standard)** - für die Gebäudeautomatisierung
* **[Modbus](https://de.wikipedia.org/wiki/Modbus)** - freier Standard für unterschiedlichste Anwendungen in der Industrie

Wir verwenden Modbus, da dies ein frei verfügbarer Standard ist und nicht zu komplex ist.

### Modbus

Das offen zugänglich Kommunikationsprotokoll Modbus wurde 1979 von Gould-Modicon ins Leben gerufen. Die Anwendungsgebiete sind die Hausautomatisierung und die Industrie. Es basiert auf dem **Server/Client** Prinzip. 

In unserem Fall stellt das SURE-Board den Server und der PC den Client dar. Am folgenden Bild lässt sich das gut erkennen:

![Server/Client Prinzip bei Modbus](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/ModbusServerClient.png)

**Es gibt 3 Arten der Datenübertragung:**

* Modbus ASCII - Die Daten werden textuell und byteweise übertragen. Frames beginnen mit einem Doppelpunkt
* Modbus RTU - Die Daten werden byteweise übertragen (= Remote Terminal Unit)
* Modbus TCP - Die Daten werden in TCP-Paketen übertragen. Besonderheit: Paketanfang/Paketende werden durch Pausen detektiert, was in auf nicht deterministischen Betriebssystemen wie Windows schnell zu Problemen führen kann.

**ASCII Transmission Mode**

Die Übertragung der Frames erfolgt hier wie bereits bekannt als ASCII-Text. Die serielle Schnittstelle wird standardmäßig 7E1 oder 7N2 konfigueriert, also nur 7 Daten-Bits! Im Bedarfsfall darf aber auch eine davon abweichende Festlegung verwendet werden.

Ein Modbus ASCII-Frame hat somit folgenden Aufbau:
![Modbus ASCII Frame](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/ModbusASCII.png)

**Modbus Datenpaket**

Ein Modbus Datenpaket muss mindestens aus den Teilen **Function Code** und **Data** bestehen. Bei den Varianten ASCII und RTU kommen zusätzlich noch die Adresse und eine Prüfsumme dazu. Das ist bei Modbus TCP nicht notwendig, da diese Bestandteile bereits im TCP-Standard beinhaltet sind. Folgendes Bild stellt den Unterschied zwischen **ADU**(Application Data Unit) und **PTU**(Protocoll Data Unit):

![ADU/PTU Modbus](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/ModbusADUPDU.png)

Die maximale Größe einer ADU liegt bei Modbus ASCII/RTU bei 256 Bytes und bei Modbus TCP bei 260 Bytes.

**Daten-Modell**

Beim Modbus Daten-Modell wird in vier verschiedene Adressräume unterschieden:

* Discrete Inputs (ein einzelnes Bit, welches nur gelesen werden kann) zum Beispiel: ein Taster
* Coils (ein Bit, welches gelesen und beschrieben werden kann) zum Beispiel: eine LED
* Input Registers (ein 16-Bit Wert der nur gelesen werden kann) zum Beispiel: ein Temperatursensor
* Hold-Registers (ein 16-Bit Wert der gelesen und beschrieben werden kann) zum Beispiel: die Anzeige am Sure-Board

**Function Codes**

Die  bereits oben erwähnten Function-Codes defineren ein Modbus-Frame. Für Requests sind Werte zwischen 1 und 127 zulässig. Dabei können Function Codes in den Bereichen 65-72 und 100-110 vom Benutzer selber vergeben werden. Der Großteil der restlichen Function Codes werden von der Modbus.org Community eindeutig definiert (**Public Function Codes**).
Einige wichtigte Public Function Codes sind hier zusammengefasst:

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

[Mehr Infos in der Spezifikation](http://www.modbus.org/docs/Modbus_Application_Protocol_V1_1b3.pdf)

**Fehlerbehandlung** 

Kommt es bei einem Request zu einem Fehler, wird im Response das Bit 7 im Function-Code Field gesetzt. Deswegen sind auch nur Funktion Codes von 1-127 für den benutzer verfügbar. Des Weiteren wird im Daten-Bereich ein Exception-Code gesendet. Dieser gibt die Art des Fehlers nach folgendem Prinzip an:

![Modbus Exception](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/ModbusException%20Code.png)

[Mehr Infos in der Modbus-Spezifikation](http://www.modbus.org/docs/Modbus_Application_Protocol_V1_1b3.pdf)

### Erstellung des Programmes

Das fertige Programm für den µC wurde vom [SVN-Server](https://www.htl-mechatronik.at/svn/modbus) der Mechatronik bezogen. Diese fertigen IntelHex-Dateien wurden dann mithilfe des Bootloaders auf die SHURE-Boards geladen. Die JAVA Swing Vorlage steht uns auf LMS zur Verfügung.

#### Serielle Schniittstelle in JAVA

Wie bereits allgemein bekannt sein sollte, wird ein Java Code nicht in eine übers Betriebssystem direkt ausführbare Datei kompiliert sondern in einen Zwischencode übersetzt (Endung **.class**). Dieser Zwischencode kann von jeder JAVA-Virtual Machine unabhängig vom Betriebssystem ausgeführt werden. Werden mehrere Datein vom Typ .class zusammengefasst lautet die Endung .jar. 

Die von standardmäßig Angebotene Lösung [JAVA Communication API](http://www.oracle.com/technetwork/java/index-jsp-141752.html) ist veraltet und funktioniert auf Windows-System nicht. Möchte man nun eine serielle Schnittstelle betreiben, muss die Java Virtual Machine überbrückt werden. Das ist durch JNI (Java  Native Interface) möglich und sieht folgendermaßen aus:

![JNI](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/JNI.svg)

Die binären Dateien unterscheiden sich logischerweise abhängig vom Betriebystem und der Wortbreite.

Für serielle Schnitstellen sind zwei Bibliotheken gebräuchlich:

* [JSSC](https://github.com/scream3r/java-simple-serial-connector) (Java Simple Serial connector) - Wir verwenden diese Bibliothek, da sie aktueller als RXTX ist
* [RTXT](http://rxtx.qbang.org/wiki/index.php/Main_Page) - Beinhaltet Bugs 
