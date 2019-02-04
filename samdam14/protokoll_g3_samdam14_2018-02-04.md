# _Protokoll Fünfte Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 04.02.2019**  
**Uhrzeit: 8:00-10:30**  
  
**Anwesenheit: Es waren alle Schüler anwesend!**  
  
**Thema: Datenbanken**  
  
-----------------------------------------------------------
  
### Aufruf Main.main();  
In TypeScript werden Programme Zeile für Zeile ausgeführt. Will man also eine Methode einer Klasse aufrufen, muss diese im Code zuerst definiert worden sein. Im jetzigen Zustand unseres REST-Servers wird unsere Main-Klasse nur erzeugt, aber nicht ausgeführt, da der Aufruf `Main.main ();` noch fehlt.  
```typescript

import { Server } from './server';

class Main {

    public static main () {
        new Server().start(8080);
    }
}

Main.main();
```
  
### Collections in Javascript / TypeScript  
Grundsätzlich gibt es in Javascript / TypeScript keine Collections wie in Java, da diese Strukturen durch andere Elemente dieser Programmiersprachen vorhanden sind und somit überflüssig wären.  
**ArrayList** und **LinkedList** aus Java sind in TypeScript durch **Felder** verfügbar, **Maps** können durch **Objekte** realisiert werden. Weiteres zu diesem Thema kann [hier](https://stackoverflow.com/questions/20699507/hashmap-arraylist-in-java-script) nachgelesen werden.  
  
### Datenbanken  
Eine Datenbank ist ein System zur elektronischen Datenverwaltung. Grundsätzlich kann man zwischen schematischen und nicht schematischen Datenbanken unterscheiden. Schematische Datenbanken haben eine klar definierte Struktur und sind daher sehr starr. Typische Programmiersprache für relationale DB ist **SQL**. Beispiele für schematische DB sind **Postgresql** oder **SQLite**.  
Nicht schematische DB werden für dynamischen Systeme benötigt, z.B. in den DB der sozialen Medien. Die Struktur ist nicht klar definiert und kann daher unterschiedlich sein. Beispiel für eine nicht schematische Db ist **MongoDB**.  
Weitere Informationen können [hier](https://stackoverflow.com/questions/20699507/hashmap-arraylist-in-java-script) nachgelesen werden.  
  
### Singleton  
Singleton ist in der Softwareentwicklung ein Entwurfsmuster das sicherstellt, dass es ein Objekt einer Klasse nur ein mal gibt und es so ein **Singleton (=Einzelstück)** ist. Dieses Einzelstück ist dann für gewöhnlich global verfügbar.  
Da eine Datenbank genau einmal existiert und nur Werte geändert werden, ist es sinnvoll, das Entwurfsmuster Singleton zu verwenden. Dies wird erreicht in dem der **Konstruktor private** ist und eine statische Methode **getInstance();** aufgerufen wird, die beim ersten Aufruf das Objekt erzeugt. Dieses Objekt wird in einer statischen Variable **instance** abgelegt.  
Weitere Informationen zu **Singleton** können [hier](https://de.wikipedia.org/wiki/Singleton_(Entwurfsmuster)) nachgelesen werden.  
  
### Änderungen am Code  
#### main.ts  
  
  
#### database.ts  
  
  
#### server.ts  
  
  
