# _Protokoll Vierte Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 28.01.2019**  
**Uhrzeit: 8:00-10:30**  
  
**Anwesenheit: Es waren alle Schüler anwesend!**  
  
**Thema: Projekt REST-Server**  
  
-----------------------------------------------------------
  
### Grundlegende Wiederholung  
Einer von vielen Unterschieden zwischen TypScript und Java ist es, dass bei TypeScript ein Konstruktor durch das Schlüsselwort **constructor** signalisiert wird. Außerdem sind Datenelemente, bei denen die Kennzeichnung **private / public** fehlt, grundsätzlich öffentlich, also *public*, anders als bei Java.  
**Express* ist ein Webserver-Framework, das auf **Node.js HTTP** aufbaut und dem Programmierer das Programmieren von Web-Server komfortabler gestaltet.  
Der **bodyParser** hilft dem Entwickler, einfacher mit Attributen / zusätzliche Informationen einer URL zu arbeiten, denn er speichert dieser Attribute als eigene **query** (Abfrage). Beispiel an unserem REST-Server wäre die HTL-ID. Auf sie kann über `req.query.htlid` zugegriffen werden.  
  
--------------------------------------------------------------  
  
### Projekt REST-Server  
Das Ziel der heutigen einheit war es, den REST-Server schöner zu gestalten, denn bis jetzt haben wir alles in unsere Main-Klasse gepackt. 
Deshalb sollen die Klassen **Server** und **Student** erstellt werden, damit alles sauber voneinander getrennt ist und man in der Main nur mehr ein Server-Objekt erzeugt werden muss.  
Die Student-Klasse wird im späteren Verlauf in irgendeiner Art von Schüler-Datenbank verwendet werden.  
  
#### Klasse student.ts  
Das Schlüsselwort **export** wird verwendet, da die Klasse **Student** später exportiert bzw. in einer anderen Klasse importiert werden muss.  
Sie wird in unserem Fall als Datenhaltungsklasse für einen Schüler agieren. Die Datenelemente sind, wie in Java auch, **private**, daher werden die Getter-Mehtoden benötigt.  
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

public getHtlid (): string {
return this.htlid;
}

public getSurename (): string {
return this.surename;
}

public getFirstname (): string {
return this.firstname;
}
}

```
  
#### Klasse server.ts  
Der Server funktioniert nach dem gleichen Prinzipien, wie auch schon in der letzten Einheit. Die einzigste Veränderung ist die, dass wir eine eigene **start**-Methode eingefügt haben. Dieser Methode wird als Parameter die Portnummer übergeben. Weiters ruft sie `this.server.listen(port)` auf, wodurch im Endeffekt der Server am gegebenen Port gestartet wird.  
Die Klasse enthält ebenfalls das Schlüsselwort **export**, da sie im weiteren Projektverlauf in der Klasse **Main.ts** importiert werden soll und ein Server-Objekt erzeugt werden soll.  
Weitere Erklärungen zum Code können [hier](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/protokoll_3_samdam14_2018-10-08.md#%C3%A4nderungen-am-rest-server) nachgelesen werden!  
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
console.log('Server auf Port ' + port + ' gestartet');
}

private handleGet (req: express.Request, resp: express.Response) {
resp.status(400);
resp.send('ERROR');
// resp.send('Hallo');
resp.end();
}

private handleGetStatus (req: express.Request, resp: express.Response) {
resp.send('Server is running');
resp.end();
}

private handleGetStudent (req: express.Request, resp: express.Response) {
switch (req.query.htlid) {
case 'samdam14':
resp.json({htlid: 'samdam14', surename: 'Sammer', firstname: 'Daniel'});
break;
case 'suspam14':
resp.json({htlid: 'suspam14', surename: 'Schuster', firstname: 'Patrick'});
break;
case 'reibem14':
resp.json({htlid: 'reibem14', surename: 'Reinbacher', firstname: 'Bernhard'});
break;
case 'rufflm14':
resp.json({htlid: 'rufflm14', surename: 'Ruffenacht', firstname: 'Florian'});
break;
case 'smumam14':
resp.json({htlid: 'smumam14', surename: 'Schmuck', firstname: 'Martin'});
break;
case 'sacmam14':
resp.json({htlid: 'sacmam14', surename: 'Sackl', firstname: 'Martin'});
break;
case 'sacrom14':
resp.json({htlid: 'sacrom14', surename: 'Sackl', firstname: 'Roland'});
break;
default:
resp.status(400);
resp.json(req.query.htlid + ' not found');
break;
}
resp.end();
}
}
```
  
#### main.ts  
Die Klasse **main.ts** wurde erst in den letzten Minuten der Einheit angefangen und ist deshalb auch noch sehr mager vorhanden und unvollständig. Zurzeit wird nicht einmal die Methode **Main.main()** aufgerufen, somit würde die Main auch noch nicht ausgeführt werden, sondern nur erzeugt werden.  
```typescript
import { Server } from 'net';

class Main {

public static main () {
new Server().setMaxListeners(8080);
}
}
```
