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

In der Klasse **server.ts** wurde die Methode ``` handleDeleteData ``` hinzugefügt:
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
Über die URL-Query id wird die gewünschte ID von Client festgelegt. Dies kann zum Beispiel mit dem Tool RESTED erfolgen.
