# Laborprotokoll  
Name: Sebastian Strutz  
Gruppe: 4  
Klasse: 5AHME  
Datum: Mo, 22. Oktober 2018  
Ort: Automatisierungslabor, Htbla Kaindorf  

Anwesend: Strauß, Strutz, Tuttner, Uhl, Wieser, Zitz  
Abwesend: Waltl  

# Thema: Typescript Server mit Visual Studio Code  
Zuerst haben wir durchbesprochen welche Datein wir in der letzten Einheit von dem [Mechatronik Server](https://www.htl-mechatronik.at/gitweb/m14/?p=sx-la1.git;a=tree;f=5AHME/g3/rest-server1/src;h=7db76bd7654e762a352c2182386aa541feca6f97;hb=a4385316c2cee94cc5348ec8be6a3fb0022d5d41) gedownloadet haben:  
* src               -> In dem Ordner stehen die typescript-Datein    
* .vscode/          -> Is diesem Ordner befinden sich 4 Konfiguration-Datein:  
  Der Vorteil an Json Dateien ist das sie Textuell sind, und somit einfach zu lesen sind.  
    * keybindings.json: In dieser Datei befinden sich verschiedene Tastenkombinationen, für die Entwicklungsumgebung.  
    * launch.json: Hier wird fest gelegt wie ein Programm gestartet wird.  
    * settings.json: In der Settings Datei befinden sich Projektspezifische Einstellungen.   
    * tasks.json: In der Tasks.json Datei stehen bestimmte Aufgaben für Programme (clean, build ..)  
    
* package.json      -> Hier befinden sich Projektinfos + Abhängigkeiten:  
    * dependencies: Abhängigkeiten  
    * devDependencies: werden mit ``` npm install ``` installiert und werden in den node_modules ordner gespeichert.
    
* package-lock.json -> In dieser Datei befinden sich die verschiedene Versionen.  

* gulpfile.json     -> Gulp ist das Übersetzungstool für Typescript. In der Guplfile steht die Stuerung der Übersetzung. Andere Übersetzungstools: make (C), ant (Netbeans), gradle (Android studio)  

* tsconfig.json     -> In dieser Jason Datei befindet sich die Konfiguration für den Transpiler. Der Transpiler wandelt das Programm von Typescript in Javascript um.  

* tslint.json       -> Der tslint ist für die Überprüfung für das Design verantwortlich, in der Datei befindet sich die Designkonfiguration.  
