# Protokoll 6 20.02.2018

## Thema: Atmel Studio

Name: Michael Mörth  
Klasse: 4AHME  
Gruppe: 2  

Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Moritz Martinak, Mario Nabernik, Muri Lorenz, Platzer Andreas, Marcel Köhler    
Abwesend: -

## JAVA-Projekt: Temperaturmessung
In der heutigen Stunde wandten wir das Wissen der letzten Stunde über den Modbus an. Unsere Aufgabe ist es,mittels eines SureBoards einen Temperatursensor zu bauen. Die Daten des Sensors sollen über einen Feldbus an den Computer übertragen werden. Die Daten sollen anschließend verarbeitet werden. Die übertragenen Daten sollen anschließend in einer mit Java-Swing-realisierten GUI visualisiert werden.

### GUI Vorlage
Zu Beginn mussten wir uns die Vorlage der GUI vom Server in Arnfels downloaden.
![GUI-Vorlage](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/GUI-Temperaturmessung.png)

### Der Quellcode

#### Verwendete Variablen
Zu Beginn wurden zwei Variablen erstellt. Das Feld aus Strings mit dem Variablennamen `ports` dient dazu, alle Namen der gefundenen Ports zu speichern. Mit der Variable `serialPort` können wir anschließend abfragen, ob der Port geöffnet ist.
```java
  private String [] ports;
  private jssc.SerialPort serialPort;
```
#### Konstruktor
Im Konstruktur rufen wir die Funktion `refresh();` auf, dies hat den einfachen Grund, dass beim Start des Programmes bereits verfügbare Ports angezeigt werden. Da wir zum derzeitigen Zeitpunkt noch keine Messung durchführen können, setzten wir den Text von  `jLabel` mit dem Befehl `jlaTemperatur.setText("? °C");` auf `? °C`. Außerdem wird mit dem Befehl `setLocationRelativeTo(null);` das GUI Fenster in der Mitte des Bildschirms angezeigt.
```java
public SureModbusGui ()
  {
    initComponents();
    setLocationRelativeTo(null);
    jlaTemperatur.setText("? °C");
    refresh();
  }
```
#### Die Methode showThrowable
Diese Methode dient zur Fehlerausgabe. Wenn ein Fehler auftritt, wird der Fehler in einem Pop-Up Fenster ausgegeben. Die Fehlernachricht `msg` wird bei Fehlerauftritt im Fenster ausgegeben.

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
  #### Die Methode updateSwingControlles
  ##### Buttons beim Start des Programmes
  * Der Button `Aktualisieren` soll eingeblendet sein.
  * Der Button `Verbinden` soll ausgeblendet sein
  * Der Button `Trennen` soll ausgeblendet sein
  * Die Combobox soll ausgeblendet werden.
  * Der Button `Einzelmessung` soll ausgeblendet werden.
  * Der Button `Laufend messen` soll ausgeblendet werden.
  * Der Button `Stop` soll ausgeblendet werden.

  ##### Wenn ein Port geöffnet wurde
  * Der Button `Aktualisieren` soll ausgeblendet werden.
  * Der Button `Trennen` soll eingeblendet werden.
  * Der Button `Verbinden` soll ausgeblendet werden.

  ##### Wenn Ports gefunden wurden
  * Die Combobox soll eingeblendet werden
  * Der Button `Verbinden` soll eingeblendet werden.

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

#### Die Methode refresh
Zu erst werden in die zuvor angelegte Variable `ports` die Namen der gefundenen Ports gespeichert. Anschließend werden die Namen der gefunden Ports mit `jcbSerialDevice.setModel(model);` in der GUI angezeigt. Abschließend werden die Buttons aktualisiert.

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
#### Methode connect
Zuerst wird der Variable `port` der aktuell gewählte Port aus der ComboBox übergeben. Mit der Methode `.openPort();` wird der Port anschließend geöffnet. 

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

##### Warum wird bei catch ein Throwable gefangen?
Wenn mann in Java mit Schnittstellen arbeitet, werden JNI-Fehler geworfen. Diese Art von Fehler wird von der Klasse `Error` und nicht von der Klasse `Exception` abgeleitet. Deswegen wird die Elternklasse (`Throwable`) beider gefangen, um jegliche Art von Fehler fangen zu können. Genauere Information kann man in der [Javadoc](https://docs.oracle.com/javase/7/docs/api/java/lang/Throwable.html) nachlesen.

#### Die Methode disconnect
Mit der Methode `serialPort.closePort();` wird der aktuell geöffnete Port geschlossen. Hier wird `finally` benötigt, um sicherzustellen, dass der aktuelle Port auch bei Fehlerauftritt auf `null` gesetzt wird.

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
    finally
    {
      serialPort = null;
      updateSwingControlles();
    }
  }
```
#### Die ActionPerformed Methoden
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
#### Ende der Einheit
Zur Überprüfung unseres Quelltextes haben wir zum Schluss versucht uns mit unseren Arduino zu verbinden. Die Ergebnisse sind unterhalb zu sehen.

##### GUI wenn keine Ports gefunden wurden
![Kein Port gefunden](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Kein_Port_Gefunden.png)
##### GUI wenn Ports gefunden wurden
![Port gefunden](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Port_Gefunden.png)
##### GUI wenn Verbindung mit Port besteht
![Port verbunden](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Port_Verbunden.png)
