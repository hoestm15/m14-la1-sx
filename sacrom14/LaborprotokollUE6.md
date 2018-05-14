# 6.Protokoll  
  
  **Name**:  *Sackl Roland*  
  **Datum:** *20.03.2018*  
  **Uhrzeit:** *9:40-12:25*  
  **Gruppe:** *3*  
  
  **Abwesend:**  Sackl Martin,Sammer Daniel,Ruffennacht Florian  
  **Anwesend:**  Sackl Roland, Reinbacher Bernhard,Schuster Patrick, Schmuck Martin   


 # Temperatursensor

In der letzten Einheit beschäftigten wir uns mit den Modbus, welches in dieser Einheit vorgesetzt wurde. in dieser Einheit ist unsere Aufgabe mittels einen SureBoard einen Temperatursensor zu bauen. Die Daten des Sensors sollen über einen Feldbus an den Computer übertragen und anschließend verarbeitet werden. Außerdem mit einer Java-Swing-realisiereten GUI visualisiert werden.  

 ## Vorlage GUI     

Diese fertige GUI war unsere Vorlage für die visualisierung,die auf dem Arnfelsserver zum Download bereit stand.  

  ![GUI](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacrom14/sacrom14/Temperatur_GUI.PNG)
  ## Die verwendeten Methoden     


  ### showThrowable()        
Diese Methode sit für die Fehlerausgbe zuständig.Tritt ein Fehler auf, wird der Fehler in einem Pop-Up Fenster ausgegeben.Die Fehlermeldung `msg` wird im Fenster ausgegeben.
```java
private void showThrowable (Throwable th)
  {
    th.printStackTrace(System.err);
    String msg = th.getMessage(); 
    if(msg == null || msg.isEmpty())
    {
      msg = th.getClass().getSimpleName();  
    }
    JOptionPane.showMessageDialog(
            this, 
            msg, 
            "Fehler aufgetreten", 
            JOptionPane.ERROR_MESSAGE);
  }  
  ```  


### refresh ()   
Zuerst werden in die zuvor angelegte Variable `ports` die Namen der gefundenen Ports gespeichert. Dannach werden die Namen der gefunden Ports in der GUI angezeigt.  
Abschließend werden die Buttons aktualisiert.    


### connect()  
Zuerst wird `port` der aktuell gewählten Port aus der Combobox übergeben und anschließend mit der Methode  `.openPort();` geöffnet.   

```java  
    private void connect ()
  {
    try
    {
      final String port = (String) jcbSerialDevice.getSelectedItem();
      serialPort = new jssc.SerialPort(port);
      if(serialPort.openPort()==false){
        throw new Exception("openPort() returns false");
      }
      if(serialPort.setParams( SerialPort.BAUDRATE_57600,
                               SerialPort.DATABITS_8,
                               SerialPort.PARITY_NONE,
                               SerialPort.STOPBITS_2
                             ) == false)
      {
        throw new Exception("setParams returns false");
      }
    }
    catch (Throwable th)  // Ausnahme durch JNI
    {
      showThrowable(new Exception("Kann nicht verbinden", th));
      if(serialPort != null)
      {
      try{
        serialPort.closePort();
      }
      catch(Throwable th2){
        //th2.printStackTrace(System.err);
        th.addSuppressed(th2);  // besser
      }
      serialPort = null;
      }
    }
    finally
    {
      updateSwingControls();
    }
  }
  ```  
### disconnect()    
Der aktuelle Port wird mit `serialPort.closePort();` geschlossen.   
Hier benötigen wir `finally` um sicherzugehen ob der aktuelle Port auch bei Fehlerauftritt auf null gesetzt wird.  

 ```java  
    private void disconnect()  
    {
    try  
    {  
      if(serialPort.closePort() == false)
      {
        throw new Exception("closePort() return false");
      }
    }
    catch(Throwable th)  
    {  
      showThrowable(th);
    }
    finally  
    {  
      serialPort = null;
      updateSwingControls();
    }
  }

 ```   

### updateSwingControls()  

 **Buttons beim Start des Programmes:**
  * Der Button `Aktualisieren` soll eingeblendet sein.
  * Der Button `Verbinden` soll ausgeblendet sein.
  * Der Button `Trennen` soll ausgeblendet sein.  
  * Der Button `Stop` soll ausgeblendet werden.  
  * Der Button `Einzelmessung` soll ausgeblendet werden.
  * Der Button `Laufend messen` soll ausgeblendet werden.

  * Die Combobox soll ausgeblendet werden.

  **Wenn ein Port geöffnet wurde:**  
  * Der Button `Aktualisieren` soll ausgeblendet werden.
  * Der Button `Trennen` soll eingeblendet werden.
  * Der Button `Verbinden` soll ausgeblendet werden.

  **Wenn Ports gefunden wurden:**

  * Der Button `Verbinden` soll eingeblendet werden.  
  * Die Combobox soll eingeblendet werden.  


```java 
private void updateSwingControls ()
  {

    jbutConnect.setEnabled(false);
    jbutContinousMeasurement.setEnabled(false);
    jbutDisconnect.setEnabled(false);
    jbutRefresh.setEnabled(false);
    jbutSingleMeasurement.setEnabled(false);
    jbutStopMeasurement.setEnabled(false);
    jcbSerialDevice.setEnabled(false);

    if(activeWorker != null)
    {
      setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
      return;
    }
    else
    {
      setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    }
    
    
    
    jbutRefresh.setEnabled(true);
    if (jcbSerialDevice.getModel().getSize() > 0)
    {
      jcbSerialDevice.setEnabled(true);
      jbutConnect.setEnabled(true);
    }

    if(serialPort != null && serialPort.isOpened())
    {
      jcbSerialDevice.setEnabled(false);
      jbutConnect.setEnabled(false);
      jbutRefresh.setEnabled(false);
      jbutDisconnect.setEnabled(true);
      jbutSingleMeasurement.setEnabled(true);
    }
  }
```


### GUISingleMeasurementWorker  
Die Temperaturmessung wird im Hintergrund die Temperaturmessung durchgeführt. Der SingleMeasurementWorker abgeleitet von GUISingleMeasurementWorker findet jede Sekunde ein Ereignis statt. In unseren Fall ist noch keine Temeraturmessung programmiert also wird jedes Mal 24.5°C aübergeben.  

 
 ```java  
   private class GuiSingleMeasurementWorker extends SingleMeasurementWorker{

    @Override
    protected void done ()
    {
      try
      {
        double temp = get();
        jlaTemperatur.setText(String.format("%.1f °C", temp));
      }
      catch(Exception ex)
      {
        showThrowable(new Exception("Einzelmessung gescheitert", ex));
      }
      finally
      {
        activeWorker = null;
        updateSwingControls();
      }
    }
```





