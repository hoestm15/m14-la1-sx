# Protokoll: REST-Server
Name: Strauß Lukas   
Klasse: 5AHME    
Gruppe: 4    
Anwesend: Strauß,Strutz,Tuttner,Uhl,Wieser,Zitz  
Abwesend: Waltl

# Visual Studio Code
## Informationen zu Code
Unter Visual Studio Code versteht man eine Programmierumgebung die plattformübegreifend verfügbar ist und von der
Firma Microsoft entwickelt wurde. Es hat eine Open-Source Lizenz und hat Funktionen wie zb. Syntaxvorhebung,Debugging,Autovervollständigung und Versionsverwaltung. Unterstützte Sprchen sind zb. C++,CSS,HTML,
Java,PHP,SQL, Typescript usw .
Durch verschiedene Plug-ins kann man die Programmierumgebung beliebig erweitern. Visual Studio Code hat allerdings trotz
der Namensähnlichkeit zu Visual Studio nicht viel damit zu tun. Zwar ist beides von der Firma Microsoft , es wurde aber
von verscheidenen Teams entwickelt. Einer der größten, wenn nicht soagr der größte Unterschied ist, dass VS Code nicht mit 
den Projektdateien , sondern mit Quelltextdateien und Ordnern arbeitet. 


## Arbeiten mit VS Code
Wenn man Code über das Desktop-Icon startet muss man im File Explorer erst das gewählte Projektverzeichnis ausgewählt werden um damit arbeiten zu können. Eine andere Möglichkeit ist es Code über den Terminal zu starten, dort kann man direkt den gewünschten Pfad dazuschreiben, so das Code diesen gleich als Projektverzeichnis nimmt.
Um in Code die Menüleiste anzeigen zu können (falls sie ausgeblendet ist) muss man auf der ALT-Taste oben bleiben, dann erscheint die Menüleiste.
Um die Hauptfunktionen aufrufen zu können befindet sich links eine Leiste mit mehreren Icons, über den Debugger Icon kann man auch auf den Terminal zugreifen ohne die Programmierumgebung verlassen zu müssen.

## Theorieteil der Stunde
Wir haben am Anfang der Stunde die von der letzen Einheit gedownloadeten Dateien und Ordner besprochen.

:point_right: **src**: In diesem Ordner findet man die typescript-Dateien

:point_right: **package.json**: Projektinfos und Abhängigkeiten sind hier zu finden  
                                *Abhängigkeiten --> depencies  
                                * devDepencies werden mit dem Befehl "npm install" installiert.  

:point_right: **package-lock.json**: Hier befinden sich die unterschiedlichen Versionen

:point_right: **gulpfile.json**: Gulp ist das Übersetzungstool für Typescript. In der Gulpfile steht die Steuerung von    
                                 der Übersetzung. Andere Übersetzungstools --> make(C), ant(Netbeans), gradle(Android Studio)

:point_right: **tslint.json**: tslint ist für die überprüfung des Designs veantwortlich. In der Datei befindet sichg die Design      
                               Konfiguration.
                           
:point_right: **tsconfig.json**:Hier befindet sich die Konfiguration für den Transpiler. Umwandlung von Typescript in    
                                Jacascript wird mit dem Transpiler vorgenommen. 

:point_right: **.vscode**: Hier befinden sie die 4 Konfigurations-Dateien ! Alles ist textuell und somit leicht zu lesen.  
                         * **keybindings.json** --> verschiedene Tastenkombinationen für die Entwicklungsumgebung  
                         * **launch.json** --> Hier wird festgelegt wie ein Programm gestartet wird.  
                         * **settings.json** --> In der settings Datei befinden sich projektspezifische Eigenschaften.  
                         * **tasks.json** -->  Hier findet man bestimmte Aufgaben für die Programme(zb. build,clean)  
                         
 ## Aufbau Visual Studio Code                       

 Links findet man eine Leiste mit 5 Icons. Der Reihe nach --> File-Explorer, Suchleiste, Versionsverwaltung(zb. Git),Debugger, 
 Verwaltung von Erweiterungen. Der File Explorer bwirkt folgendes--> Datei Dauerhaft öffen --> Doppelklick
 Wird nur einmal geklickt, und dann eine neue Datei mit einem Klick geöffnet, wir die vorherige automatisch geschlossen.
  
 ![https://github.com/HTLMechatronics/m14-la1-sx/blob/strlum14/strlum14/VS%20Code.png]
 
 
    
    




