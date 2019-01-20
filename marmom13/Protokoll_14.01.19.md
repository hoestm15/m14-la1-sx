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

## main.ts  
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
import * as express from 'express'; // Importieren des Moduls express  
import * as bodyParser from 'body-parser'; // Importieren des Moduls bodyParser


export class Server { // wird in Klasse main importiert
    private _server: express.Express; 

    constructor () { 
        this._server = express();
        this._server.use(bodyParser.urlencoded());
        this._server.get('/version', (req, res, next) => {
            res.send('Version 1.0');
        });
        this._server.get('/student', (req, res, next) => this.handleGetStudent(req, res, next));
    }

    public start (port: number) { // Wenn weder public oder private immer public
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


### Express  
Das Modul Express ist ein Framework für *http* um leichter an Webservern programmieren zu können. Durch das aufrufen von Express wird ein Server erzeugt.

>>>The Express philosophy is to provide small, robust tooling for HTTP servers, making it a great solution for single page applications, web sites, hybrids, or public HTTP APIs.  
*Quelle: [www.npmjs.com](https://www.npmjs.com/package/express)*  

Es wird mit dem Kommando *npm install express* installiert. Es ist immer ratsam zu überprüfen wie viele user ein Modul installiert haben um zu "verifiziern" ob es gut ist.

### Body-Parser  
Ich habe das Modul Body-Parser nicht wirklich verstanden, ich vermute nach etwas Recherche aber das es dabei Hilft Pakete eines Streams zu einem verarbeitbaren Body zu formartieren.  
*Quelle: [stackoverflow.com](https://stackoverflow.com/questions/38306569/what-does-body-parser-do-with-express)*  

## student.ts  

```javascript
export class Student {

    public id: string; // public statt private da keine getter
    public surname: string;
    public firstname: string;

    constructor (id: string, surname: string, firstname: string) {
        this.id = id;
        this.surname = surname;
        this.firstname = firstname;
    }
}
``` 
Bei *student.ts* handelt es sich um unsere Datenerhaltungsklasse.

## db-user.ts  

```javascript
import { Student } from './student'; //Importieren der Klasse Student

export class DbUser {

    public static getInstance (): DbUser {
        if (DbUser.instance === null) {
            DbUser.instance = new DbUser();
        }
        return DbUser.instance;
    }

    private static instance: DbUser;
    // ********************************************************************************//

    private _students: {
        [ id: string ]: Student
    };

    private constructor () {
        this._students = {};

        this._students.mangem13 = new Student('mangem13', 'Mandl', 'Gerhard');

        let s = new Student('marmom13', 'Martinak', 'Moritz');
        this._students[s.id] = s;

        s = new Student('nambam14', 'Nabernik', 'Mario');
        this._students[s.id] = s;
    }

    public get (id: string): Student {
        return this._students[id];
    }
}
```  





