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
 *localhost:8080*. Allgemein ist ein Restserver, bei dem zwei Maschinen miteinander kommunizieren. Man muss **Main.main()** extern aufrufen, da nicht automatisch eingesprungen wird.  
 
```typescript    
 import { Server } from './server';

class Main {
    public static main () {
        new Server().start(8080);
    }
}

Main.main();
```  
 ## Datenbanken  
 Datenbanken sind System zur elektronischen Datenverwaltung. Sie besteht immer aus einer Datenbankmanagementsystem und einer Datenbasis.  
 Man kann grob zwischen zwei Datenbanken unterscheiden: schmeatischen DB und nicht schematische DB, welche beide **Relationale DB** sind.    
 
 Art | Typ | Software | Eigenschaft | Link  
 --- | --- | -------- | ----------- | ----  
 schematische DB | SQL | PostgreSQL| effizient für große Datenmengen | [PostgreSQL](https://de.wikipedia.org/wiki/PostgreSQL)  
 nicht schematische DB | noSQL | MongoDB | effizient für ständige Änderungen der Daten | [MongoDB](https://de.wikipedia.org/wiki/MongoDB)      
 
Bei MongoDB ist zu sagen, dass es rund alle drei Monate eine neue Version gibt und deshalb ab und zu einige Schwierigkeiten. Noch dazu ist es eine sehr junge Sprache.  
   
 ## Collections   
 **Java**
 * ArrayList  
 * LinkedList  
 * Feld  
 * Set keine doppelten Elemente  
 * Map über Key kann man Objekte ablegen und herausholen     
 
 **Javascript**  
 * Feld: keine eigenen Collections, da in Javascript auch normale Felder dynamisch sind (deckt ArrayList und LinkedList ab)  
 * Map: kann man unter Javascript mit gewöhnlichen Objekten realisieren (deckt Map von Java ab)    
   
 ## Singleton  
 Singleton ist ein Entwurfsmuster, welches sicherstellt, dass es nur ein Objekt gibt. Der Konstruktor ist private und es wird eine statische Methode **getInstance()** aufgerufen und in **instance** abgelegt.     
UML-Diagramm: ![Singleton](/reibem14/Singleton.png)   
