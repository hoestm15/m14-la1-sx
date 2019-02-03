
# Laborprotokoll  
Vierte Einheit am 28. Jan 2019  
Martin Schmuck  
5AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: niemand  

## Thema der Einheit: TypeScript mit Visual Studio Code
________

### Erweiterung des Servers 
Wir erweitern unseren Server um eine weitere Funktion und lagern ihn in verschiedene Dateien aus. Dies hat den Vorteil, dass man die ganze Anwendung an verschiedene Gegebenheiten leichter anpassen kann. 

#### main.ts  
Die Klasse `Main` hat zur Zeit nur die Aufgabe, den Konstruktor der Klasse Server aufzurufen und somit den Server zu starten.
```typescript

```  

#### server.ts  
Die Klasse `Server` hat die Aufgabe, einen Server zu realisireren. Da Schlüsselwort `export` muss im Klassenkopf angeführt werden, wenn man wie wir die Klasse in einer anderen Klasse verwendet, also dort mit `import` importiert.  
```typescript

``` 

#### student.ts  
Die Klasse `Student` ist eine Datenhaltungsklasse. Sie representiert einen Schüler.
```typescript

```  
