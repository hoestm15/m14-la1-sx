# 1.Protokoll  
  
  **Name**:  *Bernhard Reinbacher*  
  **Datum:** *24.09.2018*  
  **Uhrzeit:** *8:00 - 10:30*  
  **Gruppe:** *3*  
  
   
    
 **Abwesend:** niemand  
 **Anwesend:** Bernhard Reinbacher, Ruffenacht Florian, Sackl Martin, Sackl Roland, Sammer Daniel, Schmuck Martin, Schuster Patrick  
  
*********************************************************************************************************************************  
## Rest Server  
Dieser Server ist dazu da, um HTTP-Statusabfragen durchführen lässt. Weiter Infos: [Representational State Transfer](https://de.wikipedia.org/wiki/Representational_State_Transfer)
*********************************************************************************************************************************  
## Systemsteuerung aus der Ferne  
Um Systeme aus der Ferne zu steuern, gibt es einige Möglichkeiten.  
### über Feldbus/Gateway/Netzwerk  
![Netzwerk1](/reibem14/Netzwerk1.PNG)    
* * hier müssen eigene Bibliotheken instaliert werden und zusätzlich ist die Programmierung komplizierter  

### über Netzwerk mit HTTP-Technik   
![Netzwerk2](/reibem14/Netzwerk2.PNG)   
* *  einfach, da nur mit HTTP gearbeitet wird und diese Bibliotheken bereitsvorhanden sind  
     die Sicherheit leidet etwas darunter    
     *********************************************************************************************************************************   
## HTTP  
... ist ein Übertragungsprotokoll, das textbasiert funktioniert.  
### Aufbau  
Im **Header** befinden sich Informationen über den Server, dem Body und der Codierung. Es werden Informationen ausgetauscht über:   
* die Verbindungsqualität  
* ob der Server HTTP spricht  
* die Länge der folgenden Nachricht  
* die Codierung des Body  
* Body Beginn und Ende    
  
Im **Body** sind die restlichen Daten vorhanden.  
  
### Funktionsweise  
Der Client schickt eine Anfrage(SYN Paket) an den Server, der währenddessen auf Anfragen wartet. Wenn die Anfrage korrekt war, antwortet der Server mit einem ACK-Paket, welches wiederum auch der Client zurückschickt. Danach sind zwei Datenröhren für den Datentranfer bereitgestellt.  

* Anfrage | Bedeutung  
  ------- | ---------  
  GET | Cliet fordert Ressource von Server an  
  

    

