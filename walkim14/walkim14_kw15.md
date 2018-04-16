# Protokoll KW 15
Name: Kilian Waltl
Klasse: 4AHME  
Datum: 10.04.2018  
Anwesend: Strauß Lukas, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz  
Abwesend: Strutz Sebastian  

## Temperaturmessung

### Klasse MySingleMeasurementWorker
```java
private class MySingleMeasurementWorker extends SingleMeasurementWorker
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
Da wir das Attribut "serialPort" an die Worker Klasse übergeben müssen, haben wir an dieser Stelle des Programms eine interne Klasse mit dem Namen "MySingleMeasurementWorker" erstellt, welche verwendet wird um das Attribut an die eigentliche Worker Klasse weiterzugeben.

### Worker Klasse SingleMeasurementWorker
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
Die hier verwendete Worker Klasse dient dazu, die Abfrage der Temperatur in einem anderen Threat laufen zu lassen, um zu verhindern, dass die GUI einfriert.
In der Methode "doInBackground" wird eine Anfrage an das Sure Board geschickt, jedoch wird dies noch nicht richtig funktionieren, da wir die Bits alle einzeln verschicken. In der nächsten Einheit werden wir hierfür ein Feld verwenden um diese Übertragung zuverlässiger zu machen.

### Button "jbutSingleMeasurementActionPerformed"
```java
  private void jbutSingleMeasurementActionPerformed(java.awt.event.ActionEvent evt)                                                      
  {                                                          
    new MySingleMeasurementWorker(serialPort).execute();
  }                                                     
```
Hier wird, wenn der Listener des Buttons "jbutSingleMeasurement" angesprochen wird, von der internen Klasse "MySingleMeasurementWorker" in kombination mit der Methode "execute()" ein Object erstellt.
