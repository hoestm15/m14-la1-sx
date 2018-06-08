# Protokoll 6 24.04.2018

Name: Michael Mörth  
Klasse: 4AHME  
Gruppe: 2  

Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Moritz Martinak, Mario Nabernik, Muri Lorenz, Platzer Andreas, Marcel Köhler    
Abwesend: -

## Kurze Wiederholung der letzten Einheit
### Java Native Interface ([JNI](https://de.wikipedia.org/wiki/Java_Native_Interface))
> Java Native Interface (JNI) ist eine standardisierte **Anwendungsprogrammierschnittstelle** (API), die die Möglichkeit schafft, aus der Programmiersprache Java heraus Plattform-spezifische Funktionen bzw. Methoden aufzurufen.
Im Gegensatz zu gewöhnlichen Java-Programmen ist ein Java-Programm, das JNI-Aufrufe verwendet, nur dann plattformunabhängig, wenn die native **Programmbibliothek auf allen Plattformen verfügbar ist**. <

> JNI ermöglicht es, native Methoden zu schreiben für Situationen, in denen es **nicht möglich ist**, **ausschließlich Java** als Programmiersprache einzusetzen. Dies ist der Fall, wenn beispielsweise die Standard-Java-Klassenbibliothek bestimmte Plattform-abhängige Features oder andere Programmbibliotheken nicht unterstützt. Weiterhin ist es per JNI möglich, eine weitere **in einer anderen Programmiersprache programmierte Anwendung für Java zugreifbar zu machen**. Viele Klassen der Java-Standardbibliothek basieren auf JNI, um beispielsweise die Datei-Ein- und Ausgabe oder Soundwiedergabe zu ermöglichen. Indem Java Leistungs- und Plattform-abhängige Implementierungen in die Standardbibliothek integriert, kann der Java-Programmierer und -Nutzer diese Features in sicherer und Plattform-unabhängiger Weise nutzen. <

> Gelegentlich wird JNI als **Fluchttür** ("escape hatch") für Java-Entwickler bezeichnet, da es ihnen den Zugriff auf Funktionalitäten ermöglicht, der andernfalls über die Standard-Java-API nicht möglich wäre. Es stellt die Schnittstelle zu anderen Programmiersprachen wie C oder C++ dar. <

*Quelle: [Wikipedia](https://de.wikipedia.org/wiki/Java_Native_Interface)*

### Beschrechen der programmierten Methoden in der letzten Einheit
Nach der kurzen Wiederholung über JNI, haben wir damit begonnen, die Methoden, welche wir in der letzten Einheit programmiert hatten, noch einmal kurz durchzusprechen. 
Folgende Mehtoden wurden bereits realisiert:
  * Konstruktor
  * `showThrowable()`
  * `updateSwingControlls()`
  * `refresh()`
  * `connect()`
  * `disconnect()`
  * ActionPerformed Methoden
  
Für genaure Informationen zu den Methoden kann das [Protokoll der letzten Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/Protokoll_20.02.2018.md#der-quellcode) verwendet werden.

## Erweiterungen und Verbessereungen des Quellcodes
### Die Methode `connect()`
```java
  private void connect()
  {
    try //erstes try
    {
      String port = (String) jcbSerialDevice.getSelectedItem();
      serialPort = new jssc.SerialPort(port);
      serialPort.openPort();
      serialPort.setParams(
              SerialPort.BAUDRATE_57600,
              SerialPort.DATABITS_8,
              SerialPort.STOPBITS_2,
              SerialPort.PARITY_NONE);
      updateSwingControlles();
    }
    catch (Throwable th)
    {
      try //zweites try
      {
        if(serialPort != null && serialPort.isOpened())
          serialPort.closePort();
      }
      catch(Throwable th2)
      {
        th.addSuppressed(th2);
      }
      finally
      {
        updateSwingControlles();
      }
      showThrowable("Serielle Schnittstelle kann nicht geöffnet werden", th);
      serialPort = null;
    }    
  }
```
Die Funktion `connect()` wurde im Laufe der Stunde erweitert. Unter anderem wurden die Parameter für die serielle Schnittstelle 
