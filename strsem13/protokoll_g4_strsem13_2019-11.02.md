# Laborprotokoll  
Name: Sebastian Strutz  
Gruppe: 4  
Klasse: 5AHME  
Datum: Mo, 22. Oktober 2018  
Ort: Automatisierungslabor, Htbla Kaindorf  

Anwesend: Strauß, Strutz, Tuttner, Uhl, Wieser, Waltl, Zitz  
Abwesend: -

# Thema:Erweiterung Rest-Server  

## Wiederholung der letzten Einheiten  
Da die letzte Einheit in diesem Labor schon sehr weit zurück lag, wiederholten wir kurz alle besprochene Themen. Wir wiederholten auch wie weit wir bisher bei unserem Rest-Server waren, für was die verschiedenen Klasse waren, und was noch zu tun war.  

### Rest-Server  
Der Name **REST**-Server steht für **RE**presentational **S**tate **T**ransfer Server und wird meist für die Maschine-zu-Maschine-Kommunikation in Websevices verwendet. Das HTTP Protokoll wird als Sprache zwischen Server und Client verwendet. Rest Server werden häufig zur Abfrage von Zuständen, z.B. an einem entferntem System eingesetzt.  
  
#### HTTP 
**HTTP** (**H**ypter**T**ext **T**ransfer **P**rotocol) ist ein Protokoll zur Übertragung von Daten. Das Protkoll ist zustandslos, dass bedeutet das Informationen aus früheren Anforderungen verloren gehen, deshalb ist ein mitführen von Sitzungsdaten erforderlich. Um Daten verschlüsselt zu Übertragen gibt es das HTTPS Protokoll. Weiteres erfolgt die Übetragung textuell. 
Wichtige Befehle:  
* **GET**:     Daten vom Server abrufen    
* **POST**:    Daten zum Server schicken   
* **PUT**:     Daten auf den Server laden  
* **DELETE**:  Datem vom Server löschen   

Weiter Infos zum Rest-Server und HTTP finden sie [hier](https://github.com/HTLMechatronics/m14-la1-sx/blob/strsem13/strsem13/protokoll_g4_strsem13_2018-10-15.md)  

### Programmiersprachen Server/Client seitig  
**Serverseitig:**
Auf der Serverseite kann mit mit vielen verschiedenen Programmiersprachen programmieren, z.B. PHP, Java, Perl, JacaScript(benötigt eine Virtuelle Maschine - Node.js)  

**Clientseitig:**  
Auf der Clientseite wird hauptsächlich JavaScript verwendet. Javascript war die erste Programmiersprache, die im Webbrowser zum Einsatz kam. Eine Subsprache von Javascript ist z.B. Typescript, mit dem wir unseren Server realisieren.  

Wenn man sich besser in die Programmierung des Servers und des Clients einfinden will, ist es leichter und besser in nur einer Programmiersprache beide Programme zu schreiben. Deswegen wird JavaScript auch gerne für die Serverseitige progammierung verwendet.  
  
### Datenerhaltung   
Für die Datenerhaltung in Java stehen dazu die Collections zur Verfügung. Beispiele für Collections:  
* ArrayList     -> Ist ein Feld, welches sich immer verdoppelt, falls es  zu klein ist
* Linked List   -> Hier werden die Datensätze hintereinander gespeichert, falls ein Wert benötigt wird, muss alles durchgeschaut      werden
* HashMap       -> Hier werden keyvalue Paare erzeugt und vergeben
* HashSet       -> Änlich wie LinkedList; der Unterschied ist, dass ein Objekt nur einmal vorkommen kann  

In Javascript:  
* für ArrayList -> Die Listen können durch Felder ersetzt werden        -> Array(Feld)
* für HashMap   -> Maps können durch einfache Objekte realisiert werden -> Object  

### Klassen student.ts, database.ts, server.ts
Die Klasse **student.ts** ist eien Datenerhaltungsklasse für Schüler. Wichtig ist dass die Klasse **export** ist, da wir sie in eine andere Klasse importieren müssen.  
Die Klasse **database.ts** stellt unsere Datenbank dar, sie wird nach dem Entwurfsmuster Singelton programmiert. In dieser Klasse haben wir auch die Methoden *GET* und *ADD* ausprogrammiert.  
In der Klasse **server.ts** wird der Server realisiert. Weiter haben wir zwei Methoden *handlePutStudnet* und *handleGetStudnet* ausprogrammiert.  

## Erweiterung Programm  
Das Ziel der Einheit war, den aktuell porgrammierten Rest-Server zu erweitern. Das bedeutet wir haben 3 weitere Methoden für den Server hinzugefügt, bzw. fertigstellt.  
  
### Klasse student.ts  
In dieser Klasse wurde ein Interface hinzugefügt.  

```
export interface IStudent {
    htlid: string;
    surname: string;
    firstname: string;
}
```
### Klasse database.ts  
Hier wurden die Methoden **remove** und **set** ausprogrammiert. Die Methode **remove** hat die Aufgabe einen Schüler zu löschen. Mit der Methode **set** soll man von einem Schüler, etwas verändern sollen.  
```
public remove (htlid: string) {
        delete this.students[htlid];
    }
    
public set (s: Student): Student {
        const rv = this.get(s.getHtlid());
        this.students[s.getHtlid()] = s;
        // this.students.tutram12 = s;
        return rv;
    }

```  

### Klasse server.ts
  






 
