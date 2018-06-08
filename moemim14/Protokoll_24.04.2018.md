# Protokoll 6 24.04.2018

Name: Michael Mörth  
Klasse: 4AHME  
Gruppe: 2  

Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Moritz Martinak, Mario Nabernik, Muri Lorenz, Platzer Andreas, Marcel Köhler    
Abwesend: -

## Kurze Wiederholung der letzten Einheit
### Java Native Interface
> Java Native Interface (JNI) ist eine standardisierte **Anwendungsprogrammierschnittstelle** (API), die die Möglichkeit schafft, aus der Programmiersprache Java heraus Plattform-spezifische Funktionen bzw. Methoden aufzurufen.
Im Gegensatz zu gewöhnlichen Java-Programmen ist ein Java-Programm, das JNI-Aufrufe verwendet, nur dann plattformunabhängig, wenn die native **Programmbibliothek auf allen Plattformen verfügbar ist**. 

> JNI ermöglicht es, native Methoden zu schreiben für Situationen, in denen es **nicht möglich ist**, **ausschließlich Java** als Programmiersprache einzusetzen. Dies ist der Fall, wenn beispielsweise die Standard-Java-Klassenbibliothek bestimmte Plattform-abhängige Features oder andere Programmbibliotheken nicht unterstützt. Weiterhin ist es per JNI möglich, eine weitere **in einer anderen Programmiersprache programmierte Anwendung für Java zugreifbar zu machen**. Viele Klassen der Java-Standardbibliothek basieren auf JNI, um beispielsweise die Datei-Ein- und Ausgabe oder Soundwiedergabe zu ermöglichen. Indem Java Leistungs- und Plattform-abhängige Implementierungen in die Standardbibliothek integriert, kann der Java-Programmierer und -Nutzer diese Features in sicherer und Plattform-unabhängiger Weise nutzen. 

> Gelegentlich wird JNI als **Fluchttür** ("escape hatch") für Java-Entwickler bezeichnet, da es ihnen den Zugriff auf Funktionalitäten ermöglicht, der andernfalls über die Standard-Java-API nicht möglich wäre. Es stellt die Schnittstelle zu anderen Programmiersprachen wie C oder C++ dar. 

*Quelle: [Wikipedia](https://de.wikipedia.org/wiki/Java_Native_Interface)*

### Beschrechen der programmierten Methoden in der letzten Einheit
Nach der kurzen Wiederholung über JNI, haben wir damit begonnen, die Methoden, welche wir in der letzten Einheit programmiert hatten, noch einmal kurz durchzusprechen. 
Folgende Mehtoden wurden bereits realisiert:
  * Konstruktor
  * `showThrowable()`
  * `updateSwingControlls()`
  * `refresh()`
  * `connect()`
  * `disconnect()`
  * ActionPerformed Methoden
  
Für genaure Informationen zu den Methoden kann das [Protokoll der letzten Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll_20.02.2018.md#der-quellcode) verwendet werden.

## Erweiterungen und Verbessereungen des Quellcodes
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
Die Funktion `connect()` wurde im Laufe der Stunde erweitert. Unter anderem wurden die Parameter für die serielle Schnittstelle festgelegt. Für den Fall das ein Fehler auftritt, wurde zur richtigen Behandlung des Fehlers ein weiteres try-catch eingebaut.

| Parameter | Beschreibung |
| --------- | ------------ |
| `SerialPort.BAUDRATE_57600` | Legt die Baudrate auf 57600 fest |
| `SerialPort.DATABITS_8` | Legt die Anzahl der Databits auf 8 fest |
| `SerialPort.STOPBITS_2` | Legt die Anzahl der Stoppbits auf 2 fest  |
| `SerialPort.PARITY_NONE` | Legt die Art der Parity fest (ODD, EVEN, NONE) |

Sollte beim Verbinden mit der seriellen Schnittstelle, ein Fehler auftreten, so fangt das erste catch ein Object vom Typ `Throwable` und versucht den Port, falls einer geöffnet wurde wieder zu schließen. Sollte dabei wieder ein Fehler auftreten, wird im zweiten catch wieder ein Object vom Typ `Throwable` gefangen. Im zweiten catch wird dann der Cause des zweiten Fehlers an den Cause des ersten Fehlers angehänt und anschließend wird die Methode `showThrowable()` aufgerufen und die Variable `serialPort` wird wieder auf `null` gesetzt.

#### Der Befehl addSupressed()
> Appends the specified exception to the exceptions that were suppressed in order to deliver this exception. This method is thread-safe and typically called (automatically and implicitly) by the try-with-resources statement. <

*Quelle: [Javadoc](https://docs.oracle.com/javase/7/docs/api/java/lang/Throwable.html#addSuppressed(java.lang.Throwable))*

### Die Methode updateSwingControlles()
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
Erweitert wurde diese Methode mit einer Weiteren `if-Verzweigung`. Mit `if(activeWorker) != null` wird überprüft, ob ein Worker aktiv ist. Wenn ein Worker aktiv ist, soll der Standard Cursor durch den `WAIT_CURSOR` ersetzt werden, die GUI soll aber weiterhin benutzbar sein.

### Neue Methode startSingleMeasurement()
```java
  private void startSingleMeasurement()
  {
    activeWorker = new MySingleMeasurementWorker(serialPort);
    activeWorker.execute();
    updateSwingControlles();
  }
```
Diese Methode starte den SwingWorker. Hierführ wird der aktuelle Port benötigt, welcher in der Variable `serialPort` gespeichert ist.

## [SwingWorker](https://docs.oracle.com/javase/7/docs/api/javax/swing/SwingWorker.html)
### Was ist Multithreading?
> Multithreading (auch Nebenläufigkeit, Mehrsträngigkeit oder Mehrfädigkeit genannt) bezeichnet in der Informatik das gleichzeitige (oder quasi-gleichzeitige) Abarbeiten mehrerer Threads (Ausführungsstränge) innerhalb eines einzelnen Prozesses oder eines Tasks (ein Anwendungsprogramm). 

> Im Gegensatz zum Multitasking, bei dem mehrere unabhängige Programme voneinander abgeschottet quasi-gleichzeitig ausgeführt werden, sind die Threads eines Anwendungsprogramms nicht voneinander abgeschottet und können somit durch sogenannte Race Conditions Fehler verursachen, die durch Synchronisation vermieden werden müssen. 

> Sowohl Multithreading als auch Multitasking können entweder auf nur einem Prozessorkern ausgeführt werden, als auch zusätzlich mit Multiprocessing kombiniert werden (echt-parallele Ausführung durch mehrere Prozessorkerne). 

*Quelle: [Wikipedia](https://de.wikipedia.org/wiki/Multithreading)*

### Wichtige Methoden im Umgang mit dem SwingWorker
| Methode | Klasse | Beschreibung |
| ------- | ------ | ------------ |
| `doInBackground()` | Worker-Klasse | Alle Befehle in dieser Methode werden im zweiten Thread ausgeführt. |
| `publish()` | Worker-Klasse | Wird verwendet um mit dem [EDT-Thread](https://docs.oracle.com/javase/tutorial/uiswing/concurrency/dispatch.html) zu kommunizieren. |
| `process()` | Innere Klasse | Diese Methode übernimmt die Aufgaben im EDT-Thread, während der zweite Thread arbeitet. |
| `get()` | Innere Klasse | Liefert den Rückgabewert von `doInBackground()` |
| `done()` | Innere Klasse | Wird sofort aufgerufen nachdem `doInBackground()` beendet oder abgebrochen wurde, oder ein Fehler aufgetreten ist. |
| `execute()` | *über Objekt aufgerufen* | Startet den WorkerThread |
| `cancel()` | *über Objekt aufgerufen* | Versucht den WorkerThread zu beenden |

### Die Klasse SingleMeasurementWorker
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
Da der Wert die 256 eines Integer Wertes übersteigen kann, wird die `response` in zwei Bytes aufgeteilt, ein `lowbyte` und ein `highbyte`. Die Konfigurationen für den Aufbau des Frames stammen aus der README des Projektes, vom SVN-Server Arnfels.

### Die innere Klasse MySingleMeasurementWorker
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
In der Methode `done()` wird nach dem Beenden der Methode `doInBackground()` mit Hilfe der Methode `get()` der Rückgabewert in die Variable `temp` gespeichert und anschließen im Label formatiert ausgegeben.
