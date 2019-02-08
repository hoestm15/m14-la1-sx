# 3.Protokoll
**Name:** Zitz Karlheinz   
**Datum:** 12.11.2018  
**Uhrzeit:** 8:00-10:30  
**Gruppe:** 4  
**Anwesend**: Tuttner Raphael, Waltl Kilian, Wieser Markus, Zitz Karlheinz  
**Abwesend**: Strauß Lukas, Strutz Sebastian, Uhl Christian  

### Datenbanken  
Eine **Datenbank** ist ein System für eine **elektornische Datenverwaltung**. Man kann zwischen einer **schematischen** (klar definierte Strucktur) und **nicht schematischen** Datenbank unterscheiden. Eine typische Programmiersprache für eine Datenbank ist **SQL**. Für schematische Datenbanken wird zum Beispiel **PostgreSQL** oder **SQLite** verwendet.  

### Singelton  
In der Softwareentwicklung ist **Singelton** ein Entwurfsmuster das sicherstellt, dass es ein Objekt einer Klasse nur einmal gibt. Das **Singelton** wird auch **Einzelstück** genannt. Dieses Einzelstück ist meistens global verfügbar. Da wie in unseren Fall eine Datenbank nur einmal existiert und nur die Werte einer Datenbank geändert werden, ist es sinnvoll, dieses Entwurfsmuster zu verwnden. Das erreicht man, wenn man den Konstruktor **private** setzt und eine statische Methothe mit dem Namen **getInstance()** am Beginn aufgerufen wird, die beim ersten Aufruf ein Objekt erzeugt. Deises Objekt wird danach in einer statischen Variable **instance** abgelegt.  

# Projekt Rest-Server  
Das Ziel der Einheit war es den aktuel programmierten Rest-Server umzugestalten. Dafür wurde eine Datenhaltungsklasse **Student** und eine Datenbank **Database** erstellt. Wir haben auch noch einige Änderungen in der **Server** Klasse vorgenommen.  

## Änderungen am Code  
### Klasse student.ts
Diese Klasse wird in unserem Fall als Datenhaltungsklasse für einen Schüler agieren. Daher sind die Datenelemente, wie auch in Java, **private**. Deswegen haben wir auch **Getter-Methoden** eingefügt.  
Das Schlüsselwort  **export** wird hier verwendet, weil die Klasse in weiterer Folge exportiert wird. Das heißt sie wird in einer anderen Klasse importiert, um auf die **Getter Methoden** zugreifen zu können.  
```typescript
export class Student {

    private htlid: string;
    private surname: string;
    private firstname: string;

    constructor (htlid: string, surname: string, firstname: string) {
        this.htlid = htlid;
        this.surname = surname;
        this.firstname = firstname;
    }
    public getHtlid (): string {
        return this.htlid;
    }
    public getSurname (): string {
        return this.surname;
    }
    public getFirstname (): string {
        return this.firstname;
    }
}
```

### Klasse database.ts  
Die Klasse **database.ts** stellt unsere Datenbank dar. Diese Klasse wurde nach dem Entwurfsmuster **Singelton** programmiert. Um das Muster umzusetzten wurde wie oben schon erklärt der Kunstruktor auf private gesetzt und die Methode **getInstace()** eingefügt. Dabei wird überprüft ob es schon die gewünschte Instanz vorhanden ist. Wenn sie nicht vorhanden ist, wird ein neues Datenbank-Objekt für diese Instanz erzeugt. 
Desweiteren haben wir noch die Methoden **add()** und **get()** ausprogrammiert.  

```typescript
import { Student } from './student';
export class Database {
    private static instance: Database;
    public static getInstance (): Database {
        if(Database.instance == null) {
            Database.instance = new Database();
        }
        return Database.instance
    }
      private students: { [id: string]: Student } = {};
    private constructor () {
        // this.add({ htlid = 'tutram12', surname = 'Tuttner', firstname = 'Raphael'});
        this.add(new Student( 'tutram12', 'Tuttner', 'Raphael'));
        this.add(new Student( 'zitkam13', 'Zitz', 'Karlheinz'));
    }

    public add (s: Student) {
        if (this.students[s.getHtlid()]) {
            throw new Error('student already exists');
        }
        this.students[s.getHtlid()] = s;
    }
    public get (htlid: string) {
        return this.students[htlid];
    }
}
```
