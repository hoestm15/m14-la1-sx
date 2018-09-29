# _Protokoll Erste Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 24.09.2018**  
**Uhrzeit: 8:00-10:30**  
  
**Anwesenheit: _Es waren alle Schüler anwesend_**  
  
-----------------------------------------------------------
  
### REST-Server  
**RE**presentational **S**tate **T**ransfer Server  
Ein REST-Server ist ein HTTP-Dienst, der HTTP-Status-Abfragen zulässt. HTTP steht für *Hypertext Transfer Protocol*, das Übertragungsprotokoll.  

-------------------------------------------------------------  

#### HTTP  
Bei HTTP handelt es sich um ein *zustandsloses* Protokoll, d.h. das Anfragen ohne Bezug auf vorherige Antworten verarbeitet werden.  
Die Übertragung findet textuell statt.  
  
##### Aufbau  
Header (*Nachrichtenkopf*)  
Der Header beinhaltet Informationen zum Body, wie zum Beispiel die verwendete Kodierung oder den Inhaltstyp, damit dieser vom Empfänger korrekt interpretiert werden kann.  
  
Body (*Nachrichtenrumpf*)  
Der Body enthält die Nutzdaten.  
  
##### Funktionsweise  
Server befindet sich grundsätzlich in einem *LISTEN*-Zustand und wartet auf eine Anfrage mit einem SYN-Package von einem Client.  
Erhält er nun eine Anfrage vom Client, antwortet er mit einem ACK-Package.  
Antwortet der Client ebenfalls mit einer ACK-Package, steht die Verbindung. Grundsätzlich sind Server und Client in diesem Status gleichwertig und könnten die Rolle tauschen (ist normal nicht der Fall).  
Zum Beenden der Verbindung schickt zuerst einer der beiden ein FIN-Package, der andere antwortet mit einem FIN-ACK-Package.  
  
##### Anfragemethoden  
Der Client legt bei seiner Request (*Anfrage*) fest, was er vom Server möchte.  
  
Methode | Erklärung
------- | ---------
GET | Daten vom Server abrufen
POST | Daten zum Server zum Weiterverarbeiten schicken
PUT | Daten auf den Server hochladen
DELETE | Daten vom Server löschen
  
Natürlich gibt es noch weitere Methoden, diese sind jedoch auf Wikipedia selbst nachzulesen.  
  
##### Statuscodes  
Bei jeder HTTP-Anfrage antwortet der Server mit einem HTTP-Statuscode. Dieser gibt Auskunft, ob die Anfrage erfolgreich bearbeitet wurde oder ob es zu Umleitungen oder Störungen kam.  

Statuscode | Bedeutung
---------- | ---------
1xx | Informationen, dient zur Antwort, falls die Bearbeitung länger andauert
2xx | Erfolgreiche Operation
3xx | Es kam zu einer Umleitung, bzw. sind noch weitere Schritte des Clients notwendig
4xx | Client-Fehler
5xx | Server-Fehler
  




Weitere Informationen zu HTTP: ![Wikipedia/HTTP](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)  
