# Labor KW50  
# 12.12.2017  

## Makefiles  
### Theorie  
Bei der C-Prpgrammierung verwendet man normalerweise für die Übersetzung des Pograms eine **IDE**(Integrated Development Environment) wie zum Beispiel Codeblocks oder Netbeans. Diese IDE's greifen aber auch aud das Tool **Make** zurück.  

Wird **make** in der Konsole aufgerufen, so wird eine Datei names **Makefile** ausgeführt.  
In der Datei ** Makefile** befinden sich die relevanten Informationen für eine Übersetzung. 

**Zum Beispiel:**  

* was ist das Ziel der Übersetzung?  
* aus welchen Dateien (Files) besteht das Projekt?  
* welche Abhängigkeiten zwischen den Dateien sind gegegeben?  
* welche Tools (Compiler, Linker, ...) werden wie und zu welchem Zeitpunkt aufgerufen?   
 
 ### Schitte einer C-Übersetzung  
 
 **1.Schritt Compilieren**  
 Für unseren µC wird der GNU-Compiler **avr-gcc** verwendet.
 
