# Protokoll 14.01.2019  

## 3. Einheit  

## Thema: Typescript

Name: Moritz Martinak  
Lehrer: sx  
Gruppe: 2  
Übungsdatum: 14.01.2019  
Abwesend: -  

## Rest-Server  

Als erstes Übungsprogramm haben wir einen einfachen Server mit einer Schülerdatenbank programmiert. 

### main.ts  
```javascript
import { Server } from './server';

class Main {
    public static main () {
        const server = new Server();
        server.start(4711);
    }
}

Main.main();```
