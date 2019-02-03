# 4.Protokoll  
  
  **Name**:  *Sackl Roland*  
  **Datum:** *28.01.2018*  
  **Uhrzeit:** *8:00-10:30*  
  **Gruppe:** *3*  
  
  **Abwesend:** -  
  **Anwesend:**   Sackl Martin, Sackl Roland, Reinbacher Bernhard,Sammer Daniel,Ruffennacht Florian,Schuster Patrick, Schmuck Martin  
  

## Wiederholung  
Da die letzte Einheit noch im vorherigen Jahr war, wiederholten wir zu Beginn das zuletzt gemachte. Wir besprochen den Unterschied von Javaascript und Typescript. Es gibt viele Unterschiede von zwischen Javaascript und Typescript. EIn untersched ist, dass bei Typescript ein Konstruktor durch das Schlüsselwort **constructor** signalisiert wird. Das Problem von Javascript ist, dass leicht Fehler passieren können, da es nicht Typenstreng ist. Um diese Fehler zu vermeiden arbeiten wir mit Typescript.Damit man nicht von null auf einen Server programmiert greifen wir auf das Express Framework zu, welches auf NodeJs baut. Die Erstellung eines Webservers erleichtert das NodeJs sehr. Der Body-Parser speichert automatisch zusätzliche Attribute und entlastet so den Programmierer sehr. Dafür dient die Methode **req.query**, mit der man die Zusatzattribute abfragen und weiterverarbeiten kann.  


## REST-Server  
Das wir alles in unseren Main-Klasse haben, war das Ziel unser Einheit, den REST-Server schöner und übersichtlicher zu gestalten. Um das erreichen zu können, haben wir die Klassen **Server** und **Student** erstellt. Dadurch ist alles voneinader getrennt.  

### Stundent.ts  
Da die Klasse **Student** später in einer anderen Klasse importiert werden muss, wird das Schlüsselwort **export** verwendet.In unseren Fall wird die Klasse die Datenerhaltungsklasse. 
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
Grundsätzlich hat sich an der Funktion dieser Klasse nichts geändert. Der Server hat nun die Aufgabe, dass er auf Requests vom Client antwortet. Dass wir eine eigene **start** Methode eingefügt haben, was die einzige Veränderung. Die Portnummer wird von der Methode als Paramter übergeben und ruft sie auf. Dadurch wird der Server am gegebenen Port gestartet.  
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
In der **main.ts** Klasse wird bis jetzt nur die public static main aufgerufen. Diese Methode wird in der nächsten Einheit fertiggestellt.  
```typescript  
    import { Server } from 'http';

class Main {
    public static main () {
        new Server().setMaxListeners(8080);
    }
}

```
