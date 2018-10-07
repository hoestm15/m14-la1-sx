# 1.Protokoll  
  
  **Name**:  *Sackl Roland*  
  **Datum:** *01.10.2018*  
  **Uhrzeit:** *8:00-10:30*  
  **Gruppe:** *3*  
  
  **Abwesend:**-   
  **Anwesend:**   Sackl Martin, Sackl Roland, Reinbacher Bernhard,Sammer Daniel,Ruffennacht Florian,Schuster Patrick,Schmuck Martin
   

----------------------------


# Visual Studio Code
Visual Studio Code ist von der Firma Microsoft ist Open-Source, basiert auf dem Framework ELectron und ist plattformübergreifend verfügbar. 
Es werden Sprachen wie Java, PHP,C++, CSS, HTML, SQL, Typescript, usw. unterstützt und durch das Plug-ins kann es beliebig erweitert werden. Visual Studio hat Funktionen wie z.B. Syntaxvorhebung, Autovervollständigung Debugging und Versionsverwaltung.
Trotz des ähnlichen Namen hat dsas Visual Studio Code nichts mit Visual Studio zu tun. Sie sind von der gleichen Firma Microsoft aber von einer anderen Teams entwickelt. Werden aber von unterschiedlichen Teams entwickelt. Einer großer Unterschied in der Handhabung zwischen den Visual Studio und Visual Studio Code ist, dass Visual Studio Code mit Quelltextdateien und Ordnern arbeitet.  


## Arbeiten mit Code


Wenn man Code über den Terminal startet kann man direkt den gewünschten Pfad dazuschreiben,sodas der Code diesen gleich als Projektverzeichnis nimmt. Wenn man den Code über das Desktop-Icon startet muss man im File Explorer erst das gewählte Projektverzeichnis ausgewählt werden um damit arbeiten zu können. Auf der ALT-Taste oben bleiben muss man wenn in Code die Menüleiste anzeigen soll.

## Anpassen der Programmierumgebung
Code  benötigt einige Modifikationen um damit effizient arbeiten zu können. 

### .vscode
Im Ordner *.vscode*  gibt es eine Datei namens *setting.json*.
In dieser können diverse Einstellungen getätigt werden
Zum Beispiel das Ausblenden von Dateien und Ordnern in der IDE.

```json
{

  "files.exclude":
        {
        "**/code_modules/": true,
        "**/.vscode/": true,
        "**/package-lock.json/": true
        }
}
```

### tsconfig.json
Hier werden die Optionen für den Compiler/Transpiler (TSC) angegeben.
```json 
{
    "compilerOptions": 
    {
        "module": "commonjs",
        "noImplicitAny": true,
        "removeComments": true,
        "preserveConstEnums": true,
        "sourceMap": true,
        "target": "es2017",
      
           

    },
        "include": 
        [
            "**/*.ts"
        ],
}  
```


Option | Bedeutung  
---- | ---------  
 
preserveConstEnums | das ConstEnums werden nicht gelöscht 
sourceMap |   Map-Dateien werden generiert
removeComments | gibt an ob Kommentare gelöscht werden  
module | spezifiziert die Quellcode generierung der Module 
target | gibt an welche Version verwendet wird
noImplicitAny | gibt an ob eine Deklaration mit any einen Error erzeugen soll  



# Server
## Unterschied zwischen Server in Java und Javascript/Typescript
In Java gibt es für die Realisierung fertige Klassen und Bibliotheken. Mit dieser Klasse kann man einfach arbeiten und leichter   ein Server erstellen.
In Javascript/Typescript hingegen gibt es keine leicht anzuwendenten Klassen. Es gibt zwar die Klassen *http* und *https*, aber der Umgang erweißt sich als recht unbequem.
## HTTP/HTTPS
Es wird immer nur ein Protokoll bei der Übertragung zwischen zwei Hosts verwendet.Jedoch können auch verschiedene verwendet werden. Innerhalb des Intranets ist keine Verschlüsselung mehr Notwendig und es kann zwischen Proxy Server und Rechner ohne Verschlüsselung übertragen werden.
## Programm
Es sollte ein Programm erstellt werden, welches den Server realisiert.Er wartet auf eine Anfrage und  antwortet mit Hallo. 
```typescript  


import * as express from 'express';

class Main {

     private port: number;
     private server: express.Express;

    constructor(port: number) 
     {
          this.port = port;
         this.server = express();

          this.server.get('*', (req, resp) => this.handleGet(req, resp));


         this.server.listen(this.port);
     }

    private handleGet(req: express.RequestHandler, resp:express.Response) 
     {
          resp.send('Hallllo');
         resp.end;
     
     }
}

let main = new Main(8080);  
```

## Express 
Ist eine Framework für das Arbeiten mit HTTPS und HTTP.Außerdem bietet eine Vielzahl von nützlichen Funktionen für das Gestalten von Webanwendungen.
## Arrow Function 
Die Arrow Funtion dient dazu die Aufgabe einer Methode an eine andere weiterzugeben. Sie ist damit man keine eigene Klasse schreiben muss.
