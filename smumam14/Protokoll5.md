# Laborprotokoll  
Dritte Einheit am 13. März 2018 
Martin Schmuck  
4AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: niemand 

## Thema der Einheit: Visualisirung eines Temperatursensors
#### Wiederholung der 4. Einheit  
Zunächst wiederholten wir den Stoff der lezten Einheit.   
C-Code ausführbar machen:
  1. Präprozessieren
  1. Kompilieren
  1. Assemblieren
  1. Linken
  1. (eventuell) in Hex-Datei umwandeln
  
Übersetzung mit make:
 * Das make-Tool steuert den Übersetzungsvorgang
 * make-Tool ruft makefiles auf, Übersetzung wird dadurch gesteuert
 * make-Tool überprüft Zeitstempel und sorgt so dafür, das nicht immer alles neu übersetzt werden muss, sondern gleichbleibende Teile übersprungen werden
 
## eigentliches Thema: Temperatursensor

Hier eine grobe Übersicht unseres Vorhabens: 
![bsb](https://github.com/HTLMechatronics/m14-la1-sx/blob/smumam14/smumam14/resources/shure_uebersicht.svg)
>(c) Martin Schmuck

Der Temperatursensor LM75A sitzt auf unserem SHURE-Board und ist mit dem µC mit I²C verbunden. Der PC, auf dem die Java Swing GUI läuft, greift über die interne Serielle Schnittstelle, den Seriell-USB-Wandler auf die USB-UART-Konvertierung auf dem SHURE-Board zu. Diese ist mit dem µC verbunden, welcher die Daten über I²C vom intelligenten Sensor ausliest. Die Daten sollen zwischen SHURE-Board und PC über einen Feldbus übertragen werden. 

:point_right: Java Swing:  
Java Swing ist eine einfache Möglichkeit, um in Java graphische Benutzerschnittstellen zu realisieren (= GUI). Der Vorteil liegt darin, dass es sehr einfach und schnell geht, sich in die Swing-Programmierung einzuarbeiten. Leider wird Java Swing aber seit ca. einem Jahrzehnt nicht mehr wirklich gepflegt. Der Nachfolger und eine alternative Lösung für noch komplexere GUI's wäre Java FX, welches wesentlich komplexer aufgebaut ist und bereits mehrere Wochen bis Monate Einarbeitung benötigt, um benutzt werden zu können. Generell besteht leider im Moment die Situation, dass Java seit der Übernahme vom eigentlichen Entwickler Sun Microsystems durch Oracle nur mehr halbherzig supported wird. 

:point_right: Intelligenter Sensor:  
Intelligent ist der Sensor deswegen, weil er schon einen fertigen Temperaturwert zurückliefert, das heißt, er muss irgendwie einen eingebauten Prozessor haben, welcher die Werte umrechenen kann. Im Gegensatz dazu würde ein unintelligenter Sensor (zB Pt100) einfach zB eine Spannung zwischen 0 und 10 Volt zurückliefern und mann müsste sich selbst um die Auswertung kümmern.
  
:point_right: Feldbus:  
folgende Felbusse sind unter anderem zur Zeit üblich:
* Automatisierungstechnik / Industrie:  
       * Powerlink (offen, Basis: Ethernet, echtzeitfähig) [B&R; 2001]  
       * Profibus [1989]  
* Automobilbereich  
       * CAN-Bus (Controller Area Network): anspruchsvolle Systeme, zB Motor-/Getriebesteuerung [Bosch, Intel; 1983]  
       * LIN (Local Interconnect Network): weniger anspruchsvolle Systeme, zB Fensterheber [Daimler, VW, BMW; 1999]  
       * FlexRay: möglicher Nachfolger von CAN [Daimler, BMW; 2000]
 * Haustechnik  
       * KNX (sehr kostspielig) [2002]  
       
       

