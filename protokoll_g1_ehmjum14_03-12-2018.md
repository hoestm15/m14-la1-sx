# 3.Protokoll  
**Name:** Ehmann Julian   
**Datum:** 03.12.2018  
**Uhrzeit:** 8:00-10:30  
**Gruppe:** 1  
**Anwesend**: Berger Emil, Bullner Jeremy, Ehmann Julian, Knappitsch Robert, Köhler Marcel  
**Abwesend**:   Böcksteiner Jakob, Kobor Markus

## Singleton  
Durch *Singleton* wird eine Klasse nach dem Prinzip (Aufbau) einer Singelton Klasse erzeugt. Mit `getInstance` wird neu ein neues Objekt erzeugt,wenn vorhin noch keines erzeugt worden ist, welches dann in der statischen Variable `instance` gespeichert wird. Falls die Methode ein nächstes Mal aufgerufen werden wird kein neues Objekt mehr erstellt und die statische Variable zurückgegeben.  


## Das Express-Modul  
Durch *Express* (ein Modul, welches die Umsetzung von HTTP/HTTPS-Servern vereinfacht) wird uns die Arbeit im Labor bzw. mit Typescript um einiges erleichtert.  
Es muss mit `npm install express` zuerst installiert werden und mit dem folgendem Kommando `npm install --save-dev @types/express` in der `package.json` eingeschrieben werden.  


## HTTP Server/Client  
Die Übertragung zwischen Server und Client findet textuell statt und das Protokoll ist zustandslos. Wird hauptsächlich dazu verwendet um Webseiten aus dem WWW in einen Webbrowser zu laden. HTTP versucht immer eine TLS-Verbindung zum Port 80 am Host aufzubauen. **Wichtig**: Client und Server sind **Keine** Rechner. Client und Server können sich auch auf dem selbem Rechner befinden. Weiters ist noch zu sagen, dass der Client eine Anfrage (**Request**) an den Server sendet und der Server nach Verarbeitung der Anfrage eine Antwort (**Respond**) zurück an den Client sendet.  

Für den Request vom Client gibt es einige Schlüsselwörter:  
* **GET** -> Fordert Inhalte vom Serveran  
* **POST** -> Mit diesem Schlüsselwort kann man Daten ändern  
* **PUT** -> Hiermit kann man neue Dateien erstellen   
* **DELETE** -> Löscht Inhalte  

### Keep-Alive Pakete
Wenn eine Verbinndung zwischen Server und Client besteht werden nicht dauerhaft Pakete übertragen. Um zu verhindern, dass der Server die Verbindung aufgrund einer Überschreitung der Zeit abbricht kann der Client sogennante *Keep-Alive-Pakete* schicken um dem Server damit mitzuteilen, dass er immernoch "lebt" und die Verbindung aufrecht erhalten will.


## Body Parser
Wird wie folgt installiert: `npm install body-parser` `npm install --save-dev @types/body-parser`
   
`npm install --save-dev @types/body-parser` wird dazu verwendet, um in der `package.json` einzuschreiben was für die Entwicklung(und nur für die Entwicklung)die Typescript-Variante benötigt wird.  
  
Der Body Parser stellt die übermittelten Informationen über eine Variable zur Verfügung. Um diesen zu benützen, muss folgendes der Server-Klasse übergeben werden: `this._server.use(bodyParser.function());`


## URL
Bei HTTP ist es möglich Informationen getrennt nach der ursprünglichen URL mit einem **?** zu übergeben. In unserer Übung sieht das wie folgt aus: **localhost:4711/data?index=0**. Durch ein kaufmännisches **&** würden sich noch mehr informationen über die URL übertragen lassen. Diese Methode ist aber ziemlich unsicher, da diese URL im Browser Verzeichnis abgespeichert wird. Somit ist diese Variante ungeeignet für wichtige/geschützte Daten.  


Damit es möglich wird Informationen aus der URL zu lesen, muss im Konstruktor folgendes programmiert werden:
`this._server.use(bodyParser.urlencoded());`  
Somit könnte man über `req.query.xxx` die Variable abrufen.  

Somit sieht unsere Methode wie im folgendem Code-Abschnitt aus:  
```typescript
private handleGetData(req: express.Request, res: express.Response, next: express.NextFunction) {
        console.log('Server ' + this._port);
        const index = +req.query.index;
        if (index >= 0 && index < Database.getInstance().size()) {
            res.json(Database.getInstance().get(index));
        } else {
            res.status(400).send('invalid index');
        }
    }
```
Mit **localhost:4711/data?index=** kann nun ein spezieller Wert aus unserer Datenbank abgerufen werden. Sollte diese Zahl kleiner 0 oder größer als die Datenbank sein, wird ein Fehler mit dem Statuscode *400: invalid index* zurückgegeben.

## Informationen im Body
  Als nächstes möchten wir einen neuen Wert hinzufügen. Dazu benötigen wir die HTTP-Request **PUT**. Dieser Wert soll sich im Body des HTTP-Paketes befinden und dem JSON-Muster entsprechen.  
  
  Dementsprechend muss auch eine neue Handler-Methode für */data* mit der Request **PUT** geschrieben werden:  

  Mit `bodyParser.json());` werden Werte, die sich im Body in einer JSON-Codierung vorfinden in Variablen gespeichert, die mit `requ.body.xxx` abgerufen werden können. Diese Werte werden im Objekt *Value* verpackt der Datenbank übergeben. Sollte ein Problem auftreten, wird der Fehlercode *400: Bad Request* zurückgegeben.  
