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

### Übertragen von Informationen mit HTTP
#### URL
Mit einem *?* können Daten direkt in der URL übergeben werden. Mit ```localhost:4711/data?index=2``` fordert man in unserem Fall des dritte Element der Datenbank an.
