# Protokoll: Marcel Köhler
## 6.Einheit
## Thema: Tempertaturmessung mittels Sureboard
Klasse: 4AHME  
Anwesend: Marcel Köhler, Michael Mörth, Florian Nebel, Lorenz Muri, Moritz Martinak, Andreas Platzer, Mario Nabernik,   Gerhard Mandl  
Abwesend: niemand  

###Aufgabenstellung
Wir hatten die Aufgabe mittels Sureboard einen Temperatursensor zu bauen und die Daten anschließend mittels Modbus wieder an den PC / an das Notebook zu senden.  Diese Daten sollen anschließend verarbeitet werden und in einer Java GUI dargestellt werden.

### Vorlage  
Zu aller erst mussten wir die GUI Vorlage vom Server in Arnfels runterladen.

![Vorlage](https://github.com/HTLMechatronics/m14-la1-sx/blob/koemam13/Protokolle/Bilder/GUI-Temperaturmessung.png)

### Quellcode

#### Variablen
```java
  private jssc.SerialPort serialPort;
  private String [] ports;
```

Zu aller erst wurden diese zwei Variablen erstell. Mit der Variable `serialPort` können wir abfragen ob der Port geöffnet ist.
Die Variable `ports`ist ein Feld aus Strings welches wir verwenden um alle Namen der gefundenen Ports zu speichern.


#### Konstruktor
```java
public SureModbusGui ()
  {
    initComponents();
    setLocationRelativeTo(null);
    jlaTemperatur.setText("? °C");
    refresh();
  }
```

Mit dem Befehl `setLocationRelativeTo(null);` wird die GUI beim Starten in der mitte des Bildschirms angezeit.  
Da wir aber noch nicht messen können haben wir mit dem Befehl `jlaTemperatur.setText("? °C");` setzen wir das Label auf `? °C`.  
Mit der Funktion `refresh();` werden beim Start des Programmes bereits verfügbare Ports angezeigt.  

#### Methode: showThrowable
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
  Diese Methode wird zur Fehlerausgabe benutzt. Sollte ein Fehler auftreten wird diese Methode aufgerufen. Nach aufrufen dieser Methode erscheint ein Pop-Up Fenster. In diesem wird dan der Fehler ausgegeben.
  #### Methode: refresh
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
  Zuerst werden alle verfügbaren Ports in der Feld-Variable `ports` gespeichert. Nach dem speichern der Ports werden diese mit dem Befehl 
  `DefaultComboBoxModel<String> model = new DefaultComboBoxModel<>(ports)` und dem Befehl `jcbSerialDevice.setModel(model);` in der Combobox angezeigt. Anschließend werden die Buttons Akualisiert. 
  
  #### Methode: updateSwingControllers
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

##### Beim Start des Programmes sollen folgender Button verfügbar sein:
* Aktualisieren 

##### nicht verfügbare Buttons:
* Einzelmessung
* Laufend messen
* Stop
* Trennen
* Verbinden

##### Wen man einen Port öffnet sollen folgender Button verfügbar sein:
* Trennen

##### nicht verfügbare Buttons:
* Aktualisieren
* Verbinden

##### Wenn nach dem Aktualisieren Ports gefunden wurden, sollen folgende Buttons verfügbar sein:
* Combobox
* Verbinden

#### Methode: connect

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

Zuerst wird der ausgewählt Port mit `String port = (String) jcbSerialDevice.getSelectedItem();` in der Variable `port` gespeichert.
Anschließend wird mit dem Befehl `serialPort.openPort();` der gewählte Port geöffnet. Da es beim Arbeiten mit Schnittstellen zu Exceptions kommen kann müssen wir ein Try-Catch benutzen um diese Exceptions zu fangen.

#### Methode: disconnect

´´´java
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
    finally
    {
      serialPort = null;
      updateSwingControlles();
    }
  }
´´´
In dieser methode schließen wir den aktuellen Port. Da es aber auch hier zu Exceptions kommen kann (kein Port angeschlossen) müssen wir erneut ein Try-Catch benutzen aber auch dazu noch ein finally damit der aktuelle Port bei auftreten eines Fehlers auf `null` gesetzt wird.

#### Methoden: ActionPerformed
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

### GUI zu Ende der Einheit

Kurz vor ende der Einheit haben wir uns mit den Sureboards verbunden.  

Dies sind die Ergebnisse:

#### Wen das Programm gestartet wurde und noch nicht auf Aktualisieren gedrückt wurde:

![Programm_start](https://github.com/HTLMechatronics/m14-la1-sx/blob/koemam13/Protokolle/Bilder/Kein_Port_Gefunden.png)

#### Nachdem Aktualisieren gedrückt wurde:

![Aktualisieren](https://github.com/HTLMechatronics/m14-la1-sx/blob/koemam13/Protokolle/Bilder/Port_Gefunden.png)

#### Nachdem man den Port ausgewählt hat und Vebinden gedrückt hat:

![Verbunden](https://github.com/HTLMechatronics/m14-la1-sx/blob/koemam13/Protokolle/Bilder/Port_Verbunden.png)







