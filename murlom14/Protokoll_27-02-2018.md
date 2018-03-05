# Protokoll 27.02.2018
## 6. Einheit

Name: Muri Lorenz <br>
Klasse: 4AHME <br>
Gruppe: 2 <br>
Datum der Einheit: 6.2.2018 <br>
Anwesend: Nebel, Mandl, Martinak, Muri, Platzer, Mörth, Nabernik, Köhler<br>
Abwesend: - <br>

## Temperaturmessung (Teil 1) - Verbindung zum Sureboard
Das Ziel der Übung ist es einen Temperatursensor, welcher sich auf dem Sureboard befinedet mittels Java-Programm auszugeben.
Um von einem Surebard Daten an eine PC übertragen zukönnen wird ein entsprechendes Feldbusprotokoll benötig, wir verwenden bei dieser Übung Modbus, und ebenfalls die jSSC Library. [jSSC](https://github.com/scream3r/java-simple-serial-connector) ist eine einfache und plattformübergreifende serielle Kommunikationsbibliothek für Java. 

Für das Java-Prgramm wurde uns eine [Vorlage](https://github.com/HTLMechatronics/m14-la1-sx/blob/murlom14/murlom14/sx-la1-25c2c67.tar.gz) zur Verfügung gestellt.

### Quellcode

#### Klassenvariable
```java
private SerialPort serialPort;          // gibt an ob ein Port geöffnet ist
private String [] ports;                // wird vverwendet um den Namen eines Ports zu "speichern"
```

#### SureModbusGUI () (Konstruktor)
```java
public SureModbusGui () {
    initComponents();
    setLocationRelativeTo(null);    // Die GUI wird mittig am Bildschirmm ausgegeben
    jlaTemperatur.setText("? °C");  // Die Temperatur ist anfangs unbekannt (noch nicht mit Sureboard verbunden) 
    
    refresh();                      // Die Methode refresh() wird aufgerufen
  }
```

#### showThrowable
```java
private void showThrowable (String msg, Throwable th)
  {
    th.printStackTrace(System.err);                                                         // gibt einen Fehler im Output aus
    JOptionPane.showMessageDialog(this, msg, "Fehler !!!", JOptionPane.ERROR_MESSAGE);      // Ausgabe eines Fehler (Pop-up-Fenster)
  }
```
JNI-Fehler statt als Exception als Error ausgegeben. Daher muss man im catch mittels Throwable alles fangen und anschließend im showThrowable eine/n Warnung/Fehler ausgeben.

#### updateSwingControls ()
```java
public void updateSwingControls ()
  {
    jcbSerialDevice.setEnabled(false);                  // bei jedem aufruf dieser Methode werden alle Buttons/Combobox zuerst deaktiviert
    jbutConnect.setEnabled(false);
    jbutDisconnect.setEnabled(false);
    jbutRefresh.setEnabled(false);
    jbutSingleMeasurement.setEnabled(false);
    jbutContinousMeasurement.setEnabled(false);
    jbutStopMeasurement.setEnabled(false);
    
    if(serialPort != null && serialPort.isOpened())     // wenn ein port erkannt wurde und der Port geöffnet ist (verbunden) 
    {
      jbutDisconnect.setEnabled(true);                  // wird der Button Trennen wieder aktiviert
      return;
    }
    
    if(ports == null || ports.length == 0)              // solange kein port erkannt/verbunden ist
    
    {
      jbutRefresh.setEnabled(true);                     // wird der Button "Aktualisieren" aktiviert
    }
    
    if(ports != null && ports.length > 0)               // sobald ein port erkannt wurde 
    {
      jcbSerialDevice.setEnabled(true);                 // wird die Combobox aktiviert
      jbutConnect.setEnabled(true);                     // der "Verbinden" Button aktiviert
      jbutRefresh.setEnabled(true);                     // und der "Aktualisieren" Button aktiviert
    }
  }
```

#### refresh ()
```java
private void refrehPorts () {
    ports = jssc.SerialPortList.getPortNames();                                 // der Portname wird in ports geschreiben
    System.out.println(ports);                                                  // gibt ports aus
    DefaultComboBoxModel <String> model = new DefaultComboBoxModel (ports)      // neues Model erzeugt
    jcbSerialDevice.setModel(model);                                            // Model wird gesetzt 
    
    updateSwingControls();                                                      // Die Methode updateSwingControls() wird aufgerufen
    
  }
```

#### connect ()
```java
private void connect ()
  {
    try                                                                                 // try catch für die Fehler behandlung
    {
    String port = (String)jcbSerialDevice.getSelectedItem();                            // die ausgewählt Verbindung (in der Combobox) wird port zugewiesen
    serialPort = new jssc.SerialPort(port);                                             // port wird einem verfügbarem serialPort zugewiesen 
    serialPort.openPort();                                                              // ein Port wird geöffnet
    }
    catch(Throwable th)
    {
      showThrowable("Serielle Schnittstelle kann nicht geöffnet werden!", th);          // wenn ein Fehler auftritt wird Funktion showThrowable() zur Fehlerbehandlung aufgerufen
    }
  }

```

#### disconnect ()
```java
private void disconnect()
  {
    try                                                                     // try catch für die Fehler behandlung
    {
      serialPort.closePort();                                               // der Port wird geschlossen, die Übertragung beendet
    }
    catch (Throwable th)
    {
      showThrowable("Schnittstelle kann nicht getrennt werden", th);        // wenn ein Fehler auftritt wird Funktion showThrowable() zur Fehlerbehandlung aufgerufen
    }
    finally
    {
      serialPort = null;                                                    // der port wird auf null gesetzt
      updateSwingControls();                                                // die Methode updateSwingControls() wird aufgerufen
    }
  }
```

#### ActionPerformed ()
```java
private void jbutConnectActionPerformed(java.awt.event.ActionEvent evt)                                            
  {                                                
    connect ();                                                               // beim drücken des Button "Verbinden" wird die Methode connect() aufgerufen
  } 
  
  private void jbutRefreshActionPerformed(java.awt.event.ActionEvent evt)                                            
  {                                                
    refresh();                                                                // beim drücken des Button "Aktualisieren" wird die Methode refresh() aufgerufen
  }                                           

  private void jbutDisconnectActionPerformed(java.awt.event.ActionEvent evt)                                               
  {                                                   
    disconnect();                                                             // beim drücken des Button "Trennen" wird die Methode disconnect() aufgerufen
  }                                              

```

##### Wenn das Programm gestartet wird (kein Sureboard erkannt)
* Wenn das Sureboard nicht verbunden ist, wird "? °C" angezeigt
* Der Button "Aktualisieren" ist aktiviert
* Der Button "Verbinden" ist deaktiviert (bei keiner erkannten Verbindung)
* Der Button "Trennen" ist deaktiviert (bei keiner erkannten Verbindung)
* Die Combobox ist deaktiviert (bei keiner erkannten Verbindung)

##### Wenn das Sureboard erkannt wurde aber nicht verbunden
* Die Combobox ist aktiviert
* Der Button "Verbinden" ist aktiviert
* Der Button "Aktualisieren" ist aktiviert
* Der Button "Trennen" ist deaktiviert

##### Wenn das Sureboard verbunden ist
* Der Button "Aktualisieren" ist deaktiviert
* Der Button "Trennen" ist aktiviert
* Der Button "Verbinden" ist deaktiviert

### Endergebniss der Einheit am 27.02.2018
![GUI-TemperaturSensor](https://github.com/HTLMechatronics/m14-la1-sx/blob/murlom14/murlom14/GUI-Temperatur.jpg)



