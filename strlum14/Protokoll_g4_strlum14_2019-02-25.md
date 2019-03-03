Name: Lukas Strauß   
Klasse: 5AHME   
Datum: 25.02.2019   
Anwesend: Strauß Lukas, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz   
Abwesend: Strutz Sebastian   

## Wiederholung der Letzten Einheit

## Rest-Server

Der Represantational State Transfer dient vorallem zur Maschine zu Maschine Kommunikation. Das heißt zum
Beispiel ein Smartphone mit einen entfernten PS oder Raspberry. Für diese Verbindungen werden zwei wichtige
Technologien verwendet. Zu einem wird das HTTP Protokoll verwendet und als zweites wird das TCP Protokoll für
die Verbindung verwendet. Das HTTP-Protokoll benötigt man für die Datenübertragung. Die Überragung erfolgt dabei
textuell. Benötigt man eine verschlüsselte Übertragung dann git es dafür das HTTPS-Protokoll. Für die Kommunikation
gibt es einige Befehle. Die wichtigsten sind:   

 
* **PUT**:      :point_right: Daten zum Server schicken 
* **DELETE**:   :point_right: um bestehende Daten am Serve zu löschen
* **GET**:      :point_right: wenn man Daten vom Server bekommen will.  
* **POST**:     :point_right: ändern von bestehenden Daten am Server 



## Hypertext Transfer Protocol(HTTP)
![HTTP](https://github.com/HTLMechatronics/m14-la1-sx/blob/strlum14/strlum14/HTTP%20Protokoll%20Schema.png)

....HTTP ist ein sogenanntes Zustandsloses Protokoll. Die Kommunikation zwischen Server und Client erfolgt mit dem Request-
Response Prinzip.Die Verbindung zwischen Server und Client wird mittels TCP/IP Protokoll aufgebaut. Nach dem Verbindungsaufbau
erfolg die Kummunikation mittels HTTP-Protokoll. Für die Kummunikation gibt es zwei Datenröhren. Eine für den Request und eine
für den Response. Der Client sendet an den Server eine Anfrage, den sogenanten Request. Auf einem Request antwortet der Server
mit dem Response. Schlüsselwörter siehe Rest-Server !










###Weiterführung des Pogrammes

Als Zusatz in unserem Programm wollen wir nun die Daten von Schülern speichern. Folgende Methode macht dies möglich. 
Die Datei config.json wird erstellt. In dieser Datei findet man den Pfad, wo die Daten gespeichert werden. 

``` JSON  
{
    "database" : { 
        "path" : "datenbank.json" 
    }
}
```

Als nächsten Schritt wird das Modul .nconf, es erleichtert das Arbeiten mit den config-Dateien.
Danach werden die Typen geladen. 

```  
npm install nconf  
```  

Der nächste Schritt ist nun das nconf in unsere main.ts zu importieren. 

```  
npm install --save-dev @types/nconf  
```  



Der nächste Schrittwäre in der Klasse main.ts am Beginn eine Zeile einfügen, damit das Modul nconf weiß wo
sich die Konfigurationsdatei befindet. Dabei ist wichtig, dass man das Modul zuerst importiert.

``` typescript  
import * as nconf from 'nconf';
nconf.argv().env().file({ file: '../config.json' });  
```

Weil sich die  Konfigurationsdatei nicht im gleichen Ordner sondern eine Ebene höher befindet als unsere main und Datenbank
benötigt man vor config.json ../. Damit wir jetzt in der Datei database.json mit files arbeiten können benötigen wir noch 
ein weiteres Modul fs. Dieses Modul müssen wir aber nur am Beginn der Klasse importieren, da es dieses schon bei npm gibt.
Für das Speichern haben wir eine eigene Methode erstellt da wir diese Methode beim hinzufügen, löschen und ändern brauchen.
In der ersten Zeile wird eine Variable erstellt in der ein JSON Objekt gespeichert wird. JSON.stringify wird benötigt, damit 
wir eine gut lesbare Formatierung haben und nicht alles in einer Zeile steht. In der zweiten Zeile werden danach die Schüler
mit Hilfe des Filesystems in die Datei datenbank.json gespeichert. Damit wir die Datei beim Starten des Servers einlesen
können, programmierten wir im Konstruktor der Klasse mit Hilfe des File-Systems eine Funktion zum Einlesen der Datei. 
Da wir in der Klasse main.ts am Beginn eine Instance der Datenbank erstellen wird der Konstruktor ausgeführt und die
Datei daher eingelesen.

``` typescript  
public writeToFile () {
        const s = JSON.stringify(this.students, null, 2);
        fs.writeFileSync('../' + this.config.path, s);
    }  
```  

In der ersten Zeile bekommt man den Eintrag von der Datei 'config.json', damit wir den Pfad haben wo die Schüler
gespeichert wurden. In der nächsten Zeile werden die Schüler mit Hilfe des File-Systems aus der Datei geladen und in
eine Variable gespeichert. Diese Variable wird dann zum Schluss in 'students' gespeichert und damit können wir 
dann weiterarbeiten. 

``` typescript  
this.config = <IDatabaseConfig> nconf.get('database');  
const b = <Buffer> fs.readFileSync('../' + this.config.path);
this.students = JSON.parse(b.toString());  
```   

Die Datei in der Die Schüler gespeichert sind sieht dann wiefolgt aus :point_right:

``` json  
{
  "tutram12": {
    "htlid": "tutram12",
    "surname": "Tuttner",
    "firstname": "Raphael"
  },
  "zitkam13": {
    "htlid": "zitkam13",
    "surname": "Zitz",
    "firstname": "Karlheinz"
  },
  "strlum14": {
    "htlid": "strlum14",
    "surname": "Strauss",
    "firstname": "Lukas"
  }
}  
```


