# 4.Protokoll  
  
  **Name**:  *Bernhard Reinbacher*  
  **Datum:** *28.01.2019*  
  **Uhrzeit:** *8:00 - 10:30*  
  **Gruppe:** *3*  
  
   
    
 **Abwesend:** niemand  
 **Anwesend:** Bernhard Reinbacher, Ruffenacht Florian, Sackl Martin, Sackl Roland, Schmuck Martin, Sammer Daniel, Schuster Patrick  
  
*************************************************************************************************************************     
## Wiederholung  
Zu Beginn wiederholten wir das zuletzt gemachte, da seit der letzten Einheit schon einige Zeit vergangen ist. Wir arbeiten mit Javascript schreiben jedoch in Typescript damit das Programmieren aufgrund der fehlenden Datentypen in Javascript. Somit wird das Arbeiten angenehmen, da Typescript Java sehr ähnlich ist. Einer von vielen Unterschieden zwischen Java und Javascript ist, dass bei Javascript automatisch public verwendet wird auch wenn man kein Schlüsselwort verwendet. In Java als auch in Typescript verwendet man private und public.  
Mithilfe des bodyPasers wird der Programmierer entlastet, da er automatisch zusätzliche Attribute zu speichern. Dafür bedient man sich der Methode **req.query**. In unserem Fall kann mit *req.query.htlid* auf das Atrribut HTLID zugegriffen werden.  
  
*************************************************************************************************************************     
## Aufteilung in Klassen  
Um den Code schöner zu gestalten und auch das Fehlerhandling zu vereinfachen, haben wir die eine Klasse in kleinere unterteilt. Somit können wir sehr schön **Server, Student und Main** unterteilen.  
### Stundent.ts  
Diese Klasse ist in unseren Fall die Datenerhaltungsklasse. **export** wird benötigt, da die Klasse später in einer anderen Klasse importiert wird.  
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
Der Server hat die Aufgabe, dass er auf Requests vom Client antwortet. Nun haben wir die Klassen Server.ts eigenständigt gemacht, was dazu füht, dass eine Methode *start* implementiert werden musste. Grundsätzlich hat sich an der Funktion dieser Klasse nichts geändert. Sie schickt immer noch bei Anfrage eines Schülers *http://localhost:8080/student?htlid=reibem14* die Informationen über den jeweiligen Schüler zurück: htlid: 'reibem14', sirname: 'Reinbacher', firstname: 'Bernhard'. Es kam auch eine ServerError Klasse für das Problemhandling dazu.  
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
In dieser Methode rufen wir bis jetzt nur eine public static main auf.   
```typescript  
    import { Server } from 'http';

class Main {
    public static main () {
        new Server().setMaxListeners(8080);
    }
}

```
