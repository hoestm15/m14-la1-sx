# _Protokoll Vierte Einheit_  

**Name: Daniel Sammer**  
**Gruppe: 3**  
**Datum: 06.03.2018**  
**Uhrzeit: 9:40-12:25**  
**Anwesend: Reinbacher B., Ruffenacht F., Sackl M., Sackl R., Sammer D., Schuster P.  
**Abwesend: Schmuck Martin**  
  
-----------------------------------------------------------  
#### Wiederholung: Übersetzungsvorgang eines Programms  
![Protokoll Einheit 2](https://github.com/HTLMechatronics/m14-la1-sx/blob/samdam14/samdam14/einheit4.jpg)  
Die meisten verwenden den Begriff _Kompilieren_ zusammenfassend für die Teilbereiche _Präprozessieren, Kompilieren_ und _Assemblieren_. Beim Kompilieren soll der Quellcode einer bestimmten Programmiersprache in eine für die Maschinen verständliche Sprache (Maschinensprache) übersetzt werden.   
Die Aufgabe vom Präprozessor ist es, Eingabedaten für folgende Programme vorzubereiten und diese weiterzugeben. Der daraus entstandene Code wird als Zwischencode bezeichnet.  
Der Assembler soll Code von Assemblersprache in Maschinensprache übersetzen (z.B. CLI -> 11111010).  
Der Linker hat die Aufgabe, verschiedene Programmmodule zu einem ausführbaren Programm (_executeable program_) verbinden.  

[Wikipedia/Compiler](https://de.wikipedia.org/wiki/Compiler)  
[Wikipedia/Präprozessor](https://de.wikipedia.org/wiki/Pr%C3%A4prozessor)  
[Wikipedia/Assembler](https://de.wikipedia.org/wiki/Assembler_(Informatik))  
[Wikipedia/Linker](https://de.wikipedia.org/wiki/Linker_(Computerprogramm))  

------------------------------------------------------------  
#### make  
_make_ ist ein Programm/Tool zum Übersetzen von Steuervorgängen. Es benötigt immer ein _Makefile_.  
>make (englisch für machen, erstellen) ist ein Build-Management-Tool, das Kommandos in Abhängigkeit von Bedingungen ausführt. Es wird hauptsächlich bei der Softwareentwicklung als Programmierwerkzeug eingesetzt.
>Genutzt wird es beispielsweise, um in Projekten, die aus vielen verschiedenen Dateien mit Quellcode bestehen, automatisiert alle Arbeitsschritte (Übersetzung, Linken, Dateien kopieren etc.) zu steuern, bis hin zum fertigen, ausführbaren Programm. 
>make ist jedoch so flexibel ausgelegt, dass es auch beliebige andere Aufgaben steuern kann, bei denen die zeitliche Abhängigkeit von Dateien eine Rolle spielt.  
Quelle: [Wikipedia/make](https://de.wikipedia.org/wiki/Make)  
-----------------------------------------------------------  
##### Makefile  
Ein Makefile ist dazu da, dem Programm make mitzuteilen, was es tun soll (_target_) und wie es es tun soll (_command_). Des weiteren kann man zu jedem _target_ angeben, von welchen anderen targets oder Dateien dieses abhängt.  
mehr dazu: [Makefile](http://www.ijon.de/comp/tutorials/makefile.html)  
  
###### Syntax  
```
<target 1>: dependencies  
<tab>command 1  
<tab>command 2  
<tab>command 3  
<tab>command n  

<target 2>: dependencies  
<tab>command 1  
<tab>command 2  
<tab>command 3  
<tab>command n  
```

Englisch | Deutsch
-------- | --------
_target_ | Ziel
_dependencies_ | Abhängigkeiten
_command_ | Anweisung, Regel  

--------------------------------------------------------  
##### Aufrufen von _make_  
Im Terminal kann man mittels dem Kommando _make_ die Abarbeitung des _Makefile_´s starten. Das _make_-Tool erkennt selbstständig, ob _targets_ überhaupt wieder erreicht werden müssen oder ob sie sich bereits im aktuellsten Zustand befinden. Zuerst wird geschaut, ob die Abhängigkeit (_dependency_) als Ziel (_target_) weiter unten im _Makefile_ befindet. Ist das nicht der Fall, dann wird der Zeitstempel des _targets_ mit dem des vorhandenen, gleichnamigen verglichen. 





