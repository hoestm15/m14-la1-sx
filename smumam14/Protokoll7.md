# Laborprotokoll  
Sechste Einheit am 20. März 2018  
Martin Schmuck  
4AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster

## Thema der Einheit: Visualisirung eines Temperatursensors
In dieser Einheit schließen wir direkt an die letzte Einheit an.

  
#### Eigene Exception erstellen
Es ist ratsam, für mehrere ähnliche Fehlerfälle eigene Exception zu erstellen. Dies erleichert die Fehlersuche erheblich. Also erstellten wir eine eigene Exception für Fehler, die im Zuge einer Modbus-Übertragung auftreten können. Hier ist das Listing der Klasse ModbusException:

