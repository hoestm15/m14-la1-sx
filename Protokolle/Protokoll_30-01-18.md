# Protokoll: Knappitsch Robert
## 6. Einheit: Temperaturmessung
* Klasse: 4AHME (Gruppe 1)
* Datum: 30.01.2018
* Anwesend: Berger Emil, Böcksteiner Jakob, Ehmann Julian, Kobor Markus, Knappitsch Robert
* Abwesend: Bullner Jeremy, Enzi Gert

### Projekt
Mit einem Sureboard, welches über Modbus mit einem PC verbunden ist, soll ein Temperatursensor gebaut werden. Die vom Sureboard
erhaltenen Daten werden in einer Java-Swing-Applikation ausgewertet und angezeigt.

### Programm-Vorlage
Vom Server in Arnfels luden wir eine Vorlage herunter, welche den Grundaufbau der GUI beinhaltete.

### Funktionen des Programms
Die Vorlage wurde von uns um einige Funktionen erweitert.
#### Öffnen des Programms
* Wenn keine Verbindung besteht, soll **--** angezeigt werden.
* Die Buttons *Verbinden*, *Trennen*, *Aktualisieren*, *Einzelmessung*, *Laufend messen* und *Stop* sowie die 
Combobox sollen ausgeblendet sein.
#### Port gefunden
* Der Button *Verbinden* und die Combobox sollen wieder eingeblendet werden.
#### Port geöffnet
* Die Buttons *Verbinden*, *Trennen* und *Aktualisieren* soll wieder eingeblendet werden.

### Quelltext
#### Klassenvariable
Mit dieser Variable, auf die von allen Methoden der Klasse zugegriffen werden kann, wird überprüft, ob ein Port
geöffnet ist.
```Java
private jssc.SerialPort serialPort;
```

#### Konstruktor
Der Konstruktor wird erweitert, sodass beim Programmstart die beiden, von uns erstellten Methoden, aufgerufen werden.
```Java
public SureModbusGui () {
    initComponents();
    setLocationRelativeTo(null);
    updateSwingControls();
    refreshPorts();
  }
  ```
  
#### updateSwingControls
Diese Methode stellt sicher, dass die Teile der GUI zur richtigen Zeit, ein- und ausgeblendet werden.
```Java
private void updateSwingControls() {
        jlaTemperatur.setText("--");
        jbutRefresh.setEnabled(true);
        jbutConnect.setEnabled(false);
        jbutDisconnect.setEnabled(false);
        jcbSerialDevice.setEnabled(false);
        jbutSingleMeasurement.setEnabled(false);
        jbutContinousMeasurement.setEnabled(false);
        jbutStopMeasurement.setEnabled(false);

        if (serialPort != null && serialPort.isOpened()) {
            jbutRefresh.setEnabled(false);
            jbutDisconnect.setEnabled(true);
            jbutConnect.setEnabled(false);
            return;
        }

        if (jcbSerialDevice.getModel().getSize() > 0) {
            jcbSerialDevice.setEnabled(true);
            jbutConnect.setEnabled(true);
        }
    }
 ```
  
 #### showThrowable
 Diese Methode gibt im Falle eines Fehlers, den Fehler und die Fehlernachricht in einem *MessageDialog* aus.
 ```Java
 private void showThrowable (Throwable th) {
    th.printStackTrace(System.err);
    String msg = th.getMessage();
    if (msg == null || msg.isEmpty()) {
      msg = th.getClass().getSimpleName();
    }
    JOptionPane.showMessageDialog(this, msg, "Fehler aufgetreten...", JOptionPane.ERROR_MESSAGE);
  }
  ```
  
#### connectPort
Diese Methode öffnet einen Port, der ihr als String übergeben wurde. Da wir mit seriellen Schnittstellen arbeiten,
werden Schnittstellen-Fehler von Error abgeleitet. Also ist es notwendig statt Exceptions Throwables zu fangen.
```Java
private void connectPort(String port) {
        serialPort = new jssc.SerialPort(port);
        try {
            serialPort.openPort(); //Verbinden mit Port
        } catch (Throwable ex)
        {
            showThrowable(new Exception("Serielle Schnittstelle kann nicht geöffnet werden", ex));
            serialPort = null;
        } finally { //Bei try und catch
            updateSwingControls();
        }
    }
  ```
  
  #### disconncetPort
  Diese Methode trennt die Verbindung zu einem Port. Vorher überprüft sie noch, ob wirklich ein Port geöffnet ist.
  ```Java
  private void disconnectPort() {
        if (serialPort == null || !serialPort.isOpened()) {
            showThrowable(new Exception("Interner Fehler!"));
            return;
        }

        try {
            serialPort.closePort();
        } catch (Throwable th) {
            showThrowable(new Exception("Serielle Schnittstelle kann nicht geschlossen werden!"));
        } finally {
            serialPort = null;
            updateSwingControls();
        }
    }
```
    
#### refreshPorts
Diese Methode aktualisiert die angezeigten Ports in der ComboBox. Alle gefundenen Port-Namen werden in einem String
gespeichert. Eine For-Each-Schleife durchsucht diesen String nach *USB*. Dieser Port wird dann an die erste 
Stelle in der ComboBox gesetzt
```Java
private void refrehPorts () {
  final String [] ports = jssc.SerialPortList.getPortNames();
    
  String preferedPort = null; 
  for (String p : ports) {
    if (p.contains("USB")) {
      preferedPort = p;
      break;
     }
  }
    
  jcbSerialDevice.setModel(new DefaultComboBoxModel<String>(ports));
    
  if (preferedPort != null) {
    jcbSerialDevice.setSelectedItem(preferedPort);
  }
  updateSwingControls();
   
  }
```
  
  
  
