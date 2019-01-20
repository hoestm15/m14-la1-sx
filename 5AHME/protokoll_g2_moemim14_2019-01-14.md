# Protokoll
Michael Mörth  
5AHME, Gruppe 2  
07.01.19  
Anwesend: Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: -  

# Projekt: REST-Server
## main.ts
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

Die Klasse `main.ts` importiert die Klasse `main.ts`. Die Methode `public static main()` startet einen Server auf dem Port 4711. Javascript arbeitet wie die Programmiersprache C das Programm von oben nach unten ab. Am Ende muss die Methode `Main.main()` aufgerufen werden, da die klasse `Main` ansonsten nicht ausgeführt wird, sondern nur erzeugt werden würde. 

## server.ts
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

In der Klasse `server.ts` wird das Modul **Express** importiert. Dieses Modul ermöglicht das Arbeiten mit **http** und **https**. Weitere Informationen zu Express können [hier](https://www.npmjs.com/package/express) nachgelesen werden.  
Das Schlüsselwort `export` wird verwendet, da die Klasse `Server` in der Klasse `Main` importiert wird.  
Die Variable `_server: express.Express` wird benötogt um den Server aufbauen zu können. Wichtig hierbei ist es, dass beim Angeben des Datentyps **Express** alleine nicht ausreicht.  
Der Konstruktor werden die Handler-Methoden `localhost:4711/version` und `localhost:4711/student` realisiert.  
Mit der Methode `start(port: number)` wird der Server gestartet.  
Die Handler-Methode `handleGetStudent` definiert, eie der Server reagiert, falls die Anfrage `/student` eintrifft.

## students.ts
