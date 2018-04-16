# Protokoll KW 15
Name: Kilian Waltl
Klasse: 4AHME  
Datum: 10.04.2018  
Anwesend: Strauß Lukas, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz  
Abwesend: Strutz Sebastian  

## Temperaturmessung

### MySingleMeasurementWorker
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
