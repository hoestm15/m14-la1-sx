# Protokoll 30.01.2018

## 6. Einheit
## Thema: Temperaturmessung
 
 Name: Markus Kobor  
 Klasse: 4AHME  
 Datum: 30.01.2018  
 Anwesend: Berger Emil, Böcksteiner Jakob, Ehmann Julian, Knappitsch Robert, Kobor Markus
 Abwesend: Bullner Jeremy, Enzi Gert
 
  
## Temperaturmessung
Ziel ist es einen Temperatursensor mittls eines Sure-Boards zu realisieren. <br>
Daten zwischen Board und PC werden mit Hilfe von Modbus übertragen. <br>
Die Ausagbe der temperatur erfolg über eine bereits vorgefertigte Java-GUI. <br>


## Ablauf
Als erstes wurde die fertige GUI vom Server heuntergeladen und geöffnet. <br>
Um überprüfen zu können, welcher Port geöffnet ist, wurde eine Variable erstellt .
 
```java
private jssc.SerialPort serialPort;
```

### Konstruktor
```java
public SureModbusGui () 
{
    initComponents();
    setLocationRelativeTo(null);
    updateSwingControls();
    refreshPorts();
}
```
Im Konstruktor werden die später Beschriebenen Funktionen `updateSwingControls();` und `refreshPorts();` aufgerufen.


### updateSwingControls
```java
private void updateSwingControls() 
{
        jlaTemperatur.setText("--");
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
            return;
        }

        if (jcbSerialDevice.getModel().getSize() > 0) 
        {
            jcbSerialDevice.setEnabled(true);
            jbutConnect.setEnabled(true);
        }
}
```
Wird das Programm gestartet, so wird der Text "--" ausgegebn. <br>
Der Button "Aktualisieren" ist drückbar, während die Buttons "Verbinden" und "Trennen" nicht drückbar sind. <br>
Die Combobox "SerialDevice" ist ausgegraut. <br>
Die Buttons "Einzelmessung", "Laufend messen" und "Stop" sind nicht drückbar. <br>

Wenn ein Port geöffnet wurde, so werden die Buttons "Aktualisieren" und "Verbinden" ausgegraut,
während der Button "Trennen" drückbar wird.

Wenn Ports gefunden werden, so wird die Combobox "SerialDevice" aktiviert und der Button Verbinden wird drückbar.


### refreshPorts
```java
private void refrehPorts () 
{
    final String [] ports = jssc.SerialPortList.getPortNames();
    
    String preferedPort = null;  //Suchen nach USB
    for (String p : ports) 
    {
      if (p.contains("USB")) 
      {
        preferedPort = p;
        break;
      }
    }
    
    jcbSerialDevice.setModel(new DefaultComboBoxModel<String>(ports));  //Implementiert direkt ports
    
    if (preferedPort != null) 
    {
      jcbSerialDevice.setSelectedItem(preferedPort);  //Auswählen der gewünschten Schnittstelle
    }
    
    updateSwingControls();
    
}
```
Es wird eine Variable "ports" mit dem dem Datentyp String erstellet, welche die Namen aller angezeigten Ports enthält. <br>
Die For-Each-Schleife durchläuft die Variable und wird die Folge "USB" gefunden, so wird dieser Port als "preferedPort" gesetzt und wird somit standardmäßig in der Combobox angezeigt.


### showThrowable
```java
private void showThrowable (Throwable th) 
{
    th.printStackTrace(System.err);
    String msg = th.getMessage();
    if (msg == null || msg.isEmpty())
    {
      msg = th.getClass().getSimpleName();
    }
    JOptionPane.showMessageDialog(this,
                                  msg,
                                  "Fehler aufgetreten...",
                                  JOptionPane.ERROR_MESSAGE);
}
```
Tritt ein Fehler auf, so wird dieser über ein Fenster ausgegeben. <br>
Enthält das Throwable th eine Nachricht, so wird diese zusätzlich mit Hilfe der Variable "msg" im Fesnter augegeben. <br>
Ist dies nicht der Fall, so wird der Name der Klasse, in welcher der Fahler aufgetreten ist, ausgegeben.


### ActionPerformed
```java
  private void jbutConnectActionPerformed(java.awt.event.ActionEvent evt) 
  {                                                
    connectPort((String) jcbSerialDevice.getSelectedItem());//Typecast, da Objekt, welches ein String sein muss
  }                                           

  private void jbutDisconnectActionPerformed(java.awt.event.ActionEvent evt) 
  {                                                   
    disconnectPort();
  }                                              

  private void jbutRefreshActionPerformed(java.awt.event.ActionEvent evt) 
  {                                                
    refreshPorts();
  }
```


### connectPort
```java
private void connectPort(String port)
{
        serialPort = new jssc.SerialPort(port);
        try 
        {
            serialPort.openPort();
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
Mit Hilfe von ".openPort()" wird der in der Variable "serialPort" enthaltene Port geöffnet. <br>
Da es zu Fehlern kommen kann, welche nicht unter die Kategorie "Exception" fallen, wird ein Throwable gefangen,
welches die Überklasse dieser darstellt.


### disconnectPort
```java
private void disconnectPort() 
    {
        if (serialPort == null || !serialPort.isOpened()) 
        {
            showThrowable(new Exception("Interner Fehler!"));
            return;
        }

        try 
        {
            serialPort.closePort();
        } 
        catch (Throwable th) 
        {
            showThrowable(new Exception("Serielle Schnittstelle kann nicht geschlossen werden"));
        } 
        finally 
        {
            serialPort = null;
            updateSwingControls();
        }
    }
    
```
Zu erst wird überprüft ob die Variable SerialPort leer ist oder kein Port geöffnet ist. <br>
So wird sichergegangen, dass ein Port nur geschlossen werden kann, wenn einer geöffnet ist.
Mit ".closePort()" wird der geöffnete Port geschlossen.
