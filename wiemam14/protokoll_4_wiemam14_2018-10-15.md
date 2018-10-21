# *1. Labororotokoll*

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
  
  
  
