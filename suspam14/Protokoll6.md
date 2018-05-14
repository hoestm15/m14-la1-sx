# Protokoll 6: Visualisierung eines Temperatursensors
Name: Patrick Schuster  
Klasse: 4AHME  
Gruppe: 3    
Anwesend: Reinbacher, Sackl R.,  Schmuck, Schuster  
Abwesend: Ruffenacht, Sammer, Sackl M.

# Aufgabenstellung
Es soll eine Java Swing GUI zur Visualisierung eines Temperatursensors erstellt werden. Mit Hilfe der GUi soll man sich mit dem Sure Board verbinden können und die Messdaten des Temperatursensors auslesen können. Für die Verbindung zwischen Java GUI und PC soll das Feldbussystem Modbus verwendet werden. Dieser wurde bereits in der vorigen Einheit besprochen. [Protokoll zu Modbus]( m14-la1-sx/suspam14/Protokoll5.md )

## SureBoard Programm
Das Programm für das Sureboard, dass den Temperatursensor ausliest und als Modbus-Slave agiert, wurde vom Server in Arnfels bezogen. Wir haben es mit dem EasyProgrammer auf das SureBoard gespielt.

## GUI 
Um Zeit zu sparen haben wir die GUI-Vorlage vom Server in Arnfels bezogen. In dieser ist der visuelle Teil der GUI bereits fertig. Die einzelnen Methoden für die Datenübertragung und Verbindung mussten noch ausprogrammiert werden.
![](https://github.com/suspam14/la1/blob/master/GUI-Temperaturmessung.png)

### Quelltext

#### Konstruktor
Der Konstruktur ruft die Methode `refreshSerialPorts() `auf und aktualisiert zu Programmstart bereits die verfügbaren Ports. 
Mit dem Befehl `jlaTemperatur.setText("- °C");` setzen wir das Anzeigelabel auf `- °C` da bei Programmstart noch keine Messung durchgeführt werden kann.
```java
public SureModbusGui ()
  {
    initComponents();
    refreshSerialPorts();
    updateSwingControls();
    jlaTemperatur.setText("- °C");
    setLocationRelativeTo(null);
    
  }
```

#### updateSwingControls()
Diese Methode aktualisiert die GUI wenn sich der Verbindungsstatus ändert. Es werden dadurch Buttons aktiviert oder deaktiviert um Logikfehler zu vermeiden. Dadurch kann man z.B. verhindern das der Verbinden-Knopf gedrückt wird, wenn z.B. die GUI mit dem Sureboard bereits verbunden ist. Wir haben auch eine Änderung beim Cursor implemetiert während die Worker-Klasse sich die Temperatur vom Sureboard holt.
```java
private void updateSwingControls () {
    jbutConnect.setEnabled(false);
    jbutContinousMeasurement.setEnabled(false);
    jbutDisconnect.setEnabled(false);
    jbutRefresh.setEnabled(false);
    jbutSingleMeasurement.setEnabled(false);
    jbutStopMeasurement.setEnabled(false);
    jcbSerialDevice.setEnabled(false);
    
    if(activeWorker != null) {
      setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
      return;
    }
    else {
      setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    }
    
    jbutRefresh.setEnabled(true);
    if(jcbSerialDevice.getModel().getSize()>0) {
      jcbSerialDevice.setEnabled(true);
      jbutConnect.setEnabled(true);
    }
    if(serialPort != null && serialPort.isOpened()) {
      jbutConnect.setEnabled(false);
      jbutRefresh.setEnabled(false);
      jcbSerialDevice.setEnabled(false);
      jbutDisconnect.setEnabled(true);
      jbutSingleMeasurement.setEnabled(true);
    }
  }
```

#### showThrowable()
Diese Methode überprüft ob die Exception *null* oder *empty* ist und gibt die *Error-Message* in einem Dialogfenster aus.
```java
 private void showThrowable (Throwable th) {
    th.printStackTrace(System.err);
    String msg = th.getMessage();
    if(msg == null || msg.isEmpty())
      msg = th.getClass().getSimpleName();
    JOptionPane.showMessageDialog(this, msg, "Fehler aufgetreten", JOptionPane.ERROR_MESSAGE);
  }
```

#### refreshSerialPorts ()
Diese Methode speichert die vorhandenen Ports in der Variable `ports` und zeigt die einzelnen Namen der Ports anschließend in der GUI an.
```java 
  private void refreshSerialPorts () {
    final String[] ports = jssc.SerialPortList.getPortNames();
    ComboBoxModel<String> m = new DefaultComboBoxModel<>(ports);
    jcbSerialDevice.setModel(m);
  }
  ```
  
#### connect()
Diese Methode dient dazu sich mit dem SureBoard zu verbinden. Die Methode uholt sich den ausgewählten Port und öffnet eine Verbindung mit `.openPort`. Es werden auch die Verbindungseinstellungen wie die Baudrate, Parity-, Daten- und Stopbit getroffen. 
```java 
private void connect () {
    try {
      final String port = (String)jcbSerialDevice.getSelectedItem();
      serialPort = new jssc.SerialPort(port);
      if (serialPort.openPort() == false)
        throw new Exception("openPort() returns false");
      
      if (serialPort.setParams(
              SerialPort.BAUDRATE_57600, 
              SerialPort.DATABITS_8, 
              SerialPort.PARITY_NONE, 
              SerialPort.STOPBITS_2) == false)
        throw new Exception("setParams() returns false");  
      
    }
    catch(Throwable th) { //Ausnahme durch JNI
      showThrowable(new Exception("Verbindung gescheitert",th));
      if(serialPort != null)
      try {
        serialPort.closePort();

      } catch (Throwable th2) {
        //th2.printStackTrace(System.err);
        th2.addSuppressed(th2);
      }
      serialPort = null;
     
    } 
    finally {
      updateSwingControls();
    }
  }
```  

#### disconnect
Diese Methode dient dazu die Serielle Verbindung mit dem SureBoard fehlerfrei zu trennen.
```java
 private void disconnect () {
    try {
     if(serialPort.closePort() == false)
        throw new Exception("closePort() returns false");
    } catch (Throwable th) {
      showThrowable(th);
    } finally {
      serialPort = null;
      updateSwingControls();
    }
```
### GUISingleMeasurementWorker
Diese Methode ist eine Worker Methode die dazu dient die Temperaturdaten vom SureBoard zu holen. Da dieser Vorgang auch länger dauern kann ist es vernünftig für diesen Vorgang einen anderen Thread zu verwenden. Die Worker Klasse arbeitet im Hintergrund und stört somit nicht den Programmverlauf der GUI. Die Worker Klasse wurde noch nicht ausprogrammiert, deswegen wird immer ein Fixwert von 24,5°C zurückgegeben um das restliche Programm zu testen.
```java
  private class GuiSingleMeasurementWorker extends SingleMeasurementWorker {

    @Override
    protected void done ()
    {
      try {
        double temp = get();
        jlaTemperatur.setText(String.format("%.1f°C", temp));
      } catch (Exception ex) {
        showThrowable(new Exception("Einzelmessung gescheitert",ex));
      } finally {
        activeWorker = null;
        updateSwingControls();
      }
    }

    @Override
    protected void process (List<String> chunks)
    {
      jtfStatus.setText(chunks.get(chunks.size()-1));
    }

  }
  ```
## Fehlerbehandlung in Java
![](https://camo.githubusercontent.com/44de9326ae31c832041c5e7a88572f3f111bdda4/68747470733a2f2f7170682e65632e71756f726163646e2e6e65742f6d61696e2d71696d672d35656364646366316536373632376563333733306465343032303034316332322d63)
### Exception
Eine Exception ist ein Fehler im Programm, durch eine Exception kann (muss aber nicht) das Programm abstürzen, die JVm aber nicht.
### Error
Ein Error ist ein schwerwiegender Fehler in der JVM, ein Error kann zum Absturz der gesamten JVM führen. 
### checked - unchecked
*checked* bedeutet das diese Exception gefangen werden muss, eine *unchecked Exception* muss hingegen nicht gefangen werden.

  
