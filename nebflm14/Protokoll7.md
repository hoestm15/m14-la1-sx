# Protokoll der 7. Einheit (24.04.2018)  
Name:     Florian Nebel  
Klasse:   4AHME  
Gruppe:   2  

Anwesend: Köhler Marcel, Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: ---  

## Java Native Interface  
![Hardwarezugriff](https://github.com/HTLMechatronics/m14-la1-sx/blob/nebflm14/nebflm14/Hardwarezugriff.svg)  
Grundsätzlich regelt das Betriebssystem z.B. Windows den Zugriff auf serielle Schnittstellen wie z.B. Uart oder USB. Ein C-Programm würde dierekt auf das Betribssystem zugreifen, welches dann mit der Hardware kommuniziert.
Unter Java wird zur Kommunikation zwischen Programm und Hardware eine virtuelle Maschine, die sogenannte **Java Virtuelle Maschine (JVM)** zwischengeschaltet.  
Die Idee: Java wendet sich an die virtuelle Machine, diese an das Betriebssystem, und dieses an die Hardware. Das Problem liegt darin, dass die JVM keine seriellen Schnittstellen unterstützt. Früher konnte man sich auf Maschinen des Herstellers Sun mit der Klasse **Java.comm** behelfen. Auch wenn man diese Software noch heute nachinstallieren könnte, wird diese nur mehr geringfügig eingesetzt, da sie nur auf einem System lauffähig wäre und dadurch die Multiplattformfähigkeit, eine der essentiellen Eigenschaften Javas verloren gehen würden.  
Gelöst wird das Problem durch das **Java Native Interface (JNI)** welches innerhalb der virtuellen Maschine eine für Java lesbare \*.jar Datei erzeugt und außerhalb, eine für das Betriebssystem lesbare binäre Bibliothek aufbaut. **rxtx comm gnu.io** bezeichnet eine aufgrund von verbuggten C-Bibliotheken und schlechter Versionsverwaltung, sowie fehlender Nutzerfreundlichkeit nicht zu empfehlende Variante. **Java Simple Serial Connector (JSSC)** orientiert sich im Gegensatz dazu nicht an java.comm und dem streaming-Konzept. Einer der großen Vorteile liegt darin, das die binären Bibliotheken automatisch an der richtigen Stelle entpackt werden. Aus Stabilitätsgründen verwenden wir im Unterricht JSSC 2.8.0 und nicht die aktuellste Version JSSC 2.8.1 experimental.  
Unter NetBeans konnten wir nach dem Einbinden die Bibliotheken der unterschiedlichen Betriebssysteme erkennen.
