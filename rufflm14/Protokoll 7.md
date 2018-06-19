# **7. Laborprotokoll** 

*von Florian Ruffenacht*

Datum: 15.05.2017 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

Abwesend: -

## Wiederholung der letzten Einheit(en)

Zu Beginn der Einheit wiederholten wir ausführlich den bereits besprochenen Stoff zum Projekt Temperaturmessung mittels Mikroprozessor. In diesem Projekt soll eine Temperaturmessung über den am SURE-Board integrierten Temperatursensor erfolgen. Die Messdaten sollen am PC über ein JAVA-Programm ausgegeben werden. Dafür steht bereits eine vorgefertigte GUI (JAVASwing) zur Verfügung. Auch für den µC ist das Programm bereits vorgegeben. 

Zur Erinnerung ist hier noch einmal der schematische Aufbau skizziert:

![Grundstruktur als SVG](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/BildGrundstruktur.svg)

[Link zum Protokoll der 5.Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/Protokoll_5.md)

## Programmieren des SingleMeasurementWorkers

Der SingleMeasurementWorker ist eine JAVAl-Klasse, die in einem eigenen Thread die Temperatur über die serielle Schnitstelle einmalig abfragen soll. Dazu wird an den Mikroprozesser (Modbus-Slave) eine Anfrage geschickt. Dem SingleMeasurementWorker wird im Konstruktor die serielle Schnitstelle (serialPort) übergeben. Die Modbus-Anfrage besteht aus folgenden 8 Bytes: 2,4,0,0x30,0,1,0x31,0xf6.

Der grundsätzliche Aufbau eines Modbus-Datenpakets:
![Modbus Aufbau](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/ModbusADUPDU.png)

[Infos über Mosbus im 5. Protokoll](https://github.com/HTLMechatronics/m14-la1-sx/edit/rufflm14/rufflm14/Protokoll_5.md)

[Link zur Modbus-Dokumentation](http://modbus.org/specs.php)

Nach einer Wartezeit von 100ms wird die Antwort ausgelesen und auf Herz und Nieren geprüft. Sie soll aus 9 Bytes bestehen und die Werte der Temperaturmessung befinden sich an der 3. und der 4. Stelle.  Gegebenenfalls wird eine Exception geworfen. Löst die Antwort keine Exception aus, wird die Temperatur in Grad ausgerechet und an GUI zurückgegeben.

```java

public class SingleMeasurementWorker extends SwingWorker<Double, String>
{
  private final SerialPort serialPort;

  public SingleMeasurementWorker (SerialPort serialPort)
    {
      this.serialPort = serialPort;
    }
  
  @Override
  protected Double doInBackground () throws Exception
    {
      publish("Sende Request an Modbus-Server");
      int[] request= { 2,4,0,0x30,0,1,0x31,0xf6};
      serialPort.writeIntArray(request);
       TimeUnit.MILLISECONDS.sleep(100);

       int[] response = serialPort.readIntArray();

       if (response == null || response.length==0)
          { 
            throw new ModbusException("Keine Atnwort erhaten",request);
          }

       if (response.length <7)
          {
            throw new ModbusException("Zu kurze Antwort erhalten", request, response);
          }

       if (response[0]!= 2)
          {
            throw new ModbusException("Antwort von falschem Gerät", request, response);
          }

       if (response[1]!= 4)
          {
            throw new ModbusException("Antwort mit falschem Function-Code", request, response);
          }

        if (response[2]!= 2)
         {
           throw new ModbusException("Antwort mit falscher Anzahl von Bytes", request, response);
         }


         double temp = (response[3]* 256.0 + response[4]) / 256.0;



      return temp;
    }
  
}
```

## Fehlerbehandlung

Die Antwort des Sure-Boards wird auf unterschiedliche Eigenschaften untersucht um Fehler zu erkennen und Exceptions werfen zu können.

code | Abfrage  
--- | ---  
```java if (response == null ... response.length==0) ``` | Hier wird überprüft, ob das Paket vorhanden ist 
```java if (response.length <7) ``` | Hier wird überprüft, ob das Paket lang genug ist
```java if (response[0]!= 2) ``` | Hier wird überprüft, ob das Paket vom richtigen Slave kommt (2 ist die richtige Slave - Adresse)
```java if (response[1]!= 4) ``` | Hier wird überprüft, ob das Paket den richitgen Function-Code enthält 
```java if (response[2]!= 2) ``` | Hier wird überprüft, ob das Paket die richtige Anzahl an Datenbytes enthält

## Programmieren von Exceptions

Hier werden eigene Exceptions definiert. Dafür muss die Klasse ModbusException von der Superklasse Exception abgeleitet werden. Das Ziel ist es unterschiedliche Fehler zu erkennen und diese unterschiedlich behandeln zu können. Ansonsten funktioniert die Fehlerbehandlung gleich wie bei einer normalen Exception.

```java
public class ModbusException extends Exception
 {
     private final int [] request;
     private final int [] response;
 
 
     public ModbusException (String message) {
         super(message); //message ist die String-Message, die beim Werfen der Exception eingegeben werden muss
         request = null;
         response = null;
     }
   
     public ModbusException (String message, Throwable cause) {
         super(message, cause);
         request = null;
         response = null;
     }
     
     public ModbusException (String message, int [] request) {
         super(message);
         this.request = request;
         response = null;
     }
     
     public ModbusException (String message, int [] request, int [] response) {
         super(message);
         this.request = request;
         this.response = response;
     }
  
     public int[] getRequest () {
         return request;
     }
  
     public int[] getResponse () {
         return response;
     }     
  }
```
