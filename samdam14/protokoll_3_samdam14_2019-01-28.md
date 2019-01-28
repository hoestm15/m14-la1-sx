# _Protokoll Vierte Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 28.01.2019**  
**Uhrzeit: 8:00-10:30**  
  
**Anwesenheit: Es waren alle Schüler anwesend!**  
  
**Thema: Projekt REST-Server**  
  
-----------------------------------------------------------
  
### Grundlegende Wiederholung  
  
  
--------------------------------------------------------------  
  
### Projekt REST-Server  
Das Ziel der heutigen einheit war es, den REST-Server schöner zu gestalten, denn bis jetzt haben wir alles in unsere Main-Klasse gepackt. 
Deshalb sollen die Klassen Server und Student erstellt werden, damit alles sauber voneinander getrennt ist und man in der Main nur mehr ein Server-Objekt erzeugt werden muss.  
Die Student-Klasse wird im späteren Verlauf in irgendeiner Art von Schüler-Datenbank verwendet werden.  
  
#### student.ts  
Das Schlüsselwort **export** wird verwendet, da die Klasse **Student** später exportiert werden muss.  
Sie wird in unserem Fall als Datenhaltungsklasse agieren, aber anders als in Java sind die Datentypen **public** und deswegen werden auch keine Getter-Methoden benötigt.  

```typescript
export class Student {

    public surname: string;
    public firstname: string;
    public id: string;

    constructor (id: string, surname: string, firstname: string ) {
        this.id = id;
        this.surname = surname;
        this.firstname = firstname;
    }
}
```
