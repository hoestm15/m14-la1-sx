# _Protokoll Siebente Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 15.05.2018**  
**Uhrzeit: 9:40-12:25**  
  
**Anwesenheit: _Es waren alle Schüler anwesend_**  
  
-----------------------------------------------------------  
#### Wiederholung Einheit 5 & 6  
Jene Schüler, die in der Einheit 6 nicht anwesend waren, wurden am Beginn der LAB-Einheit über den Stoff der 5ten und 6ten LAB-Einheit geprüft. Somit wurden unsere Gedächtnisse wieder auf den aktuellen Stand gebracht, da die letzte Einheit sehr lange her war.  
Es wurden die Themen *Serielle Schnittstellen in Java*, *UART*, *MODBUS* und *Feldbus* wiederholt.  
siehe: [Protokoll Einheit 6, Patrick Schuster](https://github.com/HTLMechatronics/m14-la1-sx/blob/suspam14/suspam14/Protokoll6.md) & [Protokoll Einheit 5, Daniel Sammer](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/Protokoll5.md)  
  
-----------------------------------------------------------  
#### Fortsetzung Projekt: Temperatur-Messung  
##### Swingworker  
Eine SwingWorker-Klasse ist eine abstrakte Klasse, mit der man länger andauernde GUI-Interaktionen in einem Background-Thread ablaufen lassen kann. Es können mehrere Background-Threads zum Ausführen solcher Aufgaben verwendet werden, da heutzutage Computer mehrere Prozessor-Kerne besitzt (siehe: [SwingWorker](https://docs.oracle.com/javase/8/docs/api/javax/swing/SwingWorker.html). Somit wird Multi-Tasking möglich und Multi-Threading ab hier zu einem sehr wichtigen Thema.  
  
###### Multi-Threading  
Mutli-Threading kann auch als Mehrsträngigkeit bezeichnet werden. Damit ist in der Informatik gemeint, dass das Abarbeiten mehrerer Threads quasi gleichzeitig stattfinden kann. Da hier die einzelnen Threads nicht voneinander abgeschottet sind (im Gegensatz zum Multi-Tasking), können diese sogenannten *Race-Conditiones* verursachen. Diese sollen durch Synchronisation vermieden werden.  
[Wiki/Mulithreading](https://de.wikipedia.org/wiki/Multithreading)  
[Wiki/Race-Conditions](https://de.wikipedia.org/wiki/Race_Condition)  
  
##### SingleMeasurementWorker  
Die Klasse *SingleMeasurementWorker* ist dafür da, damit in einem Background-Thread die Temperatur über die seriellen Schnittstelle abgefragt werden soll. Dafür soll die Klasse an das SureBoard (Slave -> Modbus) eine Anfrage senden. Die Anfrage (*request*) beinhaltet 8 Byte (2,4,0,0x30,0,1,0x31,0xf6). In den nächsten 100 ms wird auf eine Antwort (*response*) gewartet. Löst die erhaltene Antwort keine Exception aus, so wird der Temperaturwert, der sich an der 3ten und 4ten Stelle der 9 Byte großen *response* befindet, in Grad Celsius umgewandelt und zurückgegeben (Da sich der Temmperaturwert aus zwei Bytes ergibt, ist dies bei den Umrechnungen zu beachten).  
  
###### Listing  
```java
public class SingleMeasurementWorker extends SwingWorker<Double, String> {

  private final SerialPort serialport;
  
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
    if(response == null || response.length == 0) {
      throw new ModbusException("Keine Antwort erhalten",request);
    }
    if(response.length < 7 ) {
      throw new ModbusException("Antwort zu kurz",request,response);
    }
    if(response[0] != 2) {
      throw new ModbusException("Antwort vom falschem Gerät",request,response);
    }
    if(response[1] != 4) {
      throw new ModbusException("Antwort mit falschem Funktionscode",request,response);
    }
    if(response[2] != 2) {
      throw new ModbusException("Antwort mit falscher Anzahl von Bytes",request,response);
    }
    publish("Response mit " + response.length + "Bytes eingetroffen");
    double temp = (response[3] *256.0 + response[4]) / 256.0;
    
    return temp;
  }
}
```  



