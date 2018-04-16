# *Protokoll KW 15*

  Name: Markus Wieser   
  Klasse: 4AHME   
  Datum: 09.01.2018   
  Anwesend: Strauß Lukas, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz    
  Abwesend: Sebastian Strutz
  
  ## Java Theorie
  
  ### Klassen in Java
  
   Einfach erklärt ist eine Klasse ein "Bauplan" für ein Programm. Ein Klasse besteht aus Attributen und Methoden.
  
  * Abstrakte Klasse: Dies ist eine unfertige Klasse, welche verwendet wird um weitere Klassen dieser Art zu erstellen.
                      Hier müssen dann nur einige Funktionen ausimplementiert werden.
  * Interface:        Ist eine Sammlung von Methoden.
  * Interne Klasse:   In einer internen Klasse können alle Attribute von einer äußeren Klasse übernommen werden.
  * Anonyme Klasse:   Sie hat keinen eigenen Klassennamen und ist die einfachste Klasse in Java.
  
  ### Vererbungen
  
   Bei Java gibt es immer nur eine Einfachvererbung. Eine Elternklasse kann mehrere Kindklassen haben, 
   aber eine Kindklasse kann nur eine Elternklasse haben.
  
  ## Temperaturmessung mit I²C
  
  ### jbutSingleMeasurementActionPerformed
  
  Hier wird von der Klasse MySingleMeasurementWorker ein Objekt erstellt. Dies wird mithilfe von execute() gemacht.
  
  ```java
  private void jbutSingleMeasurementActionPerformed(java.awt.event.ActionEvent evt)                       
  {                                                          
    new MySingleMeasurementWorker(serialPort).execute();
  }                                                     
```

  ### MySingleMeasurementWorker
  
  Hier sieht man wie eine interne Klasse namens MySingleMeasurementWorker erstellt wird. Sie dient für die Übergabe
  der Attribut-Variable an die eigentliche Worker Klasse.
  
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
  
  ### Worker Klasse SingleMeasurementWorker
  
  Die hier zu sehende Worker Klasse lässt die Abfrage der GUI in einem anderen Threat ablaufen.
  Die Methode doInBackground schickt eine Anfrage an das SureBoard, wobei wir das nächste Mal jedoch ein Feld verwenden
  wollen.
  
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


