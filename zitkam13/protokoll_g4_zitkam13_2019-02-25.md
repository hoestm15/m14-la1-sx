# 5.Protokoll
**Name:** Zitz Karlheinz   
**Datum:** 25.2.2018  
**Uhrzeit:** 8:00-10:30  
**Gruppe:** 4  
**Anwesend**: Strauß Lukas, Tuttner Raphael,  Uhl Christian  Waltl Kilian, Wieser Markus, Zitz Karlheinz  
**Abwesend**: Strutz Sebastian  

## Wiederholung des Rest-Servers  
Der Rest-Server basiert auf drei Technologien. Diese sind **Node.js**,**Javaskript/Typeskript** und **Express**. **Typeskript** benötigen wir für die Programmierung, da wir in dieser Sprache unseren Server programmieren. **Express** ist eine Erweiterung vom HTTP Modul, welches einfacher ist damit zu arbeiten und **Node.js** benötigen wir für unseren Server.  

### HTTP (HyperText Transfer Protocoll)  
HTTP steht für **H**yper**T**ext **T**ransfer **P**rotokoll. Die Übertragung zwischen Server und Client findet textuell statt und das Protokoll ist zustandslos. Das Protokoll überträgt Daten auf der Anwendungsschicht. Die Übertragung kan  man im folgenden Bild sehen.  
![HTTP](https://github.com/HTLMechatronics/m14-la1-sx/blob/zitkam13/zitkam13/http.png)  
Die Verbindung zwischen Server und Client wird mittels **TCP/IP Protokoll** aufgebaut. Nach dem Verbindungsaufbau erfolg die Kummunikation mittels **HTTP-Protokoll**. Diese Kummunikation erfolgt dabei textuell. Für die Kummunikation gibt es zwei Datenröhren. Eine für den **Request** und eine für den **Response**. Der Client sendet an den Server eine Anfrage, den sogenanten **Request**. Auf einem **Request** antwortet der Server mit dem **Response**. Für den Request gibt es einige Schlüsselwörter. Die vier wichtigsten sind:   
* **GET** -> Fordert Inhalte vom Server  
* **POST** -> Mit diesem SChlüsselwort kann man Daten ändern  
* **PUT** -> Neue Dateien können erstellt werden  
* **DELETE** -> Löscht Inhalte 
Ein Request ist aufgebaut mit dem **Schlüsselwort** ,mit der Information die man benötigt, und mit **HTTP/1.1.**  
Weiters stehen im Header noch weitere Informationen. Zum Beispiel der **Hostname** oder falls es einen Body gibt die Länge des Bodys. Diese findet man danach unter **content-length**. Mit dieser **content-length** weiß der Server oder der Client wann der Body zu Ende ist und damit auch wann der Request oder Response zu Ende ist. Der **Response** des Servers schaut ähnlich wie der **Request** aus. Er besitzt auch einen **Head** und kann auch einen **Body** besitzen. Fals der Response einen Body besitzt wird dies im Head wieder mit der Länge des Bodys gekennzeichnet. Im **Head** vom Response befindet sich zu einem wieder **HTTP/1.1** und der **Statuscode** und der **Statuscode ausgeschrieben**. [Hier](https://de.wikipedia.org/wiki/HTTP-Statuscode) können sie die Statuscodes nachlesen.  Früher wurde das XML Format für die Übertragung verwendet. Heuter wird aber JSON für die Übertragung verwendet. Die Übertragung ist zwar umstänflicher aber die Informationen können viel besser komprimiert werden.  

## Erweiterung des Rest-Server Projektes  
Da wir die Schülerdaten noch nicht speichern konnten, wenn der Server beendet wird, schrieben wir eine Methode das wir alle bestehenden Daten in einer Datei speichern. Für diese Speicherung benötigten wir ein weiteres Modul **nconf** Dieses Modul ermöglichte uns, dass wir schnell und komfortabel mit config dateien arbeiten können.

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
