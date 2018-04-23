# Protokoll 27.02.2018  

## 6. Einheit  

## Thema: Schnittstellenprogrammierung

Name: Moritz Martinak  
Lehrer: sx  
Gruppe: 2  
Übungsdatum: 27.02.2018  
Abwesend: -  

# Temperatursensor  

## Aufgabenstellung  

Wir mussten mit Hilfe eines SureBoards einen Intelligenten Temperatursensor programieren der die Daten via einen Feldbus auf den Computer überträgt. Diese sollten anschließend verarbeitet werden und in einer vorgegebenen Java-Swing GUI visualisiert werden.  

## GUI  
Zuerst galt es die vorgefertigte GUI vom Server zu downloaden.  

## Quellcode  

### Variablen  
```java
  private String [] ports;
  private jssc.SerialPort serialPort;
```  

### Konstruktor  

```java
public SureModbusGui ()
  {
    initComponents();
    setLocationRelativeTo(null);
    jlaTemperatur.setText("? °C");
    refresh();
  }
```  

### showThrowable  

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
  
  ### updateSwingControlles  
  
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
