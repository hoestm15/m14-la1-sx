# 4.Protokoll  
  
  **Name**:  *Bernhard Reinbacher*  
  **Datum:** *28.01.2019*  
  **Uhrzeit:** *8:00 - 10:30*  
  **Gruppe:** *3*  
  
   
    
 **Abwesend:** niemand  
 **Anwesend:** Bernhard Reinbacher, Ruffenacht Florian, Sackl Martin, Sackl Roland, Schmuck Martin, Sammer Daniel, Schuster Patrick  
  
*************************************************************************************************************************     
## Wiederholung  
Zu Beginn wiederholten wir das zuletzt gemachte, da seit der letzten Einheit schon einige Zeit vergangen ist. Wir arbeiten mit Javascript schreiben jedoch in Typescript damit das Programmieren aufgrund der fehlenden Datentypen in Javascript. Somit wird das Arbeiten angenehmen, da Typescript Java sehr ähnlich ist. Einer von vielen Unterschieden zwischen Java und Javascript ist, dass bei Javascript automatisch public verwendet wird auch wenn man kein Schlüsselwort verwendet. In Java als auch in Typescript verwendet man private und public.  
Mithilfe des bodyPasers wird der Programmierer entlastet, da er automatisch zusätzliche Attribute zu speichern. Dafür bedient man sich der Methode **req.query**. In unserem Fall kann mit *req.query.htlid* auf das Atrribut HTLID zugegriffen werden.  
  
*************************************************************************************************************************     
## Aufteilung in Klassen  
Um den Code schöner zu gestalten und auch das Fehlerhandling zu vereinfachen, haben wir die eine Klasse in kleinere unterteilt. Somit können wir sehr schön **Server, Student und Main** unterteilen.  
### Stundent.ts  
Diese Klasse ist in unseren Fall die Datenerhaltungsklasse. **export** wird benötigt, da die Klasse später in einer anderen Klasse importiert wird.  
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
### Server.ts  

