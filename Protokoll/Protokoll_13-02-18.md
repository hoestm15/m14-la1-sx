# Protokoll der 5. Einheit

## 5. Einheit

* Name: Mario Nabernik  
* Klasse: 4AHME  
* Datum 13.02.2018  
* Gruppe: 2  
* Anwesend:  Florian Nebel, Lorenz Muri, Moritz Martinak, Andreas Platzer, Gerhard Mandl  
* Abwesend: Marcel Köhler, Michael Mörth, Mario Nabernik(kurz anwesend)
* Thema: Modbus

# Vorwort
Da ich, Mario Nabernik, die letzte Einheit nicht vollständig besuchen konnte, habe ich das Protokoll für die Zeit, in der ich anwesend war, geschrieben. Das bedeutet, das Protokoll umfasst nicht die konmplette Einheit des 13.02.2018.

# Modbus
Modbus TCP/IP ist ein Client/Server-Protokoll für den verbindungsorientierten gesicherten Austausch von Prozessdaten. Dies bietet ein hohes Maß an Flexibilität für dezentrale Automatisierungsarchitekturen: Die Rollen des Clients und der Servers sind nicht fest zugeordnet. Jedes Gerät im Netzwerk kann beide Rollen spielen. Somit können Zugriffe auf Daten – lesend oder schreibend – flexibel den jeweiligen Aufgabenstellungen angepasst werden.

Anfänglich wurde der Modbus für die Kommunikation zwischen SPS-Geräten entwickelt, etablierte sich aber in der Industrie als De-Facto-Standard, da es sich wie bereits erwähnt um ein offenes Protokoll handelt. Seit 2007 ist die Version Modbus TCP Teil der IEC 61158. Es lassen sich sowohl RS-232 Netzwerke, sowie TCP/IP - Netzwerke aufbauen.

## Grundlagen
Mit einem Modbus kann ein Master mit mehreren Slaves verbunden werden. Es gibt die Mögichkeit von seriellen Schnittstellen und von Ethernet.

Die drei verschiedenen Betriebsarten der Datenübertragung:
* Modbus RTU
* Modbus ASCII
* Modbus TCP

Jeder Busteilnehmer besitzt eine eindeutige Adresse. Die Adresse 0 ist für den Broadcast reserviert. Es darf jeder Slave senden. Meistens wird jedoch über den Master initiiert.

> __Lese- und Schreibzugriffe sind auf folgende Objekttypen möglich:__

> | Objekttyp | Zugriff | Größe |
> |:---------:|:-------:|:-----:|
> | Einzelner Ein-/Ausgang „Coil“ | Lesen & Schreiben | 1-bit |
> | Einzelner Eingang „Discrete Input“ | nur Lesen |	1-bit |
> | (analoge) Eingänge „Input Register“ | nur Lesen |	16-bits |
> | (analoge) Ein-/Ausgänge „Holding Register“ | Lesen & Schreiben |	16-bits |

Quelle: [Wikipedia](https://de.wikipedia.org/wiki/Modbus)
