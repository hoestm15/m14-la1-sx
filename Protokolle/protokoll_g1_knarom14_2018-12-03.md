# Protokoll: Knappitsch Robert
## 3. Einheit: REST-Server

* 5AHME (Gruppe 1)
* Datum: 03.12.2018
* Anwesend: Berger Emil, Bullner Jeremy, Ehmann Julian, Knappitsch Robert, Köhler Marcel
* Abwesend: Böcksteiner Jakob, Kobor Markus

## Wiederholung

### Express
Da das Arbeiten mit der HTTP- und der HTTPS-Methode in node.js schwierig ist, wird bei der Programmierung von Servern sehr oft das Modul Express.js verwendet. Die Installation erfolgt über den Konsolen-Befehl ```npm install express```. Um Express auch für Typescript verfügbar zu machen, wird zusätzlich der Befehl ```npm install --save-dev @types/express``` benötigt.

### Singleton
```Typescript
    public static getInstance(): Database {
        if (!this.instance) {
            this.instance = new Database();
        }
        return this.instance;
    }
    
    private static instance: Database;
```
In der Klasse database.ts verwenden wir das Entwurfsmuster Singleton. Bei jedem Aufruf von ```getInstance()``` wird überprüft, ob bereits ein Objekt der Klasse existiert. Wenn nicht, dann wird ein neues angelegt und in der Variable ```instance``` gespeichert. Zusätzlich ist der Konstruktor private, um zu verhindern, dass von außen ein neues Objekt erzeugt wird. Dieses Entwurfsmuster ist besonders in einer Datenbank-Klasse sinnvoll, da so alle Daten gesammelt in einem Objekt gespeichert werden können.

Ein anderes Entwurfsmuster wäre zum Beispiel *immutable* bei dem nur mit Getter- und Setter-Methoden auf die Daten zugegriffen werden kann.

### getAll()
```Typescript
    public getAll (): Value [] {
        return [].concat(this.data);
    }
```
Diese Methode der Klasse database.ts gibt, anstatt des originalen Arrays, ein neues mit dem selben Inhalt zurück. Ansonsten hätte man von außen direkten Zugriff auf die Datenbank und könnte Daten verändern.

### Hinzufügen von neuen Modulen in node.js
Auf der Website [www.npmjs.com](www.npmjs.com) kann man alle verfügbaren Module heruterladen. Dies erfolgt über den Konsolen-Befehl ```npm install <Modul-Name>```. Doch bevor man ein Modul installiert, sollte man überprüfen, ob die Verwendung sicher ist. Dafür sieht man sich einfach die Anzahl der wöchentlichen Downloads an. Im Falle von *body-parser* liegt diese Zahl zur Zeit bei 7.615.798. Dieses Modul kann man also bedenkenlos verwenden.

## Übertragen von Informationen mit HTTP

### Body-Parser
Dieses Modul fügt eine Variable hinzu, mit der man Daten aus der URL oder des Bodys eines HTTP-Requests auslesen kann.

Die Installation erfolgt über den Konsolen-Befehl ```npm install body-parser```. Durch einen Eintrag in der package.json macht der Befehl ```npm install --save-dev @types/body-parser``` das Modul auch für Typescript verfügbar.

#### URL
Mit einem **?** können Daten direkt in der URL übergeben werden. Mit ```localhost:4711/data?index=2``` fordert man in unserem Fall des dritte Element der Datenbank an und bekommt dieses im .json-Format. Sollte an diesem Index nichts in der Datenbank stehen, bekommt man *Invalid Index* zurück. Bearbeitet werden diese Requests mit ```bodyParser.json()```. 

Diese Möglichkeit der Datenübertragung wird allerdings nur für unsensible Daten verwendet, da diese in der Browser-History gespeichert werden.

#### Body
Mit Tools wie z.B. RESTed(einfach als Browser-AddOn herunterladen) können bei einer HTTP-Request Daten im Body mitgesendet werden. Dadurch scheinen diese Daten nicht im Verlauf des Browsers auf und die URL wird nicht unnötig lang, wie es z.B. bei mehreren Microsoft Produkten der Fall ist.

Wir verwenden diese Möglichkeit der Datenübertragung um mit dem Schlüsselwort **PUT** Einträge in die Datenbank zu tätigen. Um Daten aus der URL zu lesen verwenden wir ```bodyParser.urlencoded()```

```Typescript
    private handlePutData (req: express.Request, res: express.Response, next: express.NextFunction) {
        try {
            const m = new Value(+req.body.temp, +req.body.power);
            Database.getInstance().add(m);
            res.send({id: Database.getInstance().size() - 1});
        } catch (err) {
            res.status(400).send('400 Bad Request');
        }
    }
```
Mit dieser Methode behandeln wir PUT-Requests am Server. Es wird ein neues Objekt vom Typ *Value* erzeugt und zur Datenbank hinzugefügt.


