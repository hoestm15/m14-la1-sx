# Laborprotokoll  
Name: Sebastian Strutz  
Gruppe: 4  
Klasse: 5AHME  
Datum: Mo, 15. Oktober 2018  
Ort: Automatisierungslabor, Htbla Kaindorf  
  
Anwesend: Strauß, Strutz, Tuttner, Uhl, Waltl, Wieser, Zitz  
Abwesend: -  
## Thema: REST-Server  
Der Name **REST**-Server steht für **RE**presentational **S**tate **T**ransfer Server und wird meist für die Maschine-zu-Maschine-Kommunikation in Websevices verwendet. Das HTTP Protokoll wird als Sprache zwischen Server und Client verwendet. Rest Server werden häufig zur Abfrage von Zuständen, z.B. an einem entferntem System eingesetzt.
Der Architekturstil eines REST - Servers weist 6 Eigenschaften auf:  
1. **Zustandslosigkeit:** Die REST-nachricht enthält alle Informationen, dei für den Server/Client notwendig sind, um die Nachricht zu verstehen. Weder Server noch Client speichert Zustandsinformationen.  
2. **Client/Server Prinzip:** Client-Server-Architektur  
3. Catching: Ist eine Technik um Ressourcen anhand bestimmter Kriterien in einem Chache zwischenzuspeichern, um unötige Datenübetragungen oder Serveranfragen zu vermeiden.
4. **Einheitliche Schnittstellen:** Hauptunterscheidungsmerkmal von anderen Architekturstilen.   
Besteht aus weitern 3 Eigenschaften:  
              * Adressierbarkeit von Ressourcen: Jeder REST-konforme Dienst hat eine eindeutige Adresse.  
              * Repräsentaition zur Veränderung von Ressourcen: Ein REST-Server kann in verschiedenen Sprachen oder Formaten(HTML, JSON oder XML)   einer Ressource ausliefern.  
              * Selbstbeschreibende Nachrichten: REST-Nachrichten sind selbstbeschreiben.  
5. Mehrschichtige Systeme: Durch Mehrschichtige Systeme, wird die Architektur vereinfacht.  
6. Code on Demand: Unter Code on Demand ist zu verstehen, dass erst im Bedarfsfall an den Client, Code zur lokalen Ausführung übertragen werden kann.  

## Kommunikation in der Automatisierungstechnik  
Der klassische Ansatz Daten voon einem System(z.B. SPS) über eine kürzer Distanz zu einem PC zu übetragen, war über einen Feldbus. Dieser Ansatz bringt einige Probleme mitsich, z.B. zusätzliche Hardware. 
  
![Feldbus](https://github.com/HTLMechatronics/m14-la1-sx/blob/strsem13/strsem13/Feldbus.png)
  
Stattdessen wird heutzutage direkt über das Netzwerk gearbeitet. Das geschieht über HTTP-Server und HTTP-Clients. Das Problem an dieser Variante ist das Sicherheitsriskio.  
  
![Netzwerk über HTTP](https://github.com/HTLMechatronics/m14-la1-sx/blob/strsem13/strsem13/Netzwerk%20%C3%BCber%20HTTP.png)  

## TCP/IP

Transmission Control Protocol/ Internet Protocol ist eine Familie von Netzwerkprotokollen, die im OSI Schichten Modell auf Layer 4 (Transport Layer) arbeitet. Die Identifizierung erfolgt über IP-Adressen. Die Aufgabe des TCP/IP Protokolles ist die Datenübertragung innerhalb eines dezentralen Netzwerks. 

#### Verbindungsaufbau
Der Client sendet dem Server ein SYN-Paket, der Server empfägt das Paket. Falls der Port geschlossen ist, antwortet er mit einem TCP_RST Paket um zu signalisieren das keine Verbindung aufgebaut werden kann. Falls der Port geöffnet ist, sendet der Server ein SYN/ACK Paket zurück. Der Client sendet, nach Erhalt des SYN/ACK-Paketes, ein ACk-Packet an dem Server, um zu signalisieren, dass die Verbindung aufgebaut ist. Will einer der Teilnehmer die Verbindung trennen, so sendet er ein FIN-paket, der andere host antwortet dann mit einem FIN-ACk-Paket. 

![TCP/IP](https://github.com/HTLMechatronics/m14-la1-sx/blob/strsem13/strsem13/Verbindungsaufbau%20TCPIP.png)
  
## HTTP  
**HTTP** (**H**ypter**T**ext **T**ransfer **P**rotocol) ist ein Protokoll zur Übertragung von Daten auf der der Anwendungsschicht(OSI Schicht 7). Das Protkoll ist zustandslos, dass bedeutet das Informationen aus früheren Anforderungen verloren gehen, deshalb ist ein mitführen von Sitzungsdaten erforderlich. Um Daten verschlüsselt zu Übertragen gibt es das HTTPS Protokoll. Weiteres erfolgt die Übetragung textuell. 

### Verbindugsaufbau 
Die Kommunikation zwischen Slient und Server erfolgt durch Austausch von HTTP-Nachrichten. Dadurch das HTTP nicht auf Hyptertext beschrnkt ist, sondern auch zum Austausch von Daten verwendet wird, ist es auf ein weiteres Protokoll angewiesen. Für dieses Protokoll wird üblicherweise TCP eingesetzt.  
  
![HTTP](https://github.com/HTLMechatronics/m14-la1-sx/blob/strsem13/strsem13/Verbindungsaufbau%20HTTP.png)
  
### Keep-Alive Paket
Wenn eine Verbinndung zwischen Server und Client besteht werden nicht dauerhaft Pakete übertragen. Um zu verhindern, dass der Server die Verbindung aufgrund einer Überschreitung der Zeit abbricht kann der Client sogennante Keep-Alive-Pakete schicken um dem Server mitzuteilen, dass er immernoch "lebt" und die Verbindung aufrecht erhalten will. 
  
### Paketaufbau
HTTP Pakete werden in Header und Body (Kopf und Rumpf) eingeteilt. . Im Header verbergen sich Informationen über die verwendete HTTP-Version, die verwendete Codierung, die Größe des Bodys, etc., während im Body die eigentlichen Nutzdaten untergebracht werden. Die beiden werden durch eine Leerzeile getrennt.
  
### HTTP-Befehle  
Das HTTP-Protokoll sieht eine Vielzahl an verschiedenen Befehlen vor. Die wichtigsten vier sind:
* GET:     Daten vom Server abrufen    
* POST:    Daten zum Server schicken   
* PUT:     Daten auf den Server laden  
* DELETE:  Datem vom Server löschen    

### Statuscodes  
Wenn vom Client eine Anfrage kommt muss der Server diese interpretieren und bearbeiten. Sowohl bei der Interpretation, als auch bei der Bearbeitung können Fehler auftreten. Um dem Client mitzuteilen, was vorgefallen ist bzw. was gerade passiert sieht HTTP verschiedene Statuscodes vor. Dreitstellige Nummern sieht HTTP zur Statusmeldung vor:

* 1xx:	Die Abarbeitung der Anfrage dauert noch an.
* 2xx:	Erfolgreich
* 3xx:	Weitere Schritte des Clients notwendig
* 4xx:	Clientseitiger Fehler, z. B. 403 für unberechtigter Zugriff oder 404 für ein Dokument das nicht existiert
* 5xx	Serverseitiger Fehler
