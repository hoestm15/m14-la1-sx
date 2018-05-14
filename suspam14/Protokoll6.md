# Protokoll 6: Visualisierung eines Temperatursensors
Name: Patrick Schuster  
Klasse: 4AHME  
Gruppe: 3    
Anwesend: Reinbacher, Sackl R.,  Schmuck, Schuster  
Abwesend: Ruffenacht, Sammer, Sackl M.

# Aufgabenstellung
Es soll eine Java Swibng GUI zur Visualisierung eines Temperatursensors erstellt werden. Mit Hilfe der GUi soll man sich mit dem Sure Board verbinden können und die Messdaten des Temperatursensors auslesen können. Für die Verbindung zwischen Java GUI und PC soll das Feldbussystem Modbus verwendet werden. Dieser wurde bereits in der vorigen Einheit besprochen. [Protokoll zu Modbus]( m14-la1-sx/suspam14/Protokoll5.md )

## SureBoard Programm
Das Programm für das Sureboard, dass den Temperatursensor ausliest und als Modbus-Slave agiert, wurde vom Server in Arnfels bezogen. Wir haben es mit dem EasyProgrammer auf das SureBoard gespielt.

## GUI 
Um Zeit zu sparen haben wir die GUI-Vorlage vom Server in Arnfels bezogen. In dieser ist der visuelle Teil der GUI bereits fertig. Die einzelnen Methoden für die Datenübertragung und Verbindung mussten noch ausprogrammiert werden.
![](https://github.com/suspam14/la1/blob/master/GUI-Temperaturmessung.png)

### Quellcode



