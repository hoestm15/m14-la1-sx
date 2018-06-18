# Laborprotokoll  
Siebente Einheit am 15. Mai 2018  
Martin Schmuck  
4AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster (vollzählig)

## Thema der Einheit: Visualisirung eines Temperatursensors
In dieser Einheit schließen wir nach einer kurzen Wiederholung der Einheiten [5](https://github.com/HTLMechatronics/m14-la1-sx/blob/smumam14/smumam14/Protokoll5.md) und [6](https://github.com/HTLMechatronics/m14-la1-sx/blob/smumam14/smumam14/Protokoll6.md) direkt an die letzte Einheit an. Dies war notwendig, da seit der letzten Einheit bereits einige Wochen ins Land gezogen waren, und damit wir unser Wissen wieder auffrischen konnten.

### Multithreading
Unter Multithreading versteht man im Allgemeinen, dass man bei einem Programm nicht einen Befehl nach dem anderen ausführt, sondern mehrere "Programmpfade" zeitgleich ausgeführt werden.  Dies ist nicht mit dem Begriff Multitasking zu verwechseln, welcher bedeutet, dass meherere Programme (Tasks) sich gemeinsame Ressourcen (CPU, Speicher, etc.) teilen. Dabei handelt es sich um eine Eigenschaft des Betriebssystems. Multithreading geht hier weiter, es erweitert die Grundsätze des Multitasking auf die Programmebene, so werden zum Beispiel Rechenoperationen in mehrere Threads unterteilt, die dann wirklich parallel ablaufen. Somit verteilt das Betriebssystem die Ressource nicht mehr nur auf alle Anwendungen, sonder auch auf die Threads in den Anwendungen.

### Swing Worker
Wie bereits besprochen, sorgt ein SwingWorker dafür, dass die GUI beim Ausführen von länger andauernden Vorgängen im Programmablauf (Rechnen von aufwändigen Algorithmen, Kommunikation, ...) nicht blockiert. Hierfür haben wir die abstrakte Klasse SwingWorker abgeleitet und damit die Klasse SingleMeasuremmentWorker erstellt. Sie sendet eine Anfrage an den Modbus-Server mit 8 Byte Inhalt (0x02, 0x04, 0x00, 0x30, 0x00, 0x01, 0x31, 0xf6). Danach wird ein Timeout von 100 ms abgewartet. Falls in dieser Zeit keine Antwort zurückkommt, wird eine Exception geworfen. Danach kommt ein Fehlerhandlingbereich. Wenn keine Exception geworfen wurde, ist alles ok und die Temperatur wird ausgerechnet und zurückgeliefert. Dabei muss beachtet werden, dass die Antwort aus einem `HIGH-BYTE` und einem `LOW-BYTE` besteht. Die wird in der Rechnung durch Multiplikation des ersten Bytes mit 256 berücksichtigt. `publish`-Anweisungen senden Zwischenstände, um die Statuszeile zu aktualisieren. Hier das Listing (ohne Fehlerbehandlung, diese wird später erläutert):

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
In diesem Abschnitt kontroliieren wir, ob die Antwort plausibel ist, das heißt, ob sie den Erwartungen entspricht. Dies geschieht im nachfolgenden Fehlerhandlingblock, welcher aus dem obigen Listing entfernt wurde (Der Zweck der Abfragen ergibt sich aus dem Exception-Text):
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
Es ist ratsam, für mehrere ähnliche Fehlerfälle eigene Exceptions zu erstellen. Dies erleichert die Fehlersuche erheblich. Also erstellen wir eine eigene Exception für Fehler, die im Zuge einer Modbus-Übertragung auftreten können. Dies geschieht, in dem man die Klasse Exception ableitet. Hier ist das Listing der Klasse ModbusException:

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
