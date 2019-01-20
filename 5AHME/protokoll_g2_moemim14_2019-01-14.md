# Protokoll
Michael Mörth  
5AHME, Gruppe 2  
14.01.19  
Anwesend: Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: -  

# Projekt: REST-Server
## Main.ts
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

Die Klasse `main.ts` importiert die Klasse `Server`.  
Die Methode `public static main()` startet einen Server auf dem Port 4711.  
Javascript arbeitet wie die Programmiersprache C das Programm von oben nach unten ab. Am Ende muss die Methode `Main.main()` aufgerufen werden, da die klasse `Main` ansonsten nicht ausgeführt wird, sondern nur erzeugt werden würde. 

## Server.ts
```typescript
import * as express from 'express';
import * as bodyParser from 'body-parser';
import { json } from 'body-parser';

export class Server {

    private _server: express.Express;

    constructor() {
        this._server = express();
        this._server.use(bodyParser.urlencoded());
        this._server.get('/version', (req, res, next) => {
            res.send('Version 1.0');
        });
        this._server.get('/student', (req, res, next) => this.handleGetStudent(req, res, next));
    }

    public start(port: number) {
        this._server.listen(port);
        console.log('Server auf Port ' + port + ' gestartet!');
    }

    public stop() {
        console.log('TO DO..');
    }

    private handleGetStudent(req: express.Request, res: express.Response, next: express.NextFunction) {
        console.log('query --> ' + req.query);
        console.log('GET..');
        res.json({surname: 'Martinak', firstname: 'Moritz'});
    }
}
```
**Express**  
In der Klasse `server.ts` wird das Modul **Express** importiert. Dieses Modul ermöglicht das Arbeiten mit **http** und **https**. Weitere Informationen zu Express können [hier](https://www.npmjs.com/package/express) nachgelesen werden.  
Das Schlüsselwort `export` wird verwendet, da die Klasse `Server` in der Klasse `Main` importiert wird.
Das Modul kann mit `npm install express` und `npm install --save-dev @types/express` installiert werden.  

**Body-Parser**  
Der Body-Parser stellt Informationen zu einer Variable zur Verfügung. Genaueres kann [hier](https://www.npmjs.com/package/body-parser) nachgelesen werden.   
Das Modul kann mit `npm install body-parser` und `npm install --save-dev @types/body-parser` installiert werden.

Die Variable `_server: express.Express` wird benötogt um den Server aufbauen zu können. Wichtig hierbei ist es, dass beim Angeben des Datentyps **Express** alleine nicht ausreicht.  
Der Konstruktor werden die Handler-Methoden `localhost:4711/version` und `localhost:4711/student` realisiert.  
Mit der Methode `start(port: number)` wird der Server gestartet.  
Die Handler-Methode `handleGetStudent` definiert, eie der Server reagiert, falls die Anfrage `/student` eintrifft.

## Student.ts
```typescript
export class Student {

    public surname: string;
    public firstname: string;
    public id: string;

    constructor (id: string, surname: string, firstname: string ) {
        this.id = id;
        this.surname = surname;
        this.firstname = firstname;
    }
}
```

`students.ts` ist unsere Datenerhaltungsklasse für einen Schüler. Anders als in Java sind die Datenelemente public und es gibt keine Geter etc.

## db-user.ts
```typescript
import { Student } from './student';

export class DbUser {

    public static  getInstance (): DbUser {
        if (DbUser.getInstance === null) {
            DbUser.instance = new DbUser();
        }
        return DbUser.instance;
    }

    private static instance: DbUser;

    // **********************************

    private _students: {
        [ id: string]: Student
    };

    private constructor () {
        this._students = {};

        let s = new Student('mangem13', 'Mandl', 'Gerhard');
        this._students[s.id] = s;

        s = new Student('marmom13', 'Martinak', 'Moritz');
        this._students[s.id] = s;

        s = new Student('nabmam14', 'Nabernik', 'Mario');
        this._students[s.id] = s;
    }

    public get(id: string): Student {
        return this._students[id];
    }
}
```

### Singleton
  > Das Singleton (selten auch Einzelstück genannt) ist ein in der Softwareentwicklung eingesetztes Entwurfsmuster und gehört zur Kategorie der Erzeugungsmuster (engl. creational patterns). Es stellt sicher, dass von einer Klasse genau ein Objekt existiert.[1] Dieses Singleton ist darüber hinaus üblicherweise global verfügbar. Das Muster ist eines der von der sogenannten Viererbande (GoF) publizierten Muster.  
  *Quelle: [Wikipedia](https://de.wikipedia.org/wiki/Singleton_(Entwurfsmuster))*

Eine Datenbank sollte immer nur einmal existieren und es sollen Werte nur gelöscht/geändert/hinzugefügt werden können. Darum ist es sinnvoll, dass das Entwurfsmuster **Singleton** angewendet wird. Singleton kann umgesetzt werden, indem der Konstruktor **private** ist und eine statische Methode `getInstance()` aufgerufen wird. Diese Methode erzeugt beim ersten Aufruf das Objekt in der statischen Objektvariable `instance:DbUser`. Ist das Objekt einmal angelegt worden, wird nur mehr auf die Variable zugegriffen und kein neues Objekt erstellt.  
Im Konstruktor werden drei Schüler angelegt.  

### ArrayList und HashMap in Javascrip
Anders als in Java gibt es in JavaScript keine Klassen wie `ArrayList` oder `HashMap`. In JavaScript können hierzu ganz noramele Arrays und Objekte verwendet werden. Genaueres kann man [hier](https://stackoverflow.com/questions/20699507/hashmap-arraylist-in-java-script) nachlesen.
