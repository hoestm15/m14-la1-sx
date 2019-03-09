# 4.Protokoll  
**Name:** Ehmann Julian   
**Datum:** 10.12.2018  
**Uhrzeit:** 8:00-10:30  
**Gruppe:** 1  
**Anwesend**: Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Knappitsch Robert, Kobor Markus, Köhler Marcel  
**Abwesend**: niemand

# Wiederholung

## Installation von Modulen
  *Installieren von Express*
  
  Erstens:  `npm install express` damit Express installiert wird.  
  Zweitens:  `npm install --save-dev @types/express` hier wird die TypeScriptVariante von Express installiert.
  
## Verwenden der HTTP-Requests in unserem Programm:

GET = `this._server.get()`  mit dieser Methode wird ein Wert abgerufen  

PUT = `this._server.put()`  mit dieser Methode wird ein Wert hinzugefügt  

POST = `this._server.post()`  mit dieser Methode kann ein Wert verändert werden  

DELETE = `this._server.delete()` mit dieser Methode kann ein Wert gelöscht werden

## REST-Server: Delete  
   Damit irgendeiner dieser Befehle getestet werden kann, wird ein HTTP-Client Tool benötigt. Ein Beispiel hierfür wäre RESTed.  
   
   Um einen Wert löschen zu können ist eine Handler-Methode von nöten. Diese wird in weiterer Folge an den Constructor übermittelt. Der    Index eines Wertes muss mit **query** übergeben werden.  
   
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

## REST-Server: POST   
  
  Bei der Handler-Methode für *POST* müssen wir jedoch beachten, dass wir zuvor eine Methode `edit();` erstellen müssen.  
  Würde man das gleiche in Java machen wollen, würde man gleichnamige Methoden, aber mit unterschiedlichen Parametern erzeugen. Da     TypeScript in JavaScript übersetzt wird, JavaScript aber keine Datentypen kennt kann man diese nicht so schreiben, da die Methode nicht durch die Parameterliste unterschieden werden kann. Eine Möglichkeit hierfür wäre Signature Overloading.  
  
### Signature Overloading
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
 Diese Methode achtet alle Paramter, welche in ihr deklariert sind, nutzt jedoch nur die beim Aufruf übergebenen.  
 
 Wenn **ein** Value ankommt, wird dieser als Index genommen.  
 Wenn **zwei** Values ankommen, wird ein neues Objekt aus diesen erzeugt.
 
  
```typescript
public getPower (index: number): number {
    return this.data[index].power;
}

public getTemp (index: number): number {
    return this.data[index].temp;
}
```  
  Damit das weiter oben beschriebene auch so funktioniert, sind die beiden überhalb stehenden Methoden von nöten.

## Testen von POST

### Ausgangszustand
![Ausgangszustand](https://github.com/HTLMechatronics/m14-la1-sx/blob/boejam13/boejam13/rest_1.png)

### Ändern der Werte
![Veränderte Werte](https://github.com/HTLMechatronics/m14-la1-sx/blob/boejam13/boejam13/rest_2.png)
