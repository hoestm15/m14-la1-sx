
# *Protokoll KW 15*

  Name: Strauß Lukas   
  Klasse: 4AHME   
  Datum: 10.04.2018   
  Anwesend: Strauß Lukas, Tuttner Raphael, Uhl Chrstian, Waltl Kilian, Wieser Markus,Zitz Karlheinz    
  Abwesend: Sebastian Strutz
  
  ## 1. Theorie
  ### LM75A :point_right: Ein intelligenter Sensor ?
  
Ein Sensor ist dann intelligent, wenn er ein Rechenwerk besitzt. Das heißt also es muss einen eingebauten Prozessor geben.   Bei einem unintelligenten Sensor bekommt man nur einen Spannungswert zurück , diesen muss man dann selbst in einen Temperaturwert umrechnen. Beim dem intelligenten Sensor passiert das bereits im Rechenwerk. Der LM75A ist eigentlich ein unintelligenter Sensor, allerdings benutzen wir ihn zusammen mit einem Sureboard, welches unser Rechenwerk ist. Somit ist es in unserem Fall ein intelligenter Sensor.      
  
### JNI :point_right: Java Native Interface

JNI besteht aus zwei Komponenten:

Betriebssystemebene--> Binäre Bibliotheken werden dem Betriebssystem zu Verfügung gestellt. Das sind Funktionen die man in C/C++ geschrieben hat. Bei Windows --> DLL-Datei, Bei Linux: SO-Datei

Jacva-Ebene--> ein oder mehrere .java Dateien sind zur Verfügung gestellt

Beide zusammen schaffen es alos, eine Kommunikation über die serielle Schnitstelle zu ermöglichen. Es gibt hierfür eine schon fertig implementierte Lösung. Diese nennt sich *JSSC* = Java Simple Serial Connector. Diese Lösung benutzen wir auch in unserer Übung. Somit ist keine Konfiguration mehr möglich, da wir alle notwendigen Klassen und Bibliotheken bereits eingebunden haben.

Im Java Simple Serial Connector findet man .jar Dateien. Dateien können aus .jar Dateien extrahiert werden , so muss es der Benutzer nicht mehr machen.
    

### Klassen in Java

Unter einer Klasse versteht man in Java vereinfacht gesagt den Bauplan für ein Programm. Die Klasse besteht aus Objekten und Methoden. Objekt=Attribut.  
  
Eine Abstrakte Klasse ist wenn man es so will eine unfertige Klasse die man verwendet um weitere solche Klassen zu erstellen.
Unter Interface versteht man in Java eine Sammlung von Methoden. Eine sogenannte Interne Klasse kann alle Attribute von einer äußeren Klasse übernehmen. 
Eine anonyme Klasse hat keinen eigenen Klassennamen und ist so auch die einfachste Klasse in Java. Ansonsten ist sie der internen Klasse sehr ähnlich. Mit ihr ist es möglich einiges an Zeit zu sparen , da sie ja nicht einmal einem eigenen Klassennamen hat.
  
  
### Vererbungen 

In Java gibt es nur Einfachvererbungen. Eine Kindklasse kann nur eine Elternklasse haben aber eine Elternklasse kann mehrere Kindklassen haben.



## Temperaturmessung

Nach den Widerholungen der letzten Einheit machten wir bei unserer Temperaturmessung weiter.

### jbutSingleMeasurementActionPerformed
  Von der Klasse MySingleMeasurementWorker wird ein Objekt erstellt, das wir mithilfe von execute() gemacht.
  
  ```java
  private void jbutSingleMeasurementActionPerformed(java.awt.event.ActionEvent evt)                       
  {                                                          
    new MySingleMeasurementWorker(serialPort).execute();
  }                                                     
```

 #### SingleMeasurementWorker Worker-Klasse  

Die GUI Abfrage läuft mittels Swing Worker in einem anderen Thread ab. Die Methode doInBackground sendet eine Anfrage an das Sureboard.


  
```java
package workers;

import javax.swing.SwingWorker;
import jssc.SerialPort;


public class SingleMeasurementWorker extends SwingWorker<Double, Object>
{
  private final jssc.SerialPort serialPort;

  public SingleMeasurementWorker (SerialPort serialPort)
  {
    this.serialPort = serialPort;
  }

  @Override
  protected Double doInBackground () throws Exception
  {
    serialPort.writeInt(2); // Geraeteadresse
    serialPort.writeInt(4); // Funktioncode 0x04 = Read Input Register
    serialPort.writeInt(0); // LM75A Register
    serialPort.writeInt(0x30); // LM75A Register
    serialPort.writeInt(1); // Anzahl der Register
    serialPort.writeInt(0x31); // CRC Pruefsumme High-Byte
    serialPort.writeInt(0xf6); // CRC Pruefsumme Low-Byte
    // to do use Array to send data: serialPort.writeIntArray(buffer)
    
    return 23.5;
  }

}
```
#### MySingleMeasurementWorker  
 
 Eine innere Klasse wird erstellt,welche eine Objekt-Variable an die Worker-Klasse übergibt.
   
 ```java
  {

    public MySingleMeasurementWorker (SerialPort serialPort)
    {
      super(serialPort);
    }
    @Override
    protected void done ()
    {
      try
      {
        double temp = get();
        jlaTemperatur.setText(String.format("%.1f °C", temp));
      }
      catch (Exception ex)
      {
         showException("Schnittstelle kann nicht geöffnet werden", ex);
      }
    }
 }  
 
```  
## Swing Worker 

Da Swing nicht threadsicher ist, kann es Probleme bereiten, wenn man aus anderen Threads auf die GUI zugreifen will, um zb einen Fortschrittsbalken zu aktualisieren. Die Klasse Swing Worker hilft, um solche GUI Updates leichter darstellen zu können. 
  
  
