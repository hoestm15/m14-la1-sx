# Protokoll
Gerhard Mandl  
5AHME, Gruppe 2  
14.01.2019  
Anwesend: Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: -

## Übung:REST-Server
### main.ts
In der main.ts wird die Klasse Server impotiert und ein Server auf dem Port 4711 gestartet.
Zum Schluss muss man noch die Funktion __Main.main()__ aufrufen, damit die Main-Klasse ausgeführt wird.
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

### db-user.ts
In dieser File werden alle Schüler in einem Array gespeichert, jeder Schüler hat eine __id__ durch diese können die Schüler auch wieder abgefragt werden. 
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

## Server.ts
In dieser File werden, für Anfragen die an den Server gerichtet sind, Antworten realisiert. 
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
#### express
In dieser Datei arbeiten wir mit dem Modul __Express__ welches wir zuerst mit den Befehlen `npm install express` und `npm install --save-dev @types/express` installieren. Sobald das Modul installiert ist kann es in die Klasse importiert werden(Das Modul kann auch schon vorher importiert werden, wird aber von der Klasse nicht erkannt). Das Modul __Express__ lässt uns mit  __http__ und __https__ arbeiten.

#### body-parser
Ebenso impotieren wird das Modul __Body-Parser__, dieses wird mit den Befehlen `npm install express` und `npm install --save-dev @types/express` installiert. Das Modul wird benötigt um Infos über eine Variable zu bekommen.

### student.ts
Die File __student.ts__ ist eine Datenerhaltungsklasse. 
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

