# 7. Protokoll  
**Name:** Sackl Martin   
**Klasse** 4ahme    
**Gruppe:** 3

Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster   
Abwesend: -  
*******************************************************************************************************************************************  
## Wiederholung der letzten beiden Einheiten  
Die Schüler die in der 6. Einheit nicht anwesend waren wurden über den Stoff der letzten beiden einheiten überprüft. So wiederholten wir die Themen Serielle Schnittstellen in Java, UART, Modbus und Feldbus.  
Link: [6. Protokoll](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacrom14/sacrom14/LaborprotokollUE6.md), [5. Protokoll](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacmam14/sacmam14/Protokoll5.md)  
*******************************************************************************************************************************************  
## Fortsetzung Projekt: Temperatur Messung  
### Multi-Threading  
Multi-Threading bezeichnet in der Informatik das gleichzeitige Abarbeiten mehrer Threads. 
Im Gegensatz zum Multitasking, bei dem mehrere unabhängige Programme voneinander abgeschottet quasi-gleichzeitig ausgeführt werden, sind die Threads eines Anwendungsprogramms nicht voneinander abgeschottet und können somit durch sogenannte Race Conditions Fehler verursachen, die durch Synchronisation vermieden werden müssen.  
Sowohl Multithreading als auch Multitasking können entweder auf nur einem Prozessorkern ausgeführt werden, als auch zusätzlich mit Multiprocessing kombiniert werden.  
[Multi-Threading/Wikipedia](https://de.wikipedia.org/wiki/Multithreading)  

### Swingworker  
Es ist eine abstrakte Klasse, mit der man länger andauernde GUI-Interaktionen in einem Backgroung-Thread ablaufen lassen kann.  

### SingleMeasurementWorker  
In dieser Klasse soll die Tempertur in einem eigenem Thread über die serielle Schnittstelle einmalig abgefragt werden. Es wird eine Anfrage an den Mikroprozessor (Slave) geschickt. Die serielle Schnittstelle wird im Konstruktor übergeben.  
Modbus-Anfrage besteht aus 8-Bytes: 2,4,0,0x30,0,1,0x31,0xf6  
Auf die Antwort wird 100ms gewartet. Wird keine Exception ausgelöst, so wird der Temperaturwert, der sich an der 3ten und 4ten Stelle der 9 Byte großen response befindet, in Grad Celsius umgewandelt und zurückgegeben.  
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
Es wird die Gültigkeit des Paketes überprüft. Sollte etwas falsch/ungültig sein wird eine Exception geworfen.  

Code | Beschreibung  
--- | ---  
```if (response == null) ``` | Überprüfung ob das Paket vorhanden ist bzw. ob etwas empfangen wurde  
```if (response.length <7) ``` | Überprüfung ob Paket lang genuf ist  
```if (response[0]!= 2) ``` | Überprüfung ob Paket vom richtigen Slave kommt  
```if (response[1]!= 4) ``` | Überprüfung ob das Paket den richtigen Function Code enthält  
```if (response[2]!= 2) ``` | Überprüfung ob die richtige Anzahl an Datnebytes vorhanden ist  

### Eigene Exception programmieren  
In Java ist es möglich seine eigene Exception zu programmieren.  
 ```java  
    package Workers;



public class Modbusexception extends Exception
{
  private final int [] request;
  private final int [] response;  


  public Modbusexception (String message)
  {
    super(message);
    request = null;
    response = null;
  }
  
  public Modbusexception (String message, Throwable cause)
  {
    super(message, cause);
    request = null;
    response = null;
  }
  
  public Modbusexception (String message, int [] request)
  {
    super(message);
    this.request = request;
    response = null;
  }
  
  public Modbusexception (String message, int [] request, int [] response)
  {
    super(message);
    this.request = request;
    this.response = response;
  }


  public int[] getRequest ()
  {
    return request;
  }


  public int[] getResponse ()
  {
    return response;
  }
 }
 ```  
