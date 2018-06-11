# Protokoll 24.04.2018
## 7. Einheit

Name: Muri Lorenz <br>
Klasse: 4AHME <br>
Gruppe: 2 <br>
Datum der Einheit: 24.04.2018 <br>
Anwesend: Mandl, Martinak, Mörth, Muri, Nabernik, Nebel, Platzer, Köhler<br>
Abwesend: - <br>

## Wiederholung der letzten Einheit
Am Beginn der Einheit haben wir das Programm der letzten Einheit besprochen und außerdem über die Grundlagen der Kommunikation mit einem Modbus gesprochen.

**Besprochene Methoden**
* `showThrowable()`
* `updateSwingControlls()`
* `refresh()`
* `connect()`
* `disconnect()`
<br>

## Erweiterterungen des Quellcodes
   ``` private void connect ()
  {
    try
    {
      String port = (String) jcbSerialDevice.getSelectedItem();
      serialPort = new jssc.SerialPort(port);
      serialPort.openPort();
      serialPort.setParams(
              SerialPort.BAUDRATE_57600,
              SerialPort.DATABITS_8,
              SerialPort.STOPBITS_2,
              SerialPort.PARITY_NONE);
      updateSwingControls();
    }
    catch (Throwable th)
    {

      try
      {
        if (serialPort != null && serialPort.isOpened())
        {
          serialPort.closePort();
        }
      }
      catch (Throwable th2)
      {
        th.addSuppressed(th2);
      }
      showThrowable("Serielle Schnittstelle kann nicht geöffnet werden!", th);
      serialPort = null;
    }
    finally
    {
      updateSwingControls();
    }
  } ```
  
