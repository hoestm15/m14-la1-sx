# 6.Protokoll  
  
  **Name**:  *Lukas Strauß*  
  **Datum:** *09.01.2018*  
  **Uhrzeit:** *9:40-12:25*  
  **Gruppe:** *4* 
  
  **Abwesend:** --  
 **Anwesend:** Strauß Lukas,Strutz Sebastian,Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz
 
 
 # Aufgabenstellung

Es soll eine Temperaturmessung mit dem integrierten Temperatursensor am Sure Board erfolgen. 
Das Messergebnis soll über eine Java Visualisierung am PC ausgegeben werden.



## Exceptions in JAVA

Exception ist eine Klass3, die von Throwable abgeleitet wird. Diese wird wiederrum von der Klasse Object abgeleitet. Bei schweren Fehler wird in der Java Virtual Machine ein Fehler (Error) erzeugt, der zum Absturz des Programms führt.

Diese Errors werden von JSSC geworfen und müssen wieder weiter geworfen werden, wenn nur Exception abgefangen werden.

Throw new exception --> throws Exception
Es gibt 2 Möglichkeiten wie man Errors und oder exceptions behandeln kann. Entweder wird ein Multicatch verwendet oder es werden alle Throwables abgefangen.




## Feldbussysteme bzw Modbus WH
  
  Unter Feldbussen versteht man Kommunikationssysteme, diese können verschiedene Geräte auf der 
  Feldebene miteinander verbinden.So erfolgt also der Datenaustausch über Sensoren(Messfühler) und Aktoren(Stellglieder).
  Häufig verwendet man Feldbusse in verbindung mit SPSen und das häufig in der Gebäudeautomatisierung.
  
  Bei dem Modbus handelt es sich um einen sogennanten offenen eldbus, der 1979 von Gould-Modicon zur Kommunikation 
  mit Ihren eigenen SPSen gemacht wurde.Man unterscheidet zwischen 3 verschiedenen Ebenen:  
  
   :point_right:  Modbus ASCII: Hier kann immer ein ASCII-Zeichen nach dem anderen gesendet werden (rein textuell)  
   
   :point_right:  Modbus RTU: Hier werden die Daten Binär übertragen  
   
   :point_right:  Modbus TCP: Hier werden TCP/IP-Pakete übertragen  
   
  
  Gearbeitet wird beim Modbus nach dem Server-Client Prinzip. Bei uns ist also der Server das Sure-Board einnimmt und 
  der PC bzw. unsere Applikation als Client arbeitet.
  
  ## Serielle Schnittstelle in Java
 
   Es ist garnicht so einfach in Java zwischen Hardware und Software zu kommunizieren. Dazu ist es nötig, das die 
   JVM --> Java Virtual Machine zwischengeschaltet wird. Hierbei greift Java auf die virtuelle Maschine zu, welche
   dann auf das Betriebssystem zugreift und anschließend greift das Betriebssystem auf die Hardware zu. 
   Jetzt ist es allerdings so, dass die JVM keine seriellen Schnittstellen unterstützt. Deshalb wird das
   Java Native Interface untertützt kurz JNI !
   Es wird eine für JAVA lesbare .jar Datei erzeugt und somit auch eine lesbare Bibliothek. Außerdem verwenden wir
   in der Schule den JSSC --> Java Simple Serial Connector (JJSC). Der größte Vorteil ist darin zu finden, dass die
   Bibliotheken automatisch richtig entpackt werden. 
   Man muss sich das so vorsstellen, das Java in einer Art Kreisform aufgabaut ist: Von außen nach Innen -->
   Hardware--  
   Betriebssystem--  
   JAVA VM --  
   Java Native Code
  
  
  
  
 
  
  

