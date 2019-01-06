# Protokoll 24.04.2018
## 7. Einheit

Name: Muri Lorenz <br>
Klasse: 4AHME <br>
Gruppe: 2 <br>
Datum der Einheit: 24.04.2018 <br>
Anwesend: Mandl, Martinak, Mörth, Muri, Nabernik, Nebel, Platzer, Köhler<br>
Abwesend: - <br>

## Wiederholung der letzten Einheit
Am Beginn der Einheit haben wir das Programm der letzten Einheit besprochen und außerdem über die Grundlagen der Kommunikation mit einem Modbus gesprochen.

**Besprochene Methoden**
* `showThrowable()`
* `updateSwingControlls()`
* `refresh()`
* `connect()`
* `disconnect()`
<br>

## Erweiterterungen des Quellcodes
### connect()
```java
private void connect ()
  {
    try
    {
      String port = (String) jcbSerialDevice.getSelectedItem();
      serialPort = new jssc.SerialPort(port);
      serialPort.openPort();
      serialPort.setParams(
              SerialPort.BAUDRATE_57600,                            // Legt die Baudrate fest (57600)
              SerialPort.DATABITS_8,                                // Legt die Anzahl der Datenbits fest (8)
              SerialPort.STOPBITS_2,                                // Legt die Anzahl der Stoppbits fest (2)
              SerialPort.PARITY_NONE);                              // Legt fest, ob eine EVEN, ODD oder keine Parity besteht (keine)
      updateSwingControls();
    }
    catch (Throwable th)
    {

      try
      {
        if (serialPort != null && serialPort.isOpened())
        {
          serialPort.closePort();
        }
      }
      catch (Throwable th2)
      {
        th.addSuppressed(th2);
      }
      showThrowable("Serielle Schnittstelle kann nicht geöffnet werden!", th);
      serialPort = null;
    }
    finally
    {
      updateSwingControls();
    }
  } 
```
### updateSwingControlles
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
    
    if(activeWorker != null)                                          // Überprüft ob ein Worker aktive ist
    {
      setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));      // Cursor wird auf einen wartenden Cursor gesetzt (rotierendes Rad)
      return;
    }
    
    setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    jlaTemperatur.setEnabled(true);
    
    if(serialPort != null && serialPort.isOpened())                   // Verbindung mit einem Port erstellt --> Trennen möglich
    {
      jbutDisconnect.setEnabled(true);
      jbutSingleMeasurement.setEnabled(true);
      return;
    } 

    if(ports != null && ports.length > 0)                             // Das Verbinden mit einem Port ist möglich
    {
      jcbSerialDevice.setEnabled(true);
      jbutConnect.setEnabled(true);
      jbutRefresh.setEnabled(true);
    }
    else if(ports != null && ports.length == 0)
      jbutRefresh.setEnabled(true); 
  }
```
### startSingleMeasurement
```java
  private void startSingleMeasurement()
  {
    activeWorker = new MySingleMeasurementWorker(serialPort);
    activeWorker.execute();                                         // startet den activeWorker
    updateSwingControlles();
  }
```

## SwingWorker
### SingleMeasurementWorker
| Methode | Klasse | Beschreibung |
| ------- | ------ | ------------ |
| `doInBackground()` | Worker-Klasse | Alle Befehle in dieser Methode werden im zweiten Thread ausgeführt. |
| `publish()` | Worker-Klasse | Hierdurch kann mit dem Haupt-Thread kommuniziert werden. |
| `process()` | Innere Klasse | Aufgaben im ersten Thread während der Worker arbeitet |
| `get()` | Innere Klasse | Der Rückgabewert von `doInBackground()` |
| `done()` | Innere Klasse | wird unmittelbar nach `doInBackground()` aufgerufen |
| `execute()` | *über activeWorker aufgerufen* | Startet den Worker |
| `cancel()` | *über activeWorker aufgerufen* | Beendet den Worker (freundlich) |

### SingleMeasurementWorker
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
    int [] frame = {0x02,0x04,0x00,0x30,0x00,0x01,0x31,0xf6};                 // Modbus Konfiguration
    serialPort.writeIntArray(frame);
    TimeUnit.SECONDS.sleep(1);
    int [] response = serialPort.readIntArray();                              // Antwort des SureBoards
    System.out.println(response.length);
    double temp = response[3]+response[4] / 256.0;                            // die Bits drei und vier sind Datenbits
    return temp;
  } 
}
```
### MySingleMeasurementWorker
```java
private class MySingleMeasurementWorker extends SingleMeasurementWorker
  {
    public MySingleMeasurementWorker (SerialPort serialPort)
    {
      super(serialPort);
    }

    @Override
    protected void done ()                                          // diese Methode wird nach dem Beenden der doInBackground()
    {
      try
      {
        double temp = get();                                       // get() ist der Rückgabewert der doInBackground()
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
