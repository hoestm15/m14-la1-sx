
# Laborprotokoll  
Vierte Einheit am 28. Jan. 2019  
Martin Schmuck  
5AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: niemand  

## Thema der Einheit: TypeScript mit Visual Studio Code
________
### Wiederholung  
##### Pakete und Tools installieren  
Will man die zur Ausführung benötigten Pakete nachinstallieren, verwendet man `npm install -prod` im Terminal. Ansonsten, wenn man weiterentwickeln will, gibt man nur `npm install` ein.  
  
##### Zugriffschutz in TypeScript  
Der Zugriffsschutz funktioniert so, dass Datenelemente, welche ohne Schlüsselwort deklariert werden, anders als in Java automatisch `public` sind. Außerdem muss man auch bei Zugriffen innerhalb der Klasse auf deren klasseneigenen Attribute das `this.<Datenelement>` aufrufen, da sonst die globale Variable gebraucht wird.  

##### BodyParser
Der Bodyparser (siehe Konstruktor der Klasse Server) teilt den URL der Anfrage in die einzeilenen Teile bzw. Attribute auf, die sich dann mit `req.query` abfragen lassen.


### Erweiterung des Servers 
Wir erweitern unseren Server um eine weitere Funktion und lagern ihn in verschiedene Dateien aus. Dies hat den Vorteil, dass man die ganze Anwendung an verschiedene Gegebenheiten leichter anpassen kann. 

#### main.ts  
Die Klasse `Main` hat zur Zeit nur die Aufgabe, den Konstruktor der Klasse Server aufzurufen und somit den Server zu starten.
```typescript
import { Server } from 'http';

class Main {
    public static main () {
        new Server().setMaxListeners(8080);
    }
}


```  

#### server.ts  
Die Klasse `Server` hat die Aufgabe, einen Server zu realisireren. Da Schlüsselwort `export` muss im Klassenkopf angeführt werden, wenn man wie wir die Klasse in einer anderen Klasse verwendet, also dort mit `import` importiert.  
```typescript
import * as express from 'express';
import * as bodyParser from 'body-parser';

export class Server {

    private server: express.Express;

    constructor() {
        this.server = express();
        this.server.use(bodyParser.urlencoded({extended: false}));
        this.server.get('/status', (req, resp) => this.handleGetStatus(req, resp));
        this.server.get('/student', (req, resp) => this.handleGetStudent(req, resp));
        this.server.get('*', (req, resp) => this.handleGet(req, resp));
    }

    public start(port: number) {
        this.server.listen(port);
        console.log('started server on port' + port);
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
                resp.json({htlid: 'suspam14', surname: 'Schuster', firstname: 'Patrick'});
                break;
            case 'reibem14':
                resp.json({htlid: 'reibem14', surname: 'Reinbacher', firstname: 'Bernhard'});
                break;
            default:
                resp.status(400);
                resp.send(req.query.htlid + ' not found');
                break;

        }
        resp.end();
    }
  }

``` 

#### student.ts  
Die Klasse `Student` ist eine Datenhaltungsklasse. Sie representiert einen Schüler.
```typescript
export class Student {
    private htlid: string;
    private surname: string;
    private firstname: string;

    constructor(htlid: string, surname: string, firstname: string) {
        this.htlid = htlid;
        this.surname = surname;
        this.firstname = firstname;
    }

    public getHtlId() {
        return this.htlid;
    }

    public getSurname() {
        return this.surname;
    }

    public getFirstname() {
        return this.firstname;
    }
}

```  
