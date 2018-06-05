# Protokoll 17.04.2018

## 7. Einheit
## Thema: Temperaturmessung
 
 Name: Markus Kobor  
 Klasse: 4AHME  
 Datum: 17.04.2018  
 Anwesend: Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Enzi Gert, Knappitsch Robert, Kobor Markus <br>
 Abwesend: Niemand <br> <br> <br>
 
## Fortsetzen des Projekts "Temperaturmessung"
In dieser einheit wurde das Projekt "Temperaturmessung fortgesetzt. <br>
Dabei wurden bereits bestehende Methoden erweitert sowie neue Klassen erstellt. <br> <br>

Bis dato war unser Programm dazu in der Lage die am PC verfügabren Ports aufzulisten. <br>
Außerdem war es bereits möglich sich mit dem Sure-Board, welches für die Temperaturmessung verwendet werden soll, zu verbinden. <br>

## Erweiterungen vorhandener Methoden

### `updateSwingControls()`
```java
private void updateSwingControls() 
{
        jbutRefresh.setEnabled(true);
        jbutConnect.setEnabled(false);
        jbutDisconnect.setEnabled(false);
        jcbSerialDevice.setEnabled(false);
        jbutSingleMeasurement.setEnabled(false);
        jbutContinousMeasurement.setEnabled(false);
        jbutStopMeasurement.setEnabled(false);

        if (serialPort != null && serialPort.isOpened()) 
        {
            jbutRefresh.setEnabled(false);
            jbutDisconnect.setEnabled(true);
            jbutConnect.setEnabled(false);
            jbutSingleMeasurement.setEnabled(true);
            return;
        }

        if (jcbSerialDevice.getModel().getSize() > 0) 
        {
            jcbSerialDevice.setEnabled(true);
            jbutConnect.setEnabled(true);
        }

        if (activeWorker != null) 
        {
            jbutRefresh.setEnabled(false);
            jbutConnect.setEnabled(false);
            jbutDisconnect.setEnabled(false);
            jcbSerialDevice.setEnabled(false);
            jbutSingleMeasurement.setEnabled(false);
            jbutContinousMeasurement.setEnabled(false);
            jbutStopMeasurement.setEnabled(false);
            jlaTemperatur.setEnabled(false);
            setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
        } 
        else 
        {
            setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            jlaTemperatur.setEnabled(true);
        }
}
```
Die Methode "updateSwingControls()" wurde um eine if-else Anweisung erweitert. (if (activeWorker != null)) <br>
Dadurch ist es während eine Messung durchgeführt wird nun nicht mehr möglich mit der GUI zu interagieren, da alle Swing-controls deaktiviert werden. <br>
Der Cursor wird auf "Wait" gesetzt. <br>
 
### `connectPort()`
```java
private void connectPort(String port) 
{
        serialPort = new jssc.SerialPort(port);
        try 
        {
            if (serialPort.openPort() == false) 
            {
                throw new jssc.SerialPortException(port, "openPort", "return value false");
            }
            if (serialPort.setParams(SerialPort.BAUDRATE_57600, SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_2, SerialPort.PARITY_NONE) == false) 
            {
                throw new jssc.SerialPortException(port, "setParams", "return value false");
            }
        } 
        catch (Throwable ex)
        {
            showThrowable(new Exception("Serielle Schnittstelle kann nicht geöffnet werden", ex));
            serialPort = null;
        }
        finally 
        {
            updateSwingControls();
        }
}
```
Die Methode "connectPort()" wurde um die für die Übertragung der daten notwendigen Parameter erweitert:

 * **BAUDRATE:** 
 > Die Symbolrate oder Baudrate ist in der digitalen Übertragungstechnik und Nachrichtentechnik die Anzahl der  
 > übertragenen Symbole pro Zeitspanne. Die Einheit „pro Sekunde“ dieser Rate wird als Baud bezeichnet, abgekürzt 
 > Bd, um sie z. B. von der Bitrate zu unterscheiden.
 > Außerdem wurde eine Fehlerbehandlung miteingebaut, die, wenn ein Fehler aufritt, eine "SerialPortException" 
 > wirft. <br>
 
*Quelle: [Wikipedia, BAUDRATE](https://de.wikipedia.org/wiki/Symbolrate)*

In unserem Fall beträgt diese 57600.

* **DATABITS:** Bei Datenbits handelt es sich um die eigentlich zu übertragenden Informationseinheiten bei der Datenübertragung.

Wir übertragen 8 Databits.

* **STOPBITS:** > Stoppbits trennen die jeweilige Zeiteinheit von Daten auf einer asynchronen seriellen Verbindung. <br>
*Quelle: [msdn.microsoft, Stopbit](https://msdn.microsoft.com/de-de/library/system.io.ports.stopbits(v=vs.110).aspx)*

Wir verwenden 2 Stopbits.

* **PARITYBIT:** 
> Ein Paritätsbit ist ein zeichendiskretes Prüfbit, das zur Fehlererkennung in der Paritätsprüfung eingesetzt wird. 
> Das Paritätsbit wird zu den Datenbits hinzugefügt, wodurch die Bitsumme gerade oder ungerade wird. Empfangsseitig 
> wird die Bitsumme überprüft. Entspricht die Bitsumme nicht der vorgegebenen Parität, - die beispielsweise gerade 
> sein muss - dann liegt ein Übertragungsfehler vor. <br>

*Quelle: [IT-Wissen, Paritätsbit](https://www.itwissen.info/Paritaetsbit-parity-bit-PY.html)*

In unserem Fall wird kein Paritybit verwendet.


## Neue Methoden

### `singleMeasurement()`
```java
private void singleMeasurement() 
{
        activeWorker = new MySingleMeasurementWorker(serialPort);
        activeWorker.execute();
        updateSwingControls();
}
```
Die Methode "singleMeasurement()" ist dafür zuständig den SwingWorker zu starten.

* **SwingWorker:** Der SwingWorker ist eine Utility-Klasse, die die ordnungsgemäße Verwendung des Event-Dispatch-Threads ermöglicht. <br> <br>
-> Multithreading <br> <br>
SwingWorker ist nützlich, wenn nach einem Benutzerinteraktionsereignis eine zeitraubende Aufgabe ausgeführt werden muss. <br> <br>
Mit dem SwingWorker gehen neue Methoden einher: <br>
* *"doInBackground()":* Berechnet ein Ergebnis oder gibt eine Exception aus, wenn dies nicht möglich ist.

* *"done()":* Wird im Ereignis-Dispatch-Thread ausgeführt, nachdem die doInBackground-Methode beendet wurde.

* *"execute()":* Plant diesen SwingWorker für die Ausführung in einem Arbeitsthread.

* *"get()":* Wartet, wenn die Berechnung abgeschlossen werden muss, und ruft dann das Ergebnis ab.

* *"process()":* Empfängt Datenblöcke aus der Publish-methode asynchron im Event Dispatch-Thread.

* *"publish()":* Sendet Datenblöcke an die Process-Methode. <br> <br>

Zur veranschaulichung:

![](https://github.com/HTLMechatronics/m14-la1-sx/blob/kobmam14/kobmam14/SwingWorker.gif) <br>


* **Multithreading:** Multithreading bezeichnet in der Informatik das gleichzeitige Abarbeiten mehrerer Threads (Ausführungsstränge) innerhalb eines einzelnen Prozesses oder eines Tasks (ein Anwendungsprogramm). <br>
*Quelle: [Wikipedia, Multithreading](https://de.wikipedia.org/wiki/Multithreading)* 


## Neue Klassen

### SingleMeasurementWorker
```java
package workers;

import java.util.concurrent.TimeUnit;
import javax.swing.SwingWorker;
import jssc.SerialPort;

/**
 *
 * @author kobi
 */
public class SingleMeasurementWorker extends SwingWorker<Double, String>
{
    
    private final SerialPort serialPort;

    public SingleMeasurementWorker(SerialPort serialPort)
    {
        this.serialPort = serialPort;
    }
       
    
    @Override
    protected Double doInBackground() throws Exception 
    {
        
        publish("Einzelmessung gestartet");
        
        //Read LM75: 02 04 00 30 00 01 31 f6 (Modbus-Konfiguration aus der "README")
        byte [] frame = {0x02, 0x04, 0x00, 0x30, 0x00, 0x01, 0x31, (0xf6-256)};
        //Weil "writeBytes" nur von -128 bis +127 geht.
        
        if (serialPort.writeBytes(frame) == false) 
        {
            throw new Exception("cannot send frame");
        }
                
        TimeUnit.SECONDS.sleep(2);
        byte [] response = serialPort.readBytes();
        System.out.println(response.length);
        byte hb = response[3];
        byte lb = response[4];
        int t = (hb < 0 ? hb+256 : hb) * 256 + (lb < 0 ? lb+256 : lb);
        
        return t/256.0;
    }
    
}
```

### SingleMeasurementWorker (innere Klasse)
```java
private class MySingleMeasurementWorker extends SingleMeasurementWorker 
{

        public MySingleMeasurementWorker(SerialPort serialPort) 
        {
            super(serialPort);
        }

        @Override
        protected void done() 
        {
            try {
                double temp = get();
                jlaTemperatur.setText(String.format("%.1f °C", temp));
                jtfStatus.setText(null);
            } catch (Exception e) {
                showThrowable(new Exception("Einzemessung gescheitert", e));
            } finally {
                activeWorker = null;
                updateSwingControls();
            }
        }

        @Override
        protected void process(List<String> chunks) 
        {
            jtfStatus.setText(chunks.get(chunks.size()-1));
        }
        
    }
```
Messwerte werden mit hilfe von "get()" abgeragt und in die double Variable "temp" gespeichert. <br>
Dieser Wert wird dann mit hilfe des Labels "Temperatur" ausgegeben. <br>
Die Methode "process" empfängt Datenblöcke aus der Publish-Methode und schreibt diese in da Textfeld "Status".
