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

  ## Java
 
  Um unter Java zwischen Programm und Hardware zu kommunizieren, muss die JVM (Java Virtuelle Maschine)
  zwischengeschalten werden. Hierbei greift Java auf die virtuelle Maschine zu, dieses dann auf das
  Betriebssystem und das Betriebssystem anschließend auf die Hardware. Jedoch unterstützt die JVM
  keine seriellen Schnittstellen. Deshalb benötigt man das Java Native Interface (JNI), welches
  eine für Java lesbare .jar Datei erzeugt und eine lesbare Bibliothek erzeugt. 
  Außerdem haben wir in der Schule den Java Simple Serial Connector (JJSC) verwendet. Ein großer
  Vorteil davon liegt darin, dass die Bibliotheken automatisch richtig entpackt und verwendet werden.
  Früher gab es auch noch die Java.comm. Diese könnte man zwar heute auch noch installieren, jedoch
  ist die nur auf einem System lauffähig, was natürlich ein großer Nachteil ist.
