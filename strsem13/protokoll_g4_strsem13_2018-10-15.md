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

