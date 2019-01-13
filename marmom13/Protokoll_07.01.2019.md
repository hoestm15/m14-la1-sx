# Protokoll 07.01.2019  

## 1. Einheit  

## Thema: Typescript

Name: Moritz Martinak  
Lehrer: sx  
Gruppe: 2  
Übungsdatum: 07.01.2019  
Abwesend: -  

## Typescript  
Typescript ist eine, von Microsoft entwickelte, Programmiersprache die Java ähnelt und Client und Serverseite abdeckt und mit dem tool guplp übersetzt wird. Jeder JavaSript code ist auch gültiger Typescript code.
### Übung 
Zuerst haben wir mit dem Befehl **npm init** (npm = node package manager) ein neues Projekt angelegt. Dazu mussten wir mehrere Parameter wie unter anderem den Package Name, eine Description und den Autor angeben müssen. Dadurch wurde eine package.json angelegt die folgenden Inhalt hat:  

{  
  "name": "voruebung",  
  "version": "1.0.0",  
  "description": "Vorübung für 5AHME (18/19) G2",  
  "main": "main.js",  
  "scripts": {  
    "test": "echo \"Error: no test specified\" && exit 1"  
  },  
  "author": "marmom13",  
  "license": "MIT"  
}  

Dabei handelt es sich um die zentrale Steuerdatei.  Mit **nano** haben wir dann eine *main.ts* angelegt die den sourcecode
```  
console.log('Hallo');
```  
Um Typescript verwenden zu können haben wir es mit **npm install typescript** installiert. Installierte module finded man im 
*node_modules* Verzeichnis.
beinhaltet. Mit dem Befehle **node main.ts** haben wir die Datei dann ausgeführt.  
Daraufhin haven wir sie mit **./node_modules/typescript/bin/tsc main.ts** zu einer JavaScript Datei transpiliert, was, da eigentlich kein Unterschied zu einem JavaScript Programm bestand, nicht nötig gewäsen wäre und sie mit **node main.js** ausgeführt.  

Um diesen unterschied besser darzustellen haben wir die Datei mit

```javascript  
const x=27; 
let y: number; 
y=10*x;
console.log('Hallo', y);
```  
erweitert. Nach dem transiplieren sah es dann so aus:  
```javascript  
var x =27;  
var y:number;  
y = 10*x;  
console.log('Hallo', y);  
```  
Dann haben wir mit **npm remove typescript** typescript entfernt und es mit **npm install --save-dev typescript** in den devDependencies (statt in dependencies) abgespeichert da es nur in der Entwicklung, jedoch nicht zum Ausfühern notwendig ist.

## json Dateien   
>Die JavaScript Object Notation, kurz JSON [ˈdʒeɪsən], ist ein kompaktes Datenformat in einer einfach lesbaren Textform zum   Zweck des Datenaustauschs zwischen Anwendungen. Jedes gültige JSON-Dokument soll ein gültiges JavaScript sein und per eval() interpretiert werden können.<  

Quelle:[https://de.wikipedia.org/wiki/JavaScript_Object_Notation](https://de.wikipedia.org/wiki/JavaScript_Object_Notation)
Json Dateien sind im Gegensatz zu, zum Beispiel, CSV Dateien hirarchisch und sind übersichtlicher als .xml Dateien. Sie beginnen und enden mit einer Geschwungenen Klammer. Zwischen den Klammer Befinden sich Atribute welche auch selbst ein Objekt sein können.  

## Visual Studio  

Visual Studio ist eine IDE der Firma Microsoft die trotzdem multiplatform fähig ist und nichts mit Windows zu tun hat. Man startet sie in dem man direkt im Gewünschten Ordner den Befehl **code** aufruft. Die Quelldateien befinden sich im Ordner *src* in dem auch die main.ts vorzufinden ist. Visual Studio kann ausserdem auch readme Dateien korrekt darstelen. 

Um sich überblick zu verschaffen kann man in .vscode settings.json Elemente ein und ausblenden was die Umgebung sehr individuell anpassbar macht. In meinem Fall:  
```  
{  
	"files.exclude": {  
		"**/node_modules": true,  
		"**/package-lock.json":true,  
		"**/dist": true,  
		"**/tsconfig.json": true,  
		"**/tslint.json": true,  
		"**/gulpfile.js": true,  
		"**/.vscode": true,  
		  
	}  
}  
```  

