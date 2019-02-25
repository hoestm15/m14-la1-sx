# 5.Protokoll
**Name:** Zitz Karlheinz   
**Datum:** 25.2.2018  
**Uhrzeit:** 8:00-10:30  
**Gruppe:** 4  
**Anwesend**: Strauß Lukas, Tuttner Raphael,  Uhl Christian  Waltl Kilian, Wieser Markus, Zitz Karlheinz  
**Abwesend**: Strutz Sebastian  

Node.js Javaskript/Typescript  Express Technologien  

Verbindungsaufbau ServerClient    
HTTP 
TCP/IP
Wie schaut ein Request aus 
Head Body
content length das der server weiß wielange der body ist  
früher xml format jetzt json  
weil json für Übertragung umstänflich ist wird das Jsonobjekt komprimeirt  


{
    "database" : { 
        "path" : "datenbank.json"// pfad wo daten abgespeichert sind
    }
}
nconf  Moduldas man sehr schnell un komfortabel mit config dateien arbeiten kann 
nconf.argv().env().file({ file: 'config.json' }); in main.ts am beginn einfügen das nconf weiß wo sich die config datei befindet  
fs modul Filesystem modul für daten in eine datei speichern
damit das file am beginn eingelesen wird, wird  getInstance von der Datenbank klasse  aufgerufen... damit wird die readfs im Construktor aufgerufen und die schüler in der Datei datenbank.json werden eingelesen  
Bei der Methode für add set und remove noch this.writeToFile(); eingefügt, dass sich das File immer wieder aktualisiert falls ein schüler hinzugefügt, gelöscht oder geändert wird.  
