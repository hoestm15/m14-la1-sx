# Protokoll 14.01.2018

## 3. Einheit
Name: Muri Lorenz <br>
Klasse: 5AHME <br>
Gruppe: 2 <br>
Datum der Einheit: 14.01.2018 <br> 
Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Mario Nabernik, Muri Lorenz, Platzer Andreas, Moritz Martinak <br>
Abwesend: - <br>

## Thema: REST - Server

### Wiederholung der letzten Einheit
Am Anfang der dritten Einheit wurden die Protokolle der zweiten Einheit besprochen. Anschließend wiederholten wir den transpilier und den kompilier Vorgang, das json Datenformat und wir gingen die Einrichtung von Visual Studio Code noch einmal durch. <br> <br>

### Prgrammierung
Nach der Wiederholung der letzten Einheit begannen wir mit der Programmierung des REST-Servers fortzusetzen.

####  main.ts
```typescript
import { Server } from './server';          // Es wird die Kalsse Server impotiert

class Main {                                // main wird erzeugt/angelegt
public static main () {

    const server = new Server();            // legt einen Server an
    server.start(8080);                     // startet einen Server auf dem Port 8080
    }
}

Main.main();                                // Main führt die main aus
```
Diese Main Klasse ist dazu da einen Server am Port 8080 anzulegen. Durch den Aufruf am Ende der Main wird erst die Methode main ausgeführt und nicht nur angelegt.
