# Protokoll
  Böcksteiner Jakob 
  5AHME, Gruppe 1  
  10.12.18  
  Anwesend: Berger, Böcksteiner, Bullner, Ehmann, Knappitsch, Kobor, Köhler  
  Abwesend: niemand  
  
# Wiederholung

## Installation von Modulen
  *Bsp: Installieren von express*
  Zuerst `npm install express` 
  Danach `npm install --save-dev @types/express`
  
## Verwenden der HTTP-Requests in unserem Programm:

GET -> `this._server.get()`  -> Abrufen 

PUT -> `this._server.put()`  -> Hinzufügen

POST -> `this._server.post()`  -> Ändern

DELETE -> `this._server.delete()` -> Löschen 

# DELETE 

  Um einen Wert zu löschen muss man eine Handler-Methode schreiben und diese an den Constructor des Servers weitergeben.
  Der Index des Wertes wird in der URL mit *query* übergeben.
  
  Contructor  
```typescript
this._server.delete('/data',
    (req, res) => this.handleDeleteData(req, res));
```

  Handler-Methode
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
  Porblem: Die Idizes der dahintergereihten Werte änderns sich.

# POST 

  Vor der Handler-Methode müssenw wir noch eine Methode zum editieren der Datenback schreiben. Javascript kann nicht mehrere Methoden mit dem gleichen Namen und unterschiedlicher Parameterliste haben da Javascript keine Datentypen hat. Möglichkeit dafür ist Signature Overloading.
  
## Signature Overloading
  Bsp:  
```typescript
// Signature Overloading in TS
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
 
  
  Value kommt an -> Indexwert 
  zwei Werte -> neues Objekt  
  ein Wert -> alter Wert wird für den zweiten Wert verwendet
  
  Damit das funktioniert bracuht man noch zwei Methoden in der Klasse *database*.
```typescript
public getPower (index: number): number {
    return this.data[index].power;
}

public getTemp (index: number): number {
    return this.data[index].temp;
}
```

## Testen von POST

### Ausgangszustand
```json
[{"time":"2018-12-10T19:11:02.486Z","temp":23.4,"tempUnit":"°C","power":100,"powerUnit":"W"},
{"time":"2018-12-10T19:11:02.486Z","temp":23.5,"tempUnit":"°C","power":120,"powerUnit":"W"},
{"time":"2018-12-10T19:11:02.486Z","temp":23.6,"tempUnit":"°C","power":150,"powerUnit":"W"},
{"time":"2018-12-10T19:11:02.486Z","temp":23.7,"tempUnit":"°C","power":200,"powerUnit":"W"}]
```

### Ändern beide Werte
  **Request:**  
  ![2 Werte](boejam13/2_rest)
  **Response:**  
```json
[{"time":"2018-12-10T19:07:11.529Z","temp":50,"tempUnit":"°C","power":1000,"powerUnit":"W"},
{"time":"2018-12-10T19:07:11.529Z","temp":23.5,"tempUnit":"°C","power":120,"powerUnit":"W"},
{"time":"2018-12-10T19:07:11.529Z","temp":23.6,"tempUnit":"°C","power":150,"powerUnit":"W"},
{"time":"2018-12-10T19:07:11.529Z","temp":23.7,"tempUnit":"°C","power":200,"powerUnit":"W"}]
```

### Ändern ein Wert 
  **Request:**  
  ![1 wert](boejam13/1_rest)  
  **Response:**  
```json
[{"time":"2018-12-10T19:11:44.008Z","temp":50,"tempUnit":"°C","power":2000,"powerUnit":"W"},
{"time":"2018-12-10T19:11:02.486Z","temp":23.5,"tempUnit":"°C","power":120,"powerUnit":"W"},
{"time":"2018-12-10T19:11:02.486Z","temp":23.6,"tempUnit":"°C","power":150,"powerUnit":"W"},
{"time":"2018-12-10T19:11:02.486Z","temp":23.7,"tempUnit":"°C","power":200,"powerUnit":"W"}]
```


