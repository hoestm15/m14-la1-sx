# Protokoll der 1.Einheit
* Name: Mario Nabernik
* Klasse: 4AHME
* Datum: 24.04.2018
* Gruppe: 2
* Anwesend: Marcel Köhler, Michael Mörth, Florian Nebel, Lorenz Muri, Moritz Martinak, Andreas Platzer, Mario Nabernik, Gerhard Mandl  
* Abwesend: -
* Thema: SwingWorker

## Wiederholung der [letzten Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll_20.02.2018.md#der-quellcode)
### Java Native Interface
> Java Native Interface (JNI) ist eine standardisierte **Anwendungsprogrammierschnittstelle** (API), 
die die Möglichkeit schafft, aus der Programmiersprache Java heraus Plattform-spezifische Funktionen 
bzw. Methoden aufzurufen.
Im Gegensatz zu gewöhnlichen Java-Programmen ist ein Java-Programm, 
das JNI-Aufrufe verwendet, nur dann plattformunabhängig, wenn die native **Programmbibliothek auf allen 
Plattformen verfügbar ist**. 

*Quelle: [Wikipedia](https://de.wikipedia.org/wiki/Java_Native_Interface)*

Für genauere Informationen und Übungen, anbei ein kleines 
[Tutorial](https://de.wikipedia.org/wiki/Java_Native_Interface)

### Methoden der letzten Einheit
Die Methoden, die wir bereits in der letzten Einheit realisiert haben: 
  
  * `updateSwingControlls()`
  * `disconnect()`
  * `Konstruktor`
  * `refresh()`
  * `connect()`
  * `showThrowable()`
  * `ActionPerformed Methoden`

## Geschriebener Code in dieser Einheit
### Die Methode `connect()`
```java
  private void connect()
  {
    try //erstes try
    {
      String port = (String) jcbSerialDevice.getSelectedItem();
      serialPort = new jssc.SerialPort(port);
      serialPort.openPort();
      serialPort.setParams(
              SerialPort.BAUDRATE_57600,
              SerialPort.DATABITS_8,
              SerialPort.STOPBITS_2,
              SerialPort.PARITY_NONE);
      updateSwingControlles();
    }
    catch (Throwable th)
    {
      try //zweites try
      {
        if(serialPort != null && serialPort.isOpened())
          serialPort.closePort();
      }
      catch(Throwable th2)
      {
        th.addSuppressed(th2);
      }
      finally
      {
        updateSwingControlles();
      }
      showThrowable("Serielle Schnittstelle kann nicht geöffnet werden", th);
      serialPort = null;
    }    
  }
```
Sollte beim Verbinden mit der seriellen Schnittstelle, ein Fehler auftreten, 
so fangt das erste catch das `Throwable` und schließt den Port. Sollte dabei wieder ein Fehler auftreten, 
wird im zweiten catch wieder ein  `Throwable` gefangen. 
Im zweiten catch die beiden Fehler verbunden und es wird `showThrowable()` aufgerufen und die Variable 
`serialPort` wird wieder auf `null` gesetzt.

Schnittstellen:

| Parameter | Beschreibung |
| --------- | ------------ |
| `SerialPort.BAUDRATE_57600` | Baudrate auf 57600 |
| `SerialPort.DATABITS_8` | Anzahl der Databits auf 8 |
| `SerialPort.STOPBITS_2` | Anzahl der Stoppbits auf 2 |
| `SerialPort.PARITY_NONE` | Art der Parity (ODD, EVEN, NONE) |

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
    
    if(activeWorker != null)
    {
      setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
      return;
    }
    
    setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    jlaTemperatur.setEnabled(true);
    
    if(serialPort != null && serialPort.isOpened()) //Es wurde eine Verbindung mit einem Port erstellt -> Trennen möglich
    {
      jbutDisconnect.setEnabled(true);
      jbutSingleMeasurement.setEnabled(true);
      return;
    } 

    if(ports != null && ports.length > 0) //Verbinden mit einem Port möglich
    {
      jcbSerialDevice.setEnabled(true);
      jbutConnect.setEnabled(true);
      jbutRefresh.setEnabled(true);
    }
    else if(ports != null && ports.length == 0)
      jbutRefresh.setEnabled(true); 
  }
```
Erweitert wurde diese Methode mit einer Weiteren `if-Verzweigung`.
Aktivität des Workers wird mit `if(activeWorker) != null` überprüft. 
Sollte er aktiv sein, wird der Standard Cursor durch den Wait Cursor ersezt. 
Die GUI soll weiterhin benutzbar sein.

### Neue Klassenvariable `activeWorker`
```java
  private SwingWorker activeWorker;
```

### Neue Methode `startSingleMeasurement()`
```java
  private void startSingleMeasurement()
  {
    activeWorker = new MySingleMeasurementWorker(serialPort);
    activeWorker.execute();
    updateSwingControlles();
  }
```
SwingWorker wird gestartet. Hierführ benötigen wir den aktuellen Port, welcher in der Variable `serialPort` gespeichert ist.

## [SwingWorker](https://docs.oracle.com/javase/7/docs/api/javax/swing/SwingWorker.html)
### Was ist Multithreading?

Multithreading bedeutet, dass innerhalb eines Prozesses oder eines Tasks verschiedene Arbeitsstränge gleichzeitig abgearbeitet werden.
Multithreading kann auf einem Prozesskern ausgeführt werden, als auch auf mehreren Prozesskernen (echte Parallel-Ausführung).

### Methoden, die wir beim Arbeiten mit dem SwingWorker benötigen
| Methode | Beschreibung |
| ------- | ------------ |
| `doInBackground()` | Befehle in dieser Methode werden im zweiten Thread ausgeführt |
| `publish()` | Kommunikation mit dem EDT-Thread |
| `process()` | Führt die Aufgaben des EDT Threads aus |
| `get()` | Liefert den Rückgabewert von `doInBackground()` |
| `done()` | Wird nach `doInBackground()` ausgeführt |
| `execute()` | Startet den WorkerThread |
| `cancel()` | Beendet den Workthread |

### Die Klasse SingleMeasurementWorker
```java
package workers;
import java.util.concurrent.TimeUnit;
import javax.swing.SwingWorker;
import jssc.SerialPort;


/**
 *
 * @author mario
 */
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
    serialPort.writeIntArray(frame);
    TimeUnit.SECONDS.sleep(1);
    int [] response = serialPort.readIntArray();
    System.out.println(response.length);
    double temp = response[3]+response[4] / 256.0;
    return temp;
  } 
}
```
Da der Wert die Größe eines Integers übersteigen kann, wird die `response`
in ein `lowbyte` und ein `highbyte` aufgeteilt.

### MySingleMeasurementWorker (innere Klasse)
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
