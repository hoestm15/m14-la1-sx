# Protokoll 10.12.2018

## 4. Einheit
 
 Name: Markus Kobor  
 Klasse: 5AHME  
 Datum: 10.12.2018  
 Anwesend: Berger Emil, Bullner Jeremy, Böcksteiner Jakob, Ehmann Julian, Knappitsch Robert, Kobor Markus, Köhler Marcel
 Abwesend: Niemand <br> <br> <br>
## Wiederholung

### Express
Express ist ein einfaches und flexibles Node.js-Framework von Webanwendungen, welches das einfachere Entwickeln von Webanwendungen, mithilfe von vielen HTTP-Dinestprogrammmethoden, möglich macht. <br> <br>
Um es zu installieren sind folgende Schritte notwendig: <br>
1.  npm install express  → Express wird insatlliert.
2.  npm install --save-dev @types/express  → Die TypeScript-Variante von Express wird installiert und in die package.json eingetragen.

### Collections

Da es in TypeScript Collections wie die „Lists“ in Java nicht gibt, muss „Array“ verwendet werden, was über ähnliche Features wie beispielsweise eine ArrayList in Java verfügt. <br>
Alternativ kann man sich auch fertige Bibliotheken, von zum Beispiel Github, herunterladen um diese Funktionalitäten anbieten. <br><br>

## HTTP-Requests in unserem Programm:

GET: `this._server.get()`  Dieser Request dient zum Abrufen eines Wertes 

DELETE: `this._server.delete()` Dieser Request dient zum Löschen eines

POST: `this._server.post()`  Dieser Request dient zum Ändern eines Wertes   Wertes  

PUT: `this._server.put()`  Dieser Request dient zum Hinzufügen eines Wertes  <br><br>




## REST-Server: DELETE
  
Um einen Wert aus der Datenbank löschen zu können wurde zu erst eine Handler-Methode geschrieben:

```typescript
private handleDeleteData(req: express.Request, res: express.Response) {
    try {
        const id = +req.query.id;
        if (id >= 0 && id < Database.getInstance().size()) {
            Database.getInstance().remove(id);
            res.status(200).end();
        } else {
            throw new Error('invalid index ' + id);
        }
    } catch (err) {
        res.status(400).send('400 Bad Request');
    }
}
```
Der Index des zu löschenden Wertes muss wie oben erkenntlich mit „query“ übergeben werden. <br>

Die Handler-Methode wurde dann im Konstruktor an den Server übergeben:

```typescript
this._server.delete('/data',
    (req, res) => this.handleDeleteData(req, res));
```

Um HTTP-Requests wie Delete testen zu können benötigen wir ein HTTP-Client-Tool. Hierfür wurde „RESTed“ genützt. <br><br>


## REST-Server: POST   

Damit der HTTP-Request „POST“ richtig verwendet werden kann muss vor dem Erstellen einer Handler-Methode eine „edit“ Methode erstellt werden, welche regelt welcher der vorhandenen Werte auszutauschen ist.<br>
Dabei muss darauf geachtet werden, dass TypeScript gleichnamige Methoden nicht voneinander unterscheiden kann auch, wenn sich diese unterschiedliche Parameterlisten aufweisen. <br>
Um diese Problematik aus dem Weg zu räumen besteht die Möglichkeit des Signature Overloadings.
   
### Signature Overloading 

Mit Hilfe von „Signature Overloading“ werden nun auch die Parameter der Methoden berücksichtigt, wodurch diese nun auch unterschieden werden können:

```typescript
public edit (index: number, value: Value): void;
public edit (index: number, temp: number, power: number): void;
public edit (index: number, p2: any, power?: any): void {
    if (p2 instanceof Value) {
        this.data[index] = p2;
    } else if (typeof p2 === 'number' && typeof power === 'number') {
        this.data[index] = new Value(p2, power);
    } else if (typeof p2 === 'number' && typeof power === 'undefined') {
        this.data[index] = new Value(p2, this.getPower(index));
    } else if (typeof power === 'number' && typeof p2 === 'undefined') {
        this.data[index] = new Value(this.getTemp(index), power);
    }
}
```  
Da bei der dritten edit-Methode der dritte Parameter nicht verwendet werden muss, wird hier der „Fragezeichen-Operator“ angeführt.<br>

Im Quellcode können wir beim ersten „if“ sehen, dass wenn „p2 instance of Value“, also „p2“ ein Value-Objekt ist, dieses als Wert beim Index gesetzt wird.<br>

Kommen nun, wie beim ersten „else-if“ zu sehen, zwei Werte an, so entsteht ein neues Value-Objekt.<br>

Kommt jedoch nur ein Wert an so wird, für den nicht angekommenen Wert der bereits gespeicherte verwendet, was durch die beiden letzten „else-if‘s“ realisiert wurde.<br>

Nach der Realisierung von „edit“, wurden in der „database“ noch die Methoden „getpower()“ sowie „getTemp()“ angelegt:
 
  
```typescript
public getPower (index: number): number {
    return this.data[index].power;
}

public getTemp (index: number): number {
    return this.data[index].temp;
}
```  
<br>

## Testen von „POST“

Am Ende der Einheit wurde noch die Funktionalität unserer POST-Request überprüft.

![Ausgangszustand](https://github.com/HTLMechatronics/m14-la1-sx/blob/kobmam14/kobmam14/Vorher.PNG)

![Veränderte Werte](https://github.com/HTLMechatronics/m14-la1-sx/blob/kobmam14/kobmam14/Nachher.PNG)

Hier siet man, dass die Verbindung in den Headers auf keep-alive eingestellt ist.

Mit der Nutzung von HTTP ist es wichtig, dass eine einmal aufgebaute "kostbare" Verbindung nicht gleich wieder verworfen wird.<br>
So wurde im HTTP-Header das Feld "Connection: keepalive" definiert, mit dem der Client dem Server sagen kann, dass die Verbindung nach der Antwort nicht abgebaut werden soll und weitere Anfragen sequentiell folgen können.
