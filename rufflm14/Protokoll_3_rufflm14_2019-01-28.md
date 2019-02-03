# 4. Laborprotokoll 

*von Florian Ruffenacht*

Datum: 28.01.2019 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

## Wiederholung der letzten Einheiten
Da die letzte Einheit in diesem Labor für uns schon weit zurück lag, versuchten wir unsere Kenntnisse im Rahmen einer Wiederholung aufzufrischen. Dabei wurden folgende Themen, die in den letzten Protokollen nicht zu lesen waren, besprochen:

### Installieren des node_modules-Ordner
Zum Installieren des **node_modules**-Ordners des JavaScript- oder TypeScript-Projekts nach dem Laden des Projekts aus einem Repositories gibt es zwei Möglichkeiten:

Befehl | Wirkung
--------- | ---------
npm install --piod | Es werden nur die Module installiert, die zum Ausführen des Programms notwendig sind. 
npm install | Es werden auch die Module installiert, die zum Weiterentwickeln des Programms notwendig sind.

### Datenkapselung in JavaScript
Wird eine Variable ohne Definition der Zugriffsart deklariert, ist sie ```public```. Trotzdem kann aus Gründen der Übersichtlichkeit sinnvoll sein das Schlüsselwort ```public``` zu verwenden. 
Bei jeder Verwednung einer Variable, die in der Klasse deklariert wurde, muss das Schlüsserwort ```this.<Variable>``` verwendet werden, do sonst auch auf globale Variablen zugegriffen wird.

### bodyParser
Der bodyParser ist ein Modul, das die in der URL übergebenen Attribute in einem Objekt speichert und sie für den Programmierer leicht vefügbar macht. Sie lassen sich mit **req.query** abfragen.
[bodyParser]()

## Verbesserung des Codes
Bis jetzt befand sich der gesamte Quellcode des Rest-Servers in einer Datei. Das ist unübersichtlich und entspricht nicht dem Standard. Deswegen wurde der Code auf die Dateien main.ts, server.ts und student.ts aufgeteilt. Grundsätzlich wäre es in JavaScript/TypeScript auch möglich mehrere, oder auch alle Klassen in einer Datei zu speichern. Das macht aber nur Sinn, wenn z.B. eine eigene Fehlerklasse, die zur Klasse gehört, in der gleichen Datei plaziert wird.

### server.ts
Hier werden die Anfragen (**request**), abhängig von der URL, in unterschiedlichen Handlermethoden verarbeitet. Abschließend wird eine Antwort (**response**) erzeugt und zurückgeschickt. Zum Starten des Servers muss zuerst der Konstruktor und dann die Methode start() aufgerufen werden. Die Klasse ServerError repräsentiert einen Fehler, der in der Klasse Server auftreten kann.

```javascript
import * as express from 'express';
import * as bodyParser from 'body-parser';

export class Server {

    private server: express.Express;

    public constructor () {
        this.server = express();
        this.server.use(bodyParser.urlencoded({ extended: false }));
        this.server.get('/status', (req, resp, next) => this.handleGetStatus(req, resp, next));
        this.server.get('/student', (req, resp) => this.handleGetStudent(req, resp));
        this.server.get('*', (req, resp) => this.handleGet(req, resp));
    }

    public start (port: number) {
        this.server.listen(port);
        console.log('Server auf Port ' + port + ' gestartet');
    }

    private handleGet (req: express.Request, resp: express.Response) {
        resp.status(400);
        resp.send('ERROR');
        // resp.send('Hallo');
        resp.end();
    }

    private handleGetStatus (req: express.Request, resp: express.Response, next: express.NextFunction) {
        resp.send('Server is running');
        resp.end();
    }

    private handleGetStudent (req: express.Request, resp: express.Response) {
        switch (req.query.htlid) {
            case 'suspam14':
                resp.json({ htlid: 'suspam14', surename: 'Schuster', firstname: 'Patrick'});
                break;
            case 'reibem14':
                resp.json({ htlid: 'reibem14', surename: 'Reinbacher', firstname: 'Bernhard'});
                break;
            default:
                resp.status(400);
                resp.send(req.query.htlid + ' not found');
                break;

        }
        // resp.json({ htlid: 'suspam14', surename: 'Schuster', firstname: 'Patrick'});
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
In dieser Hauptklasse wird ein Server-Objekt erzeugt und somit der Server gestartet. Dazu wird die Serverklasse importiert.

```javascript
import { Server } from 'net';

class Main {

    public static main () {
        new Server().setMaxListeners(8080);
    }

}

```

### student.ts
Hier ist der Code zur Datenerhaltungsklasse Student. Das Schlüsselwort **export** wird hier benötigt, da diese Klasse in der Serverklasse importiert wird.

```javascript
export class Student {

    private htlid: string;
    private surname: string;
    private firstname: string;

    constructor (htlid: string,
                 surname: string,
                 firstname: string ) {
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


