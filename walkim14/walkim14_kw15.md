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
