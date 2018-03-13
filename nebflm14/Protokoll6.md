# Protokoll der 6. Einheit (27.02.2018)

## Thema: 

Name:     Florian Nebel  
Klasse:   4AHME  
Gruppe:   2  

Anwesend: Köhler Marcel, Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: ---

Zu Beginn der Einheit luden wir den Modbusslave vom [Server](https://www.htl-mechatronik.at/svn/modbus/) herunter und führten die *sure.elf.hex*-Datei mit dem EasyProgrammer aus. Das Template zur grafische Oberfläche für die Temperaturanzeige konnten vom Server über einen am LMS liegenden Link herunterladen und mit NetBeans öffnen.
![Display](https://github.com/HTLMechatronics/nebflm14/)

##Java
![Hardwarezugriff](https://github.com/HTLMechatronics/m14-la1-sx/blob/nebflm14/nebflm14/Hardwarezugriff.jpg)
Grundsätzlich regelt das Betriebssystem z.B. Windows den Zugriff auf serielle Schnittstellen wie z.B. Uart oder USB. Ein C-Programm würde dierekt auf das Betribssystem zugreifen, welches dann mit der Hardware kommuniziert.
Unter Java wird zur Kommunikation zwischen Programm und Hardware eine virtuelle Maschine, die sogenannte **Java Virtuelle Maschine (JVM)** zwischengeschaltet. Die Idee: Java wendet sich an die virtuelle Machine, diese an das Betriebssystem, und dieses an die Hardware. Das Problem liegt darin, dass die JVM keine seriellen Schnittstellen unterstützt. Früher konnte man sich auf Maschinen des Herstellers Sun mit der Klasse **Java.comm** behelfen. Auch wenn man diese Software noch heute nachinstallieren könnte, wird diese nur mehr geringfügig eingesetzt, da sie nur auf einem System lauffähig wäre und dadurch die Multiplattformfähigkeit, eine der essentiellen Eigenschaften Javas verloren gehen.
Gelöst wird das Problem durch das **Java Native Interface (JNI)** welches innerhalb der virtuellen Maschine eine für Java lesbare .jar Datei erzeugt und außerhalb, eine für das Betriebssystem lesbare binäre Bibliothek aufbaut. **rxtx comm gnu.io** bezeichnet eine aufgrund von verbuggten C-Bibliotheken und schlechter Versionsverwaltung, sowie fehlender Nutzerfreundlichkeit nicht zu empfehlender Variante. **Java Simple Serial Connector (JSSC)** orientiert sich im Gegensatz dazu nicht an java.comm und dem streaming-Konzept. Einer der großen Vorteile liegt darin, das die binären Bibliotheken automatisch an der richtigen Stelle entpackt werden. Zuletzt veröffentlicht wurde die Version JSSC 2.8.1 experimetal. Aus Stabilitätsgründen verwenden wir im Unterricht JSSC 2.8.0. Unter NetBeans konnten wir nach dem Einbinden die Bibliotheken der unterschiedlichen Betriebssysteme erkennen.

## Installation
Um Nutzern eine ausführbare Datei zur Verfügung stellen zu können, haben wir in unser momentan leeres NetBeans-Projekt, in welchem nur die handler-Methoden enthalten waren, über die Projekt-Properties das Package */usr/java/packages/lib/jssc.jar* eingebunden. Nach dem durchführen eines "Clean&Build" wurde die Datei jssc-2.8.0.jar dem Ordner angefügt. Um die Datei tatsächlich in SureModbusTempG2.jar aufzunehmen bearbeiteten wir die build.xml-Datei.

## Temperaturmessung
Um Logikfehler im Programm zu vermeiden steuern wir die Aktivierung bzw. Deaktivierung aller Buttons in einer zentralen Methode:
```java
public void updateSwingControls () {
    jcbSerialDevice.setEnabled(flase);
    jbutConnect.setEneabled(false);
    jbutDisconnect.setEneabled(false);
    jbutRefresh.setEneabled(false);
    jbutSingleMeasurement.setEneabled(false);
    jbutContinousMeasurement.setEneabled(false);
    jbutStopMeasurement.setEneabled(false);
    
    if(serialPort != null && serialPort.isOpened()) {
      jbutDisconnect.setEnabled(true);
      return;
    }
      
    if(ports == null && ports.length == 0) {
        jbutRefresh.setEneabled(true);
    }
    else if(ports != null && ports.length > 0) {
        jcbSerialDevice.setEneabled(true);
	jbutConnect.setEneabled(true);
    }
}
```
Die Methode *updateSwingControls()* wird über die Methode *refresh()*, deren Aufruf sich im Konstruktor befindet, aufgerufen.
Die Mehode *refresh()* wird auch dann aufgerufen wenn der *Refresh-button* betätigt wird.
```java
setLocationRelativeTo(null);
jlabTemperatur.setText("? °C");
refresh();
```
Zuerst muss noch abgefragt werden, welche Schnittstellen zur Verfügung stehen und welche Geräte angeschlossen sind. Die dazu notwendigen Codesegmente sind der Java-Doc zu entnehmen.
```java
private void refresh {
    String [] ports = jssc.SerialPortList.getPortNames();
    updateSwingControls();
}
```
Eine Schnittstelle entspricht einem Interface, also einer Methodensammlung. Aus diesem Grund ist sie ableitber, jedoch nicht instanzierbar.
```java
jcbSerialDevice.setModel(new DefaultComboBoxModel<String>(ports));
```
*<E>* Generics typisieren Klassen. Wenn das Typisieren möglich ist, sollte es zur Fehlerverhinderung durch den Compiler auch getan werden.
Als nächstes wurde die lokale Variable String [] ports durch eine globale Variable im Quellcode ersetzt.

```java
private String [] ports;
private jssc.SerialPort serialPort;
```
Als nächstes werden die Methoden zum Verbinden und Trennen der Verbindung, welche beim betätigen der jeweiligen Buttons aufgerufen werden, realisiert.
```java
private void connect () {
    try{
        String port = (String)jcbSerialDevice.getSelectedItem();
        serialPort = new jssc.SerialPort(port);
        serialPort.openPort();
	updateSwingControls();
    } catch (Throwable th) {
        show Throwable("Serielle Schnittstelle kann nicht geöffnet werden", th);
    }
}
```

```java
private void disconnect () {
    try
    {
        serialPort.closePort();
	
    } 
    catch (Throwable th)
    {
        showThrowable("Fehler beim Schließen der Schnittstelle");
    }
    finally {
      serialPort = null;
      updateSwingControls();
    }
}
```
Für die Ausgabe der Fehler wurde eine eigene Methode erstellt.
```java
private showThrowable (String msg, Throwable th) {
  th.printStackTrace(System.err);
  JOptionPane.showMessageDialog(this, msg, "Fehler aufgetreten", JOptionPane.ERROR_MESSAGE);
}
```

## Exception
![Ableitungsbaum](https://github.com/HTLMechatronics/m14-la1-sx/blob/nebflm14/nebflm14/Exception.jpg)
Die Klasse [Exception](https://docs.oracle.com/javase/7/docs/api/java/lang/Exception.html) wird von der Klasse [Throwable](https://docs.oracle.com/javase/7/docs/api/java/lang/Throwable.html) abgeleitet, welche von der Klasse [Object](https://docs.oracle.com/javase/7/docs/api/java/lang/Object.html) abgeleitet wird. Eine weiter Ableitung von Throwable ist der [Error](https://docs.oracle.com/javase/7/docs/api/java/lang/Error.html). Ein solcher wird unter anderem bei schwerwiegenden Fehlern in der JVM erzeugt, nach welchen das Programm beendet wird. JSSC wirft Errors, welche weitergeworfen werden würden wenn nur Exeptions abgefangen werden würden und das Programm würde ohne Fehlermeldung auf GUI-Ebene schließen. Als Lösung bieten sich zwei Möglichkeiten an. Entweder es werden alle Throwables abgefangen, oder es wird ein Multicatch realisiert. In beiden Fällen könnten sowohl Errors, als auch Exceptions behandelt werden.
