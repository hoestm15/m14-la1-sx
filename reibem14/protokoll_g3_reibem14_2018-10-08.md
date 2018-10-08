# 3.Protokoll  
  
  **Name**:  *Bernhard Reinbacher*  
  **Datum:** *08.10.2018*  
  **Uhrzeit:** *8:00 - 10:30*  
  **Gruppe:** *3*  
  
   
    
 **Abwesend:** Schmuck Martin  
 **Anwesend:** Bernhard Reinbacher, Ruffenacht Florian, Sackl Martin, Sackl Roland, Sammer Daniel, Schuster Patrick  
  
*************************************************************************************************************************     
## Übersetzungstools  
Je nach Programmiersprache gibt es andere Anforderungen an den Compiler und deshalb gibt es auch verschiedene.   

Typescript | Java | Java(unter Android) | C  
---------- | ---- | ------------------- | -  
gulp | javac | gradle | make  
[Gulp](https://de.wikipedia.org/wiki/Gulp.js) | [javac](https://en.wikipedia.org/wiki/Javac) | [gradle](https://de.wikipedia.org/wiki/Gradle) | [make](https://de.wikipedia.org/wiki/Make)    




## Rest-Server anlegen  
Dieser Rest-Server unterscheidet sich grundsätzlich nur wenig zum Vorhergegangenen. Auch hier wird mittels HTTP Technik gearbeitet. In unserem Fall soll durch aufrufen einer URL eine Meldung bzw. Informationen über Schüler zurückgegeben werden.  
```  typescript  
import * as express from 'express';
import * as bodyParser from 'body-parser';

class Main {

    private port: number;
    private server: express.Express;

    constructor(port: number) {
        this.port = port;
        this.server = express();
        this.server.use(bodyParser.urlencoded({extended: false}));
        this.server.get('/status', (req, resp) => this.handleGetStatus(req, resp));
        this.server.get('/student', (req, resp) => this.handleGetStudent(req, resp));
        this.server.get('*', (req, resp) => this.handleGet(req, resp));
        this.server.listen(this.port);
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

const main = new Main(8080);  
```  
### Konstruktor und Handlermethode  
Der Server wird darin auf *listen(zuhören)* geschalten. Somit wartet er bis ein *Request* eintrifft. Die Zeile ```typescript this.server.get('/status', (req, resp) => this.handleGetStatus(req, resp)); ``` bewirkt, dass wenn man */status* in der URL eingibt, wird die Handlermethode *HandleGetStatus* aufgerufen wird. Die Handlermethode selbst bewirkt, dass als *Response* "Server is running" zurückgegeben wird.   
Nach dem gleichen Prinzip arbeiten die restlichen Handlermethoden, je nach dem was als URL eingegeben werden die Handlermethoden *handleGetStudent* oder *handleGet* aufgerufen. Diese geben dann einen Schüler bzw. Error als Response am Bildschirm erscheint.  
