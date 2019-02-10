# 5. Laborprotokoll 

*von Florian Ruffenacht*

Datum: 04.02.2019 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

## Starten des Rest-Servers über die Main-Klasse
In der uns  gut bekannten Programmiersprache Java wird zum Starten des Programmes automatisch die statische main-Methode der Hauptklasse aufgerufen. In JavaScript/TypeScript hingegen muss diese Methode mittels dem Aufruf **Main.main()** nach der Klasse Main aufgerufen werden. 

```typescript
import { Server } from './server';

class Main {

    public static main () {
        new Server().start(8080);
    }

}

Main.main();
```
## Aufbau einer URL mit Pararmetern
Elemente | .../student | ? | htlid=suspam14 | & | htlid=reibem14
---|---|---|---|---|---
Erklärung | URL | signalisiert Beginn der Pararmeterübergabe | Pararmeter | signalisiert weitere Pararmeter | Pararmeter

## Klasse als Datenbank
Die Daten, die von einem Rest-Server abgefragt werden können, liegen üblicherweise in einer Datenbank. Wir erstellen dazu eine Klasse, die eine Datenbank simuliert.

### Allgemeines zu Datenbanken
Die wichtigsten Arten von Datenbanken sind relationale Datenbanken und nicht schemenbehafteten Datenbanken.

In **relationalen Datenbanken** werden die Datenelemente in Tabellen gespeichert. Diese Tabellen können miteinander verknüpft werden und somit können Daten sehr strukturiert abgelegt werden. Der Nachteil besteht darin, dass die Veränderung der Datenbankstruktur kompliziert sein kann und große Datenbanken sehr unübersichtlich werden können. 

Beispiele für realtionale Datenbanken sind:
* [PostgreSQL](https://www.postgresql.org/)
* [SQL](https://www.sqlite.org/index.html)

Die **nicht schemenbehafteten Datenbanken** (auch dokumentenorientierte Datenbanken genannt) werden in zur Zeit vor allem im Social-Media-Bereich immer wichitger. In diesem Bereich sind hohe Abfrageraten und häufige Datenänderungen üblich, mit denen relationale Datenbanken schwer zurecht kommen. In dokumentorientierten Datenbanken können unterschiedliche Dokumente abgelegt werden (Textdateien, Bilddateien, JSON-Objekte,..), die einem strengen Schema unterliegen können, aber nicht müssen. Dadurch wird die Datenbank sehr flexibel und Veränderungen sind verhältnismäßig leicht möglich.

Beispiele für nicht schemenbehaftete Datenbanken sind:
* [mongoDB](https://www.mongodb.com/de)
* [couchDB](http://couchdb.apache.org/)

Weitere Links:
* [Relationale Datenbanken](https://de.wikipedia.org/wiki/Relationale_Datenbank)
* [Nicht schemenbehaftete Datenbanken](http://wi-wiki.de/doku.php?id=bigdata:dokumentdb)
