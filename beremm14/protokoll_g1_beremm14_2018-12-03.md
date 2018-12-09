# Protokoll
  Berger Emil  
  5AHME, Gruppe 1  
  03.12.18  
  Anwesend: Berger, Bullner, Ehmann, Enzi, Köhler, Knappitsch  
  Abwesend: Böcksteiner, Kobor  

## Wiederholung

### [Express](https://www.npmjs.com/package/express)
  Express ist ein Modul, das die Programmierung von HTTP/HTTPS-Servern vereinfacht.  
  Um es verwenden zu können, muss es mit `npm install express` installiert werden, und mit `npm install --save-dev @types/express` wird in der `package.json` eingetragen, dass die TypeScript-Variante zur Entwicklung benötigt wird.
  
### `getall()`
```typescript
public getAll (): Value [] {
        return [].concat(this.data);
    }
```
Diese Methode gibt ein neues Array mit dem Inhalt des alten Arrays zurück. Das wird gemacht, dass von außen niemand auf das "originale" Array der Datenbank zugreifen kann.

### Singleton - Realisierung
```typescript
private static instance: Database;

public static getInstance (): Database {
        if (!this.instance) {
            this.instance = new Database();
        }
        return this.instance;
    }
```
Mit dieser Methode wird die Klasse mit dem Entwurfsmuster **Singleton** erstellt. Die Methode `getInstance()` erstellt nur ein neues Objekt, wenn noch keines angelegt wurde - dieses wird dann in der statischen Variable `instance` abgelegt. Sollte die Methode ein weiteres Mal aufgerufen werden, wird die Variable zurückgegeben und kein neues Objekt mehr erstellt. Wichtig ist auch, dass der **Konstruktor private** ist, damit nicht unverhofft von außen ein neues Objekt erzeugt werden kann.

### HTTP Requests

Request | Beschreibung  
------- | ---------  
GET | Daten vom Server abrufen  
POST | Daten an Server senden (für Weiterverarbeitung)  
PUT | Daten auf den Server hochladen  
DELETE | Daten vom Server löschen  

Mit diesen Requests kann über HTTP kommuniziert werden. Diese befinden sich im *Header*.

## Informationsübertragung über HTTP
Es gibt zwei Möglichkeiten über HTTP Informationen zu übertragen: In der **URL** oder im **Body**. Um die Informationen auszulesen (egal wie sie übermittelt wurden) braucht man das Modul **Body Parser**.

### [Body Parser](https://www.npmjs.com/package/body-parser)
  Installation: `npm install body-parser` `npm install --save-dev @types/body-parser`  
  Letzteres Kommando wird dazu verwendet, um in der `package.json` einzutragen, dass für die Entwicklung (und nur für die Entwicklung) die Typescript-Variante benötigt wird.  
  
  Der Body Parser stellt die übermittelten Informationen über eine Variable zur Verfügung.  
  Um ihn zu verwenden, muss er dem Server übergeben werden: `this._server.use(bodyParser.function());`
  
### Informationen in der URL
  Man kann mit HTTP Informationen nach der eigentlichen URL mit einem **?** getrennt übermitteln. In unserem Beispiel würde das so aussehen: **localhost:4711/data?index=0**. Mit einem **&** könnte man noch weitere Parameter übergeben. Diese Methode ist aber nur für Abfragen gut geeignet, da diese URL in der Browser-History abgespeichert wird. Sollte es sich um sensible Informationen handeln, bleiben diese ungeschützt am PC gespeichert.  

  Um Informationen aus der URL auslesen zu können, muss im Konstruktor folgendes eingetragen sein: `this._server.use(bodyParser.urlencoded());`  
  Dann kann über `req.query.xxx` die Variable abgerufen werden.

  Unsere Handler-Methode sieht daher wie folgt aus:  
```typescript
private handleGetData(req: express.Request, res: express.Response, next: express.NextFunction) {
        console.log('Server ' + this._port);
        const index = +req.query.index;
        if (index >= 0 && index < Database.getInstance().size()) {
            res.json(Database.getInstance().get(index));
        } else {
            res.status(400).send('invalid index');
        }
    }
```
Mit **localhost:4711/data?index=** kann nun ein spezieller Wert aus unserer Datenbank abgerufen werden. Sollte diese Zahl kleiner 0 oder größer als die Datenbank sein, wird ein Fehler mit dem Statuscode *400: invalid index* zurückgegeben.

### Informationen im Body
  Als nächstes möchten wir einen neuen Wert hinzufügen. Dazu benötigen wir die HTTP-Request **PUT**. Dieser Wert soll sich im Body des HTTP-Paketes befinden und dem JSON-Muster entsprechen.  

  Dem Konstruktor muss folgendes hinzugefügt werden:
```typescript
this._server.use(bodyParser.json());

this._server.put('/data',
            (req, res) => this.handlePutData(req, res));
```
  
  Dementsprechend muss auch eine neue Handler-Methode für */data* mit der Request **PUT** geschrieben werden:  
```typescript
private handlePutData(req: express.Request, res: express.Response) {
        try {
            const m = new Value(req.body.temp, req.body.power);
            Database.getInstance().add(m);
            res.send({id: Database.getInstance().size() - 1});
        } catch (err) {
            res.status(400).send('Bad Request');
        }
    }
```
  Mit `bodyParser.json());` werden Werte, die sich im Body in einer JSON-Codierung vorfinden in Variablen gespeichert, die mit `requ.body.xxx` abgerufen werden können. Diese Werte werden im Objekt *Value* verpackt der Datenbank übergeben. Sollte ein Problem auftreten, wird der Fehlercode *400: Bad Request* zurückgegeben.  

#### [RESTed](https://itunes.apple.com/at/app/rested-simple-http-requests/id421879749?mt=12)
  Da nun alles funktionstüchtig sein sollte, muss man es testen. Da wir einen **REST-Server** bauen, müssen wir die Maschine-zu-Maschine-Kommunikation irgendwie simulieren.  
  Eine Möglichkeit ist die App [RESTed](https://itunes.apple.com/at/app/rested-simple-http-requests/id421879749?mt=12). Der Name ist Programm - man kann an eine Server eine Request schicken, im Body etwas eintragen und die Response auslesen.  
  
  ![RESTed](Bildschirmfoto%202018-12-09%20um%2015.22.17.png)  
  Auf der linken Seite kann man die Parameter eintragen, die Codierung (JSON) auswählen und die Request-Methode (PUT) auswählen.  
  Auf der rechten Seite sehen wir das gesendete Paket und die Antwort: **HTTP/1.1 200 OK**, bzw es wurde zurückgesendet, dass der neue Wert die ID "4" bekommen hat. Würden wir nun **localhost:4711/dataset** aufrufen, würden wir sehen, dass ein wert dazugekommen ist:  
  ```json
  [{"time":"2018-12-09T14:21:40.799Z","temp":23.4,"tempUnit":"°C","power":100,"powerUnit":"W"},
  {"time":"2018-12-09T14:21:40.799Z","temp":23.5,"tempUnit":"°C","power":120,"powerUnit":"W"},
  {"time":"2018-12-09T14:21:40.799Z","temp":23.6,"tempUnit":"°C","power":150,"powerUnit":"W"},
  {"time":"2018-12-09T14:21:40.799Z","temp":23.7,"tempUnit":"°C","power":200,"powerUnit":"W"},
  {"time":"2018-12-09T14:21:40.799Z","temp":32,"tempUnit":"°C","power":300,"powerUnit":"W"}]
  ```
  
  Alternativen zu RESTed wären Browser-Extensions für Mozilla Firefox oder Google Chrome, aber die einzelnen Programme unterscheiden sich nicht wirklich in ihrer Funktionsweise.  
  
## Visual Studio: Attach Debugger Mode
  Da mein Mac aus irgendwelchen Gründen die Programme nicht launchen will (bei Lorenz funktioniert es), verwende ich nun die Methode über das Attachen des Debuggers.  
  Dazu muss in der `launch.json` ein neuer Eintrag erfolgen:  
```json
{
    "version": "0.2.0",
    "configurations": [
        
        {
            "type": "node",
            "request": "launch",
            "name": "Launch Program",
            "program": "${workspaceRoot}/src/main.ts",
            "cwd": "${workspaceRoot}/dist",
            "console": "integratedTerminal",
            "outFiles": [ "${workspaceRoot}/dist/*.js" ],
            //"trace": "all",
            "sourceMaps": true,
            "preLaunchTask": "build",
            "smartStep": true
        },
        {
            "type": "node",
            "request": "attach",
            "name": "Attach",
            "port": 9229
        }

    ]
}
```
  Das Programm wird über `node --inspect dist/main.js` gestartet und wenn ein Debugger benötigt wird, wird dieser über den Lanch-Button in vsCode attached. (Das funktioniert)
