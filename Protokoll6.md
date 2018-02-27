# Protokoll der 6. Einheit (27.02.2018)

## Thema: 

Name:     Florian Nebel  
Klasse:   4AHME  
Gruppe:   2  

Anwesend: Köhler Marcel, Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: ---

[Modbusslave](https://www.htl-mechatronik.at/svn/modbus/)
sure_modbusslave
sure.elf.hex herunterladen
easyprogrammer öffnen
sure.elf.hex auswählen
Start
Template mit gezeichneter Grafik aus Github(LMS) holen
Vorlage Java Programm für Modbus Temp mit snapshot speichern
Projekt mit Netbeans öffnen
Grafische Oberfläche zur Temperaturmessung erscheint
Projekt umbenennen ("Vorlage" entfernen)

## Java
Hardware Uart(Serielle Schnittstelle)
	USB
Betriebssystem sorgt für Zugriff
	C-Programm würde auf Betriebssystem zugreifen, welches dann auf Hardware zugreift
Javavirtuellemachine
Idee: Java Programm wendet sich an JVM, an OS, an HW
Problem: JVM unterstützt keine serielle Schnittstelle
java.comm früher auf sun-machinen, nicht auf anderen Systemen
	(würde Multiplattformfähigkeit zerstören)
kann heute unter selben Einschränkungen nachinstalliert werden
Java native Interface baut binäre Bibliothek außerhalb der JVM und für JVM lesbare Datei jar innerhalb
rxtxcomm gnu.io
	Problem: C-Bibliotheken verbuggt, schlechte Versionsorganisation, Dateien mussten händisch positioniert werden
Java Simple Serial Connector JSSC, orientiert sich nicht an java.comm und streaming-Konzept
	Vorteil: in jar File sind binäre Bibliotheken enthalten welche automatisch an richtiger Stelle entpackt werden
JSSC 2.8.0	Files, jar-Datei (2.8.1 experimental)
jar Datei (zip-Datei) META-INF ordner, Manifest-Datei
	JVM jar Datei übergeben und damit Programm ausführen
Class unter jssc
3.Ordner libs (Bibliotheken für unterschiedliche Betriebssysteme).so Dateien unter linux

## Installation
leeres projekt (handler Methoden enthalten)
/usr/java/packages/lib  jssc.jar
Project Properties add jar (jssc.jar)
nach clean&build wird dist (Distribution) ordner mit lib/jssc-2.8.0.jar hinzugefügt
buld.xml bearbeiten damit jssc*.jar in SureModbusTempG2.jar aufgenommen wird


## SURE-Board Temperatur
Buttons durch eine Zentrale Methode aktivieren/deaktivieren in abhängigkeit zum Zustand des Programms um Logikfehler zu vermeiden
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

Aufruf in Constructor:
```java
setLocationRelativeTo(null);
jlabTemperatur.setText("? °C");
refresh();
```
(Java-Doc zur Hilfe nehmen)
Überprüfen welche Geräte angeschlossen sind
Welche Schnittstellen stehen zur Verfügung?
```java
private void refresh {
    /*String*/ [] ports = jssc.SerialPortList.getPortNames(); //wird durch Objekt private String [] ports abgelöst
    updateSwingControls();
}
```
im Debugging-Modus überprüfen welchen inhalt "ports" besitzt (Schnittstellen werden angezeigt)
Schnittstelle=Interface(Methodensammlung) ableitbar, nicht instanzierbar
```java
jcbSerialDevice.setModel(new DefaultComboBoxModel<String>(ports));
```
<E> Klassen typisieren (Generics) wichtig für Fehlerverhinderung durch Compiler
	wenn möglich hinzufügen
Ports nicht lokal sondern als object abspeichern
```java
private String [] ports;
private jssc.SerialPort serialPort;
```
Beim drücken des refresh But
```java
refresh();
```
Verbinden
	jbutConnectActionPerformed
	{
	    connect();
	}
	
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
    

```java
private showThrowable (String msg, Throwable th) {
  th.printStackTrace(System.err);
  JOptionPane.showMessageDialog(this, msg, "Fehler aufgetreten", JOptionPane.ERROR_MESSAGE);
}
```
Exeptionhandling bei Schnittstellenabfrage hinzufügen

## Ableitungsbaum Fehlerklassen (Baum zeichnen)
Exception abgeleitet von Throwable, abgeleitet von Object
davon abgeleitet: RuntimeException
unter anderem von Throwable abgeleitet: Error wird bei schwerwiegenden Fehlern in VM erzeugt, Programm beenden
Fehler der jssc werden als Error geworfen (wird weitergeworfen wenn nur Exceptions gefangen werden) Programm würde ohne Fehlermeldung auf GUI-Ebene beendet werden, Fehlermeldung nur im Terminal
Deshalb: Throwable (Error und Exception) fangen und ausgeben
andere Möglichkeit: Multicatch
