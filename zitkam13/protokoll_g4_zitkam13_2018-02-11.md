# 4.Protokoll
**Name:** Zitz Karlheinz   
**Datum:** 11.2.2018  
**Uhrzeit:** 8:00-10:30  
**Gruppe:** 4  
**Anwesend**: Strauß Lukas,Strutz Sebastian, Tuttner Raphael,  Uhl Christian  Waltl Kilian, Wieser Markus, Zitz Karlheinz  

## Wiederholung der letzten Einheiten  

Da die letzte einheit schon anfang November gewesen ist haben wir am Beginn einige Themen unseres Projektes wiederholt. Wir besprachen auch was wir in den jeweiligen Klassen programmiert haben und für was wie die jeweilige Klasse benötigen. 

### Was ist ein Rest-Server?
Ein Rest-Server wird verwendet für eine Kommunikation zwischen Maschine und Maschine. Das hei0t zum Beispiel ein Smartphone mit einen entfernten PS oder Raspberry. Für diese Verbindungen werden zwei wichtige Technologien verwendet. Zu einem wird das HTTP Protokoll verwendet und als zweites wird das TCP Protokoll für die Verbindung verwendet. Das HTTP-Protokoll benötigt man für die Datenübertragung. Die Überragung erfolgt dabei textuell. Benötigt man eine verschlüsselte Übertragung dann git es dafür das HTTPS-Protokoll. Für die Kommunikation gibt es einige Befehle. Die wichtigsten sind:  
* **GET**:     Benötigt man, wenn man Daten vom Server bekommen will.  
* **POST**:    Benötigt man, wenn man bestehende Daten Am Server ändern will.  
* **PUT**:     Benötigt man, wenn man neue Daten auf den Server schicken will. 
* **DELETE**:  Benötigt man, wenn man bestehende Daten am Server löschen will. 

Das HTTP Protokoll gibt nach der Anfrage immer einen Statuscode zurück. Diese können [hier](https://en.wikipedia.org/wiki/List_of_HTTP_status_codes) nachgelesen werden. 
Der Name **REST-Server** steht für  **RE**presentational **S**tate **T**ransfer **Server**.  Weitere Informaionen für den Rest-Server findet man [hier](https://de.wikipedia.org/wiki/Representational_State_Transfer) .  

### Wie programmiert man den Server doer Client?  
Für die Programmierung einem Server und einem Client gibt es einige Programmiersprachen mit denen man programmieren kann. Wir haben uns entschieden, dass wir den Server und den Client mit JavaScript programmieren. Der große Vorteil dabei ist, dass man nie zwischen 2 Sprachen hin und her switchen muss. Daher kann man sich daher sehr gut auf eine Sprache konzentrieren und kommt damit auf bessere Lösungen. Der Server benötigt mit JavaScript eine virtuelle Maschine. Diese wird **Node.js** genannt. Andere Sprachen für einen Server wären JAVA, PHP,der Pearl. Für den Client wird hauptsächich JavaScript verwendet. Da es bei JavaScript aber keine Datentypen gibt und man daher keine Fehlerüberprüfung hat, verwenden wir im Unterricht die Subsprache von Javascript. Diese Subsprache ist **Typescript**. 

### Collections in Java und JavaScript  
Für eine Datenspeicherung können Java Collections verwendet werden. Wichtige Beispiele für Collections sind:  
* ArrayList     -> Bei der ArrayList wird ein Feld mit einer bestimmten Größe erstellt. Wird das Feld zu klein dann wird automatisch das Feld um das doppelte vergrößert.  
* Linked List   -> In der LinkedList werden alle Daten hintereinander gespeichert. Daher wird diese Liste erst zum Vorteil, wenn man alle Werte in der Liste hintereinander abrfragen will und einzelne Elemente herauslöschen will.  
* HashMap       -> Für jedes Element in der Map wird ein KeyValue Paar erzeugt. Damit können danach schnell verschiedene Elemente gefunden werden.  
* HashSet       ->Das HashSet ist ähnlich wie die LinkedList. Dabei darf beim HashSet ein Element nur einmal vorkommen.  

#### In Javascript:  
* Listen werden durch Felder (Arrays) ersetzt.
* Maps werden durch Objekte (Objects) ersetzt.  

## Wiederholung und Erweiterung der bestehenden Klassen  
### server.ts  
In der Klasse **server.ts** wird unser Server realisiert. Das heißt der Server bekommt die Clientanfrage, verarbeitet sie und gibt die passende Antwort auf den Client zurück. Wir haben diese Klassen mit 3 weiteren Methoden (**handlePutStudent, handlePostStudent, handleDeleteStudent)** erweitert. 

 private handlePostStudent(req: express.Request, resp: express.Response, next: express.NextFunction) {
        console.log(req.query.htlid);
        const s = <IStudent>req.body;
        try {
        const stud = new Student(s.htlid, s.surname, s.firstname);
        if (Database.getInstance().get(stud.getHtlid())) {
            Database.getInstance().set(stud);
            resp.status(200).end();
            return;
        }
        resp.status(400).send('hdlid not exist');
        resp.end();
    } catch (err) {
            console.log(err);
            resp.status(404).send('invalid JSON data');
            resp.end();
    }
    }
    private handleDeleteStudent(req: express.Request, resp: express.Response, next: express.NextFunction) {
        try {
        if (Database.getInstance().get(req.query.htlid)) {
            Database.getInstance().remove(req.query.htlid);
            resp.status(200).end();
            return;
        }
        resp.status(400).send('htlid not found');
    } catch (err) {
            console.log(err);
            resp.status(404).send('invalid JSON data');
            resp.end();
    }
    }
    private handlePutStudent (req: express.Request, resp: express.Response, next: express.NextFunction) {
        console.log(req.query.htlid);
        // Abfragen obs einen Studenten gibt sonst muss post verwendet werden wenn es sschon einen gibt
        const s = <IStudent>req.body;
        try {
        const stud = new Student(s.htlid, s.surname, s.firstname);
        if (Database.getInstance().get(stud.getHtlid())) {
            resp.status(400).send('htlid already exists');
            resp.end();
            return;
        }
        Database.getInstance().add(stud);
        resp.status(200).end();
        } catch (err) {
            console.log(err);
            resp.status(404).send('invalid JSON data');
            resp.end();
        }
    }
