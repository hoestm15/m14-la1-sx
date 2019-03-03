# *5. Laborprotokoll*

  Name: Markus Wieser   
  Klasse: 5AHME   
  Datum: 25.02.2019   
  Anwesend: Strauß Lukas, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz    
  Abwesend: Strutz Sebastian


  ## Wiederholung
  
  ## REST-Server
  
  Ein Representational State Transfer - Server (kurz REST-Server) wird für verschiedenste Maschine zu Maschine Kommunikationen verwendet. Als Beispiel hierfür nannten wir eine Verbindung zwischen einem Smartphone und einem PC. Weiters werden Rest-Server meist für Zustandsabfragen verwendet.
  
  ## HTTP (Hypertext Transfer Protocol)
  
  Das HTTP ist ein zustandsloses Protokoll zur Übertragung von Daten. Es ist textuell aufgebaut und basiert auf einem Server-Client Prinzip (Request/Response). Für eine verschlüsselte Übertragung gibt es das HTTPS Protokoll.
  
  ![HTTP(s) Datenaustausch](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/requestResponse.png)
  
  Für den Verbindungsaufbau wird ein TCP/IP Protokoll verwendet. Es sind zwei Datenröhren vorhanden, welche für den Request und die Response zuständig sind. Der Client sendet den Request und der Server antwortet mit einer Response.
  
  ### Schlüsselwörter für den Request
  
* **GET**     -> Inhalte vom Server ansehen
* **POST**    -> Inhalte ändern
* **DELETE**  -> Inhalte löschen
* **PUT**     -> Neue Inhalte anlegen

### Aufbau eines Pakets
  
  Hier sieht man, dass ein HTTP Paket immer in Header und Body aufgeteilt sind. Im Header sind Informationen über das Protokoll (die verwendete Version), über den Client und über den Server. Weiters wird die Länge des Bodys (content-length) auch im Header angegeben, dadurch weiß man wann der Body zu Ende ist. Im Body sind die Daten selbst enthalten. 
  
  ![Paketaufbau](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/paketaufbau.jpg)

  Im Head von einer Response steht wie auch bei einer Request die Version (zum Beispiel HTTP/1.1) aber auch der Statuscode als Zahl und Wort.

## Fortsetzung des REST-Servers

Um unsere Serverdaten zu speichern schrieben wir eine Methode. Hierfür erstellten wir die Datei config.json und schrieben dort den Pfad hinein, wo die Daten gespeichert werden.

``` typescript 
{
    "database": {
        "path": "datenbank.json" 
    }
}
```
Danach installierten wird das Modul nconf. nconf ermöglicht einem ein angenehmes arbeiten mit config Dateien.

Installieren:
```  
npm install nconf 
```  

Laden der Typen:
```  
npm install --save-dev @types/nconf  
```  
Als nächstes importierten wir nconf in unserer main.ts.
``` typescript 
import * as nconf from 'nconf';
nconf.argv().env().file({ file: 'config.json'});
`
```

Um in unserer Datenbank mit files arbeiten zu können, importierten wir das Modul fs. Dieses Modul musste jedoch nur importiert und nicht mehr installiert werden.
```typescript
import * as fs from 'fs';
```
Zum Speichern haben wir eine Methode namens writeToFile erstellt. Diese kommt beim Hinzufügen, Ändern und Löschen zum Einsatz. 


