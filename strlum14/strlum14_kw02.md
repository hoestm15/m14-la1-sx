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

## Feldbussysteme bzw Modbus WH
  
  Unter Feldbussen versteht man Kommunikationssysteme, diese können verschiedene Geräte auf der 
  Feldebene miteinander verbinden.So erfolgt also der Datenaustausch über Sensoren(Messfühler) und Aktoren(Stellglieder).
  Häufig verwendet man Feldbusse in verbindung mit SPSen und das häufig in der Gebäudeautomatisierung.
  
  Bei dem Modbus handelt es sich um einen sogennanten offenen eldbus, der 1979 von Gould-Modicon zur Kommunikation mit Ihren      
  eigenen SPSen gemacht wurde.Man unterscheidet zwischen 3 verschiedenen Ebenen:  
  
   :point_right:  Modbus ASCII: Hier kann immer ein ASCII-Zeichen nach dem anderen gesendet werden (rein textuell)  
   
   :point_right:  Modbus RTU: Hier werden die Daten Binär übertragen  
   
   :point_right:  Modbus TCP: Hier werden TCP/IP-Pakete übertragen  
   
  
  Gearbeitet wird beim Modbus nach dem Server-Client Prinzip. Bei uns ist also der Server das Sure-Board einnimmt und 
  der PC bzw. unsere Applikation als Client arbeitet.
  
  
  
 
  
  

