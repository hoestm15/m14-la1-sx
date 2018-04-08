# *Protokoll KW 11*

  Name: Markus Wieser   
  Klasse: 4AHME   
  Datum: 13.03.2018   
  Anwesend: Strauß Lukas, Strutz Sebastian, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz    
  Abwesend: -
  
  ## Feldbussysteme/Modbus
  
  Grundsätzlich sind Feldbusse Kommunikationssysteme, die Geräte auf der Feldebene miteinander verbinden.
  Damit kann man mit Sensoren und Aktoren Daten austauschen. Feldbusse werden häufig in der Fahrzeugtechnik,
  in der industriellen Automatisierung und in der Gebäudeautomatisierung verwendet.
  
  Das Kommunikationsprotokoll des Modbus ist ein zustandsloses Protokoll, welches auf dem Request/Response Prinzip aufgebaut ist.
  Der große Vorteil des Modbus-Protokolls liegt darin, dass sich andere Geräte mit unterschiedlichen Verbindungstechnologien     
  miteinander verbinden lassen. (Zum Beispiel eine Serielle Schnittstelle wie UART und ein Netzwerk wie TCP/IP)

  Es gibt drei unterschiedliche Varianten zur Datenübertragung:

  * Modbus ASCII   (textuelle byteweise Übertragung)     
  * Modbus RTU     (Remote Terminal Unit, binäre byteweise Übertragung)      
  * Modbus TCP     (Übertragung in TCP Paketen)   

  ## Serielle Schnittstelle Java
 
  Um unter Java zwischen Programm und Hardware zu kommunizieren, muss die JVM (Java Virtuelle Maschine)
  zwischengeschalten werden. Hierbei greift Java auf die virtuelle Maschine zu, dieses dann auf das
  Betriebssystem und das Betriebssystem anschließend auf die Hardware. Jedoch unterstützt die JVM
  keine seriellen Schnittstellen. Deshalb benötigt man das Java Native Interface (JNI), welches
  eine für Java lesbare .jar Datei erzeugt und eine lesbare Bibliothek erzeugt. 
  Außerdem haben wir in der Schule den Java Simple Serial Connector (JJSC) verwendet. Ein großer
  Vorteil davon liegt darin, dass die Bibliotheken automatisch richtig entpackt und verwendet werden.
  Früher gab es auch noch die Java.comm. Diese könnte man zwar heute auch noch installieren, jedoch
  ist die nur auf einem System lauffähig, was natürlich ein großer Nachteil ist.
  
  ## Installation
  
  Bei der Installation haben wir in der Schule in ein leeres Projekt, in welchem nur Handler Methoden
  zur Verfügung standen, das Package /usr/java/packages/lib/jssc.jar eingebunden. Danach haben wir
  ein Clean and Build durchgeführt und die build.xml bearbeitet. Dies machten wir um die Datei 
  wirklich aufzunehmen.
  
  ## Temperaturmessung
  
  Am Anfang luden wir den Modbusslave von unserem Server herunter und führten die sure.elf.hex
  Datei mit Hilfe des EasyProgrammer aus. Die GUI luden wir von einem Link auf LMS herunter
  und konnten diese anschließend einfach in NetBeans öffnen.

  ![Display](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/GUI.PNG)
  
  Steuerung der Buttons:
  
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

  ## Exception
  
  Exception ist eine Klasse welche von Throwable abgeleitet wird, welche wiederum von der Klasse Object abgeleitet wird.
  Bei schweren Fehlern wird in der JVM ein Error erzeugt, welcher zum Absturz des Programmes führt. Die Errors, welche
  von JSSC geworfen werden, müssen weitergeworfen werden, wenn nur Exceptions abgefangen werden. Hierfür gibt es zwei
  Lösungen. Entweder wird ein Multicatch verwendet oder es werden alle Throwables abgefangen. Mit beiden Varianten kann man 
  Errors und die Exceptions behandeln.
  
  

