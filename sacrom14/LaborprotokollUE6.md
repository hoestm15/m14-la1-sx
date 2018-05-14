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

  ## Die verwendeten Methoden     


  ### showThrowable()        
Diese Methode sit für die Fehlerausgbe zuständig.Tritt ein Fehler auf, wird der Fehler in einem Pop-Up Fenster ausgegeben.Die Fehlermeldung `msg` wird im Fenster ausgegeben.



### refresh ()   
Zuerst werden in die zuvor angelegte Variable `ports` die Namen der gefundenen Ports gespeichert. Dannach werden die Namen der gefunden Ports in der GUI angezeigt.  
Abschließend werden die Buttons aktualisiert.    


### connect()  
Zuerst wird `port` der aktuell gewählten Port aus der Combobox übergeben und anschließend mit der Methode  `.openPort();` geöffnet.   

### disconnect()    
Der aktuelle Port wird mit `serialPort.closePort();` geschlossen.   
Hier benötigen wir `finally` um sicherzugehen ob der aktuelle Port auch bei Fehlerauftritt auf null gesetzt wird.  


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


### GUISingleMeasurementWorker  
Die Temperaturmessung wird im Hintergrund die Temperaturmessung durchgeführt. Der SingleMeasurementWorker abgeleitet von GUISingleMeasurementWorker findet jede Sekunde ein Ereignis statt. In unseren Fall ist noch keine Temeraturmessung programmiert also wird jedes Mal 24.5°C aübergeben.  




