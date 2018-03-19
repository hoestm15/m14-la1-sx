# 5.Protokoll  
  
  **Name**:  *Sackl Roland*  
  **Datum:** *13.03.2018*  
  **Uhrzeit:** *9:40-12:25*  
  **Gruppe:** *3*  
  
  **Abwesend:**   -  
  **Anwesend:**   Sackl Martin, Sackl Roland, Reinbacher Bernhard,Sammer Daniel,Ruffennacht Florian,Schuster Patrick, Schmuck Martin   




# Aufgabenstellung


Mithilfe eine Temeratursensors soll eine Temperaturmessung am Sure Board erfolgen, welche die Messergebnisse über ein Java Visulisierung ausgeben werden soll. Es steht bereits eine vorgefertigte GUI und für den µC ein Programm bereits zur Verfügung.


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

JAVA Swing ist unter Java die standardmäßige Lösung für GUIs, womit auch die grafische Benutzeroberfläche programmiert wurde.Keine lange Einarbeitungszeit und normal reicht die zu Verfügung stehenden  Controls zur Darstellung aus.Das GUIToolkit Java FX(Nachfolger von Java Swing) gibt es für komplexe GUIs. Seit 1998 ist es Bestandteil der JAVARuntime.  
[weitere Infos zu Java Swing](https://www.java-tutorial.org/swing.html)  

### Asynchrone Datenübertragung  
Daten die jderzeit übertragen werden können,werden Daten asynchron übertragen.Diejenigen die nur zu gewissen Zeiten übertragen werden können werden synchron übertragen.

### UART
Universal Asynchronous Reciever Transmitter steht für die Abkürzung UART und ist eine **serielle Schnittstelle**. Haufige Anwendung bei µCs.  
[weitere Infos zu UART](https://www.mikrocontroller.net/articles/UART)




