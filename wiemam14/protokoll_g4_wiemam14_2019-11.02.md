# *4. Laborprotokoll*

  Name: Markus Wieser   
  Klasse: 5AHME   
  Datum: 11.02.2019 
  Anwesend: Strauß Lukas, Strutz Sebastian, Tuttner Raphael, Uhl Christian, Waltl Kilian, Wieser Markus, Zitz Karlheinz    
  Abwesend: -

## REST - Server

  Ein Representational State Transfer - Server (kurz REST-Server) wird für verschiedenste Maschine zu Maschine Kommunikationen verwendet. Als Beispiel hierfür nannten wir eine Verbindung zwischen einem Smartphone und einem PC. Weiters werden Rest-Server meist für Zustandsabfragen verwendet. Die zwei wichtigsten Technologien für REST-Server sind HTTP und TCP/IP Protokolle.

 ## HTTP (Hypertext Transfer Protocol)
  
  Das HTTP ist ein zustandsloses Protokoll zur Übertragung von Daten. Es ist textuell aufgebaut und basiert auf einem Server-Client Prinzip (Request/Response). Für eine verschlüsselte Übertragung gibt es das HTTPS Protokoll.
  
  ![HTTP(s) Datenaustausch](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/requestResponse.png)
  
  ### Schlüsselwörter für den Request
  
* **GET**     -> Inhalte vom Server ansehen
* **POST**    -> Inhalte ändern
* **DELETE**  -> Inhalte löschen
* **PUT**     -> Neue Inhalte anlegen

 ### TCP/IP
  
  Das Transmission Control Protocol/Internet Protocol ist eine Familie von Netzwerkprotokollen. Die Identifizierung der Rechner geschieht über die IP-Adresse. Für TCP/IP gibt es verschiedene Hilfs- und Anwendungsprotokolle, wie zum Beispiel DHCP.

## Server/Client Programmiersprachen

  Auf der Serverseite gibt es viele verschiedene Programmiersprachen wie zum Beispiel PHP, Pearl, Java, Javascript. Auf der Clientseite hingegen wird hauptsächlich Javascript verwendet. Da man sich um einiges leichter tut, wenn man auf beiden Seiten die gleiche Programmiersprache verwendet, programmieren wir unseren Server mit Typescript. Ein gültiger Javascript Code ist nämlich auch immer ein gültiger Typescript Code.
