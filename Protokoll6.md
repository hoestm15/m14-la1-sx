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
}
```

Aufruf in Constructor:
```java
updateSwingControls();
setLocationRelativeTo(null);
jlabTemperatur.setText("? °C");
```

Überprüfen welche Geräte angeschlossen sind
Welche Schnittstellen stehen zur Verfügung?
```java
String [] port = jssc.SerialPortList.getPortNames();
```




