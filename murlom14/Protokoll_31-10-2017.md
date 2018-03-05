# Protokoll 31.10.2017
## 1. Einheit

Name: Muri Lorenz <br>
Klasse: 4AHME <br>
Gruppe: 2 <br>
Datum der Einheit: 31.10.2017 <br>
Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Moritz Martinak, Mario Nabernik, Muri Lorenz, Platzer Andreas, Marcel Köhler <br>
Abwesend: - <br>

## Thema: Versionsverwaltung

### Versionsverwaltungen
Versionsverwaltungsprogramme werden verwendet um Änderungen an Dateien "rückverfolgen" zu können, zeitlicher Verlauf wird abgespeichert.
Es wird vor allem in Arbeitsgruppen zum austausch von Dateien verwendet. 
<br>
**Versionsverwaltungsprogramme:**  
* Git
* SVN (Subversion)
* Mercury
* ... <br>

### Git
**Linus Torvalds** entwickelte 2005 die **OpenSource-Software** Git, diese Software dient zur **Versionsverwaltung** von Dateien. <br>
**Unterscheide zu herkömmlichen Versionsverwaltungen:** 
* Versionsverwaltung kann auch offline genutzt werden
* Repositories werden auf dem Rechner gespeichert
* Lokale Repositories werden (sobald Verbindung besteht) mit einem zentralem Repository abgeglichen <br>
                                                        
### GitHub
GitHub ist ein **Onlien-Dienst** basierend auf dem Versionsverwaltungssystem **Git**.
**Eigenschaften:** 
* dieser *Dienst* ist für jeden zugänglich 
* alle Daten sind öffentlich
* Öffentliche Repositories sind kostenlos
* Private Repositories sind kostenpflichtig

### Aufbau von Git/GitHub
Git/GitHub ist in mehreren Ebenen Aufgeteilt, zwischen diesen Ebenen wird mittels Befehlen kommuniziert.
![Git-Commands](/git_data_transport_commands.png)
Quelle: [Git-Protokoll SX](https://www.htl-mechatronik.at/e-books/sx/html/git/git.html#(1))

### Git-Repository mit SSH-Key
Bei einer Übeung haben wir, um das Arbeiten mit GitHub zu erleichtern, einen SSH-*Verbigung* angelegt. Dies geschah wie folgt: <br>
1. SSH-Schlüsselpaar am PC anlegen mit `ssh-keygen`
1. nun wird der Public-Key auf github.com unter *Settings* *SSH and GPG keys* eingefügt. [Hilfe](https://help.github.com/articles/connecting-to-github-with-ssh/) <br> <br>
Nun muss man sich nicht mehr bei jedem Zugriff auf das Repository mit seinem Benutzname und Passwort anmelden, dies erledigt der SSH-Key.

### Markdown
Markdown ist ein Textdateisystem welches oft im Internet gebrauch findet (HTML-Webpages), es dient zu einfachen Formatieurung von Texten. <br>
**Syntax:** 
* **Fett:**  `**(text)**`
* *Kursiv:*  `*(text)*`
* Überschriften: `# 1. Überschrift, ## 2. Überschrift, ...`
* Bilder: `![Bildbezeichnung](Dateipfad)`
* Reihung mit Ordnung: `1. Erstens, 1. Zweitens, 1. Drittens, ...`
* Reihung ohne Ordnung: `* Ersents, * Zweitens, * Drittens, ...`
* Links: `[Name](Addresse)`
* ...
