# Protokoll
Gerhard Mandl  
5AHME, Gruppe 2  
14.01.2019  
Anwesend: Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: -

# Übung:REST-Server
## main.ts
In der main.ts wird die Klasse Server impotiert und ein Server auf dem Port 4711 gestartet.
Zum Schluss muss man noch die Funktion 'Main.main()' aufrufen, damit die Main-Klasse ausgeführt wird.
```typescript
import {Server} from './server';

class Main {

    public static main () {
        const server = new Server();
        server.start(4711);
    }
}

Main.main();
```
