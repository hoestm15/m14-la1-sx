# Protokoll der 7. Einheit (24.04.2018)  
Name:     Florian Nebel  
Klasse:   4AHME  
Gruppe:   2  

Anwesend: Köhler Marcel, Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: ---  

## Java Native Interface  
![Hardwarezugriff](https://github.com/HTLMechatronics/m14-la1-sx/blob/nebflm14/nebflm14/Hardwarezugriff.svg)  
Grundsätzlich regelt das Betriebssystem z.B. Windows den Zugriff auf serielle Schnittstellen wie z.B. Uart oder USB. Ein C-Programm würde dierekt auf das Betribssystem zugreifen, welches dann mit der Hardware kommuniziert.
Unter Java wird zur Kommunikation zwischen Programm und Hardware eine virtuelle Maschine, die sogenannte **Java Virtuelle Maschine (JVM)** zwischengeschaltet.  
Die Idee: Java wendet sich an die virtuelle Machine, diese an das Betriebssystem, und dieses an die Hardware. Das Problem liegt darin, dass die JVM keine seriellen Schnittstellen unterstützt. 
Gelöst wird das Problem durch das **Java Native Interface (JNI)** welches innerhalb der virtuellen Maschine eine für Java lesbare \*.jar Datei erzeugt und außerhalb, eine für das Betriebssystem lesbare binäre Bibliothek aufbaut. **rxtx comm gnu.io** bezeichnet eine aufgrund von verbuggten C-Bibliotheken und schlechter Versionsverwaltung, sowie fehlender Nutzerfreundlichkeit nicht zu empfehlende Variante. **Java Simple Serial Connector (JSSC)** orientiert sich im Gegensatz dazu nicht an java.comm und dem streaming-Konzept. Einer der großen Vorteile liegt darin, das die binären Bibliotheken automatisch an der richtigen Stelle entpackt werden.  

## [SwingWorker](https://docs.oracle.com/javase/7/docs/api/javax/swing/SwingWorker.html)
Multithreading bzw. Mehrsträngigkeit bezeichnet in der Informatik das "gleichzeitige" abarbeiten mehrerer Aufgaben(Threads) innerhalb eines einzelnen Prozesses/Tasks.
siehe [wikipedia.org](https://de.wikipedia.org/wiki/Multithreading)

## Das Programm
Es wurde am Programm der letzten Einheit weitergearbeitet.  
### `connect()`
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
Als erstes haben wir zur Methode `connect()` Parameter zur Definition der seriellen Schnittstelle hinzugefügt und eine Fehlerbehandlung angefügt.  
Fehler, welche beim Verbinden der seriellen Schnittstelle auftreten, werden in Form eines **Throwables** vom ersten `catch` gefangen. Eventuell geöffnete Ports werden daraufhin wieder geschlossen. Auch dabei können Fehler auftreten, welche von dem darauffolgenden `catch` gefangen werden würden. Sollte dieser Fall eintreten, wird dem zuerst geworfenen Fehler, der zweite mithilfe der Methode [`addSupressed()`](https://docs.oracle.com/javase/7/docs/api/java/lang/Throwable.html#addSuppressed(java.lang.Throwable)) angehängt und die Methode `showThrowable` wird aufgerufen. `serialPort` wird in den Zustand `null` gesetzt.  

### `updateSwingControlles()`
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
Um dem Nutzer zu signalisieren, dass zum aktuellen Zeitpunkt ein **Worker** aktiv ist, wird der Cursor als `WAIT_CURSOR` dargestellt. Um das zu erreichen wird eine if-Verzweigung verwendet.  

### `activeWorker`
```java
  private SwingWorker activeWorker;
```
In der GUI-Klasse wird die Variable `activeWorker`angelegt, welche in der Methode `updateSwingControlls()` verwendung findet. Sie wird genutzt um überprüfen zu können, ob ein Worker gestartet wurde.

### `startSingleMeasurement()`
```java
  private void startSingleMeasurement()
  {
    activeWorker = new MySingleMeasurementWorker(serialPort);
    activeWorker.execute();
    updateSwingControlles();
  }
```
Zum starten des **SwingWorkers** ist der aktuelle Port notwendig. Dieser kann der Vaariable `serialPort` entnommen werden.

### SingleMeasurementWorker
```java
package workers;
import java.util.concurrent.TimeUnit;
import javax.swing.SwingWorker;
import jssc.SerialPort;


/**
 *
 * @author michael
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
Da die maximalgröße des Integer-Wertes überschritten werden könnte wird der Rückgabewert in zwei Bytes geteilt, dem *highbyte* und dem *lowbyte*. Die für die Zusammensetzung des Frames notwendigen Konfigurationen stammen aus der readme-Datei des Projekts, am SVN-Server Arnfels.  

### MySingleMeasurementWorker
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
In der inneren Klasse wird nach dem Beenden der Methode `doInBackground()` mittels `get()` der Rückgabewert in der Variable `temp`gespeichert. Die Variable `temp` wird dann im Label ausgegeben.
