# Laborprotokoll  
Sechste Einheit am 20. März 2018  
Martin Schmuck  
4AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Sackl M., Sackl R., Schmuck, Schuster  
Abwesend: Ruffenacht, Sammer

## Thema der Einheit: Visualisirung eines Temperatursensors
In dieser Einheit schließen wir direkt an die letzte Einheit an.
Wir nahmen die von unserem Professor zur Vefügung gestellte GUI-Vorlage zur Hand sowie das fertige Programm für den µC, womit selbiger auch gleich bespielt wurde. 

### GUI
Hier sieht man den grundsätzlichen Aufbau der GUI:
![jframe form swing](https://github.com/HTLMechatronics/m14-la1-sx/blob/smumam14/smumam14/resources/gui1.png)
>(c) Martin Schmuck  

Folgende Methoden wurden bis jetzt implementiert:  
  
#### Datenelemente + Konstruktor + Handler-Methoden
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
    // TODO add your handling code here:
  }                                                        

  private void jbutStopMeasurementActionPerformed(java.awt.event.ActionEvent evt)                                                    
  {                                                        
    // TODO add your handling code here:
  }                                                  
  
  }

```
