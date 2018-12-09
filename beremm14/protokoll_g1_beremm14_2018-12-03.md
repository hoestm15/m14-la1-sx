# Protokoll
  Berger Emil  
  5AHME, Gruppe 1  
  19.11.18  
  Anwesend: Berger, Bullner, Ehmann, Enzi, Köhler, Knappitsch  
  Abwesend: Böcksteiner, Kobor  

# Wiederholung

## [Express](https://www.npmjs.com/package/express)
  Express ist ein Modul, das die Programmierung von HTTP/HTTPS-Servern vereinfacht.  
  Um es verwenden zu können, muss es mit `npm install express` installiert werden, und mit `npm install --save-dev @types/express` wird in der `package.json` eingetragen, dass die TypeScript-Variante zur Entwicklung benötigt wird.
  
## `getall()`
```typescript
public getAll (): Value [] {
        return [].concat(this.data);
    }
```
Diese Methode gibt ein neues Array mit dem Inhalt des alten Arrays zurück. Das wird gemacht, dass von außen niemand auf das "originale" Array der Datenbank zugreifen kann.

## Singleton - Realisierung
```typescript
private static instance: Database;

public static getInstance (): Database {
        if (!this.instance) {
            this.instance = new Database();
        }
        return this.instance;
    }
```
Mit dieser Methode wird die Klasse mit dem Entwurfsmuster **Singleton** erstellt. Die Methode `getInstance()` erstellt nur ein neues Objekt, wenn noch keines angelegt wurde - dieses wird dann in der statischen Variable `instance` abgelegt. Sollte die Methode ein weiteres Mal aufgerufen werden, wird die Variable zurückgegeben und kein neues Objekt mehr erstellt. Wichtig ist auch, dass der **Konstruktor private** ist, damit nicht unverhofft von außen ein neues Objekt erzeugt werden kann.

