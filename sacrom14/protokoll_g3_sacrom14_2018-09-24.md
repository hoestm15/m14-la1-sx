# 1.Protokoll  
  
  **Name**:  *Sackl Roland*  
  **Datum:** *24.09.2018*  
  **Uhrzeit:** *8:00-10:30*  
  **Gruppe:** *3*  
  
  **Abwesend:**-   
  **Anwesend:**   Sackl Martin, Sackl Roland, Reinbacher Bernhard,Sammer Daniel,Ruffennacht Florian,Schuster Patrick,Schmuck Martin
   

----------------------------

# REST-Server  
REST-Server steht für **R**epresentational **S**tate **T**ransfer Server, der für die 
Maschine-zu-Maschine-Kommunikation in Werbsevices verwendet wird.HTTP ist das verwendete Übertragungsprotkoll.

# HTTP
HTTP steht für **H**yper**T**ext **T**ransfer **P**rotokoll. Das Protkoll ist zustandslos und die Übertragung findet textuell statt.Das Protokoll überträgt Daten auf der Anwendungsschicht.  


  
## Aufbau  
**Header**   
Der Header beinhaltet Informationen über den Server, dem Body und der Codierung.
Informtionen werden ausgetauscht über:
* die Codierung des Body 
* die Verbindungsqualität  
* spricht  der Server HTTP 
* Body Beginn und Ende
* die Länge der folgenden Nachricht  
 
**Body**
Der Body enthält die Nutzdaten.  
  

## Funktionsweise  

Eine  Anfrage(SYN Paket) wird von Client an den Server geschickt,währenddessen der Server auf die Anfragen wartet.War die Anfrage korrekt antwortet der Server mit einem ACK-Paket,welches wiederum auch der Client zurückschickt.Danach sind zwei Datenröhren für den Datentranfer bereitgestellt. Zum Beenden der Verbindung schickt zuerst einer der beiden ein FIN-Package darauf der andere mit einem FIN-ACK-Package antwortet.


  Anfrage | Bedeutung 
  ------- | ---------  
  GET | Cliet fordert Ressource von Server an  
  DELETE | Client löscht Daten am Server  
  POST | Client schickt Daten an Server, jedoch muss die URL bereits am Server existieren.  
  PUT | Client schickt Daten an Server, jedoch kann die URL bereits am Server erstellt werden.
  
  
   
