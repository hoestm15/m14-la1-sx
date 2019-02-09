# *3. Laborprotokoll*

  Name: Markus Wieser   
  Klasse: 5AHME   
  Datum: 12.11.2018   
  Anwesend: Strauß Lukas, Tuttner Raphael, Waltl Kilian, Wieser Markus, Zitz Karlheinz    
  Abwesend: Strutz Sebastian, Uhl Christian

  ## Singleton (Entwurfsmuster)
  
Ein Singleton ist in der Softwareentwicklung ein Entwurfsmuster. Dieses Entwurfsmuster stellt sicher, dass es von einer Klasse auch nur ein Objekt gibt. Es bietet normalwereise globalen Zugriff auf das Objekt. Da in unserem Beispiel mit einer Datenbank gearbeitet wird, wird auch diesses Entwurfsmuster verwendet. Eine Datenbank existiert nämlich nur einmal und es werden auch nur die Werte dieser verändert. 

  ## Datenbank
  
  Eine Datenbank ist ein elektronisches Verwaltungssystem. Sie soll Daten halten, sammeln und verwalten können. Datatenbanken sollen mit großen Datenmenge vorallem effizient, dauerhaft und ohne wiedersprüche umgehen können. Es gibt schematische (klare Struktur) und nicht schematische (nicht klar definiert) Datenbanken. Eine sehr weit verbreitete Programmiersprache für Datenbanken ist SQL.

  ## Rest-Server
  
  In dieser Einheit erstellten wir die Klasse student und database. Die Klasse student agiert hierbei als Datenhaltungsklasse und database als Datenbank. Außerdem wurde die Klasse server erweitert.

  ## Klasse database.ts
  
  Unsere Datenbank wurde als Singleton realisiert. Hierfür setzten wir unsere Konstruktor private und riefen getInstance() zu Beginn auf, wodurch wir ein Objekt erzeugten. Ist schon eine Instanz vorhanden, wird dieser Vorgang übersprungen. Weiters fügten wir noch die Funktionen add() und get() hinzu.
  
  ```typescript
import { Student } from './student';

export class Database {

    private static instance: Database;

    public static getInstance (): Database {
        if (Database.instance == null) {
            Database.instance = new Database();
        }
        return Database.instance;
    }

    private students: { [ id: string ]: Student } = {};

    private constructor () {

         this.add(new Student('tutram12', 'Tuttner', 'Raphael' ));
         this.add(new Student('zitkam13', 'Zitz', 'Karlheinz' ));
    }

    public add (s: Student) {
        if (this.students[s.getHtlid()]) {
            throw new Error('student already existing');
        }
        this.students[s.getHtlid()] = s;
    }

    public get (htlid: string): Student {
        return this.students[htlid];
    }
}

  ```
  
  ## Klasse student.ts
  
  Bei der Datenhaltungsklasse student sind alle Datenelemente für einen Schüler private. Aufgrund dessen werden hier auch Getter Methoden verwendet. Um die Klasse exportieren zu können, wird zu Beginn export verwendet. Wenn man sie nun in einer anderen Klasse importiert, kann man auf die verschiedenen Getter Methoden zugreifen (wie in der Klasse database.ts).
  
  
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
  
  
  
  
  
  
