# Protokoll 24.04.2018  

## 7. Einheit  

## Thema: Schnittstellenprogrammierung

Name: Moritz Martinak  
Lehrer: sx  
Gruppe: 2  
Übungsdatum: 24.04.2018  
Abwesend: -  

## Wiederholung  

### Besprechung des Programs  
Zu beginn der Stunde besprachen wir das Programm welches wir in der letzen Einheit begonnen hatten. Dies findet man im [letzen Protokoll](https://github.com/HTLMechatronics/m14-la1-sx/blob/marmom13/marmom13/Protokoll_27.02.18.md).  Ausserdem haben wir noch über das Java Native Interface (JNI) gesprochen.  

### Java Native Interface (JNI)  
>Java kann nicht wirklich eine plattformunabhängige Programmiersprache sein – spätestens, wenn es an die tatsächlichen Ressourcen eines Rechners geht, müssen diese in Java eingebunden werden. Ein Sortierverfahren oder eine Datenstruktur ist wirklich plattformneutral, für das Bearbeiten von Dateien oder das Setzen von Punkten auf dem Bildschirm ist jedoch die jeweilige Architektur zuständig. Dazu ruft Java die nativen Methoden auf, die nicht in Java implementiert sind. Native Methoden sind in der>API-Dokumentation nicht immer zu erkennen, aber ein Blick in den Quellcode verrät sie schnell.  

>Um diese Schnittstelle zwischen Java und konkreter Plattform kümmert sich das Java Native Interface (JNI). Mithilfe von JNI können aus der JVM heraus plattformspezifische Funktionen verwendet werden. Die native Funktion – wir gehen im Folgenden von einer Funktion in C aus – kann aber auch wieder die JVM steuern und Objekte erfragen, Ausnahmen auslösen, neue Klassen laden usw. 

*Quelle: [Java 7: Mehr als eine Insel](http://openbook.rheinwerk-verlag.de/java7/1507_21_001.html)*  

## Programmieren  

### startSingleMeasurement()  

Diese neue Methode dient dazu den SwingWorker zu starten, dazu verwenden wir die neue Klassenvariable *activeWorker*:

```java
private void startSingleMeasurement()
  {
    activeWorker =  new MySingleMeasurementWorker(serialPort);
    activeWorker.execute(); //die Klassenvariable des Workers
    updateSwingControls();
  }
```

## updateSwingControlls()  

Wir haben die Methode mit ```java if(activeWorker != null)``` erweitert. Diese if-Verzweigung überprüft ob ein Worker aktiv ist. Ist dies der fall wird der Cursor durch den *WAIT_CURSOR* ersetzt, die GUI soll aber weiterhin responsive bleiben.

```java
 public void updateSwingControls()
  {
    jcbSerialDevice.setEnabled(false);
    jbutConnect.setEnabled(false);
    jbutDisconnect.setEnabled(false);
    jbutRefresh.setEnabled(false);
    jbutSingleMeasurement.setEnabled(true);
    jbutContinousMeasurement.setEnabled(false);
    jbutStopMeasurement.setEnabled(false);
    jlaTemperatur.setEnabled(false);
    if (activeWorker != null)
    {
      setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
      return;
    }
    setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    jlaTemperatur.setEnabled(true);
    
    if (serialPort != null && serialPort.isOpened())
    {
      jbutDisconnect.setEnabled(true);
      //jbutSingleMeasurement.setEnabled(true);
      return;
    }
    
    if(ports == null || ports.length == 0)
    {
      jbutRefresh.setEnabled(true);
    }
    
    else if(ports != null && ports.length > 0); 
    {
      jcbSerialDevice.setEnabled(true);
      jbutConnect.setEnabled(true);
      jbutRefresh.setEnabled(true);
    }
  }
```

## connect() 

Wir haben die Parameter für die serielle Schnittstelle festgelegt(Baudrate = 57600, 8 Datenbits usw.)

```java
private void connect ()
  {
    try{
      String port = (String)jcbSerialDevice.getSelectedItem();
      
      serialPort.openPort();
      serialPort.setParams(SerialPort.BAUDRATE_57600, //legt Baudrate fest 
                           SerialPort.DATABITS_8, //legt Anzahl der Datenbits fest
                           SerialPort.STOPBITS_2, //legt Anzahl der Stopbits fest
                           SerialPort.PARITY_NONE); //legt Parity fest
      updateSwingControls();
    }
    catch (Throwable th)
    {
      showThrowable("Serielle Schnittstelle kann nicht geöffntet werden", th);
      try {
        if (serialPort != null && serialPort.isOpened())
        {
          serialPort.closePort();
        }
      }
        catch (Throwable th2)
        {
          th.addSuppressed(th2);
        }
      showThrowable("Serielle Schnitt", th);
        serialPort = null;
    } finally {
      updateSwingControls();
    }
  }
```
