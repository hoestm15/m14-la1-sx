# 4.Protokoll  
  
  **Name**:  *Sackl Roland*  
  **Datum:** *28.01.2018*  
  **Uhrzeit:** *8:00-10:30*  
  **Gruppe:** *3*  
  
  **Abwesend:** -  
  **Anwesend:**   Sackl Martin, Sackl Roland, Reinbacher Bernhard,Sammer Daniel,Ruffennacht Florian,Schuster Patrick, Schmuck Martin  
  
   ## Wiederholung der vorherigen Einheiten:
Folgende Punkte wurden besprochen:
#### Javascript-Typescript Unterschied   
Das Problem beim arbeiten mit JS ist, dass es nicht Typenstreng ist und somit leicht Fehler passieren können, welche erst in der Laufzeit aufscheinen. Um dies zu vermeiden arbeiten wir mit Typescipt. 
#### Express Framework
Um nicht von null auf einen Server programmieren greifen wir auf das Express Framework zurück. Dieses Framework baut auf NodeJs auf und erleichtert die Erstellung eines Webservers erheblich.
#### Body-Parser
Wir verwenden den Body-Parser um konfortabel mit Zusatz-Attributen in der URL arbeiten zu können. Diese Zusatzattribute werden in einer query gespeichert, welche man mit der Methode `reg.query` abfragen und weiterverarbeiten kann.

## Wiederholung  
Da die letzte Einheit noch im vorherigen Jahr war, wiederholten wir zu Beginn das zuletzt gemachte. Wir besprochen den Unterschied von Javaascript und Typescript. Es gibt viele Unterschiede von zwischen Javaascript und Typescript. EIn untersched ist, dass bei Typescript ein Konstruktor durch das Schlüsselwort **constructor** signalisiert wird. Das Problem von Javascript ist, dass leicht Fehler passieren können, da es nicht Typenstreng ist. Um diese Fehler zu vermeiden arbeiten wir mit Typescript.Damit man nicht von null auf einen Server programmiert greifen wir auf das Express Framework zu, welches auf NodeJs baut. Die Erstellung eines Webservers erleichtert das NodeJs sehr. Der Body-Parser speichert automatisch zusätzliche Attribute und entlastet so den Programmierer sehr. Dafür dient die Methode **req.query**, mit der man die Zusatzattribute abfragen und weiterverarbeiten kann.  


## REST-Server  
Das wir alles in unseren Main-Klasse haben, war das Ziel unser Einheit, den REST-Server schöner und übersichtlicher zu gestalten. Um das erreichen zu können, haben wir die Klassen **Server** und **Student** erstellt. Dadurch ist alles voneinader getrennt.  

### Stundent.ts  
Da die Klasse **Student** später in einer anderen Klasse importiert werden muss, wird das Schlüsselwort **export** verwendet.In unseren Fall wird die Klasse die Datenerhaltungsklasse. 
```typescript  
  export class Student {

    private htlid: string;
    private surname: string;
    private firstname: string;


    constructor (htlid: string,
                 surname: string,
                 firstname: string) {
        this.htlid = htlid;
        this.surname = surname;
        this.firstname = firstname;

    }

    public getHtlid () {
        return this.htlid;
    }

    public getSurname () {
        return this.surname;
    }

    public getFirstname () {
        return this.firstname;
    }
}
```  


