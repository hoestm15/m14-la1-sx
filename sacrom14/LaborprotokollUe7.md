# 7.Protokoll  
  
  **Name**:  *Sackl Roland*  
  **Datum:** *20.03.2018*  
  **Uhrzeit:** *9:40-12:25*  
  **Gruppe:** *3*  
  
  **Abwesend:**  -
  **Anwesend:**  Sackl Martin,Sammer Daniel,Ruffennacht Florian,Sackl Roland, Reinbacher Bernhard,Schuster Patrick, Schmuck Martin    
  
 ## Wiederholung der letzten Einheit
 Zu Beginn widerhoolten wir den besprochen Stoff der letzen Einheit.Jene Schüler, die in der lezten Einheit nicht anwesend waren,wurden am Beginn über den Stoff geprüft. Da die letzte Einheit sehr lang her war, wurden so wieder unser Gedächtniss aufgefrischt.Es wurden die Themen *Serielle Schnittstellen in *UART*, *Java* ,*Feldbus* und *MODBUS* wiederholt. Weitere Infos [Protokoll 6](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacrom14/sacrom14/LaborprotokollUE6.md)


## Projekt:Temperatur-Messung  
### SingleMeasurementWorker  
Hat die Funktion, dass in einem Background-Thread die Temperatur über die seriellen Schnittstelle abgefragt werden soll.
Dem SingleMeasurementWorker wird im Konstruktor die serielle Schnittstelle *serialPort* übergeben.Die Modbus-Anfrage besteht aus 2,4,0,0x30,0,1,0x31,0xf6 8 Bytes.Auf die Antwort wird 100ms gewartet.Wird keine Exception ausgelöst, , so wird der Temperaturwert, der sich an der 3ten und 4ten Stelle der 9 Byte großen *response* befindet, in Grad Celsius umgewandelt und zurückgegeben

```java
public class SingleMeasurementWorker extends SwingWorker<Double, String> 
  {

  private final SerialPort serialport;
  
  //Konstruktor
  
  public SingleMeasurementWorker (SerialPort serialport)
  {
    this.serialport = serialport;
  }
  
  @Override
  protected Double doInBackground () throws Exception
  {
    publish("Sende Anfrage/Request an Modbus Server");
    int [] request = {02, 04, 00, 0x30, 00, 01, 0x31, 0xf6 };
    serialport.writeIntArray(request);
    TimeUnit.MILLISECONDS.sleep(100);
    int [] response = serialport.readIntArray();
    
    //Beginn der Fehlerbehandlung
    if(response == null || response.length == 0) 
    {
      throw new ModbusException("Keine Antwort erhalten",request);
    }
    if(response.length < 7 ) 
    {
      throw new ModbusException("Antwort zu kurz",request,response);
    }
    if(response[0] != 2) 
    {
      throw new ModbusException("Antwort vom falschem Gerät",request,response);
    }
    if(response[1] != 4) 
    {
      throw new ModbusException("Antwort mit falschem Funktionscode",request,response);
    }
    if(response[2] != 2) 
    {
      throw new ModbusException("Antwort mit falscher Anzahl von Bytes",request,response);
    }
    publish("Response mit " + response.length + "Bytes eingetroffen");
    double temp = (response[3] *256.0 + response[4]) / 256.0;
    
    return temp;
  }
}
```  


### Swingworker  
Ist eine Java-Klasse, mit der man länger andauernde GUI-Interaktionen in einem Background-Thread ablaufen lassen kann. Können mehrere Treads zum Ausführen solcher Aufgaben verwendet werden.Muti-Tasking und MultiThreading wird möglich. 
### Multi-Threading  
Kann als Mehrsträngigkeit bezeichnet werden. Heißt, dass das Abarbeiten mehrerer Threads quasi gleichzeitig stattfinden kann.Da im Gegensatz zum Multi-Tasking die einzelnen Threads nicht voneinander abgeschottet sind
[Wiki/Mulithreading](https://de.wikipedia.org/wiki/Multithreading)  


## Fehlerbehandlung
Wird überprüft, ob im richtigen Paket der richtige Wert steht. Wenn das nicht Erfüllt wird, so soll eine Exception geworfen werden.  


Code | Abfrage  
--- | ---  
```java if (response.length <7) ``` | Ist das Paket lang genug ?
```java if (response[0]!= 2) ``` |  Kommt das Paket von demrichtigen Slave ?
```java if (response[2]!= 2) ``` |  Enthält das Paket die richtige Anzahl an Datenbytes?
```java if (response[1]!= 4) ``` |  Enthält das Paket den richitgen Function-Code?
```java if (response == null ... response.length==0) ``` | Ist das Paket vorhanden oder nicht ? 



## Programmieren einer eigenen Exception  
Mit Java ist es möglich selbst eine Excepion zu programmieren.Die Exception Klasse ist die Superklasse aller Exceptions, deshalb wird von dieser Klasse abgeleitet sodas man eine eigene Exception erstellen kann.

```java
public class ModbusException extends Exception
 {
     private final int [] request;
     private final int [] response;
 
 
     public ModbusException (String message) 
     {
         super(message); //message ist die String-Message, die beim Werfen der Exception eingegeben werden muss
         request = null;
         response = null;
     }
   
     public ModbusException (String message, Throwable cause) 
     {
         super(message, cause);
         request = null;
         response = null;
     }
     
     public ModbusException (String message, int [] request) 
     {
         super(message);
         this.request = request;
         response = null;
     }
     
     public ModbusException (String message, int [] request, int [] response) 
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



