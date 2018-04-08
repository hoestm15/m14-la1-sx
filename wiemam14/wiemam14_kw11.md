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



