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
beinhaltet. Mit dem Befehle **node main.ts** haben wir die Datei dann ausgeführt.  
Daraufhin haven wir sie mit **./node_modules/typescript/bin/tsc main.ts** zu einer JavaScript Datei transpiliert, was, da eigentlich kein Unterschied zu einem JavaScript Programm bestand, nicht nötig gewäsen wäre und sie mit **node main.js** ausgeführt.  

Um diesen unterschied besser darzustellen haben wir die Datei mit

```  
const x=27; 
let y: number; 
y=10*x;
console.log('Hallo', y);
```  
erweitert. Nach dem transiplieren sah es dann so aus:  
```  
var x =27;  
var y:number;  
y = 10*x;  
console.log('Hallo', y);  
```  

