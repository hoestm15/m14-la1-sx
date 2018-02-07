# Protokoll - 06.02.2018
Name: Michael Mörth  
Klasse: 4AHME  
Gruppe: 2  

Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Moritz Martinak, Mario Nabernik, Muri Lorenz, Platzer Andreas, Marcel Köhler    
Abwesend: -

## Wiederholung vom Compiliervorgang
### Compilevorgang
Zu Beginn der Stunde begannen wir damit, noch einmal den "Compilevorgang" zu besprechen.  
**Die Tabelle zeigt den Übersetzungsvorgang eines C-Programmes für den Atmega328p**  
Vorhaben | Befehl zum umwandeln | Beschreibung
--------------- | --------- | ---------
`main.c`zu `main.o` | avr-gcc -mmcu="atmega328p" -Os -c -DF_CPU=16000000L main.c | `-mmcu` gibt an um welches System es sich handelt .`-c` sorgt dafür das nur kompiliert wird (der Linker wird nicht gestartet). `-DF_CPU=16000000L` gibt die Taktfrequenz an.
