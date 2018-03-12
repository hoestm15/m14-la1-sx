# 4. Protokoll  
## Thema: Makefiles  
**Name:** Sackl Martin   
**Klasse** 4ahme    
**Gruppe:** 3

Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schuster   
Abwesend: Schmuck  

### Wiederholung: Wie wird ein C-Programm übersetzt?  
Um ein C-Programm übersetzen zu können, müssen folgende Schritte durchgeführt werden:  

Schritte | Funktion  
------- | --------  
**Präprozessieren** | main.c wird hier vorbereitet  
**Compelieren** | Assemblercode wird erzeugt, aus main.c wird main.a    
**Assemblieren** | Assemblercode wird in Maschinensprache übersetzt, aus main.a wird main.o  
**Linken** | Programmteile werden miteinander verbunden, ausführbares Programm mit der Endung main.exe oder main.out (Windows oder Ubuntu)  
**Umwandelen** | Ausführbares Programm wird in ein Format umgewandelt, dass der Programmer versteht (Hex, ...)    

Je gröber der Sprachgebrauch ist, desto eher werden alle Schritte zu einem Schritt, **Compelieren**, zusammengefasst.  
