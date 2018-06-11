# Protokoll 7: Visualisierung eines Temperatursensors
Name: Patrick Schuster  
Klasse: 4AHME  
Gruppe: 3    
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: -

# Aufgabenstellung
Es soll eine Java Swing GUI zur Visualisierung eines Temperatursensors erstellt werden. 
Mit Hilfe der GUi soll man sich mit dem Sure Board verbinden können und die Messdaten des Temperatursensors auslesen können. 
Für die Verbindung zwischen Java GUI und PC soll das Feldbussystem Modbus verwendet werden. 
Das Programm wurde bereits in der vorherigen Einheit begonnen, konnte aber nicht fertig gestellt werden.
[Protokoll der vorherigen Einheit]( m14-la1-sx/suspam14/Protokoll6.md)

# SwingWorker
Der Swingworker ist eine Klasse zur Verwendung von Multithreading in einer Java Swing-Gui.
## Multithreading
Multithreading ist das parallele arbeiten von mehreren Threads innerhalb eines einzigen Programms. Das Programm wird somit auf mehrere CPU-Threads aufgeteilt. Es kommt somit zu keinen Verzögerungen durch z.B. Ladevorgänge oder komplexe Rechenvorgänge da diese im Hintergrund ausgeführt werden.
## SingleMeasurmentWorker
Der SingleMeasurementWorker soll an den Modbus-Slave (Sureboard) eine Anfrage senden, dass dieser den ausgelesenen Wert des Temperatursensors and die JAVA-Gui übermittelt. Dazu senden wir eine Anfrage mit 8 Bytes und warten 100ms auf eine Antwort. Falls kein Paket angekommen ist oder das Paket ungültig ist wird durch die Fehlerbehandlung eine Exception geworfen. Der empfangene Temperaturwert besteht aus zwei Bytes, einem High-Byte und einem Low-Byte. Das muss beim auslesen beachtet werden. Der aus den zwei Bytes zusammengerechnte Wert (zwischen 0 und 256) wird danach in Grad Celsius umgewandelt und zurückgegeben.
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
    publish("sende Request an Modbus Server");
    int [] request = {02, 04, 00, 0x30, 00, 01, 0x31, 0xf6 };
    serialport.writeIntArray(request);
    TimeUnit.MILLISECONDS.sleep(100);
    int [] response = serialport.readIntArray();
    
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
      throw new ModbusException("Antwort mit falschen Funktioncode",request,response);
    }
    if(response[2] != 2) {
      throw new ModbusException("Antwort mit falscher Antwort von Bytes",request,response);
    }
    
    publish("response eingetroffen");
    
    double temp = (response[3] *256.0 + response[4]) / 256.0;
    
    return temp;
  }
  
}
```
## Fehlerbehandlung
Für unsere Fehlerbehandlung haben wir ein Modbus Paket im ASCII-Mode analysiert und abgefragt ob in den einzelnen Bytes das richtige steht und somit das Paket gültig ist.
![](https://github.com/suspam14/la1/blob/master/modbus_ascii.png)  

Abfrage | Fehler  
--- | ---  
response == null | Abfrage ob Paket empfangen wurde  
response.length<7 | Abfrage ob Paket genug Bytes hat
response[0]!=2 | Abfrage ob das Paket vom richtigen Sender kommt (Adresse soll 2 sein)  
response[1]!=4 | Abfrage ob das Paket den richtigen Funktionscode enthält (Funktionscode soll 4 sein)  
response[2]!=2 | Abfrage ob das Paket die richtige Anzahl an Datenbytes hat (Anzahl der Datenbytes soll 2 sein)


