# 4.Protokoll
**Name:** Lukas Strauß   
**Datum:** 11.02.2019    
**Gruppe:** 4  
**Anwesend**: Strauß Lukas,Strutz Sebastian,Tuttner Raphael,Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz  

## Wiederholung der letzten Einheit  

Am Anfang haben wir das in den letzten Einheiten gemachte erneut durchbesprochen, das es schon einige Zeit her ist, seit 
wir das letzte mal gehabt haben.

## Collections in Java und JavaScript  
Für eine Datenspeicherung können Java Collections verwendet werden. Wichtige Beispiele für Collections sind:  

* ArrayList     -> Bei der ArrayList wird ein Feld mit einer bestimmten Größe erstellt. Wird das Feld zu klein dann
                   wird automatisch das Feld um das doppelte vergrößert.  
                   
* HashMap       -> Für jedes Element in der Map wird ein KeyValue Paar erzeugt. Damit können danach schnell verschiedene
                   Elemente gefunden werden.  
                   
* HashSet       ->Das HashSet ist ähnlich wie die LinkedList. Dabei darf beim HashSet ein Element nur einmal vorkommen.  

* Linked List   -> In der LinkedList werden alle Daten hintereinander gespeichert. Daher wird diese Liste erst zum Vorteil, 
                   wenn man alle Werte in der Liste hintereinander abrfragen will und einzelne Elemente herauslöschen will.


## Rest-Server

Der Represantational State Transfer dient vorallem zur Maschine zu Maschine Kommunikation. Das heißt zum
Beispiel ein Smartphone mit einen entfernten PS oder Raspberry. Für diese Verbindungen werden zwei wichtige
Technologien verwendet. Zu einem wird das HTTP Protokoll verwendet und als zweites wird das TCP Protokoll für
die Verbindung verwendet. Das HTTP-Protokoll benötigt man für die Datenübertragung. Die Überragung erfolgt dabei
textuell. Benötigt man eine verschlüsselte Übertragung dann git es dafür das HTTPS-Protokoll. Für die Kommunikation
gibt es einige Befehle. Die wichtigsten sind:   

 
* **PUT**:     --> Daten zum Server schicken 
* **DELETE**:  --> um bestehende Daten am Serve zu löschen
* **GET**:     --> wenn man Daten vom Server bekommen will.  
* **POST**:    --> ändern von bestehenden Daten am Server 
 
### In Javascript:  
* Listen werden durch Felder (Arrays) ersetzt.
* Maps werden durch Objekte (Objects) ersetzt.  

###  Singelton

Singelton ist ein Entwurfsmuster welches sicherstellt, dass es ein Objekt einer Klasse nur einmal gibt.
Das Singelton wird auch Einzelstück genannt. Dieses Einzelstück ist meistens global verfügbar.
Da wie in unseren Fall eine Datenbank nur einmal existiert und nur die Werte einer Datenbank geändert werden,
ist es sinnvoll, dieses Entwurfsmuster zu verwenden. Das erreicht man, wenn man den Konstruktor private setzt
und eine statische Methothe mit dem Namen getInstance() am Beginn aufgerufen wird, die beim ersten Aufruf ein
Objekt erzeugt. Deises Objekt wird danach in einer statischen Variable instance abgelegt.


## Programmierung Server Client ! 

Es gibt einige Programmiersprachen mit denen man programmieren kann. Wir haben uns entschieden, dass wir den Server 
und den Client mit JavaScript programmieren. 
Der große Vorteil dabei ist, dass man nie zwischen 2 Sprachen hin und her switchen muss. Daher kann man sich daher
sehr gut auf eine Sprache konzentrieren und kommt damit auf bessere Lösungen. Der Server benötigt mit JavaScript 
eine virtuelle Maschine. Diese wird **Node.js** genannt. Andere Sprachen für einen Server wären JAVA, PHP,der Pearl. 
Für den Client wird hauptsächich JavaScript verwendet. Da es bei JavaScript aber keine Datentypen gibt und man daher 
keine Fehlerüberprüfung hat, verwenden wir im Unterricht die Subsprache von Javascript. Diese Subsprache ist **Typescript**.


  
### server.ts  

In der Server.ts Klasse bekommt der Server die Clientanfrage, verarbeitet sie
und gibt die passende Antwort auf den Client zurück. Wir haben diese Klassen mit 3 weiteren Methoden
(**handlePutStudent, handlePostStudent, handleDeleteStudent)** erweitert. 


```typescript
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
```  
Die Methode 'handlePutStudent' Methode wird wie man schon erkennen kann für eine 'PUT'-Anfrage vom Client verwendet.
Dabei wird zuerst abgefragt ob es diesen Student in der Datenbank schon gibt. Wenn es den Student nicht gibt wird 
er hinzugefügt, ansonsten wird eine Fehlermeldung zurückgegeben. Die 'handlePostStudent' Methode wird wie man schon
erkennen kann für eine 'POST'-Anfrage vom Client verwendet. Dabei wird wie in der Put Handler-Methode zuerst 
abgefragt ob des diesen Student gibt. Falls es diesen gibt wird er danach geändert, ansonsten wird wieder eine
Fehlermeldung augegeben. Bei der Handler-Methode **handleDeleteStudent** wird auch wieder abgefragt ob sich der Student
in der Datenbank befindet und wird danach gelöscht. Wenn der richtige Schüler nicht in der Datenbank vorkommt, dann 
wird eine Fehlermeldung an den Client gesendet. 

### database.ts  
Die Klasse 'database.tsw' representiert unsere Datenbank. Diese Klasse wird nach dem Entwufsmuster 'Singelton'(siehe oben) programmiert.
In dieser Klasse befinden sich 4 Methoden, damit man einen Student aus der Datenbank einfügen, bearbeiten, löschen und #
herausholen kann.  In der letzten Einheit mussten wir noch 2 Methoden einfügen, damit wir einen Schüler ändern
und löschen können.  

```typescript
public remove (htlid: string) {
        delete this.students[htlid];
    }
    public set (s: Student): Student {
        const rv = this.get(s.getHtlid());
        this.students[s.getHtlid()] = s;
        return rv;
    }
```   

### student.ts  
Die # 'student.ts' Klasse representiert eine Datenhaltungsklasse für einen Schüler. Die Klasse besitzt gleich wie in Java Getter-Methoden, damit man die Datenelemente in der Klasse abfrragen kann, da diese private sind. In dieser Klasse haben wir ein Inerface erstellt. Mit diesem Interface können wir das Objekt vom Request-Body in ein Studet-Objekt casten können.  Dieses Interface muss natürlich *export* beinhalten, weil wir das Interface in der Klasse *server.ts* benötigen.  
```typescript
export interface IStudent {
    htlid: string;
    surname: string;
    firstname: string;
```   
