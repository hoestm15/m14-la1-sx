# Protokoll
Florian Nebel
5AHME
Gruppe 2  
Montag, 14.Jänner 2019  
Anwesend: Mandl Gerhard, Martinak Moritz, Mörth Michael, Muri Lorenz, Nabernik Mario, Nebel Florian, Platzer Andreas  
Abwesend: ---  

## REST Server
### Main.ts
Unten dargestellt ist die Klasse `main.ts` welche als erstes die Klasse `Server` importiert. In der Methode `public static main()`, 
bei welcher es im Gegensatz zu Java nicht notwendig ist, einen Datentyp anzugeben wird ein Server gestartet, welcher auf den Port 
7070 hört. Auch die Festlegung auf `public` ist nicht notwendig, sollte jedoch gemacht werden, um den Quellcode verständlicher zu 
gestalten.  

```typescript
import {Server} from './server';

class Main {

    public static main () {
        const server = new Server();
        server.start(7070);
    }
}

Main.main();
```

Da JavaScript alle Befehle von oben, nach unten abarbeitet muss die Methode `main()` im Quellcode aufgerufen werden, da sie ansonsten 
nur erzeugt, aber nie ausgeführt werden würde.  
### Server.ts
```typescript
import * as bodyParser from 'body-parser';
import * as express from 'express';
import { json } from 'body-parser';

export class Server {

    private _server: express.Express;

    constructor() {
        this._server = express();
        this._server.use(bodyParser.urlencoded());
        this._server.get('/version', (req, res, next) => {
            res.send('Version 1.0');
        });
        this._server.get('/student', (req, res, next) => this.handleGetStudent(req, res, next));
    }

    public start(port: number) {
        this._server.listen(port);
        console.log('Server auf Port ' + port + ' erfolgreich gestartet!');
    }

    public stop() {
        //Todo...
        console.log('Methode nicht fertiggestellt');
    }

    private handleGetStudent(req: express.Request, res: express.Response, next: express.NextFunction) {
        console.log('query --> ' + req.query);
        console.log('GET..');
        res.json({surname: 'Steiner', firstname: 'Manfred'});
    }
}
```

#### Body-parser
Das notwendige Modul, um Body-parser zu verwenden, kann mit `npm install body-parser` und dem darauffolgenden Befehl 
`npm install --save-dev @types/express` am Rechner installiert werden. Wird dieses ins Programm eingebunden, kann es Informationen 
zu einer Variable liefern. Um das Paket tatsächlich verwenden zu können ist es notwendig dieses dem Server mit dem Methodenaufruf 
`this._server.use(bodyParser.urlencoded())` zu übergeben.
siehe auch: [npmjs.com](https://www.npmjs.com/package/body-parser)  

#### export
Um die Klasse `Server` in die Klasse `Main` importieren zu können ist es wichtig das Schlüsselwort **export** zu verwenden. Es wird 
der Klassendeklaration `class Server {}` vorangestellt.

#### Express
Das Modul **Express** welches als zweites importiert wird ermöglicht den Zugriff auf das HypertextTransferProtokoll, kurz http bzw. 
https. Installiert wird es mit den selben Befehlen wie zuvor der body-parser: `npm install express` gefolgt von 
`npm install --save-dev @types/express`.

### Student.ts
Im Gegensatz zu Java ist sind alle Datenelemente in der folgenden Datenhaltungsklasse `public`. Das hat die Auswirkung, dass Getter 
und Setter überflüssig geworden sind.  

```typescript
export class Student {

    public surname: string;
    public firstname: string;
    public id: string;

    constructor (id: string, surname: string, firstname: string ) {
        this.id = id;
        this.surname = surname;
        this.firstname = firstname;
    }
}
```

### db-user.ts
```typescript
import { Student } from './student';

export class DbUser {

    public static  getInstance (): DbUser {
        if (DbUser.getInstance === null) {
            DbUser.instance = new DbUser();
        }
        return DbUser.instance;
    }

    private static instance: DbUser;

    // **********************************

    private _students: {
        [ id: string]: Student
    };

    private constructor () {
        this._students = {};

        let s = new Student('mangem13', 'Mandl', 'Gerhard');
        this._students[s.id] = s;

        s = new Student('murlom14', 'Muri', 'Lorenz');
        this._students[s.id] = s;

        s = new Student('nabmam14', 'Nabernik', 'Mario');
        this._students[s.id] = s;
    }

    public get(id: string): Student {
        return this._students[id];
    }
}
```
#### Singleton
Da eine Datenbank nur einmal existeren darf ist es von Vorteil, dass Entwurfsmuster **Singleton** zu verwenden. Durch einen privaten 
Konstruktor und den Aufruf der statischen Methode `getInstance()` wird dies realisiert. Beim ersten Aufruf dieser Methode wird ein 
Objekt erzeugt, durch welches auf die Variable zugegriffen werden kann, welche die Datenbank beinhaltet; das Objekt kann nur einmal 
erzeugt werden.

Singleton bezeichnet laut [wikipedia.org](https://de.wikipedia.org/wiki/Singleton_(Entwurfsmuster)) ein Entwursmuster der 
Softwareentwicklung, welches zur Gruppe der Erzeugungsmuster gehört. Dieses garantiert, dass von einer Klasse nur ein Objekt existieren 
kann. Darüberhinaus sind diese Objekte gängigerweiße global verfügbar.

#### Arraylist?
Im Gegensatz zu Java sind ArrayList's in Javascript nicht notwendig bzw. nicht verfügbar. In dieser Programmiersprache können 
gewöhnliche Felder bzw. Objekte auch als ArrayList dienen.  
siehe auch: [stackoverflow.com](https://stackoverflow.com/questions/20699507/hashmap-arraylist-in-java-script)
