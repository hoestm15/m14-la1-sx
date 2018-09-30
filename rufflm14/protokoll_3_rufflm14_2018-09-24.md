# 1.Laborprotokoll 

*von Florian Ruffenacht*

Datum: 24.09.2018 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

Abwesend: -

## HTTP-Kommunikation

### Ansatz von HTTP
In der klassischen Variante den Datenaustausch zwischen einem PC und einem anderen Gerät über größere Distanzen zu realisieren, erfolgt dieser über ein Netzwerk und einen Feldbus:

![Klassischer Datenaustausch]()

Heutzutage wird aber immer mehr ein anderer Ansatz verfolgt. Der PC (= HTTP(s)-Client) und der sogenannte HTTP(s)-Server sind nur über das Netzwerk verbunden.Weil dieses Prinzip dazu verwendet wird, Webseiten aus dem World Wide Web (WWW) in einen Webbrowser zu laden, ist es ein wichitger Bestandteil des modernen Lebens. Die Netzwerkverbindung muss aber nicht zwingend das Internet sein, da dies oft Sicherheitsrisiken mit sich bringt. 

![HTTP(s) Datenaustausch]()

### HTTP-Protokoll
Das Hypertext Transfer Protokoll ist textuell aufgebaut und basiert auf dem Server-Client Prinzip. Der Client sendet eine Anfrage (=Request), auf die der Server antwortet (=Response).

![Server-Client Prinzip]()

Für den Request stehen folgende Schlüsselwörter zur Verfügung:

* **GET**     -> Inhalte vom Server fordern
* **POST**    -> Übermitteln von Inhalten
* **PUT**     -> Erstellen von neuen Inhalten auf dem Server
* **DELETE**  -> Löschen von Inahlten

Mit dem Kommando **nc <URL> <PORT>**kan




