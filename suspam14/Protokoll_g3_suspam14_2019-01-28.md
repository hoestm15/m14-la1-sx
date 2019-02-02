# Protokoll 4: REST-Server
Name: Patrick Schuster  
Klasse: 5AHME  
Gruppe: 3    
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: -




### Stundent.ts  
  
```typescript  
  export class Student {

    private htlid: string;
    private surname: string;
    private firstname: string;


    constructor (htlid: string,
                 surname: string,
                 firstname: string) {
        this.htlid = htlid;
        this.surname = surname;
        this.firstname = firstname;

    }

    public getHtlid () {
        return this.htlid;
    }

    public getSurname () {
        return this.surname;
    }

    public getFirstname () {
        return this.firstname;
    }
}
```  

### Server.ts
```typescript  
   import * as express from 'express';
import * as bodyParser from 'body-parser';

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
        console.log('Server auf Port' + port + 'gestartet');
    }

    private handleGet(req: express.Request, resp: express.Response) {
        resp.status(400);
        resp.send('Error');
        resp.end();
    }

    private handleGetStatus(req: express.Request, resp: express.Response) {
        resp.send('Server is running');
        resp.end();
    }

    private handleGetStudent(req: express.Request, resp: express.Response) {
        switch (req.query.htlid) {
            case 'suspam14':
                resp.json({htlid: 'suspam14', sirname: 'Schuster', firstname: 'Patrick'});
                break;
            case 'reibem14':
                resp.json({htlid: 'reibem14', sirname: 'Reinbacher', firstname: 'Bernhard'});
                break;
            default:
                resp.status(400);
                resp.send(req.query.htlid + ' not found');
                break;

        }
        resp.end();
    }


}
export class ServerError extends Error {
    constructor (msg: string, public cause: Error) {
        super(msg);
    }
}
```  
### main.ts    
```typescript  
    import { Server } from 'http';

class Main {
    public static main () {
        new Server().setMaxListeners(8080);
    }
}

```
