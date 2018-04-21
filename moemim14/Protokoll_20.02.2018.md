# Protokoll 6 20.02.2018

## Thema: Atmel Studio

Name: Michael Mörth  
Klasse: 4AHME  
Gruppe: 2  

Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Moritz Martinak, Mario Nabernik, Muri Lorenz, Platzer Andreas, Marcel Köhler    
Abwesend: -

## JAVA-Projekt: Temperaturmessung
In der heutigen Stunde wandten wir das Wissen der letzten Stunde über den Modbus an. Unsere Aufgabe ist es,mittels eines SureBoards einen Temperatursensor zu bauen. Die Daten des Sensors sollen über einen Feldbus an den Computer übertragen werden. Die Daten sollenanschließend verarbeitet werden. Die übertragenen Daten sollen anschließend in einer mit Java-Swing-realisierten GUI visualisiert werden.

### GUI Vorlage
Zu Beginn mussten wir uns die Vorlage der GUI vom Server in Arnfels downloaden.
![GUI-Vorlage](https://github.com/HTLMechatronics/m14-la1-sx/blob/moemim14/moemim14/GUI-Temperaturmessung.png)

### Der Quellcode

#### Verwendete Variablen
Zu Beginn wurden zwei Variablen erstellt. Das Feld aus Strings mit dem Variablennamen `ports` dient dazu, alle Namen der gefundenen Ports zu speichern. Mit der Variable `serialPort` können wir anschließend abfragen, ob der Port geöffnet ist.
```java
  private String [] ports;
  private jssc.SerialPort serialPort;
```
