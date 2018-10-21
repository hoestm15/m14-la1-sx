# *1. Laborprotokoll*

  Name: Markus Wieser   
  Klasse: 5AHME   
  Datum: 15.10.2018   
  Anwesend: Strauß Lukas, Strutz Sebastian, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz    
  Abwesend: -
  
  ## Grundsätzlicher Aufbau von HTTP
  
  Ganz grundsätzlich werden Daten zwischen einem System (z.B. SPS) und einem PC über einen Feldbus übertragen. Feldbusse sind zum Beispiel Modbus, Profibus oder Powerlink.
  
  ![Feldbus](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/netzwerkFeldbus.png)
  
  Heute wird aber der Client mit dem Server direkt über das Netzwerk verbunden. Dies bringt jedoch ein Sicherheitsrisiko mit sich.
  
  ![Netzwerk Direkt](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/netzwerkDirekt.png)
  
  
  ## HTTP (Hypertext Transfer Protocol)
  
  Das HTTP ist ein zustandsloses Protokoll zur Übertragung von Daten. Es ist textuell aufgebaut und basiert auf einem Server-Client Prinzip (Request/Response). Für eine verschlüsselte Übertragung gibt es das HTTPS Protokoll.
  
  ![HTTP(s) Datenaustausch](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/requestResponse.png)
  
  ### Schlüsselwörter für den Request
  
* **GET**     -> Inhalte vom Server ansehen
* **POST**    -> Inhalte ändern
* **DELETE**  -> Inhalte löschen
* **PUT**     -> Neue Inhalte anlegen

 ### Aufbau eines Pakets
  
  Hier sieht man, dass ein HTTP Paket immer in Header und Body aufgeteilt sind. Im Header sind Informationen über das Protokoll (die verwendete Version), über den Client und über den Server. Im Body sind die Daten enthalten.
  
  ![Paketaufbau](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/paketaufbau.jpg)
  
  ## REST-Server
  
  Der Begriff Rest-Server steht für Representational State Transfer. Ein Rest-Server wird häufig zur Abfrage von Zuständen verwendet. Diese Abfragen erfolgen meist über HTTP und sind zudem zustandslos. Ein REST-Server hat 6 bestimmte Eigenschaften:
  
  * Zustandslos:  Jede REST-Nachricht enthält alle Informationen, die für den Server bzw. Client notwendig sind, um die Nachricht zu verstehen. Weder der Server noch die Anwendung soll Zustandsinformationen zwischen zwei Nachrichten speichern. 
  * Client/Server Prinzip:  Grundsätzlich gilt die Client-Server-Architektur
  * Caching:  Hiermit werden bestimmte Ressourcen gespeichert und unnötige Datenübertragungen vermieden.
  * Einheitliche Schnittstelle: Dies ist ein Hautpunterscheidungsmerkmal. Sie besteht aus vier Eigenschaften:
  
  -> Adressierbarkeit von Ressourcen
  
  -> Repräsentationen zur Veränderung von Ressourcen
  
  -> Selbstbeschreibende Nachrichten
  
  -> Hypermedia as the Engine of Application State
  
  * Mehrschichtige Systeme: Durch diese System wird die Architektur vereinfacht.
  * Code on Demand: Diese Forderung von Fielding ist optional. Unter Code on Demand ist zu verstehen, dass erst im Bedarfsfall an den Client Code zur lokalen Ausführung übertragen werden kann.
  
  
  
