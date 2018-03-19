# 5.Protokoll  
  
  **Name**:  *Sackl Roland*  
  **Datum:** *13.03.2018*  
  **Uhrzeit:** *9:40-12:25*  
  **Gruppe:** *3*  
  
  **Abwesend:**   -  
  **Anwesend:**   Sackl Martin, Sackl Roland, Reinbacher Bernhard,Sammer Daniel,Ruffennacht Florian,Schuster Patrick, Schmuck Martin   




# Aufgabenstellung


Mithilfe eine Temeratursensors soll eine Temperaturmessung am Sure Board erfolgen, welche die Messergebnisse über ein Java Visulisierung ausgeben werden soll. Es steht bereits eine vorgefertigte GUI und für den µC ein Programm zur Verfügung.


## **Realisierung**  
![](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacrom14/sacrom14/lab5.png)


## **Temperatursensor**
Der **LM75** ist direkt am SURE Board verbaut und über I²C mit dem µC verbunden. Die Messdaten liest der µC aus und überträgt sie mithilfe von UART an den PC. Es wird unterschieden zwischen ein "intelligenter" Sensor und einen "unintelligenten" Sensor. Bei ein "intelligenter" Sensor ist er in einen Prozessor eingebaut und kann die fertigen Temperaturen zurückliefern.  Bei "unintelligenten" Sensor muss er sich den Wert die man von einer Spannung zurückgeliefert wird selbst ausrechnen.


### Feldbus
Ist ein Bussystem, dass Daten der Feldebene(Sensoren und Aktoren) überträgt.Diese Feldebenen werden über das Bussystem mit dem Steuergerät verbunden.  

Feldbussystem | Andwendungsgebiet | Details  
------------- | ----------------- | -----  
**Profibus** | Industrie | RS485   
**Modbus** | Industrie | RS485 und TCP/IP   
**Powerlink** | Industrie | Ethernet, ist echtzeitfähig   
**KNX** | Haustechnik |    
**CAN, LIN, Flexray** | Automobilindustrie | 





### JAVA Swing 

JAVA Swing ist unter Java die standardmäßige Lösung für GUIs, womit auch die grafische Benutzeroberfläche programmiert wurde. Keine lange Einarbeitungszeit und normal reicht die zu Verfügung stehenden  Controls zur Darstellung aus. Das GUIToolkit Java FX(Nachfolger von Java Swing) gibt es für komplexe GUIs. Seit 1998 ist es Bestandteil der JAVARuntime.  
[weitere Infos](https://www.java-tutorial.org/swing.html)  

### Asynchrone Datenübertragung  
Daten die jederzeit übertragen werden können,werden Daten asynchron übertragen. Diejenigen die nur zu gewissen Zeiten übertragen werden können, werden synchron übertragen.

### UART
Universal Asynchronous Reciever Transmitter steht für die Abkürzung UART und ist eine **serielle Schnittstelle**. Haufige Anwendung bei µCs.  
[weitere Infos](https://www.mikrocontroller.net/articles/UART)




## **Modbus**  
 Modbus wurde 1979 für die Kommunikation zwischen zwei SPS Geräten entwickelt. Heutzutage sieht man es häufig in der Haustechnik und in der Industrie, weil es ein offenes Protokoll ist und sich Lösungen mit TCP/IP-,RS232- und RS482- Verbindungen realisieren lässt. Die Version Modbus TCP ist seit 2007 ein Teil der IEC 61158. Es lassen sich RS-232- und TCP/IP-Netzwerke aufbauen. Es basiert auf dem Server/Client Prinzip.
  

![](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacrom14/sacrom14/ModbusServerClient.png)  



Es gibt drei unterschiedliche Übertragungsvarianten:  
* **Modbus RTU**  Datenübertragung: binär byteweise   
* **Modbus ASCII**  Datenübertragung: textuell byteweise Datenpakete   
* **Modbus TCP** Datenübertragung: über ein TCP Pakete 


Die Übertragung der Frames erfolgt  als ASCII-Text. Die serielle Schnittstelle wird standardmäßig nur als 7 Daten-Bits(7E1 oder 7N2)  konfigueriert. 

**Aufbau eines Modbus ASCII-Frame:**    

![](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacrom14/sacrom14/ModbusASCII.png)  


Im ASCII-Modus beginnt eine Nachricht mit einem Doppelpunkt.Die ersten zwei Bytes enthalten zwei ASCII-Zeichen(stellen die Adressen des Empfängers dar).Der auszuführende Befehl ist auf den nächsten zwei Bytes codiert.Das Ende der Nachricht wird durch die Zeichenfolge Carriage return – Line feed markiert.  

Wenn während der Übertragung eines Frames eine Pause von mind. 1s auftritt, wird der Frame als Fehlerfall bewertet. Man kann als benutzer ein längeres Timeout konfigurieren.  




## Modbus-Daten-Modell  
Vier verschiedenen Bereiche:    

Name | Funktion  
---- | --------   
Coils |   ein Bit,kann gelesen und beschrieben werden
Input Registers |  ein 16 Bit, kann nur gelesen werden  
Discrete Inputs |  ein einzelnes Bit, kann nur gelesen werden  
Hold Registers |  ist ein 16 Bit Wert, kann gelesen und beschrieben werden   



## **Modbus Datenpaket**

Aus mindestens den zwei Teilen **Function Code** und **Data** muss ein Modbus Datenpaket bestehen.  
Bei  ASCII und RTU, zusätzlich noch die Adresse und eine Prüfsumme .
Bei Modbus TCP nicht notwendig.  

Unterschied zwischen **ADU** und **PTU**:  

![](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacrom14/sacrom14/ModbusADUPDU.png)  




## **Exceptions**  
Tritt beim Request ein Fehler auf, so wird in der darauffolgenden Response das Bit-7 gesetzt. Dies hat die Funktion, dass sich der Function Code ändert und im Daten-Bereich wird ein Exception-Code generiert. Mithilfe dieses Exception-Codes, kann man den vorliegenden Fehler kategorisieren.

Wenn bei einem Request ein Fehler auftritt, dann wird in der Response das Bit-7 im Function-Code Feld gesetzt.Aus dem Function-Code 1 bis 127 entsteht ein Wert 129-255.Weiteres wird ein Exception Code gesendet.Mithilfe dieses Exception Code, kann man den vorliegenden Fehler kategorisieren.

![](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacrom14/sacrom14/ModbusException%20Code.png)  

## **Function Codes**

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

## Serielle Schniittstelle in JAVA

![](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacrom14/sacrom14/lb5.1.png)  


