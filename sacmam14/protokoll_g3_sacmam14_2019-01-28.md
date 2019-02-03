# 4. Protokoll  
**Name:** Sackl Martin  
**Klasse** 5ahme  
**Gruppe:** 3  

Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster   
Abwesend: -    
*******************************************************************************************************************************************  
# Wiederholung der vorherigen Einheit  
Wenn man mit Java programmieren würden leichter Fehler passieren und diese Fehler würden erst in der Laufzeit aufscheinen. Um dies zu vermeiden arbeiten wir mit Typescript.  
Das Webserver-Framework **Express** baut auf Node.js und gestaltet das Programmieren eines Web-Servers komfortabler.  
Um mit Zusatz-Attributen in der URL zu arbeiten verwenden wir den **Body-Parser**. Mit der Methode *req.query* können wir diese Atribute abfragen und weiterverarbeiten.  
[Vorherige Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/sacmam14/sacmam14/protokoll_g3_sacmam14_2018-10-08.md)  
*******************************************************************************************************************************************  
# Projekt: REST-Server  
### Aufteilung in Klassen  
Um das Fehlerhandling leichter zu gestalten haben wir unsere *main.ts* Klasse in kleinere Klassen unterteilt. Somit haben wir jetzt 3 Klassen: **Server, Student und Main**.  

### Server.ts  
Diese Klasse haben wir seit der letzten Einheit kaum verändert. Wir haben nur eine *start-Methode* hinzugefügt. Mit dieser Methode wird Server-Objekt gestartet, das wir in der *main.ts* erstellt haben. Mit dem Befehl `this.server.listen(port)`, dieser wird von der start-Methode aufgerufen, wird der Server gestartet.  
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
                resp.json({htlid: 'suspam14', surename: 'Schuster', firstname: 'Patrick'});
                break;
            case 'reibem14':
                resp.json({htlid: 'reibem14', surename: 'Reinbacher', firstname: 'Bernhard'});
                break;
            case 'sacmam14':
                resp.json({htlid: 'sacmam14', surename: 'Sackl', fistname: 'Martin'});
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

### Student.ts  
Für das anlegen von Schülern benötigen wir diese Datenerhaltungsklasse. Die einzelnen Datenelemente sind *private* und werden durch Getter-Methoden abgefragt. Das Schlüssewort **export** wird benötigt, um die Klasse in eine andere Klasse importieren zu können.  
```typescript  
  export class Student {

    private htlid: string;
    private surename: string;
    private firstname: string;


    constructor (htlid: string,
                 surename: string,
                 firstname: string) {
        this.htlid = htlid;
        this.surename = surename;
        this.firstname = firstname;

    }

    public getHtlid () {
        return this.htlid;
    }

    public getSurename () {
        return this.surename;
    }

    public getFirstname () {
        return this.firstname;
    }
}
```  

### Main.ts  
Hier wird die *public static main* aufgerufen um in das Programm einzuspringen.  
Main.ts konnte in der Einheit nicht fertiggestellt werden.  
```typescript  
import { Server } from 'http';

class Main {
    public static main () {
        new Server().setMaxListeners(8080);
    }
}
```  
