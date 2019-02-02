# Protokoll 4: REST-Server
Name: Patrick Schuster  
Klasse: 5AHME  
Gruppe: 3    
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: -

## Wiederholung der vorherigen Einheiten:
Folgende Punkte wurden besprochen:
#### Javascript-Typescript Unterschied   
Das Problem beim arbeiten mit JS ist, dass es nicht Typenstreng ist und somit leicht Fehler passieren können, welche erst in der Laufzeit aufscheinen. Um dies zu vermeiden arbeiten wir mit Typescipt. 
#### Express Framework
Um nicht von null auf einen Server programmieren greifen wir auf das Express Framework zurück. Dieses Framework baut auf NodeJs auf und erleichtert die Erstellung eines Webservers erheblich.
#### Body-Parser
Wir verwenden den Body-Parser um konfortabel mit Zusatz-Attributen in der URL arbeiten zu können. Diese Zusatzattribute werden in einer query gespeichert, welche man mit der Methode `reg.query` abfragen und weiterverarbeiten kann.
## REST-Server
Um den Quellcode für den REST-Server schöner zu gestalten, haben wir unser Programm in mehrere Klassen aufgeteilt, anstatt nur ein main-programm zu haben. Es wurden die Klassen *Student.ts* und *Server.ts* erstellt. Zusätzlich wird eine die Klasse *main.ts* benötigt in welcher ein Server Objekt erzeugt wird.
(Protokoll zur 2. Einheit)[https://github.com/HTLMechatronics/m14-la1-sx/blob/suspam14/suspam14/Protokoll_g3_suspam14_2018-10-01.md]
(Protokoll zur 3. Einheit)[https://github.com/HTLMechatronics/m14-la1-sx/blob/suspam14/suspam14/Protokoll_g3_suspam14_2018-10-08.md]

### Stundent.ts  
Diese Klasse ist eine Datenerhaltungsklasse für das anlegen von Schülern. Das Prinzip der Datenerhaltungsklasse ist gleich wie in Java, wonach die einzelnen Datenelemente private sind und diese über Getter-Methoden abgefragt werden können.
Es wird das Schlüsselwort **export** benötigt, ansonsten könnte die Klasse nicht in einer anderen importiert werden.
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
Die Server Klasse hat sich seit der letzten Einheit nur geringfügig verändert. Es wurde lediglich eine **start**-Methode hinzugefügt. Diese wird ab jetzt benötigt da in der main ein Server-Objekt erstellt wird, dass daraufhin erst gestartet werden muss. Um den Server zu starten wird von der start-Methode der Befehl `this.server.listen(port)` aufgerufen, wodurch der eigentliche Server gestartet wird.
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
In dieser Klasse wird die public static main aufgerufen, diese Methode ist der EInsprung in das Programm. 
Diese Methode konnte in der Einheit nicht fertiggestellt werden und wird somit in der nächsten vervollständigt.
```typescript  
    import { Server } from 'http';

class Main {
    public static main () {
        new Server().setMaxListeners(8080);
    }
}

```
