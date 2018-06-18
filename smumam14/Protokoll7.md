# Laborprotokoll  
Sechste Einheit am 20. März 2018  
Martin Schmuck  
4AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster

## Thema der Einheit: Visualisirung eines Temperatursensors
In dieser Einheit schließen wir direkt an die letzte Einheit an.

  
#### Eigene Exception erstellen
Es ist ratsam, für mehrere ähnliche Fehlerfälle eigene Exception zu erstellen. Dies erleichert die Fehlersuche erheblich. Also erstellten wir eine eigene Exception für Fehler, die im Zuge einer Modbus-Übertragung auftreten können. Dies geschieht, in dem man die Klasse Exception ableitet. Hier ist das Listing der Klasse ModbusException:

```java
package gui;

public class ModbusException extends Exception
{

  final private int[] request;
  final private int[] response;


  public ModbusException (String message)
  {
    super(message);
    request = null;
    response = null;
  }


  public ModbusException (String message, Throwable cause)
  {
    super(message, cause);
    request = null;
    response = null;
  }


  public ModbusException (String message, int[] request)
  {
    super(message);
    this.request = request;
    response = null;
  }


  public ModbusException (String message, int[] request, int[] response)
  {
    super(message);
    this.request = request;
    this.response = response;
  }


  public int[] getRequest ()
  {
    return request;
  }


  public int[] getResponse ()
  {
    return response;
  }
}
```
#### Fehlerhandling
