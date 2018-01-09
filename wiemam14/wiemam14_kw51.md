# *Protokoll KW 51*

  Name: Markus Wieser   
  Klasse: 4AHME   
  Datum: 19.12.2017   
  Anwesend: Tuttner Raphael, Waltl Kilian, Wieser Markus    
  Abwesend: Strauß Lukas, Strutz Sebastian, Uhl Christian, Zitz Karlheinz
  
  ## **Modbus**
  
  Das Kommunikationsprotokoll des Modbus ist ein zustandsloses Protokoll, welches auf dem Request/Response Prinzip aufgebaut ist.
  Der große Vorteil des Modbus-Protokolls liegt darin, dass sich andere Geräte mit unterschiedlichen Verbindungstechnologien miteinander verbinden lassen. (Zum Beispiel eine Serielle Schnittstelle wie UART und ein Netzwerk wie TCP/IP)

Es gibt drei unterschiedliche Varianten zur Datenübertragung:

* Modbus ASCII   (textuelle byteweise Übertragung)     
* Modbus RTU     (Remote Terminal Unit, binäre byteweise Übertragung)      
* Modbus TCP     (Übertragung in TCP Paketen)   

## **Tabellen des Modbus Daten-Modells**

* Discrete Inputs  -> Ein einzelnes Bit welches nur gelesen werden kann (z.B. Taster).    
* Coils            -> Ein einzelnes Bit welches gelesen und beschrieben werden kann (z.B. LED).     
* Input Register   -> Ein 16 Bit Wert welcher nur gelesen werden kann (z.B. Temperatursensor).    
* Holding Register -> Ein 16 Bit Wert welcher gelesen und beschrieben werden kann.    

## **Function-Codes**

Der Function-Code definiert die Bedeutung eines Frames.   
Dies wird in drei Kategorien unterteilt:

* User defined Function Codes (65-72, 100-110)                    -> Werte dürfen individuell verwendet werden.    
* Reserved Function Codes (8,9,10,13,14,41,42,90,91,125,126,127)  -> Werte welche von Unternehmen für Produkte verwendet werden.    
* Public Function Codes(Alle Restlichen Werte)                    -> Werte welche von der Modbus.org community festgelegt werden.   

## **Modbus-Gateway**

Mithilfe eines Modbus-Gateway kann man verschiedene Modbus Varianten miteinander verbinden.   
In der PDU (Protocol Data Units) sind der Function code und und Dateien enthalten.    
In der ADU (Application Data Unit) sind Frame Felder enthalten welche für die Adressierung und die Fehlererkennung zuständig sind.

## Java

Einfach erklärt ist eine Klasse ein "Bauplan" für ein Programm. Ein Klasse besteht aus Attributen und Methoden.   
public abstract class -> Bei einer abstrakten Klasse werden Methoden und Namen geschrieben aber es gibt keinen Code dazu.   
Vererbungen -> Bei Java gibt es immer nur eine Einfachvererbung. 
