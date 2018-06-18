# Laborprotokoll  
Sechste Einheit am 20. März 2018  
Martin Schmuck  
4AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Sackl R., Schmuck, Schuster  
Abwesend: Ruffenacht, Sackl M., Sammer

## Thema der Einheit: Visualisirung eines Temperatursensors
In dieser Einheit schließen wir direkt an die letzte Einheit an.
Wir nahmen die von unserem Professor zur Vefügung gestellte GUI-Vorlage zur Hand sowie das fertige Programm für den µC, womit selbiger auch gleich bespielt wurde. 

### GUI
Hier sieht man den grundsätzlichen Aufbau der GUI:
![jframe form swing](https://github.com/HTLMechatronics/m14-la1-sx/blob/smumam14/smumam14/resources/gui1.png)
>(c) Martin Schmuck  

Folgende Methoden wurden bis jetzt implementiert (Beschreibung der Einzelschritte siehe Kommentare):  
  
#### Konstruktor + Handler-Methoden
Wie allgemein bekannt sein sollte, wird der Konstruktor stets beim Erzeugen eines Objekts ausgeführt. Deshalb bringen wir hier alle Befehle unter, welche beim Start ausgeführt werden sollen. Anschließend sind noch die Handler-Methoden für die Buttons zu sehen, aus Gründen der Übersichtlichkeit und vor allem des Fehlerschutzes werden die eigentlichen Handlermethoden in seperate Methoden ausgelagert.
```java
public class SureModbusGui extends javax.swing.JFrame
{
  private static final Logger LOG = Logger.getLogger(SureModbusGui.class.getName());
  private jssc.SerialPort serialPort;
  private SwingWorker activeWorker;


  /**
   * Gui- Konstruktor
   */
  public SureModbusGui ()
  {
    // Ganz Am Anfang ausgeführt
    initComponents();
    refreshSerialPorts(); // Liste von verfügbaren Ports aktualisieren
    jlaTemperatur.setText("- °C"); // Den voreingestellten Temperaturwert löschen
    updateSwingControl(); //Controls aktualisieren, siehe weiter unten
    setLocationRelativeTo(null); // Fenster in die Bildschirmmitte setzen

  }
   private void jbutConnectActionPerformed(java.awt.event.ActionEvent evt)                                            
  {                                                
    connect();
  }                                           
  /**
   * Handlermethode Trennen
   *
   * @param evt
   */
  private void jbutDisconnectActionPerformed(java.awt.event.ActionEvent evt)                                               
  {                                                   
    disconnect();
  }                                              
  /**
   * Handlermethode Aktualisieren
   *
   * @param evt
   */
  private void jbutRefreshActionPerformed(java.awt.event.ActionEvent evt)                                            
  {                                                
    refreshSerialPorts();
    updateSwingControl();
  }                                           
  /**
   * Handlermethode Einzelmessung
   *
   * @param evt
   */
  private void jbutSingleMeasurementActionPerformed(java.awt.event.ActionEvent evt)                                                      
  {                                                          
    activeWorker = new GuiSingleMeasurementWorker();
    activeWorker.execute();
    updateSwingControl();
  }                                                     

  private void jbutContinousMeasurementActionPerformed(java.awt.event.ActionEvent evt)                                                         
  {                                                             
    // Noch nicht ausprogrammiert
  }                                                        

  private void jbutStopMeasurementActionPerformed(java.awt.event.ActionEvent evt)                                                    
  {                                                        
    // Noch nicht ausprogrammiert
  }                                                  
  
  }

```
#### updateSwingControls
Damit man nicht durcheinanderkommt, wann man welches Control deaktivieren und wieder aktivieren muss, erfolgt die Steuerung dieser Controls zentral in einer Methode, in der eine Art Zustandsmaschine realisiert ist.
```java
/**
   * Methode mit Zustandsmaschine zum Aktualisieren der Swing Controls abhähnig vom Programmzustand
   */
  private void updateSwingControl ()
  {
    // Zuerst einmal alle Controls deaktivieren
    jbutConnect.setEnabled(false);
    jbutContinousMeasurement.setEnabled(false);
    jbutDisconnect.setEnabled(false);
    jbutRefresh.setEnabled(false);
    jbutSingleMeasurement.setEnabled(false);
    jbutStopMeasurement.setEnabled(false);

    if (activeWorker != null) // Hiermit wird der Cursor geändert, sobald gemssen wird
    {
      setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
      return;
    }
    else  // Wenn fertig gemessen, wird es wieder zurückgesetzt
      setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));

    jbutRefresh.setEnabled(true); // Aktualisieren-Button aktivieren
    if (jcbSerialDevice.getModel().getSize() > 0) // Wenn serielle Schnittstellen vorhanden, 
    { //                                      werden  Verbinden und die Combobox aktiviert
      jbutConnect.setEnabled(true);
      jcbSerialDevice.setEnabled(true);
    }
    if (serialPort != null && serialPort.isOpened()) // Wenn die Verbindung zum µC steht, passiert folgendes
    {
      jbutConnect.setEnabled(false); // Verbinden, Combobox und aktualisieren deaktivieren
      jbutRefresh.setEnabled(false);
      jcbSerialDevice.setEnabled(false);
      jbutDisconnect.setEnabled(true); // Trennen und Einzelmessung aktivierung
      jbutSingleMeasurement.setEnabled(true);
    }
  }
```  
#### showThroable
Ein Schaubild zur Fehlerbehandlung in Java:  
![err](https://lh5.googleusercontent.com/WqqNoyFEkZXfmZBBQjgIutY72_BUV6_By_BAe7Ih9u36HfelS3nTWQEYtdRUkQS32Tuhg9P9CUXo-jgvOpkO84vLm2viI4Od0BNustwONdMm7DKZnKC6kyVHyRJbsESLIPV4uBU)
> abgerufen von [JavaMadeSoEasy.com](http://www.javamadesoeasy.com/2015/05/exception-handling-exception-hierarchy.html) am 14.05.2018  
  
  
Hier sieht man, warum man RuntimeExceptions nicht unbedingt fangen muss: Sie gehören der Gruppe der "unchecked" - Fehler an, welche nicht zwingend behandelt werden müssen. Von Throwable abgeleitet werden die Klassen Exception und Error, wobei man im Normalfall nur Exceptions fangen sollte (Laufzeit-Programm-Fehler), da Errors wirklich schwerwiegende Fehler in der JVM sind, auf die man eigentlich nicht mehr reagieren kann. Deshalb ist es auch sinnentleert, derartige Errors zu fangen.  
An dieser Stelle muss jedoch eine Ausnahme gemacht werden, da JSSC (siehe [Protokoll der 5. Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/smumam14/smumam14/Protokoll5.md#java-native-interface)) Errors wirft, welche aber wie Exceptions behandelt werden müssen. 
```java
  /**
   * Methode zum Ausgeben von Throwables (Errors und Exceptions)
   *
   * @param th Zu werfendes Throwable-Object
   */
  private void showThrowable (Throwable th)
  {
    th.printStackTrace(System.err);  // Stacktrace auf den Error-Output-Stream loggen
    String message = th.getMessage(); // Fehlermeldung erhalten
    if (message == null || message.isEmpty()) // Wenn man keine Fehlermeldung erhält, gibt man 
      message = "Unbekannter Fehler: " + getClass().getSimpleName(); // die Klasse aus, um zumindest 
    // rudimentär etwas über den Fehler in Erfahrung bringen zu können
    JOptionPane.showMessageDialog(this, message, "Fehler aufgetreten", JOptionPane.ERROR_MESSAGE);
    // Fehlermeldung im passenden Fenster ausgeben
  }
```  
  
  #### refreshSerialPorts
Diese Methode wird aufgerufen, um die Combobox mit verfügbaren Schnittstellen zu aktualisieren
```java

  /**
   * Methode zum Aktualisieren der Combobox mit seriellen Ports
   */
  private void refreshSerialPorts ()
  {
    final String[] ports = jssc.SerialPortList.getPortNames(); // Liste von vefügbaren Ports erhalten
    ComboBoxModel<String> m = new DefaultComboBoxModel<>(ports); // Combobox-Model erzeugen
    jcbSerialDevice.setModel(m); // Model setzen
```  

  #### connect
Öffnen der Verbindung über die serielle Schnittstelle, inklusive der Behandlung aller möglichen Fehlerfälle.
```java

  /**
   * Methode zum Verbinden mit dem µC
   */
  private void connect ()
  {
    try
    {
      final String port = (String) jcbSerialDevice.getSelectedItem(); // Gewählten Port auslesen aus Combobox
      serialPort = new jssc.SerialPort(port); // Öffnen des Ports
      if (serialPort.openPort() == false) //Laufzeitfehlerbehandlung 1 (Öffnen) 
        throw new Exception("open port returns false");
      if (serialPort.setParams(serialPort.BAUDRATE_57600,
                               serialPort.DATABITS_8,
                               serialPort.PARITY_NONE,
                               serialPort.STOPBITS_2) == false) // Laufzeitfehlerbehandlung 2 (Konfigurieren)
        throw new Exception("set params returns false");
    }
    catch (Throwable th) //Normalerweise nicht erlaubt, man muss hier wegen JNI eine Ausnahme machen
    {
      showThrowable(new Exception("Kann Port nicht öffnen", th)); // Ausgeben am Bildschirm
      if (serialPort != null) // Im Fehlerfall Port schließen
        try
        {
          serialPort.closePort();
        }
        catch (Throwable th2) // Wenn dies nicht möglich ist, dann dies melden
        {
          th.addSuppressed(th2);
        }
      serialPort = null;
    }
    finally // finally-Block wird in jedem Fall ausgeführt
    {
      updateSwingControl(); 
    }
  }
```  
  
  
 #### disconnect
Schließen der Verbindung über die serielle Schnittstelle, inklusive der Behandlung aller möglichen Fehlerfälle.
```java

  /**
   * Methode zum trennen der Verbindung zum µC
   */
  private void disconnect ()
  {
    try
    {  
      if (serialPort.closePort() == false)
        throw new Exception("close port returns false");
    }
    catch (Throwable th) //Fehlerbehandlung beim Schließen mit entsprechende Meldung
    {
      showThrowable(new Exception("Kann nicht trennen", th));
    }
    finally
    {
      serialPort = null;
      updateSwingControl();
    }
  }

```
_____________________________  

  
  ### Swing Worker
Da Messungen in der Regel etwas dauern und es nicht angenehm ist, wenn in dieser Zeit die GUI einfriert, wird der eigentliche Messvorgang (also die Kommunikation mit µC) in einen eigenen Thread ausgelagert, hier mithilfe des Swing Workers. Nachfolgend die Klasse, in welcher zu Testzwecken eine delay-Funktion und die Rückgabe eines Festwertes eingebaut wurden. 
```java
public class SingleMeasurementWorker extends SwingWorker <Double, String>
{

  @Override
  protected Double doInBackground() throws Exception
  {
    TimeUnit.SECONDS.sleep(3);  // Delay-funktion um Messzeit zu simulieren
    return 12.4; // Rückgabe eines Festwertes, um eine Gemessene Temperatur zu simulieren
  }
  
}
```  
__________________________________________  

  
  ### Dokumentationskommentare
Der Dokumentationskommentar wurden Java eingeführt, um beim Dokumentieren mehr Komfort zu erzielen. Dieser wird statt mit einem normalen `/*` mit einem `/**` eingeleitet und direkt vor den Methoden- bzw. Klassenkopf geschrieben. Dadurch werden zwei Effekte erreicht: 
1. man sieht bei der Auto-Vervollständigung (`CTRL + SPACE`) auch gleich die Beschreibung der Methode und
1. man kann sich über die Funktion `Generate Javadoc` im Netbeans-Menü `Run` eine Dokumentationsseite zu seinem Projekt automatisch erstellen lassen, die man zum Beispiel dem Programm beilegen oder auch für spätere Änderungen am Programm archivieren kann. 
```java
/**
* Dieser Kommentar soll eine Sinnbefreite Klasse kommentieren
*/
public class SinnloseKlasse
{
  /**
  * Methode zur Rückgabe der Zahl 5
  * @return Zahl 5.0
  */
  protected Double getFive()
  {
    return Math.sqrt(4)*2.5;
  }
  
}
```  
_____________________________
Abschließend noch ein Thema, welches bei unserem Projekt nicht von Relevanz ist, jedoch nicht unerwähnt bleiben sollte:  
#### Testumgebung
Software, welche kommerziell vermarktet wird und insbesondere jene, die zur gewerblichen Nutzung vorgesehen ist, muss vor der Auslieferung getestet werden. Damit versucht man möglichst viele Bugs und anderer Probleme schon im vorhinein abzufangen, da eine Problembehebung beim Kunden immer ungünstig ist. Daher ist es ratsam, für Software, welche man eventuell irgendwann verkaufen möchte, gleich eine Testumgebung zu bauen.   
In großen Softwareentwicklungsunternehmen gibt es dafür eigene Abteilungen, welche ausschließlich mit dem Testen der hauseigenen Programme betraut sind.


