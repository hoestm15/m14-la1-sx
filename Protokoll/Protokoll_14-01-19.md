# Protokoll der 3. Einheit

## 3. Einheit

* Name: Mario Nabernik  
* Klasse: 5AHME  
* Datum 14.01.2019
* Gruppe: 2  
* Anwesend: Marcel Köhler, Michael Mörth, Florian Nebel, Lorenz Muri, Moritz Martinak, Andreas Platzer, Mario Nabernik, Gerhard Mandl  
* Abwesend: -  
* Thema: Erstellen eines REST-Servers


# REST-Server
Informationen zu REST-Server, siehe auch [Protokoll der 1.Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/nabmam14/Protokoll/Protokoll_17-12-2018.md).

## main.ts
In der ersten Zeile des Quellcodes importietren wir die Klasse Server.
In der letzten Zeile des Quellcodes rufen wir `Main.main()` auf, damit diese Klasse ausgeführt wird.
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

## Server.ts
Dies ist die eigentliche "Server Datei", da wir hier unseren Server und dessen Antworten realisieren.
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

### express
> Express.js ist ein serverseitiges Webframework für die JavaScript-basierte Plattform Node.js. 
> Es erweitert Node.js um Werkzeuge, mit denen das Entwickeln moderner Webanwendungen einfacher gestaltet wird.

 [Quelle: Wikipedia](https://de.wikipedia.org/wiki/Express.js)
 
### body-parser
> To handle HTTP POST request in Express.js version 4 and above, you need to install middleware module called body-parser.
> body-parser extract the entire body portion of an incoming request stream and exposes it on req.body.
> The middleware was a part of Express.js earlier but now you have to install it separately.

[Quelle: StackOverflow](https://de.wikipedia.org/wiki/Express.js)

Installiert wird der body-parser mit den Befehlen `npm install express` und `npm install --save-dev @types/express`.


## db-user.ts
In dieser Klasse werden unsere Daten in einer Array List gespeichert. Ähnlich wie wir es schon aus dem Programmieren mit Java kennen.
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

## student.ts
Eine Datenerhaltungsklasse, wie wir sie auch schon vom Programmieren mit Java kennen.
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
