# Protokoll KW 15
Name: Kilian Waltl
Klasse: 4AHME  
Datum: 10.04.2018  
Anwesend: Strauß Lukas, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz  
Abwesend: Strutz Sebastian  

## Java Theorie

### Klassen

Interface: Ein Interface ist eine Sammlung von Methoden welche nur aus dem Methodenkopf bestehen.

Abstrakte Klasse: Eine "unfertige Klasse", wird verwendet um mehrere änhliche Klassen zu erstellen, worin man dann nur mehr einige Methoden ausimplementieren muss.

Interne Klasse: Eine Klasse in einer Klasse, hat den Vorteil, dass alle Attribute der äußeren Klasse übernommen werden.

Anonyme Klasse: Hat keinen eigenen Klassennamen, nur "new", einfachste Java Klasse.

### Vererbung in Java

In Java kann eine Klasse die Methoden einer so genannten Elternklasse übernehmen --> Vererbung
Jedoch gibt es in Java nur Einfachvererbungen im gegesatz zu zum Beispiel C++.
Eine Kindklasse kann nur eine Elternklasse haben, eine Elternklasse kann allerdings mehrere Kindklassen haben.
Dies hat den Vorteil, dass es nicht zu verwirrung kommen kann, wenn man zwei Methoden mit dem gleichen Namen aus verschiedenen Elternklassen erbt.

### JSSC

Um unter Java zwischen Programm und Hardware zu kommunizieren, muss die JVM (Java Virtuelle Maschine)
  zwischengeschalten werden. Hierbei greift Java auf die virtuelle Maschine zu, dieses dann auf das Betriebystem und das Betriebssystem anschließend auf die Hardware. Jedoch unterstützt die JVM eine seriellen Schnittstellen. Deshalb benötigt man das Java Native Interface (JNI), welches eine für Java lesbare .jar Datei erzeugt und eine lesbare Bibliothek erzeugt. Außerdem haben wir in der Schule den Java Simple Serial Connector (JJSC) verwendet. Ein großer Vorteil davon liegt darin, dass die Bibliotheken automatisch richtig entpackt und verwendet werden. Früher gab es auch noch die Java.comm. Diese könnte man zwar heute auch noch installieren, jedoch ist die nur auf einem System lauffähig, was natürlich ein großer Nachteil ist.


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
Hier wird, wenn der Listener des Buttons "jbutSingleMeasurement" angesprochen wird, von der internen Klasse "MySingleMeasurementWorker" in kombination mit der Methode "execute()" ein Objekt erstellt.
