# Protokoll 12.02.2018
## 5. Einheit

Name: Muri Lorenz <br>
Klasse: 4AHME <br>
Gruppe: 2 <br>
Datum der Einheit: 6.2.2018 <br>
Anwesend: Nebel Florian, Mandl Gerhard,  Moritz Martinak,  Muri Lorenz, Platzer Andreas <br>
Abwesend: Michael Mörth, Mario Nabernik, Marcel Köhler <br>

## Feldbus-Systeme
> Ein Feldbus ist ein Bussystem, das in einer Anlage Feldgeräte wie Messfühler (Sensoren) und Stellglieder (Aktoren) zwecks Kommunikation mit einem Automatisierungsgerät verbindet. Wenn mehrere Kommunikationsteilnehmer ihre Nachrichten über dieselbe Leitung senden, dann muss festgelegt sein, wer (Kennung) was (Messwert, Befehl) wann (Initiative) sagt. Hierfür gibt es normierte Protokolle.

Quelle: [Wikipadia](https://de.wikipedia.org/wiki/Feldbus)

**Beispiele für Feldbus-Systeme**
* PROFIBUS (Anlagenbau, Robotik, ...) 
* PowerLink
* CAN (Atomotive-Bereich)
* Modbus
* ...

## Modbus
Mit Hilfe des Modbus kann ein "Master" mit mehreren "Slaves" kommunizieren.
Der "Master" ist zum Beispiel ein Computer, dieser kann mit mehreren "Slaves" wie zum Beispiel Sensoren oder Aktoren Daten austauschen. 
Jeder Slave besitzt eine bestimmte Adresse (mit 1 beginnend) durch diese Adresse kann der Master entscheiden von welchem Slave er gerade Daten erhalten möchte.

![Modbus-Darstellung](https://technologyuk.net/telecommunications/industrial-networks/modbus.shtml)

Die Daten können über drei Arten übertragen werden:
* Modbus RTU
* Modbus ASCII
* Modbus TCP
