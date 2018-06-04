# Protokoll: Knappitsch Robert
## 7. Einheit: Temperaturmessung Fortsetzung
* Klasse: 4AHME (Gruppe 1)
* Datum: 17.04.2018
* Anwesend: Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Enzi Gert, Knappitsch Robert, Kobor Markus
* Abwesend: -

### Stand der letzten Einheit
Das Programm kann die Ports des PCs durchsuchen und das Sureboard an die erste Stelle in der Combobox setzen. Danach kann man sich mit dem Board verbinden und die Verbindung wieder trennen.
Erstellte Klassen:
* Konstruktor
* `updateSwingControls()`
* `showThrowable()`
* `connectPort()`
* `disconnectPort()`
* `refreshPorts()`

### Änderungen an vorhandenen Methoden
#### `updateSwingControls()`
Eine neue If-Klausel wurde hinzugefügt. Damit werden wärend einer Messung alle GUI-Elemente deaktiviert. Zusätzlich wird der Mauszeiger auf `WAIT_CURSOR` (Spinning Wheel) gesetzt. Nachdem der Worker fertig ist, wird der Mauszeiger wieder auf `DEFAULT_CURSOR` (Standart Mauszeiger) gestellt und das Temperatur-Label aktiviert.
 ``` Java
        if (activeWorker != null) {
            jbutRefresh.setEnabled(false);
            jbutConnect.setEnabled(false);
            jbutDisconnect.setEnabled(false);
            jcbSerialDevice.setEnabled(false);
            jbutSingleMeasurement.setEnabled(false);
            jbutContinousMeasurement.setEnabled(false);
            jbutStopMeasurement.setEnabled(false);
            jlaTemperatur.setEnabled(false);
            setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
        } else {
            setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            jlaTemperatur.setEnabled(true);
        }
 ```
 
 #### `connectPort()`
 In der `jssc.SerialPort` - `Variable serialPort` wurden die Parameter für die serielle Schnittstelle gesetzt: 
 ```Java 
 serialPort.setParams(SerialPort.BAUDRATE_57600, 
                      SerialPort.DATABITS_8,
                      SerialPort.STOPBITS_2, 
                      SerialPort.PARITY_NONE)
 ```
 Parameter | Beschreibung 
-----------|--------------
 Baudrate | Anzahl der übertragenen Symbole pro Zeitspanne (1 Baud = 1 Symbol pro Sekunde) 
 Datenbits | Anzahl der Datenbits in einem Paket
 Stopbits | 1 oder 2 Bits, die dem Empfänger signalisieren, dass das Paket zu Ende ist
 Paritybit | Dient als Ergänzungsbit in einem Paket. Es zeigt an, ob die Anzahl der Bits gerade (even-parity) oder ungerade (odd-parity) ist. Das Paritätsbit kann auch zur Erkennung von Übertragungsfehlern eingesetzt werden.
 
 Außerdem wurde eine Fehlerbehandlung hinzugefügt, mit welcher mit If-Klauseln überprüft wird, ob `serialPort.openPort()` oder `serialPort.setParams()` den Wert `false` zurückliefern. In diesem Fall wird eine `jssc.SerialPortException` geworfen.
 ```Java
 private void connectPort(String port) {
        serialPort = new jssc.SerialPort(port);
        try {
            if (serialPort.openPort() == false) {
                throw new jssc.SerialPortException(port, "openPort", "return value false");
            }
            if (serialPort.setParams(SerialPort.BAUDRATE_57600, SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_2, SerialPort.PARITY_NONE) == false) {
                throw new jssc.SerialPortException(port, "setParams", "return value false");
            }
        } catch (Throwable ex)
        {
            showThrowable(new Exception("Serielle Schnittstelle kann nicht geöffnet werden", ex));
            serialPort = null;
        } finally {
            updateSwingControls();
        }
    }
 ```
 
 ### Neue Klassen, Methoden und Klassenvariablen
 #### Klassenvariablen
 ##### `activeWorker`
 Diese Variable wird immer auf den aktiven SwingWorker gesetzt. So kann die Methode `updateSwingControls()` sehen, ob gerade ein Worker läuft.
 ```Java
 private SwingWorker activeWorker;
 ```
 
 #### Methoden
 ##### `singleMeasurement()`
 Diese Methode setzt die Klassenvariable `activeWorker` auf einen neuen `MySingleMeasurementWorker` und übergibt ihm die Variable `serialPort`. Danach wird der Worker gestartet und die Methode `updateSwingControls()` aufgerufen.
 ```Java
 private void singleMeasurement() {
        activeWorker = new MySingleMeasurementWorker(serialPort);
        activeWorker.execute();
        updateSwingControls();
    }
 ```
 
 #### Klassen
 ##### `SingleMeasurementWorker`
 Diese Klasse leitet sich von der Klasse `SwingWorker` ab. In ihr befindet sich die Methode `doInBackground()`. Nach dem Start der Messung wird die Modbus-Konfiguration (aus Projekt-README) mit `serialPort.writeBytes(frame)` an das SureBoard gesendet. Die `response` (Antwort) wir in zwei Bytes gespeichert (high byte, low byte). Das ist notwendig da die möglichen Werte von `writeBytes` nur von -128 bis 127 gehen und `response` diese Werte übersteigen kann.
 ```Java
 package workers;

import java.util.concurrent.TimeUnit;
import javax.swing.SwingWorker;
import jssc.SerialPort;

public class SingleMeasurementWorker extends SwingWorker<Double, String> {
    
    private final SerialPort serialPort;

    public SingleMeasurementWorker(SerialPort serialPort) {
        this.serialPort = serialPort;
    }
       
    @Override
    protected Double doInBackground() throws Exception {
        
        publish("Einzelmessung gestartet");
        
        //Read LM75: 02 04 00 30 00 01 31 f6 (Modbus-Konfiguration aus README)
        byte [] frame = {0x02, 0x04, 0x00, 0x30, 0x00, 0x01, 0x31, (0xf6-256)};
        
        if (serialPort.writeBytes(frame) == false) {
            throw new Exception("cannot send frame");
        }
                
        TimeUnit.SECONDS.sleep(2);
        //"writeBytes" nur von -128 bis +127
        byte [] response = serialPort.readBytes();
        System.out.println(response.length);
        byte hb = response[3];
        byte lb = response[4];
        int t = (hb < 0 ? hb+256 : hb) * 256 + (lb < 0 ? lb+256 : lb);
        
        return t/256.0;
    } 
}
 ```
 
##### `MySingleMeasurementWorker`
Hierbei handelt es sich um eine innere Klasse in der Hauptklasse `SureModbusGui`. Sie leitet sich von der Worker-Klasse `SingleMeasurementWorker` ab und enthält die Methoden `done()` und `process()`. Die Methode `done()` liest mit `get()` den Rückgabewert der `doInBackground` - Methode. Dieser wird in das Temperatur-Label geschrieben. Mit `process()` wird der String aus `publish()` in das Status-Textfield geschrieben.
```Java
private class MySingleMeasurementWorker extends SingleMeasurementWorker {

        public MySingleMeasurementWorker(SerialPort serialPort) {
            super(serialPort);
        }

        @Override
        protected void done() {
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
        protected void process(List<String> chunks) {
            jtfStatus.setText(chunks.get(chunks.size()-1));
        }
        
    }
```

#### SwingWorker
Der Swingworker erlaubt es, arbeitsintensive Aufgaben in einen anderen Thread auszulagern. Dadurch kann man zum Beispiel eine GUI problemlos verwenden, wärend im Hintergrund gerechnet wird. Ein solcher Vorgang wird "reales Multitasking" genannt.

##### Methoden der Worker-Klasse
* `doInBackground()`: Der Inhalt dieser Methode wird in einem zweiten Thread ausgeführt.
* `publish()`: Diese Methode kann Zwischenergebnisse des Vorgangs im zweiten Thread an den Haupt-Thread senden.

##### Methoden der inneren Klasse
* `done()`: Wird nach dem Beenden der `doInBackground` - Methode ausgeführt.
* `get()`: Hiermit wird der Rückgabewert der `doInBackground` - Methode gelesen.
