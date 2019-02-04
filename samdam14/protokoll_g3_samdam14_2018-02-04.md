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
Die Klasse **main.ts** wurde richtig gestellt. Dafür wurde der Import und der Methodenaufruf geändert. Außerdem wird die Funktion durch den Aufruf von `Main.main();` auch ausgeführt.  
```typescript
import { Server } from './server';

class Main {

    public static main () {
        new Server().start(8080);
    }
}

Main.main();
```
#### database.ts  
Die Klasse **database.ts** stellt unsere Datenbank dar und wurde nach dem **Singleton**-Schema programmiert. Um das Schema zu realisieren ist der Konstruktor *private* und es wurde die statische Methode **getInstance** erstellt. Darin wird überprüft, ob die gewünschte Instanz bereits vorhanden ist. Ist dies nicht der Fall, so wird eine neue Datenbank-Objekt für diese Instanz erzeugt.  
Außerdem wurden in dieser Klasse die Methoden **add**, **get** und **remove** ausprogrammiert, da dies wichtige Funktionen einer Datenbank sind.  
```typescript
import { Student } from './student';

export class Database {

    public static getInstance (): Database {
        if (!Database.instance) {
            Database.instance = new Database ();
        }
        return Database.instance;
    }

    private static instance: Database;

    private students: { [htlid: string]: Student} = {};

    private constructor () {
        this.add(new Student('samdam14', 'Sammer', 'Daniel'));
    }

    public add (s: Student) {
        this.students[s.getHtlid()] = s;
    }

    public get (htlid: string): Student {
        return this.students[htlid];
    }

    public remove (htlid: string) {
        delete this.students[htlid];
    }
}
```
#### server.ts  
In der Klasse **server.ts** wurde nur die Handler-Methode **handleGetStudent** bearbeitet. In einer konstanten Variable wird die Anfrage, die in der URL steht und durch den **bodyParser** für uns bereitgestellt wird, zwischengespeichert. Danach wird überprüft, ob der Schüler mit einer bestimmten *htlid* in der Datenbank vorhanden ist. Wenn dies der Fall ist, soll er ausgegeben werden. Ansonsten soll der Server mit einer ERROR-Meldung antworten.  
```typescript
import * as express from 'express';
import * as bodyParser from 'body-parser';
import { Database } from './database';

export class Server {

    private server: express.Express;

    constructor () {
        this.server = express();
        this.server.use(bodyParser.urlencoded({extended: false}));
        this.server.get('/status', (req, resp) => this.handleGetStatus(req, resp));
        this.server.get('/student', (req, resp) => this.handleGetStudent(req, resp));
        this.server.get('*', (req, resp) => this.handleGet(req, resp));
    }

    public start (port: number) {
        this.server.listen(port);
        console.log('Server auf Port ' + port + ' gestartet');
    }

    private handleGet (req: express.Request, resp: express.Response) {
        resp.status(400);
        resp.send('ERROR');
        // resp.send('Hallo');
        resp.end();
    }

    private handleGetStatus (req: express.Request, resp: express.Response) {
        resp.send('Server is running');
        resp.end();
    }

    private handleGetStudent (req: express.Request, resp: express.Response) {
        const s = Database.getInstance().get(req.query.htlid);

        if (s) {
            resp.json(s);
        } else {
            resp.status(404);
            resp.send('NOT FOUND');
        }
        resp.end();
    }
}
```
