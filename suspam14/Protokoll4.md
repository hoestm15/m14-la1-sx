# Protokoll 4: Makefiles
Name: Patrick Schuster  
Klasse: 4AHME  
Gruppe: 3    
Anwesend: Reinbacher, Ruffenacht, Sackl, Sackl, Sammer, Schmuck, Schuster  
Abwesend: Schmuck Martin

# Wiederholung: C Übersetzungsvorgang
Um eine Hochsprache (wie z.B. C, C++ oder Java) ausführen zu können muss diese zuerst in Maschinencode übersetzt. Diesen Vorgang nennt man Umgangssprachlich kompilieren. Wenn man es genau nimmt ist das kompilieren nur ein Zwischenschritt.
## nötige Schritte für den Übersetzungsvorgang  
Schritt | Dateiendung | Beschreibung  
--- | --- | ---  
Präprozessieren | .i | Präprozessoranweisungen (#include, #define, #ifdef,...) werden verarbeitet  
Kompilieren | .s | C Anweisungen werden in Assembler übersetzt  
Assemblieren | .o | Assembler Befehle werden in ein binäres Maschinenbefehlsmuster übersetzt   
Linken | .out | Es werden alle Maschinenbefehle und Bibliotheken aus verschiedenen Objektdateien zusammengeführt und Speicheradressen vergeben   

Um das übersetzte Programm für einen Mikrocontroller zu verwenden muss das Programm noch in ein Format übersetzt werden das der Programmer verwenden kann. In unserem Fall eine Hex-Datei (.hex).  

![Übersetzungsvorgang ](https://github.com/suspam14/la1/blob/master/C_Uebersetzungsvorgang.svg)
Quelle: Mikrocontroller Skript von Professor Steiner  

# Makefiles
Das Tool make benötigt die Datei Makefile. Diese Makefile steuert den Übersetzungsvorgang.   
Die Makefile Datei ist eine gewöhnliche Textdatei.  

Datei Makefile  
Ziel A: Abhängigkeit 1, Abhängigkeit 2,...  
[Tab] Kommando   
[Tab] Kommando  
...

Ziel B: Abhängigkeit 1, ...   
[Tab]   Kommando  
...  

Bsp.:  
test1:main.o  
[Tab] gcc -o test1 main.o  
main.o:main.c  
[Tab] gcc -c main.c  


