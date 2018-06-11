# Protokoll: Marcel Köhler
## 7.Einheit
## Thema: Verbesserung/Erweiterung des Quellcodes
Klasse: 4AHME  
Anwesend:Nebel Florian, Mandl Gerhard, Michael Mörth, Moritz Martinak, Mario Nabernik, Muri Lorenz, Platzer Andreas, Marcel Köhler 
Abwesend: niemand  

### Neue Variable
```java
  private SwingWorker activeWorker;
```
Diese wird für Multithreading benötigt um später einen neuen Thread zu starten.

### Die Methode `updateSwingControlles()`
```java
  public void updateSwingControlles()
  {
  
    jcbSerialDevice.setEnabled(false);
    jbutConnect.setEnabled(false);
    jbutContinousMeasurement.setEnabled(false);
    jbutDisconnect.setEnabled(false);
    jbutRefresh.setEnabled(false);
    jbutSingleMeasurement.setEnabled(false);
    jbutStopMeasurement.setEnabled(false);
    jlaTemperatur.setEnabled(false);
    
    if(activeWorker != null)                                        //
    {                                                               //
      setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));    // Erweiterung der Funktion
      return;                                                       //
    }                                                               //
    
    setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    jlaTemperatur.setEnabled(true);
    
    if(serialPort != null && serialPort.isOpened()) 
    {
    
      jbutDisconnect.setEnabled(true);
      jbutSingleMeasurement.setEnabled(true);
      return;
      
    }

    if(ports != null && ports.length > 0)
    {
    
      jcbSerialDevice.setEnabled(true);
      jbutConnect.setEnabled(true);
      jbutRefresh.setEnabled(true);
      
    }
    else if(ports != null && ports.length == 0)
    
      jbutRefresh.setEnabled(true); 
  }
```
Es wurde eine weitere `if-Verzweigung` hinzugefügt in der wird mit dem ausdruck `activeWroker != null` überpruft ob ein Worker aktiv ist. Wenn dies der fall ist soll der Cursor durch einen `WAIT_CURSOR`ersetzt werden wobei die GUI bedienbar bleiben soll. 


### Neue Methode `startSingleMeasurement()`
```java
  private void startSingleMeasurement()
  {
  
    activeWorker = new MySingleMeasurementWorker(serialPort);
    activeWorker.execute();
    updateSwingControlles();
    
  }
```

Diese Methode startet eine einen neuen Thread. Dazu wird der port benötigt welcher in der Variable `serialPort` gespeichert ist.



### Erweiterungen der Methode `connect()`
```java
  private void connect()
  {
    try //erstes try
    {
    
      String port = (String) jcbSerialDevice.getSelectedItem();
      serialPort = new jssc.SerialPort(port);
      serialPort.openPort();
      serialPort.setParams(                     //
              SerialPort.BAUDRATE_57600,        //
              SerialPort.DATABITS_8,            //  Erweiterungen
              SerialPort.STOPBITS_2,            //
              SerialPort.PARITY_NONE);          //
      updateSwingControlles();                  //
    }
    catch (Throwable th)
    {
      try                                                                      //
      {                                                                        //
        if(serialPort != null && serialPort.isOpened())                        //
          serialPort.closePort();                                              //
      }                                                                        //
      catch(Throwable th2)                                                     //
      {                                                                        //
        th.addSuppressed(th2);                                                 //  Erweiterungen
      }                                                                        //
      finally                                                                  //
      {                                                                        //
        updateSwingControlles();                                               //
      }                                                                        //
      showThrowable("Serielle Schnittstelle kann nicht geöffnet werden", th);  //
      serialPort = null;                                                       //
    }                                                                          //
  }
```
Dieser Methode wurden Parameter für die Serielle Schnittstelle hinzugefügt sowie ein weiteres `try-catch` für den fall des ein Fehler auftreten soll, das dieser auch passend behandelt wird. Sollte beim versuch eine verbindung aufzubauen ein Fehler auftreten wird dieser beim ersten catch behandelt. In diesem wird versucht den Port zu schließen. Tritt dort wieder ein Fehler auf wird dieser im zweiten catch behandelt. Dort wir die Ursache des ersten Fehlers + die des zweitens mit der funktion `showThrowable()`ausgegeben und der port auf `null`gesetzt.

```java
              SerialPort.BAUDRATE_57600,        //  stellt die bautrate auf 57600 ein
              SerialPort.DATABITS_8,            //  Anzahl der Datenbits, in diesem Fall 8 Bits
              SerialPort.STOPBITS_2,            //  Anzahl der Stoppbits, in diesem Fall 2 Bits
              SerialPort.PARITY_NONE);          //  Festlegung ob es ein Partity Bit gibt, in diesem Fall keines
   ```
   
   Der Befehl `th.addSuppressed(th2)` fügt der Fehlermeldung th die Fehlermeldung von th2 hinzu.
   
   ### Klasse SingleMeasurementWorker
```java
package workers;
import java.util.concurrent.TimeUnit;
import javax.swing.SwingWorker;
import jssc.SerialPort;

public class SingleMeasurementWorker extends SwingWorker<Double,String>
{
  private final jssc.SerialPort serialPort;

  public SingleMeasurementWorker (SerialPort serialPort)
  {
    this.serialPort = serialPort;
  }
  
  @Override
  protected Double doInBackground () throws Exception
  {
    int [] frame = {0x02,0x04,0x00,0x30,0x00,0x01,0x31,0xf6};
    int [] response = serialPort.readIntArray();
    
    serialPort.writeIntArray(frame);
    TimeUnit.SECONDS.sleep(1);
    System.out.println(response.length);
    double temp = response[3]+response[4] / 256.0;
    return temp;
  } 
}
```
Da die Werte die größe eines Integer Wertes übersteigen können, werden diese in zwei Bytes aufgeteilt, in ein `low-` und ein `highbyte`. Die Konfigurationen für den Aufbau stammt aus der README des Projektes, vom SVN-Server in Arnfels.

### Innere Klasse MySingleMeasurementWorker
```java
  private class MySingleMeasurementWorker extends SingleMeasurementWorker
  { 
    public MySingleMeasurementWorker (SerialPort serialPort)
    {
      super(serialPort);
    }

    @Override
    protected void done ()
    {
      try
      {
        double temp = get();
        
        jlaTemperatur.setText(String.format("%.01f °C", temp));
      }
      catch (Exception ex)
      {
        showThrowable("Einzelmessung gescheitert", ex);
      }
      finally
      {
        activeWorker = null;
        updateSwingControlles();
      }
    }

    @Override
    protected void process (List<String> chunks)
    {

    }  
  }
```
Nach dem Beenden der Methode `doInBackground` wir in der Methode `done()` mit hilfe der Methode `get()` der Rückgabewert in die Variable `temp`gespeichert, welcher anschließen im Label ausgegeben wird.


## SwingWorker

SwingWorker wird benötigt um Multithreading nutzen zu können.

### Wichtige Methoden

| Methode | Beschreibung |
| ------- | ------------ |
| doInBackground() | Alle Funktionen uned Befehler in dieser Methode werden in einem anderen Thread ausgeführt. |
| get() | holt den Rückgabewert doInBackground() |
| done() | Wird aufgerufen wenn doInBackground() mit der Aufgabe fertig ist, dieser gestoppt wird oder wenn ein Fehler auftritt. |
| publish() | Sendet eine Liste von Chunks zur publish Methode in den Event-Dispatch-Thread. |
| process() | Mit dieser Meethode erhält mann eine Liste von Chunks von der publish() Methode im Event-Dispatch-Thread. |
| execute() | Startet einen neuen Worker-Thread |
| cancel() | Setzt das cancel Flag des Threads und versucht somit den Thread zu beenden |

#### ([Quelle](https://docs.oracle.com/javase/7/docs/api/javax/swing/SwingWorker.html))
