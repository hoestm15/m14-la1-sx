# Protokoll der 6. Einheit

## 6. Einheit

* Name: Mario Nabernik  
* Klasse: 4AHME  
* Datum 20.02.2018  
* Gruppe: 2  
* Anwesend:  Florian Nebel, Lorenz Muri, Moritz Martinak, Andreas Platzer, Gerhard Mandl, Marcel Köhler, Michael Mörth, Mario Nabernik
* Abwesend: -
* Thema: Java Temperaturmessung

# Aufgabenstellung
Aufgabe ist es, einen Temperatursensor mit Hilfe des SureBoards zu bauen, welcher via Feldbus die Daten an auf den Computer übertägt.
Die Daten sollen über eine Java Swing, welche schon ein vorgefertigtes Model war, ausgegeben werden.
Wichtig bei der ganzen Aufgabe war es, unser Wissen über modbus zu nutzen, welches wir in der vorherigen Stunde angesammelt haben.

## Arbeitsschritte
* Download der GUI Vorlage von unserem Server (Arnfels)
* Schreiben des Quellcodes

# Quellcode
```java
  private String [] ports;
  private jssc.SerialPort serialPort;
```  
* Erstellen der Variablen.
Die Variable _serialPort_ lässt uns abfragen ob der Port offen ist.

```java
public SureModbusGui ()
  {
    initComponents();
    setLocationRelativeTo(null);
    jlaTemperatur.setText("? °C");
    refresh();
  }
```  
* Mit dem _setText_ setzen wir unsere Temperatur auf "?".
Das _refresh_ zeigt uns beim Start des Programms alle verfügbaren Ports an.

```java
private void showThrowable (String msg, Throwable th)
  {
    th.printStackTrace(System.err);
    JOptionPane.showMessageDialog(
      this,
      msg,
      "Fehler aufgetreten", 
      JOptionPane.ERROR_MESSAGE
    );
  }
  ``` 
  * Methode zur Fehlerausgabe.
  
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
    
    if(serialPort != null && serialPort.isOpened()) //Es wurde eine Verbindung mit einem Port erstellt -> Trennen möglich
    {
      jbutDisconnect.setEnabled(true);
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
  * Dieser Abschnitt ist für das "Button-Management" zuständig. Hier wird geregelt wann und wo ein Button aktiviert sein soll.
  Wenn ich mich zum Beispiel mit einem gerät verbunden habe sind andere Buttons aktiviert und deaktiviert, als wenn noch keine Verbindung besteht.
  
  ```java
  private void refresh()
  {
    ports = jssc.SerialPortList.getPortNames(); //Vorhande Ports speichern
    DefaultComboBoxModel<String> model = 
            new DefaultComboBoxModel<>(ports); 
    jcbSerialDevice.setModel(model); //Vorhandene Ports implementieren
    updateSwingControlles(); //Buttons aktualisieren
  }
  ```
  * In der Methode _refresh_ werden die Portnamen gespeichert (_ports_).
  _jcbSerialDevice.setModel(model)_ listet die Portnamen.
  _updateSwingControlles_ aktualisiert wieder die Buttons.
  
    ```java
private void connect()
  {
    try
    {
      String port = (String) jcbSerialDevice.getSelectedItem();
      serialPort = new jssc.SerialPort(port);
      serialPort.openPort();
      updateSwingControlles();
    }
    catch (Throwable th)
    {
      showThrowable("Serielle Schnittstelle kann nicht geöffnet werden", th);
    }    
  } 
  ```
  
 * In dieser Methode stellen wir Verbindung mit dem gewünschten Port her.
 
 ```java
  private void disconnect()
  {
    try
    {
      serialPort.closePort();
    }
    catch (Exception e)
    {
      showThrowable("Fehler beim Schließen der Schnittstelle", e);
    }
    finally // sorgt dafür das der Port trotz Fehlermeldung geschlossen wird
    {
      serialPort = null;
      updateSwingControlles();
    }
  }
```  
* In dieser Methode wird die Verbindung getrennt.

```java
  private void jbutConnectActionPerformed(java.awt.event.ActionEvent evt)                                            
  {                                                
    connect();
  }                                           

  private void jbutDisconnectActionPerformed(java.awt.event.ActionEvent evt)                                               
  {                                                   
    disconnect();
  }                                              

  private void jbutRefreshActionPerformed(java.awt.event.ActionEvent evt)                                            
  {                                                
    refresh();
  }                                           
```
* Zeigt Funktion der Button.
