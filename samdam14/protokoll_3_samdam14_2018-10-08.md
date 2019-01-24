# _Protokoll Dritte Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 10.08.2018**  
**Uhrzeit: 8:00-10:30**  
  
**Anwesenheit: _Es waren alle Schüler anwesend_**  
  
**Thema: Tools zur Programmierung in Typescript**  
  
-----------------------------------------------------------
  
### Tools in Typescript  
Um das Programmieren in Typescript angenehmer zu machen, bzw. schöner zu gestalten, kann man ganz einfach Tools nachinstallieren und somit in ein Projekt einbinden. Diese Tools können dann dazu verhelfen, schöneren Code zu erzeugen oder z.B. den Code zu kompilieren.  
[Diverse Tools für Typescript](http://definitelytyped.org/directory/tools.html)  
  
#### TSLint  
TSLint hilft, den Typescript-Code "schöner" zu gestalten. Dabei ist nicht nur die Optik gemeint, sondern der Code wird generell übersichtlicher und somit leserlicher. TSLint ist mit 1,8 Millionen wöchentlichen Downloads auch ein viel verwendetes Tool. Mit *npm install tslint typescript --save-dev* kann man das Tool im Arbeitsverzeichnis installieren.  
[npmjs/tslint](https://palantir.github.io/tslint/)  
  
In der tslint.json Datei können Einstellungen am Tool getroffen werden, also auf was es achten soll. Z.B. kann man TSLint sagen, wie lange eine Zeile maximal sein darf und / oder wie Leerzeichen und -zeilen gehandhabt werden sollen.  
```typescript
// Beispiel maximale Zeilenlänge
"rules": {
        "max-line-length": {
            "options": [120]
        },
```
