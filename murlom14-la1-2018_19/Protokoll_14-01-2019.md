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
Diese Main Klasse ist dazu da einen Server am Port 8080 anzulegen. Durch den Aufruf am Ende der Main wird erst die Methode main ausgeführt und nicht nur angelegt. <br>

#### server.ts
```typescript
import * as express from 'express';             // ein Framework für HTTP
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
        console.log('Da müss am noch ran');
    }

    private handleGetStudent(req: express.Request, res: express.Response, next: express.NextFunction) {
        console.log('query --> ' + req.query);
        console.log('GET..');
        res.json({surname: 'Platzer', firstname: 'Andreas'});
    }
}
```
**Express**  
Die Klasse `server.ts` importiert das Modul **Express**. Dieses Modul ist ein Framework welches das Arbeiten mit **http** und **https** ermöglicht. Man muss **Express** mit `npm install express` und `npm install --save-dev @types/express` installieren.  

**Body-Parser**  
Diese body-parser Modul analysiert die JSON -, Puffer -, string-und URL-kodierte Daten, mit HTTP POST Anfrage.
Das Modul kann mit `npm install body-parser` und `npm install --save-dev @types/body-parser` installiert werden.  
Um den Body-Parser verwenden zu können muss er dem Server übergeben werden `this._server.use(bodyParser.urlencoded())`. <br>

Der Konstruktor werden die Handler-Methoden `localhost:8080/version` und `localhost:4711/student` realisiert.  
Mit der Methode `start(port: number)` wird der Server gestartet.  
Die Handler-Methode `handleGetStudent` beschreibt wie der Server bei einer Anfrage von `/student` reagieren soll.

#### Student.ts
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

`students.ts` ist unsere Datenerhaltungsklasse.

#### db-user.ts
```typescript
import { Student } from './student';

export class DbUser {

    public static  getInstance (): DbUser {         // Die Singleton Methode
        if (DbUser.getInstance === null) {
            DbUser.instance = new DbUser();
        }
        return DbUser.instance;
    }

    private static instance: DbUser;
    
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
Singelton wird dann eingesetzt wenn man von einer Klasse wirklich nur ein Objekt haben darf/sollte. In diesem Fall wird es bei unserer "Datenbank" eingesetzt.

### Arrays
In JavaScript werden gewöhnliche Arrays verwendtn um Listen zu erstellen, nicht wie in Java mit Hashmaps und Arraylists.
