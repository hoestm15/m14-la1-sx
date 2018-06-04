# Protokoll 17.04.2018

## 7. Einheit
## Thema: Temperaturmessung
 
 Name: Markus Kobor  
 Klasse: 4AHME  
 Datum: 17.04.2018  
 Anwesend: Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Enzi Gert, Knappitsch Robert, Kobor Markus <br>
 Abwesend: Niemand <br> <br> <br>
 
## Fortsetzen des Projekts "Temperaturmessung"
In dieser einheit wurde das Projekt "Temperaturmessung fortgesetzt.
Dabei wurden bereits bestehende Methoden erweitert sowie neue Klassen erstellt.

Bis dato war unser Programm dazu in der Lage die am PC verfügabren Ports aufzulisten.
Außerdem war es bereits möglich sich mit dem Sure-Board, welches für die Temperaturmessung verwendet werden soll, zu verbinden.

## Erweiterungen vorhandener Methoden

### `updateSwingControls()`
```java
private void updateSwingControls() 
{
        jbutRefresh.setEnabled(true);
        jbutConnect.setEnabled(false);
        jbutDisconnect.setEnabled(false);
        jcbSerialDevice.setEnabled(false);
        jbutSingleMeasurement.setEnabled(false);
        jbutContinousMeasurement.setEnabled(false);
        jbutStopMeasurement.setEnabled(false);

        if (serialPort != null && serialPort.isOpened()) 
        {
            jbutRefresh.setEnabled(false);
            jbutDisconnect.setEnabled(true);
            jbutConnect.setEnabled(false);
            jbutSingleMeasurement.setEnabled(true);
            return;
        }

        if (jcbSerialDevice.getModel().getSize() > 0) 
        {
            jcbSerialDevice.setEnabled(true);
            jbutConnect.setEnabled(true);
        }

        if (activeWorker != null) 
        {
            jbutRefresh.setEnabled(false);
            jbutConnect.setEnabled(false);
            jbutDisconnect.setEnabled(false);
            jcbSerialDevice.setEnabled(false);
            jbutSingleMeasurement.setEnabled(false);
            jbutContinousMeasurement.setEnabled(false);
            jbutStopMeasurement.setEnabled(false);
            jlaTemperatur.setEnabled(false);
            setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
        } 
        else 
        {
            setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            jlaTemperatur.setEnabled(true);
        }
    }
```
Die Methode "updateSwingControls()" wurde um eine if-else Anweisung erweitert. (if (activeWorker != null))
Dadurch ist es während eine Messung durchgeführt wird nun nicht mehr möglich mit der GUI zu interagieren, da alle Swing-controls deaktiviert werden.
Der Cursor wird auf "Wait" gesetzt.
 
### `connectPort()`
```java
private void connectPort(String port) 
{
        serialPort = new jssc.SerialPort(port);
        try 
        {
            if (serialPort.openPort() == false) 
            {
                throw new jssc.SerialPortException(port, "openPort", "return value false");
            }
            if (serialPort.setParams(SerialPort.BAUDRATE_57600, SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_2, SerialPort.PARITY_NONE) == false) 
            {
                throw new jssc.SerialPortException(port, "setParams", "return value false");
            }
        } 
        catch (Throwable ex)
        {
            showThrowable(new Exception("Serielle Schnittstelle kann nicht geöffnet werden", ex));
            serialPort = null;
        }
        finally 
        {
            updateSwingControls();
        }
    }
```
Die Methode "connectPort()" wurde um die für die Übertragung der daten notwendigen Parameter erweitert:

 * BAUDRATE -> Die Symbolrate oder Baudrate ist in der digitalen Übertragungstechnik und Nachrichtentechnik die Anzahl der übertragenen Symbole pro Zeitspanne. Die Einheit „pro Sekunde“ dieser Rate wird als Baud bezeichnet, abgekürzt Bd, um sie z. B. von der Bitrate zu unterscheiden.
Außerdem wurde eine Fehlerbehandlung miteingebaut, die, wenn ein Fehler aufritt, eine "SerialPortException" wirft.
Quelle: Wikipeda

In unserem Fall beträgt diese 57600.

* DATABITS -> Bei Datenbits handelt es sich um die eigentlich zu übertragenden Informationseinheiten bei der Datenübertragung.

Wir übertragen 8 Databits.

* STOPBITS -> Stoppbits trennen die jeweilige Zeiteinheit von Daten auf einer asynchronen seriellen Verbindung.
Quelle: msdn.microsoft

Wir verwenden 2 Stopbits.

* PARITYBIT -> Ein Paritätsbit ist ein zeichendiskretes Prüfbit, das zur Fehlererkennung in der Paritätsprüfung eingesetzt wird. Das Paritätsbit wird zu den Datenbits hinzugefügt, wodurch die Bitsumme gerade oder ungerade wird. Empfangsseitig wird die Bitsumme überprüft. Entspricht die Bitsumme nicht der vorgegebenen Parität, - die beispielsweise gerade sein muss - dann liegt ein Übertragungsfehler vor.
Quelle: itwissen.info

In unserem Fall wird kein Paritybit verwendet.
