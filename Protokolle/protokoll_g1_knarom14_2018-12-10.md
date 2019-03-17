# Protokoll: Knappitsch Robert
## 4. Einheit: REST-Server

* 5AHME (Gruppe 1)
* Datum: 10.12.2018
* Anwesend: Berger Emil, Böcksteiner Jakob, Bullner Jeremy, Ehmann Julian, Knappitsch Robert, Kobor Markus, Köhler Marcel
* Abwesend: -

### Löschen eines Eintrages - DELETE
Um einen Wert löschen zu können, verwendeten wir die Methode ``` remove ```, welche wir bereits in der zweiten Einheit erstellt haben:

``` TypeScript
public remove (index: number) {
    this.data.splice(index, 1);
}
```
Diese bekommt den Index des zu löschenden Elements übergeben und entfernt dieses mithilfe der ```splice```-Methode.

Diese Lösung hat allerdings zur Folge, dass nach einem erfolgreichen Löschvorgang alle nachfolgenden Einträge nachrücken und somit ihren Index ändern. Dies könnte durch die Verwendung von ```Object``` anstatt eines Arrays behoben werden. Dieses hat nämlich ähnliche Funktionen, wie eine ```HashMap``` in Java. 

In der Klasse **server.ts** wurde die Methode ``` handleDeleteData ``` hinzugefügt. Wenn ein gültiger Index vorliegt, wird die oben beschriebene Methode ```remove``` aufgerufen und der Code ```200``` als Antwort gesendet. Sollte kein gültiger Index vorliegen, wird lautet die Antwort ```400 invalid index```.
``` TypeScript
private handleDeleteData (req: express.Request, res: express.Response, next: express.NextFunction) {
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
Natürlich musste ```handleGetData``` auch im Konstruktor eingetragen werden.
```TypeScript
this.server.delete('/data', (req, res, next) => this.handleDeleteData(req, res, next));
```

Über die URL-Query id wird die gewünschte ID von Client festgelegt. Dies kann zum Beispiel mit dem Tool RESTED erfolgen.

![DELETE RESTED](https://github.com/HTLMechatronics/m14-la1-sx/blob/knarom14/Protokolle/delete_rested.png)

### Bearbeiten eines Eintrages - POST
Für das Bearbeiten von bereits existierenden Datenbankeinträgen wurde eine neue Methode in der Datenbank-Klasse hinzugefügt:

``` TypeScript
public edit (index: number, value: Value) {
    if (value.temp !== undefined && value.power !== undefined) {
        this.data[index] = value;
    } else if (value.temp !== undefined && value.power === undefined) {
        this.data[index] = new Value(+value.temp, this.data[index].power);
    } else if (value.temp === undefined && value.power !== undefined) {
        this.data[index] = new Value(this.data[index].temp, +value.power);
    } else {
        throw new Error();
    }
}
```
Als Parameter werden der Index des betroffenen Elements und ein Objekt vom Typ ```Value```, welches die zu ändernden Daten enthält, übergeben. Nun wird überprüft, ob die Werte für Temperatur und Leistung einen Wert enthalten oder ```undefined``` (nicht definiert) sind. Falls keiner der zwei Werte definiert ist, wird ein Fehler geworfen. Nun wird an der Stelle des alten Eintrages ein neuer eingefügt, der die neuen Werte enthält.

Eine andere Lösung für diese Aufgabe wäre die Verwendung von **Signature Overloading**. Dabei werden mehrere Köpfe für die selbe Methode erstellt:
```TypeScript
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
So können verschiedene Parameter übergeben werden:
* als Objekt ```Value```, wenn beide Werte geändert werden sollen
* beide Werte als ```Number```
* nur einer von beiden Werten ist definiert

Der dritte Parameter wird mit dem ```?```-Operator versehen, um anzuzeigen, dass dieser nicht unbedingt vorhanden sein muss.

Auch in der Server-Klasse wurde eine Methode zum Bearbeiten mit dem Namen ```handlePostData``` erstellt:
```TypeScript
private handlePostData (req: express.Request, res: express.Response, next: express.NextFunction) {
    try {
        const id = +req.query.id;
        const m = new Value(+req.body.temp, +req.body.power);
        if (id >= 0 && id < Database.getInstance().size()) {
            Database.getInstance().edit(id, m);
            res.status(200).send();
        } else {
            throw new Error('invalid index ' + id);
        }
    } catch (err) {
        res.status(400).send('400 Bad Request');
    }
}
```
Diese ruft, wie ```handleDeleteData``` die dazugehörige Datenbank-Methode auf, wenn ein gültiger Index vorliegt. 

Und auch sie wird in den Konstruktor eingetragen:
```TypeScript
this.server.post('/data',   (req, res, next) => this.handlePostData(req, res, next));
```

Zum Testen kann auch hier, RESTED verwendet werden:

![POST RESTED](https://github.com/HTLMechatronics/m14-la1-sx/blob/knarom14/Protokolle/post_rested.png)

Dieses Mal werden zusätzlich zur ID in der URL-Query auch die gewünschten Daten im Body übergeben.
