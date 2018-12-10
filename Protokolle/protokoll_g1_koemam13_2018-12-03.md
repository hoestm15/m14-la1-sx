
# Protokoll: Marcel Köhler
## 3.Einheit
## Thema: REST Server
Klasse: 5AHME  
Anwesend: Berger, Bullner, Ehmann, Knappitsch, Köhler  
Abwesend: Böcksteiner, Kobor


## Wiederholung der letzten Einheit.
### Express-Modul
Dieses Modul vereinfacht die programmierung eines HTTP/HTTPS-Server.
Es benutzt die bereits vorhandenen HTTP/HTTPS Module von Node.js.  
Um Express nutzen zu können, muss mann es zuerst installieren. Dies kann mann mit dem Konsolen Befehl `npm install express`. Unter anderem benötigt mann dazu auch noch die zusätzlichen Typen der Variablen für das Modul. Da mann diese aber nur zum Entwickeln der Software braucht, wird dieses Modul mit dem `npm install --save-dev @types/express` installiert. Mann sieht anschließend das beide Module in der `package.json` Datei eingetragen wurden.

```typescript
"devDependencies": {
    "@types/express": "^4.16.0",
  }
  
 "dependencies": {
    "express": "^4.16.4"
  }
  ```
  
  ### Singleton
  Singleton ist ein Entwurfsmuster für Datenbanken. Es wird dann angewendet wenn ein Datensatz nur einmal vorkommen soll.  
  Mit der folgenden Klasse haben wir dieses Entwurfsmuster umgesetzt.
  
  ```typescript
  private static instance: Database;

public static getInstance (): Database {
        if (!this.instance) {
            this.instance = new Database();
        }
        return this.instance;
    }
  ```
  
  Die Methode `getInstance()` erstellt ein neues Objekt aber nur dann wenn es noch kein bestehendes Objekt gibt. Wenn es noch kein existierendes Objekt gibt wird das neu erstellte Objekt in der statischen Variable `instance` abgelegt. Wird die Methode weitere male aufgerufen so wird kein neues Objekt erstellt sondern das bereits bestehende Objekt zurückgegeben. Das wichtigste ist aber, dass der Konstruktor private ist, damit niemand von außen ein neues Objekt erzeugen kann.
  
  #### getAll()
  ```typescript
  public getAll (): Value [] {
        return [].concat(this.data);
    }
  ```
  
Da wir sicher sein wollen das niemand von außen an die originale Datenbank direkt herankommt wird bei dieser Methode ein zweites Array mit dem selben Inhalt des ursprünglichen Arrays erzeugt. Dieses Array wird anschließend zurückgegeben.


### HTTP Requests

**Request** | **Beschreibung**
------------|-----------------
Get| Daten vom Server abrufen
Post|Daten an den Server senden
Put| Neue Daten auf den Server hochladen
Delete|Daten vom Server löschen
  
  
## Informationsübertragung mittels HTTP-Requests
Mann kann mittels zwei Möglicheiten Informationen übertragen. Entweder mit der **URL** oder mit dem **Body**.
Egal welche Möglichkeit mann verwendet mann brauch in beiden Fällen das **Body-Parser** Modul.


### Das Body-Parser Modul
Diese Modul ermöglicht es uns Anfragen automatisch als Variablen zu speichern. Es legt für alle Übermittelten Informationen eine Variable an.  
Dieses Modul installiert mann mit dem folgenden Konsolen Befehl: `npm install body-parser`  
Aber gleich wie bei dem Express Modul benötigt mann auch das dazu gehörige Variablen modul welches mann mit dem folgenden Befehl installiert: `npm install --save-dev @types/body-parser`  
Aber damit dieses Modul verwendet wird muss mann dies dem Server zuerst bekannt geben. Hierbei ist es wichtig die Reihenfolge zu beachten und das Modul möglichst weit oben bekannt zu geben. Dies macht mann mit der folgenden Funktion.
```typescript
this._server.use(bodyParser.function());
```
### Informationen in der URL
Wenn mann die Informationen mit der URL sendet kann man diese einfach reinschreiben mann muss nur nach der abfrage einen verweis dazu machen, damit der Server weiß das es sich um eine Abfrage handelt. Dieser Verweis ist in diesem Falle das Fragezeichen **?**. Um weitere Informationen auf einmal zu senden muss man das Kaufmännische UND **&** nach jeder Information verwenden. Eine Abfrage könnte so aussehen: `localhost:4711/data?index=0`

**Die Handler-Methode**
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
Mit dieser Methode kann mann nun einen speziellen Wert aus der Datenbank abrufen. Dies machen wir indem wir den Index aus der Variable `req.query.index` holen. Diesen Index setzten wir dann anschließend in unsere get Methode der Datenbank ein.
Sollte der index jedoch **kleiner als 0** oder **großer als die Anzahl der Datensätze** sein wird eine response mit dem Statuswert **400** und einer Nachricht "invalid index" zurück gesendet.

### Informationen in dem Body
Hiermit werden Informationen mit hilfe des Bodys an den server gesendet. Hierzu wird die **PUT** request benutzt. Die Informationen werden im **json** Format übertragen.  
Damit dies auch funktioniert muss dem Konstruktor des servers noch etwas hinzugefügt werden, da er sonst nichts mit der **PUT** request anfangen kann.

```typescript
this._server.use(bodyParser.json());

this._server.put('/data',
            (req, res) => this.handlePutData(req, res));
```
Dies reicht aber nochnicht aus. Es muss zusätzlich noch eine Handler-Methode geschrieben werden die diese **PUT** request verarbeitet.

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
In dieser Handler Methode erstellen wir ein Neues **Value** Objekt mit den Daten aus dem Body, welche wir mittels req.body.abc aus der request bekommen. Dieses neue Objekt wird dann anschließend der Datenbank hinzugefügt. Zum abschluss wird eine response im JSON Format zurückgesendet. Diese beinhaltet die ID des neu hinzugefügten Objektes. Für den Fall das etwas bei diesem Vorgang schief läuft wird eine response mit dem Statuscode **400** und der Nachricht "Bad Request" zuruck gesendet.

## [RESTED](https://addons.opera.com/en/extensions/details/rested/)
Um zu testen ob der Server so funktioniert wie wir es möchten benutze ich die Browser extension **RESTED**. Mit diesem Tool können wir eine Maschine-zu-Maschine Kommunikation aufbauen. 
![Rested](https://github.com/HTLMechatronics/m14-la1-sx/blob/koemam13/Protokolle/Bilder/rested.svg)
Auf der Linken Seite kann mann die Collections auswählen und auch den Verlauf anzeigen lassen.
Auf der Rechten Seite kann man auswählen welche art von Request mann machen möchte. In diesem Fall handelt es sich um eine **PUT** request. Diese Request wird automatisch im JSON Format gesendet. Zuerst muss mann die URL eingeben. Dann wählt mann die Request Methode aus und anschließend welchen Wert mann senden möchte.
Diese Tool zeigt zudem auch direkt die Antwort des Servers.
