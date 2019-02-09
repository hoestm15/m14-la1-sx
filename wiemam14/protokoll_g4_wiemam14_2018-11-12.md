# *3. Laborprotokoll*

  Name: Markus Wieser   
  Klasse: 5AHME   
  Datum: 12.11.2018   
  Anwesend: Strauß Lukas, Tuttner Raphael, Waltl Kilian, Wieser Markus, Zitz Karlheinz    
  Abwesend: Strutz Sebastian, Uhl Christian

  ## Singleton (Entwurfsmuster)
  
Ein Singleton ist in der Softwareentwicklung ein Entwurfsmuster. Dieses Entwurfsmuster stellt sicher, dass es von einer Klasse auch nur ein Objekt gibt. Es bietet normalwereise globalen Zugriff auf das Objekt. Da in unserem Beispiel mit einer Datenbank gearbeitet wird, wird auch diesses Entwurfsmuster verwendet. Eine Datenbank existiert nämlich nur einmal und es werden auch nur die Werte dieser verändert. 

  ## Datenbank
  
  Eine Datenbank ist ein elektronisches Verwaltungssystem. Sie soll Daten halten, sammeln und verwalten können. Datatenbanken sollen mit großen Datenmenge vorallem effizient, dauerhaft und ohne wiedersprüche umgehen können. Es gibt schematische (klare Struktur) und nicht schematische (nicht klar definiert) Datenbanken. Eine sehr weit verbreitete Programmiersprache für Datenbanken ist SQL.

  ## Rest-Server
  
  In dieser Einheit erstellten wir die Klasse student und database. Die Klasse student agiert hierbei als Datenhaltungsklasse und database als Datenbank. Außerdem wurde die Klasse server erweitert.

  ## Klasse database.ts
  
  Unsere Datenbank wurde als Singleton realisiert. Hierfür setzten wir unsere Konstruktor private und riefen getInstance() zu Beginn auf, wodurch wir ein Objekt erzeugten. 
