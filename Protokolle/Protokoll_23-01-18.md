# Protokoll: Knappitsch Robert
## 5. Einheit: Modbus
* Klasse: 4AHME (Gruppe 1)
* Datum: 23.01.2018
* Anwesend: Berger Emil, Bullner Jeremy, Böcksteiner Jakob, Ehmann Julian, Enzi Gert, Kobor Markus, Knappitsch Robert
* Abwesend: -

### Modbus
[Modbus](http://http://www.modbus.org/) ist ein Kommunikationsprotokoll, welches ursprünglich für das Verbinden von SPS'en entwickelt wurde. Es basiert auf einer Master/Slave- und einer Client/Server-Architektur. Da es sich um ein offenes Protokoll handelt, entwickelte es sich zu einem Standart in der Industrie. Auch in der Hausautomatisierung wird der Modbus gerne verwendet, da es sich um ein kostenloses Protokoll handelt.
#### Varianten
Die zwei Hauptvarianten sind:
* Serielle Snittstelle (z.B.: UART, RS 232, ...)
* Netzwerk/Ethernetverbindungen (TCP/IP)
#### Datenübertragung
Für die Datenübertragung verwendet man drei Varianten:
* RTU (Remote Terminal Unit): Daten werden binärcodiert, byteweise übertagen.
* ASCII: Daten werden textuell , byteweise übertragen.
* TCP: Daten werden mit Hilfe von TCP-Paketen übertragen.
#### Gateway
Das Modbus-Gateway kann, über verschiedene Modbus-Varianten erreichbare Server und Clients, miteinander verbinden. Es setzt sich aus zwei Teilen zusammen:
* PDU (Protokoll Data Units): Enthalten Daten und den Function Code
* ADU (Application Data Unit): Adressiert die gesendeten Pakete und führt eine Fehlererkennung durch

#### Daten-Modell
Das Modbus-Datenmodell besteht aus vier Tabellen. Jede Tabelle darf aus 65536 16-Bit-Adressen bestehen.
* Discrete Inputs: ein einzelnes Bit, welches nur gelesen werden kann (z.B.: Taster)
* Coils: ein einzelnes Bit, welches gelesen und beschrieben werden kann (z.B.: LED)
* Input-Registers: ein 16-Bit-Wert, welcher nur gelesen werden kann (z.B.: Temperatursensor)
* Hold-Registers: ein 16-Bit-Wert, welcher gelesen und beschrieben werden kann (z.B.: PWM-Einheit)

#### Function-Codes
Function-Codes legen die Bedeutung eines Frames fest. Sie sind in drei Kategorien unterteilt:
* User defined Function Codes: Diese Werte dürfen von Usern individuell verwendet werden.
* Reserved Function Codes: Diese Werte werden von Unternehmen für ihre Produkte verwendet.
* Public Function Codes: Die restlichen Werte werden von der Community festgelegt.
Einige wichtige Public Function Codes sind:

Function Code | Hex | Name | Typ
--- | --- | --- | :---:
1 | 01 | Read Coils | Bit
2 | 02 | Read Discrete Inputs | Bit
3 | 03 | Read Holding Registers | 16-Bit
4 | 04 | Read Input Register | 16-Bit
5 | 05 | Write Single Coil | Bit
6 | 06 | Write Single Register | 16-Bit 
15| 0F | Write Multiple Coils |	Bit
16| 10 | Write Multiple Registers | 16-Bit

### Verbindungsschichten
![Beispiel für einzelne Schichten](https://github.com/HTLMechatronics/m14-la1-sx/blob/knarom14/Protokolle/Schichten.png)

#### Java Native Interface
> JNI ermöglicht es, native Methoden zu schreiben für Situationen, in denen es nicht möglich ist, ausschließlich Java als Programmiersprache einzusetzen. Dies ist der Fall, wenn beispielsweise die Standard-Java-Klassenbibliothek bestimmte Plattform-abhängige Features oder andere Programmbibliotheken nicht unterstützt. Weiterhin ist es per JNI möglich, eine weitere in einer anderen Programmiersprache programmierte Anwendung für Java zugreifbar zu machen. Viele Klassen der Java-Standardbibliothek basieren auf JNI, um beispielsweise die Datei-Ein- und Ausgabe oder Soundwiedergabe zu ermöglichen. Indem Java Leistungs- und Plattform-abhängige Implementierungen in die Standardbibliothek integriert, kann der Java-Programmierer und -Nutzer diese Features in sicherer und Plattform-unabhängiger Weise nutzen.
*Quelle: [Wikipedia, JNI](https://de.wikipedia.org/wiki/Java_Native_Interface)*

### Übung
Um den Stoff dieser Einheit anzuwenden, ist, mit Hilfe eines Java-Programms, ein Temperatursensor über das Sure-Board anzusteuern. Die Temperatur wird in einer GUI dagestellt.




