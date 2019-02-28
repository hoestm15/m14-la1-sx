# *5. Laborprotokoll*

  Name: Markus Wieser   
  Klasse: 5AHME   
  Datum: 11.02.2019   
  Anwesend: Strauß Lukas, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz    
  Abwesend: Strutz Sebastian


  ## Wiederholung
  
  ## REST-Server
  
  Ein Representational State Transfer - Server (kurz REST-Server) wird für verschiedenste Maschine zu Maschine Kommunikationen verwendet. Als Beispiel hierfür nannten wir eine Verbindung zwischen einem Smartphone und einem PC. Weiters werden Rest-Server meist für Zustandsabfragen verwendet.
  
  ## HTTP (Hypertext Transfer Protocol)
  
  Das HTTP ist ein zustandsloses Protokoll zur Übertragung von Daten. Es ist textuell aufgebaut und basiert auf einem Server-Client Prinzip (Request/Response). Für eine verschlüsselte Übertragung gibt es das HTTPS Protokoll.
  
  ![HTTP(s) Datenaustausch](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/requestResponse.png)
  
  Für den Verbindungsaufbau wird ein TCP/IP Protokoll verwendet. Es sind zwei Datenröhren vorhanden, welche für den Request und die Response zuständig sind.
  
  ### Schlüsselwörter für den Request
  
* **GET**     -> Inhalte vom Server ansehen
* **POST**    -> Inhalte ändern
* **DELETE**  -> Inhalte löschen
* **PUT**     -> Neue Inhalte anlegen

### Aufbau eines Pakets
  
  Hier sieht man, dass ein HTTP Paket immer in Header und Body aufgeteilt sind. Im Header sind Informationen über das Protokoll (die verwendete Version), über den Client und über den Server. Im Body sind die Daten enthalten.
  
  ![Paketaufbau](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/paketaufbau.jpg)

  
