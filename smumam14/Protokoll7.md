# Laborprotokoll  
Sechste Einheit am 20. März 2018  
Martin Schmuck  
4AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster

## Thema der Einheit: Visualisirung eines Temperatursensors
In dieser Einheit schließen wir direkt an die letzte Einheit an.

### Swing Worker
Wie bereits besprochen, sorgt ein SwingWorker dafür, dass die GUI beim Ausführen von länger andauernden Vorgängen im Programmablauf nicht blockiert. Hierfür haben wir die abstrakte Klasse SwingWorker abgeleitet und damit die Klasse SingleMeasuremmentWorker erstellt. Sie sendet eine Anfrage an den Modbus-Server mit 8 Byte Inhalt (0x02, 0x04, 0x00, 0x30, 0x00, 0x01, 0x31, 0xf6). Danach wird ein Timeout von 100 ms abgewartet. Falls in dieser Zeit keine Antwort zurückkommt, wird eine Exception geworfen. Danach kommt ein Fehlerhandlingbereich. Wenn keine Exception geworfen wurde, ist alles ok und die Temperatur wird ausgerechnet und zurückgeliefert. `publish`-Anweisungen senden Zwischenstände, um die Statuszeile zu aktualisieren. Hier das Listing (ohne Fehlerbehandlung, diese wird später behandelt):

```java
public class SingleMeasurementWorker extends SwingWorker<Double, String> {

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
    
    //Hier ist ein Fehlerhandlingabsschnitt, wird später erklärt
    
    publish("Response mit " + response.length + "Bytes eingetroffen");
    double temp = (response[3] *256.0 + response[4]) / 256.0;
    
    return temp;
  }
}
```

### Fehlerhandling
#### Plausibilitätskontrolle der Antwort  
In diesem Abschnitt kontroliieren wir, ob die Antwort plausibel ist, das heißt, ob sie den Erwartungen entspricht. Dies geschieht im nachfolgenden Fehlerhandlingblock, welcher aus dem obigen Listing entfernt wurde (Der Sinn der Abfragen ergibt sich aus dem Exception-Text9:
```java
    if (response == null || response.length == 0)
      throw new ModbusException("keine Antwort", request);
    if (response.length < 7)
      throw new ModbusException("Antwort zu kurz", request, response);
    if (response[0] != 2)
      throw new ModbusException("Antwort vom Falschen Gerät", request, response);
    if (response[1] != 4)
      throw new ModbusException("Falscher Function Code", request, response);
    if (response[2] != 2)
      throw new ModbusException("Falsche Anzahl an Bytes", request, response);
```

#### Eigene Exception erstellen
Es ist ratsam, für mehrere ähnliche Fehlerfälle eigene Exception zu erstellen. Dies erleichert die Fehlersuche erheblich. Also erstellten wir eine eigene Exception für Fehler, die im Zuge einer Modbus-Übertragung auftreten können. Dies geschieht, in dem man die Klasse Exception ableitet. Hier ist das Listing der Klasse ModbusException:

```java
package gui;

public class ModbusException extends Exception
{

  final private int[] request;
  final private int[] response;


  public ModbusException (String message)
  {
    super(message);
    request = null;
    response = null;
  }


  public ModbusException (String message, Throwable cause)
  {
    super(message, cause);
    request = null;
    response = null;
  }


  public ModbusException (String message, int[] request)
  {
    super(message);
    this.request = request;
    response = null;
  }


  public ModbusException (String message, int[] request, int[] response)
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


