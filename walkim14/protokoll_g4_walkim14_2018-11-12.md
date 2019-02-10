# 3.Protokoll
**Name:** Kilian Waltl   
**Datum:** 12.11.2018  
**Gruppe:** 4  
**Anwesend**: Strauß Lukas, Tuttner Raphael, Waltl Kilian, Wieser Markus, Zitz Karlheinz  
**Abwesend**:  Strutz Sebastian, Uhl Christian  

### Datenbanken  
Als Datenbank bezeichnet man ein elektronisches Verwaltungssystem, welches Daten halten, sammeln und verwalten kann. Das Ziel liegt hierbei große Datenmengen effizient, dauerhaft und widerspruchslos zu verwalten. Hierbei wird zwischen einer schematischen, also einer klar Strukturierten, und einer nicht schematischen Datenbank unterschieden. Zur Programmierung solcher Datenbanken wird meist SQL verwendet.  

### Singelton  
Ein Singleton, zu deutsch auch Einzelstück genannt, ist ein Entwurfsmuster, welches, wie der Name schon andeutet, sicherstellt, dass immer nur ein Objekt einer Klasse existiert. Wir verwenden dieses Entwurfsmuster, da unsere Datenbank nur einmal existieren soll und nur die Werte geändert werden sollen. Deswegen ist es meist sinnvoll das Singleton global zugängig zu machen.

# Implementierung von Datenbanken im Unterricht  
Dafür wurde der in den vorherigen Einheiten erstellte REST-Server verändert. So erstellten wir die Datenhaltungsklasse Student und die Datenbank Database, außerdem mussten wir noch einiges an der Server Klasse verändern.  
  
### Klasse student.ts

Wie bei einer Datenhaltungsklasse üblich sind die Datenelemente eines Schülers private, wodurch Getter Methoden benötigt werden um die verschiedenen Daten auslesen zu können. Um die Klasse ordnungsgemäß in einer anderen Klasse importieren zu können das Schlüsselwort export verwendet.
```typescript
export class Student {

    private htlid: string;
    private surname: string;
    private firstname: string;

    constructor (htlid: string, surname: string, firstname: string) {
        this.htlid = htlid;
        this.surname = surname;
        this.firstname = firstname;
    }
    public getHtlid (): string {
        return this.htlid;
    }
    public getSurname (): string {
        return this.surname;
    }
    public getFirstname (): string {
        return this.firstname;
    }
}
```

### Klasse database.ts  
  
Um eine Datenbank zu realisieren erstellten wir die Klasse database, welche nach dem Entwurfsmuster Singleton ausprogrammiert wurde. Hierzu wird der Konstruktor auf private gesetz und die Methode getInstance() eingefügt. Dies bewirkt, dass eine neue Instanz erzeugt wird, wenn schon ein Datenbank-Objekt vorhanden ist, wird dieser Schritt übersprungen. Um neue Schüler hinzu zu fügen, bzw. bereits vorhandene Einträge aus zu lesen, erstellten wir noch die Methoden add() und get().
```typescript
import { Student } from './student';
export class Database {
    private static instance: Database;
    public static getInstance (): Database {
        if(Database.instance == null) {
            Database.instance = new Database();
        }
        return Database.instance
    }
      private students: { [id: string]: Student } = {};
    private constructor () {
        // this.add({ htlid = 'tutram12', surname = 'Tuttner', firstname = 'Raphael'});
        this.add(new Student( 'tutram12', 'Tuttner', 'Raphael'));
        this.add(new Student( 'zitkam13', 'Zitz', 'Karlheinz'));
    }

    public add (s: Student) {
        if (this.students[s.getHtlid()]) {
            throw new Error('student already exists');
        }
        this.students[s.getHtlid()] = s;
    }
    public get (htlid: string) {
        return this.students[htlid];
    }
}
```

### Klasse server.ts  

Hier implementierten wir unserere Datenbank in der Handler-Methode. Dabei fragt der Body-Parser die HTL-ID ab, wodurch in weiterer folge überprüft wird, ob es einen Eintrag mit dieser ID gibt. Bei gefundenem Eintrag wird der Schüler ausgegeben, wird jedoch nichts gefunden resultiert das ganze in einer Fehlermeldung. Zum Schluss der Einheit fingen wir noch an die Methode HandlePutStudent aus zu programmieren, welche dafür verwendet werden soll einen neuen Schüler anlegen zu können.
```typescript

import * as express from 'express';
import * as bodyParser from 'body-parser';
import { Database } from './database';

export class  Server {

   private _server: express.Express;
    constructor ( port: number) {
        this._server = express(); 
        this._server.use(bodyParser.urlencoded({extended: false}));
        this._server.use(bodyParser.json);
        this._server.get('/student', (req, resp, next) => this.handleGetStudent(req, resp, next));
        this._server.put('/student', (req, resp, next) => this.handlePutStudent(req, resp, next));
        this._server.listen(port); 
        console.log('HTTP server gestartet auf Port ' + port);
    }
    private handlePutStudent (req: express.Request, resp: express.Response, next: express.NextFunction) {
        console.log(req.query.htlid);
        console.log(req.body);
        resp.send('Test');
        resp.end();
    }
    private handleGetStudent (req: express.Request,
                              resp: express.Response,
                              next: express.NextFunction) {
        console.log('Abfrage');
        console.log(req.query.htlid);

        const id = req.query.htlid;
        const s = Database.getInstance().get(id);
        if (s) {
            resp.json(s);
        }
        switch (req.query.htlid) {
            case 'tutram12':
            resp.json({surname: 'Tuttner', firstname: 'Raphael'}); break;
            case 'zitkam13':
            resp.json({surname: 'Zitz', firstname: 'Karlheinz'}); break;
            case 'strlum14':
            resp.json({surname: 'Strauß', firstname: 'Lukas'}); break;

            default:
                resp.status(404);
                resp.end();
        }
        resp.send('Antwort' + req.query.htlid);
    }
}
```
