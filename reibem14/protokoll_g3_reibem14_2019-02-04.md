# 5.Protokoll  
  
  **Name**:  *Bernhard Reinbacher*  
  **Datum:** *04.02.2019*  
  **Uhrzeit:** *8:00 - 10:30*  
  **Gruppe:** *3*  
  
   
    
 **Abwesend:** niemand  
 **Anwesend:** Bernhard Reinbacher, Ruffenacht Florian, Sackl Martin, Sackl Roland, Schmuck Martin, Sammer Daniel, Schuster Patrick   
 ********************************************************************************************************************************  
 ## Main.ts   
 Der Restsever ist ab nun lauffähig. Er wird mit *new Server().start(8080)* auf Port 8080 gestartet. Aufrufen kann man ihn über  
 *localhost:8080*. Allgemein ist ein Restserver, bei dem zwei Maschinen miteinander kommunizieren.
```typescript    
 import { Server } from './server';

class Main {
    public static main () {
        new Server().start(8080);
    }
}

Main.main();
 ´´´  
 ## Datenbanken  
 Datenbanken sind System zur elektronischen Datenverwaltung. Sie besteht immer aus einer Datenbankmanagementsystem und einer Datenbasis.  
 Man kann grob zwischen zwei Datenbanken unterscheiden: schmeatischen DB und nicht schematische DB, welche beide **Relationale DB sind.  
 Art | Sprache | Eigenschaft | Link  
 --- | ------- | ----------- | ----  
 Schematische DB | SQL | PostgresSQL 
