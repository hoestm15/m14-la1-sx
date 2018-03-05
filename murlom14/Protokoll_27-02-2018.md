# Protokoll 27.02.2018
## 6. Einheit

Name: Muri Lorenz <br>
Klasse: 4AHME <br>
Gruppe: 2 <br>
Datum der Einheit: 6.2.2018 <br>
Anwesend: Nebel, Mandl, Martinak, Muri, Platzer, Mörth, Nabernik, Köhler<br>
Abwesend: - <br>

## Temperaturmessung (Teil 1) - Verbindung zum Sureboard
Das Ziel der Übung ist es einen Temperatursensor, welcher sich auf dem Sureboard befinedet mittels Java-Programm auszugeben.
Um von einem Surebard Daten an eine PC übertragen zukönnen wird ein entsprechendes Feldbusprotokoll benötig, wir verwenden bei dieser Übung Modbus, und ebenfalls die jSSC Library. [jSSC](https://github.com/scream3r/java-simple-serial-connector) ist eine einfache und plattformübergreifende serielle Kommunikationsbibliothek für Java. 

Für das Java-Prgramm wurde uns eine [Vorlage](https://github.com/HTLMechatronics/m14-la1-sx/blob/murlom14/murlom14/sx-la1-25c2c67.tar.gz) zur Verfügung gestellt.

### Quellcode

#### Klassenvariable
Mit Hilfe dieser Variable kann abgefragt werden ob ein Port geöffnet ist.
```java
private jssc.SerialPort serialPort;
```
#### SureModbusGUI (Konstruktor)
```java
public SureModbusGui () {
    initComponents();
    setLocationRelativeTo(null);    // Die GUI wird mittig am Bildschirmm ausgegeben
    jlaTemperatur.setText("? °C");  // Die Temperatur ist anfangs unbekannt (noch nicht mit Sureboard verbunden) 
    
    refresh();                      // Die Methode refresh(); wird aufgerufen
  }
```

