# Protokoll KW 02
Name: Tuttner Raphael  
Klasse: 4AHME  
Datum: 09.01.2018  
Anwesend: Strauß Lukas, Strutz Sebastian, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz  
Abwesend: Keiner  

## Labortest
Am Anfang der Einheit haben wir einen Labortest geschrieben.  
Die Themengebiete waren **Makefiles** und **Modbus**.  

## Serielle Schnittstelle in JAVA
Damit man mit JAVA zwischen Programm und Hardware kommunizieren kann, muss man die JVM (Java Virtual Machine) nutzen. Da dies aber nativ nicht möglich ist, muss man zusätzlich die JNI (Java Nativ Interface) nutzen. Außerdem haben wir in der Schule noch den JSSC (Java Simple Serial Connector) verwendet.  

### Installation
Für die Installation haben wir zuerst ein leeres Projekt erstellt. Dieses hat nur Handler-Methoden beinhaltet. Dort haben wir dann das Package /usr/java/packages/lib/jssc.jar eingebunden und einen Clean Build durchgeführt. Danach haben wir die **build.xml** bearbeitet um sie wirklich aufzunehmen.  

## Temparaturmessungsprogramm
Zu Beginn haben wir die Datei **sure.elf.hex** und den **Modbusslave** von unserem Server heruntergeladen. Dann haben wir die sure.elf.hex mit dem EasyProgrammer auf unsere SureBoards geladen. Die GUI haben wir von einem Link, der uns auf LMS bereit gestellt wurde, heruntergeladen.  

![Bereitgestellte GUI](https://github.com/HTLMechatronics/m14-la1-sx/blob/tutram12/tutram12/GUI.PNG)  

Quellcode für die Buttons:  
 ```java
    private void updateSwingControls () {
    jcbSerialDevice.setEnabled(false);
    jbutRefresh.setEnabled(true);
    jbutConnect.setEnabled(false);
    jbutDisconnect.setEnabled(false);
    jbutSingleMeasurement.setEnabled(false);
    jbutContinousMeasurement.setEnabled(false);
    jbutStopMeasurement.setEnabled(false);
    
    if (jcbSerialDevice.getModel().getSize() > 0) {
      jcbSerialDevice.setEnabled(true);
      jbutConnect.setEnabled(true);
    }
    
    if (serialPort != null) {
      jbutConnect.setEnabled(false);
      jbutDisconnect.setEnabled(true);
      jbutRefresh.setEnabled(false);
      jcbSerialDevice.setEnabled(false);
    } else {
      jbutConnect.setEnabled(true);
      jbutDisconnect.setEnabled(false);
    }
  }

```
## Exceptions im Programm
Für die Exceptions haben wir eine von **Throwable** abgeleitete Klasse erstellt.  
Sollte ein schwerer Fehler auftretten, wird ein ERROR in der JVM erzeugt. Dieser führt zum **Programmabsturz**.  
Die von dem JSSC geworfenen ERROR's müssen weitergeworfen werden, wenn nur Exceptions abfangen werden sollten. In einem solchen Fall gibt es **zwei Lösungen**:  
* ein Multicatche
* oder alle Throwables abfangen.  

Mit beiden Varianten kann anfallende Exceptions und ERROR's behandeln.
