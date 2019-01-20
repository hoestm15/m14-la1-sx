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
import { Server } from './server'; // Importieren der Klasse Server

class Main {
    public static main () {
        const server = new Server(); // Anlegen eines neuen Servers
        server.start(4711);  // Starten des Servers auf 
    }
}

Main.main(); // Ausführen der Methode main
```
In der Klasse *main.ts* wird der Server angelegt und gestartet.  

## server.ts  
```javascript
import * as express from 'express';
import * as bodyParser from 'body-parser';


export class Server {
    private _server: express.Express;

    constructor () {
        this._server = express();
        this._server.use(bodyParser.urlencoded());
        this._server.get('/version', (req, res, next) => {
            res.send('Version 1.0');
        });
        this._server.get('/student', (req, res, next) => this.handleGetStudent(req, res, next));
    }

    public start (port: number) {
        this._server.listen(port);
        console.log('Server auf port ' + port +  ' gestartet');
    }

    public stop () {

    }

    private handleGetStudent (req: express.Request, res: express.Response, next: express.NextFunction) {
        console.log('query -->', req.query);
        console.log('--> GET....');
        res.json({ surname: 'Martinak', firstname: 'Moritz'});
    }
}
```


