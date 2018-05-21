# **7. Laborprotokoll** 

*von Florian Ruffenacht*

Datum: 15.05.2017 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

Abwesend: -

## Wiederholung der letzten Einheit(en)

Zu Beginn der Einheit wiederholten wir ausführlich die den bereits besprochenen Stoff zum Projekt Temperaturmessung mittels Mikroprozessor. Zum Beispiel wurde uns der Hardwareaufbau wieder ins Gedächtnis gerufen. 

[Link zum Protokoll der 5.Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/Protokoll_5.md)

## Programmieren des SingleMeasurementWorkers

Der SingleMeasurementWorker ist eine JAVAl-Klasse, die in einem eigenen Thread die Temperatur über die serielle Schnitstelle einmalig abfragen soll. Ihm wird im Konstruktor die serielle Schnitstelle (serialPort) übergeben. Die Modbus-Anfrage besteht aus folgenden 8 Bytes: 2,4,0,0x30,0,1,0x31,0xf6.

Nach einer Wartezeit von 100ms wird die Antwort abgefragt und auf Herz und Nieren geprüft. Gegebenenfalls wird eine Exception geworfen. Sie soll aus 9 Bytes bestehen und die Werte der Temperaturmessung befinden sich an der 3. und der 4. Stelle. Löst die Antwort keine Exception aus, wird die Temperatur in Grad ausgerechet und zurückgegeben.

´´´java

public class SingleMeasurementWorker extends SwingWorker<Double, String>
{
  private final SerialPort serialPort;

  public SingleMeasurementWorker (SerialPort serialPort)
    {
      this.serialPort = serialPort;
    }
  
  @Override
  protected Double doInBackground () throws Exception
    {
      publish("Sende Request an Modbus-Server");
      int[] request= { 2,4,0,0x30,0,1,0x31,0xf6};
      serialPort.writeIntArray(request);
       TimeUnit.MILLISECONDS.sleep(100);

       int[] response = serialPort.readIntArray();

       if (response == null || response.length==0)
          { 
            throw new ModbusException("Keine Atnwort erhaten",request);
          }

       if (response.length <7)
          {
            throw new ModbusException("Zu kurze Antwort erhalten", request, response);
          }

       if (response[0]!= 2)
          {
            throw new ModbusException("Antwort von falschem Gerät", request, response);
          }

       if (response[1]!= 4)
          {
            throw new ModbusException("Antwort mit falschem Function-Code", request, response);
          }

        if (response[2]!= 2)
         {
           throw new ModbusException("Antwort mit falscher Anzahl von Bytes", request, response);
         }


         double temp = (response[3]* 256.0 + response[4]) / 256.0;



      return temp;
    }
  
}

´´´
