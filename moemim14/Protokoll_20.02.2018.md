# Protokoll 6 20.02.2018

## Thema: Atmel Studio

Name: Michael Mörth  
Klasse: 4AHME  
Gruppe: 2  

Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Moritz Martinak, Mario Nabernik, Muri Lorenz, Platzer Andreas, Marcel Köhler    
Abwesend: -

## JAVA-Projekt: Temperaturmessung
In der heutigen Stunde wandten wir das Wissen der letzten Stunde über den Modbus an. Unsere Aufgabe ist es,mittels eines SureBoards einen Temperatursensor zu bauen. Die Daten des Sensors sollen über einen Feldbus an den Computer übertragen werden. Die Daten sollenanschließend verarbeitet werden. Die übertragenen Daten sollen anschließend in einer mit Java-Swing-realisierten GUI visualisiert werden.

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
